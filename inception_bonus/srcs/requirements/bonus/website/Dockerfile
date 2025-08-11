FROM node:18-alpine

WORKDIR /app

# Copy package files
COPY src/package*.json ./

# Install dependencies
RUN npm install

# Copy source code
COPY src/ ./

# Build the application
RUN npm run build

# Install a simple HTTP server
RUN npm install -g serve

EXPOSE 3000

CMD ["serve", "-s", "build", "-l", "3000"]
