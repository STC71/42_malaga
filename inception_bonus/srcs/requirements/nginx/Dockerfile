FROM debian:bullseye

RUN apt update -y && apt upgrade -y && \
    apt install -y nginx vim openssl && \
    mkdir -p /etc/nginx/ssl

RUN openssl req -x509 -nodes \
    -out /etc/nginx/ssl/inception.crt \
    -keyout /etc/nginx/ssl/inception.key \
    -subj "/C=ES/ST=Andalucia/L=Malaga/O=42/OU=42/CN=sternero.42.fr/UID=sternero"

RUN mkdir -p /var/run/nginx /var/www/html

COPY conf/nginx.conf /etc/nginx/nginx.conf

RUN chmod -R 755 /var/www/html && \
    chown -R www-data:www-data /var/www/html && \
    chown -R www-data:www-data /var/run/nginx && \
    chown -R www-data:www-data /var/log/nginx && \
    chmod 644 /etc/nginx/ssl/inception.crt && \
    chmod 640 /etc/nginx/ssl/inception.key && \
    chgrp www-data /etc/nginx/ssl/inception.key

CMD ["nginx", "-g", "daemon off;"]

