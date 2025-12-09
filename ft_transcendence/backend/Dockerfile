FROM node:20-bullseye-slim
WORKDIR /app

# instalar dependencias de compilación necesarias para node-gyp/node-pre-gyp (bcrypt, etc.)
RUN apt-get update && apt-get install -y \
    build-essential \
    python3 \
    python3-dev \
    pkg-config \
    libc6-dev \
    make \
    g++ \
    ca-certificates \
  && rm -rf /var/lib/apt/lists/*

# asegurar que node-gyp use python3 (export via env vars)
ENV PYTHON=/usr/bin/python3
ENV npm_config_python=/usr/bin/python3

# copiar sólo package.json para aprovechar cache
COPY backend/package*.json ./

# instalar dependencias (usamos --unsafe-perm para permitir builds de binarios)
RUN npm ci --unsafe-perm

# ==========================================
# BLOCKCHAIN: INSTALAR DEPENDENCIAS DE HARDHAT
# ==========================================
WORKDIR /app/blockchain/hardhat
COPY backend/blockchain/hardhat/package*.json ./
RUN npm install

# ==========================================
# BLOCKCHAIN: COMPILAR CONTRATOS
# ==========================================
# Copiar archivos necesarios para compilación

COPY backend/blockchain/hardhat/hardhat.config.js ./
COPY backend/blockchain/hardhat/contracts/ ./contracts/

# Compilar contratos (genera artifacts/)

RUN npx hardhat compile

# ==========================================
# AGREGAR: COPIAR CERTIFICADOS SSL
# ==========================================
WORKDIR /app
RUN mkdir -p /app/certs
COPY srcs/secrets/certs/fullchain.pem /app/certs/fullchain.pem
COPY srcs/secrets/certs/privkey.pem /app/certs/privkey.pem

RUN mkdir -p /app/public
# copiar el resto del código
COPY backend/ .

# intentar rebuild desde fuente por si hay binarios precompilados incompatibles
RUN npm rebuild --build-from-source || true

# comando de arranque
CMD ["node","--enable-source-maps","--trace-warnings","--unhandled-rejections=strict","pon-server.js"]
