FROM owasp/modsecurity-crs:nginx

# Copy the main nginx.conf file
COPY srcs/conf/nginx/nginx.conf /etc/nginx/nginx.conf

# Remove default configurations in conf.d
RUN rm -rf /etc/nginx/conf.d/*

# Copy custom ModSecurity rules
COPY srcs/conf/modsecurity/custom-rules/ /etc/modsecurity.d/custom-rules/

# Copy scripts if you use them
COPY srcs/scripts/ /scripts/

# Copy the certificates to the container
COPY srcs/secrets/certs /srcs/secrets/certs

# Copy crs-setup.conf like setup.conf
COPY srcs/conf/modsecurity/crs-setup.conf /etc/modsecurity.d/setup.conf
COPY srcs/conf/modsecurity/crs-setup.conf /etc/modsecurity.d/crs-setup.conf

# Copy modsecurity.conf to the container
COPY srcs/conf/modsecurity/modsecurity.conf /etc/modsecurity.d/modsecurity.conf

# Copy the mime.types file to the container
COPY srcs/conf/nginx/mime.types /etc/nginx/mime.types

# Adjust permissions only if necessary                                                          OJOOOO DEJAR COMENTADO PARA QUE NO SALGAN ERRORES????
RUN chmod -R 755 /etc/modsecurity.d/custom-rules /etc/nginx || true \
 && chmod -R 755 /scripts || true

# Create an empty file in conf.d to avoid warnings
RUN touch /etc/nginx/conf.d/default.conf
RUN echo "" > /etc/nginx/conf.d/default.conf

# Change to root user to have permissions to remove the certificate generation script
USER root

# Ensure modsec log dir/files exist and are writable by nginx user
RUN mkdir -p /var/log/modsecurity \
 && touch /var/log/modsecurity/modsec_debug.log /var/log/modsecurity/modsec_audit.log \
 && chown -R nginx:nginx /var/log/modsecurity \
 || true

# Secure permissions in the ModSecurity directory
RUN mkdir -p /etc/modsecurity.d && chmod -R 755 /etc/modsecurity.d

# Remove the script that causes errors
RUN rm -f /docker-entrypoint.d/10-generate-certificate.sh
RUN rm -f /docker-entrypoint.d/20-envsubst-on-templates.sh
RUN rm -f /docker-entrypoint.d/90-copy-modsecurity-config.sh
RUN rm -f /docker-entrypoint.d/92-update-real_ip.sh

# --- Add explicit healthcheck so Docker checks /healthz on HTTP 8080 ---
HEALTHCHECK --interval=10s --timeout=3s --start-period=10s --retries=3 \
  CMD curl -fsS http://127.0.0.1:8080/healthz || exit 1