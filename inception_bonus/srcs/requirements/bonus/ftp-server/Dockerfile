FROM debian:bullseye

RUN apt update && apt upgrade -y && \
    apt install -y vsftpd && \
    rm -rf /var/lib/apt/lists/*

# Create directories for FTP
RUN mkdir -p /var/ftp && \
    mkdir -p /var/empty

# Copy vsftpd configuration
COPY conf/vsftpd.conf /etc/vsftpd.conf

# Copy startup script
COPY tools/start.sh /usr/local/bin/start.sh
RUN chmod +x /usr/local/bin/start.sh

EXPOSE 21 21100-21110

CMD ["/usr/local/bin/start.sh"]
