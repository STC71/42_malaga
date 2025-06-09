#!/bin/sh

# Ver si el usuario mysql existe
if [ -d "/run/mysqld" ]; then
    echo "[i] mysqld already present, skipping creation"
    chown -R mysql:mysql /run/mysqld || true
else
    echo "[i] mysqld not found, creating..."
    mkdir -p /run/mysqld
    chown -R mysql:mysql /run/mysqld || true
    chmod 755 /run/mysqld
fi

# Comprobar si mysql se ha iniciado
if [ -d "/var/lib/mysql/${MARIADB_DATABASE}" ]; then
    echo "[i] MySQL directory already present, skipping creation"
else
    echo "[i] Initializing database..."
    chown -R mysql:mysql /var/lib/mysql

    # Creamos un fichero temporal para la configuración 
    tfile=$(mktemp)
    if [ ! -f "$tfile" ]; then
        echo "Failed to create temp file"
        exit 1
    fi

    # Configuramos la base de datos y los usuarios
    cat << EOF > $tfile
USE mysql;
FLUSH PRIVILEGES;
GRANT ALL ON *.* TO 'root'@'%' IDENTIFIED BY '${MARIADB_ROOT_PASSWORD}' WITH GRANT OPTION;
GRANT ALL ON *.* TO 'root'@'localhost' IDENTIFIED BY '${MARIADB_ROOT_PASSWORD}' WITH GRANT OPTION;
CREATE DATABASE IF NOT EXISTS ${MARIADB_DATABASE};
CREATE USER '${MARIADB_USER}'@'%' IDENTIFIED BY '${MARIADB_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MARIADB_DATABASE}.* TO '${MARIADB_USER}'@'%';
FLUSH PRIVILEGES;
EOF

    # Se inicia el servidor de MariaDB temporalmente para ejecutar las instrucciones
    echo "[i] Starting temporary MariaDB server..."
    /usr/sbin/mysqld --user=mysql --bootstrap < $tfile
    rm -f $tfile
fi

echo "[i] MariaDB setup complete. Starting MariaDB server..."
# Iniciar el servidor de MariaDB
exec /usr/sbin/mysqld --user=mysql --console --skip-networking=0 --bind-address=0.0.0.0
