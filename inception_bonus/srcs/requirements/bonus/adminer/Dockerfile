FROM debian:bullseye

RUN apt update && apt upgrade -y && \
    apt install -y \
        php7.4-fpm \
        php7.4-mysqli \
        php7.4-pdo-mysql \
        php7.4-json \
        php7.4-mbstring \
        curl && \
    rm -rf /var/lib/apt/lists/*

# Create directory for adminer
RUN mkdir -p /var/www/html

# Create PHP-FPM runtime directory
RUN mkdir -p /run/php

# Download Adminer
RUN curl -L https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php \
    -o /var/www/html/adminer.php

# Copy custom Adminer configuration
COPY conf/index.php /var/www/html/index.php

# Create php-fpm configuration
COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

# Set proper permissions
RUN chown -R www-data:www-data /var/www/html && \
    chmod -R 755 /var/www/html

EXPOSE 8080

CMD ["php", "-S", "0.0.0.0:8080", "-t", "/var/www/html"]
