FROM debian:bullseye

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y mariadb-server && \
    rm -rf /var/lib/apt/lists/*

COPY tools/mariadb.sh /mariadb.sh

RUN chmod +x /mariadb.sh

USER root

ENTRYPOINT ["/mariadb.sh"]

