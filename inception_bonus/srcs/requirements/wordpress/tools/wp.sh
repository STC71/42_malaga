#!/bin/bash

# Check if MariaDB is accessible using mysqladmin

#echo if mysqladmin ping -h "${WORDPRESS_DB_HOST}" -u "${MARIADB_USER}" "--password=${MARIADB_PASSWORD}" --silent

mkdir -p /run/php

# to wait until MariaDB is available before proceeding
echo "Waiting for MariaDB to be available..."
for i in {1..60}; do
    if mysqladmin ping -h "${WORDPRESS_DB_HOST}" -u "${MARIADB_USER}" "--password=${MARIADB_PASSWORD}" --silent; then
        echo "MariaDB is up."
        break
    else
        echo "MariaDB not available, retrying in 10 seconds..."
        sleep 10
    fi
done

cd /var/www/html

if [ -f wp-config.php ]; then
	echo "wordpress already installed"
else
    # Download WP-CLI if not present
    if [ ! -f /usr/local/bin/wp ]; then
        echo "Downloading WP-CLI..."
        curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
        chmod +x wp-cli.phar
        mv wp-cli.phar /usr/local/bin/wp
    fi


# Download wordPress files 
if [ ! -f /usr/local/bin/wp ]; then
    echo "Downloading WP-CLI..."
    curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
    chmod +x wp-cli.phar
    mv wp-cli.phar /usr/local/bin/wp
fi

echo "Downloading WordPress core files..."
wp core download --allow-root

echo "Generating wp-config.php..."
wp config create \
    --dbname=${WORDPRESS_DB_NAME} \
    --dbuser=${WORDPRESS_DB_USER} \
    --dbpass=${WORDPRESS_DB_PASSWORD} \
    --dbhost=${WORDPRESS_DB_HOST} \
    --allow-root

echo "Installing WordPress..."
wp core install \
    --url=${WORDPRESS_URL} \
    --title="${TITLE}" \
    --admin_user=${WORDPRESS_ADMIN_USER} \
    --admin_password=${WORDPRESS_PASSWORD} \
    --admin_email=${WORDPRESS_ADMIN_EMAIL} \
    --allow-root

echo "Creating additional WordPress user..."
wp user create ${WORDPRESS_USER} ${WORDPRESS_USER_EMAIL} --role=author --user_pass=${WORDPRESS_PASSWORD} --allow-root

# Install and configure Redis cache plugin
echo "Installing Redis cache plugin..."
wp plugin install redis-cache --activate --allow-root

# Configure Redis in wp-config.php
echo "Configuring Redis cache..."
wp config set WP_REDIS_HOST redis --allow-root
wp config set WP_REDIS_PORT 6379 --allow-root
wp config set WP_REDIS_PASSWORD ${REDIS_PASSWORD} --allow-root
wp config set WP_CACHE true --type=constant --allow-root

# Enable Redis cache
wp redis enable --allow-root

chmod -R 775 wp-content

fi
# Start PHP-FPM
exec php-fpm7.4 -F
