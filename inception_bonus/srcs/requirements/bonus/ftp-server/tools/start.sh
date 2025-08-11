#!/bin/bash

# Create FTP user from environment variables
useradd -m -s /bin/bash ${FTP_USER} 2>/dev/null || true
echo "${FTP_USER}:${FTP_PASSWORD}" | chpasswd

# Create userlist file
echo "${FTP_USER}" > /etc/vsftpd.userlist

# Create FTP directory and set permissions
mkdir -p /home/${FTP_USER}/ftp
chown ${FTP_USER}:${FTP_USER} /home/${FTP_USER}/ftp

# Add FTP user to www-data group for write access to /var/www/html
usermod -aG www-data ${FTP_USER}

# Start vsftpd
exec vsftpd /etc/vsftpd.conf
