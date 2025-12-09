FROM node:20-alpine as builder

WORKDIR /app

# Copy package files
COPY frontend/package*.json ./
RUN npm ci

# Copy source code
COPY frontend/ .

# Build production
RUN npm run build

# Stage 2: Serve with nginx
FROM nginx:alpine
COPY --from=builder /app/dist /usr/share/nginx/html

# Nginx configuration for SPA + proxy to backend
COPY srcs/conf/frontend/default.conf /etc/nginx/conf.d/default.conf

EXPOSE 80