FROM debian:bullseye

RUN apt update && apt upgrade -y && \
    apt install -y redis-server && \
    rm -rf /var/lib/apt/lists/*

# Create redis configuration directory
RUN mkdir -p /etc/redis

# Copy redis configuration
COPY conf/redis.conf /etc/redis/redis.conf

# Create redis user and directories
RUN mkdir -p /var/lib/redis && \
    chown redis:redis /var/lib/redis && \
    chmod 755 /var/lib/redis

# Set proper permissions for configuration file
RUN chown redis:redis /etc/redis/redis.conf

USER redis

EXPOSE 6379

CMD ["redis-server", "/etc/redis/redis.conf"]
