<div align="center">

# 🎮 Transcendence

### *El Pong Definitivo del Siglo XXI*

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://www.42malaga.com/)
[![TypeScript](https://img.shields.io/badge/TypeScript-007ACC?style=for-the-badge&logo=typescript&logoColor=white)](https://www.typescriptlang.org/)
[![React](https://img.shields.io/badge/React_19-20232A?style=for-the-badge&logo=react&logoColor=61DAFB)](https://react.dev/)
[![Node.js](https://img.shields.io/badge/Node.js_20-43853D?style=for-the-badge&logo=node.js&logoColor=white)](https://nodejs.org/)
[![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)](https://www.docker.com/)

**Una experiencia de juego multijugador en tiempo real con tecnologías de vanguardia**

by davigome, jesopan-, nporras-, rdel-olm & sternero (2025)

[🚀 Inicio Rápido](#-inicio-rápido) • [📚 Documentación](#-documentación-completa) • [🏗️ Arquitectura](#-arquitectura-del-sistema) • [🎯 Features](#-características-principales)

---

</div>

## 📋 Descripción del Proyecto

**Transcendence** es una implementación moderna del clásico juego **Pong**, transformado en una plataforma de juego multijugador completa con:

- 🤖 **Inteligencia Artificial avanzada** con 4 niveles de dificultad
- 🌐 **Multijugador en tiempo real** mediante WebSockets
- 🏆 **Sistema de torneos** con brackets de eliminación
- 💬 **Chat integrado** con mensajería instantánea
- 👥 **Sistema social completo** (amigos, perfiles, estadísticas)
- 🔒 **Seguridad de nivel empresarial** (WAF, Vault, SSL/TLS)
- 🎨 **UI/UX moderna** con animaciones y efectos visuales

> 🎓 **Proyecto final de 42 School** - Desarrollado como culminación del curriculum de desarrollo web full-stack

---

## 🚀 Inicio Rápido

### Requisitos Previos

- **Node.js** 20+ y npm
- **Docker** y Docker Compose (opcional pero recomendado)
- **SQLite** (se crea automáticamente)
- **Credenciales OAuth 2.0** de Google (opcional para login social)

### Instalación Express (5 minutos)

```bash
# 1. Clonar el repositorio
git clone https://github.com/...
cd transcendence

# 2. Inicializar infraestructura (certificados SSL + Vault + WAF)
make init

# 3. Instalar dependencias del backend
npm install

# 4. Instalar dependencias del frontend
cd frontend && npm install && cd ..

# 5. Iniciar todo con Docker Compose
docker-compose up -d

# 6. O iniciar manualmente:
# Terminal 1 - Backend
npm start

# Terminal 2 - Frontend
cd frontend && npm run dev
```

### Acceso a la Aplicación

- 🎮 **Frontend**: http://localhost:5173
- 🔧 **Backend API**: http://localhost:3000
- 🔐 **Vault UI**: http://localhost:8200
- 📊 **Nginx Status**: http://localhost/nginx_status

---

## 🏗️ Arquitectura del Sistema

### 📊 Stack Tecnológico Completo

<table>
<tr>
<td width="50%">

#### Frontend
- ⚛️ **React 19** con React Compiler
- 🔷 **TypeScript 5.7** para type-safety
- ⚡ **Vite 6** como build tool
- 🎨 **TailwindCSS 4** para estilos
- 🔌 **Socket.IO Client** para WebSockets
- 🧭 **React Router 7** para SPA routing

</td>
<td width="50%">

#### Backend
- 🚀 **Fastify 4** como framework HTTP
- 🔌 **Socket.IO 4** para tiempo real
- 🗄️ **Sequelize 6** como ORM
- 💾 **SQLite 3** para base de datos
- 🔐 **bcrypt** para hashing de passwords
- 🎫 **JWT** para autenticación

</td>
</tr>
<tr>
<td width="50%">

#### Infraestructura
- 🐳 **Docker Compose** para orquestación
- 🌐 **Nginx** como reverse proxy
- 🛡️ **ModSecurity WAF** con OWASP CRS
- 🔒 **HashiCorp Vault** para secretos
- 📜 **SSL/TLS** con certificados autofirmados

</td>
<td width="50%">

#### Desarrollo
- 📦 **npm** para gestión de paquetes
- 🔧 **nodemon** para auto-reload
- 🧪 **Vitest** para testing
- 📝 **ESLint** para linting
- 🎯 **TypeScript** en todo el proyecto

</td>
</tr>
</table>

### 🔄 Flujo de Arquitectura

```
┌──────────────┐         HTTPS          ┌────────────┐
│   Cliente    │ ────────────────────►  │   Nginx    │
│   Browser    │                        │   :443     │
└──────────────┘                        └─────┬──────┘
                                              │
                                ┌─────────────┴─────────────┐
                                │                           │
                          ┌─────▼──────┐             ┌──────▼─────┐
                          │ ModSecurity│             │  Frontend  │
                          │    WAF     │             │  React:80  │
                          └─────┬──────┘             └────────────┘
                                │
                    ┌───────────┴───────────┐
                    │                       │
              ┌─────▼─────┐          ┌──────▼──────┐
              │  Backend  │          │  Socket.IO  │
              │Fastify:300│◄─────────┤   Server    │
              └─────┬─────┘          └─────────────┘
                    │
        ┌───────────┼──────────┐
        │           │          │
   ┌────▼────┐  ┌───▼───┐  ┌───▼────┐
   │ SQLite  │  │ Vault │  │  Logs  │
   │   DB    │  │ :8200 │  │  /logs │
   └─────────┘  └───────┘  └────────┘
```

### 📁 Estructura del Proyecto

```
transcendence/
├── 📂 backend/                   # Servidor Node.js
│   ├── pon-server.js             # Servidor principal (1071 líneas)
│   ├── auth.js                   # Autenticación JWT + OAuth (522 líneas)
│   ├── chat.js                   # Sistema de chat (376 líneas)
│   ├── db.js                     # Modelos Sequelize
│   └── README.md                 # 📚 Documentación detallada
│
├── 📂 frontend/                   # Aplicación React
│   ├── src/
│   │   ├── main.tsx              # Entry point
│   │   ├── App.tsx               # Componente raíz (404 líneas)
│   │   ├── Components/           # 11 componentes
│   │   │   ├── Game.tsx          # Juego Pong (1913 líneas)
│   │   │   ├── Chat.tsx          # Chat principal
│   │   │   └── Chat/             # 10 subcomponentes
│   │   ├── Context/              # Contextos globales
│   │   ├── middleWare/           # Rutas protegidas
│   │   └── types.tsx             # Tipos TypeScript
│   └── README.md                 # 📚 Documentación frontend
│
├── 📂 srcs/                       # Infraestructura
│   ├── conf/                     # Configuraciones
│   │   ├── nginx/                # Reverse proxy
│   │   └── modsecurity/          # WAF + OWASP CRS
│   ├── scripts/                  # Scripts de automatización
│   ├── secrets/                  # Gestión de secretos
│   │   ├── certs/                # Certificados SSL
│   │   ├── vault/                # Keys de Vault
│   │   └── api-approle/          # Credenciales AppRole
│   ├── data/                     # Datos persistentes
│   └── logs/                     # Logs de servicios
│
├── docker-compose.yml            # Orquestación de servicios
├── Makefile                      # Comandos de automatización
└── README.md                     # 👈 Estás aquí

📚 Cada directorio incluye README.md detallado con ejemplos y documentación completa
```

---

## 🎯 Características Principales

### 🎮 Sistema de Juego

<table>
<tr>
<td width="33%">

#### 🤖 IA Avanzada
- 4 niveles de dificultad
- Predicción de trayectoria
- Tiempos de reacción realistas
- Errores calculados por nivel

</td>
<td width="33%">

#### 🏓 Física Realista
- Sistema de colisiones preciso
- Aceleración gradual de bola
- Efecto spin en impactos
- 60 FPS de actualización

</td>
<td width="33%">

#### 🎬 Sistema de Replay
- Grabación automática
- Controles play/pause/speed
- Análisis de partidas
- Exportación de datos

</td>
</tr>
</table>

### 👥 Sistema Social

- 🤝 **Sistema de Amigos**: Enviar solicitudes, aceptar/rechazar, ver estado online
- 💬 **Chat en Tiempo Real**: Conversaciones privadas, grupos, mensajes instantáneos
- 🚫 **Bloqueo de Usuarios**: Lista de bloqueados con filtrado automático
- 📊 **Perfiles Personalizados**: Avatar, bio, estadísticas, historial de partidas
- 🏆 **Rankings y ELO**: Sistema de clasificación competitivo

### 🔐 Seguridad Empresarial

- 🛡️ **ModSecurity WAF**: Protección contra XSS, SQLi, LFI, RFI, RCE
- 🔒 **HashiCorp Vault**: Gestión centralizada de secretos
- 📜 **SSL/TLS**: Cifrado end-to-end
- 🎫 **JWT + Refresh Tokens**: Autenticación stateless segura
- 🔑 **OAuth 2.0**: Login con Google (opcional)
- 🚦 **Rate Limiting**: Protección contra brute-force y DDoS

### 🏆 Sistema de Torneos

- 🗓️ **Creación de Torneos**: Brackets de eliminación simple
- 🎯 **Progresión Automática**: Ganadores avanzan automáticamente
- 📊 **Visualización de Bracket**: Gráfico interactivo del torneo
- 🎉 **Celebración de Victoria**: Animación con confeti para el campeón

---

## 🔧 Configuración Detallada

### Variables de Entorno

## 🏗️ Arquitectura del Sistema


## Environment variables

Create a `.env` file in the project root:

```
# Backend
JWT_SECRET=supersecretkey               # change in production

# Google OAuth (optional)
GOOGLE_CLIENT_ID=your-google-client-id
GOOGLE_CLIENT_SECRET=your-google-client-secret
GOOGLE_CALLBACK_URL=http://localhost:3000/auth/google/callback

# Frontend URL for post-login redirect (used by Google flow)
FRONTEND_URL=http://localhost:2323/login
```

Notes:
- `pon-server.js` currently uses a default secret `'supersecretkey'`; setting `JWT_SECRET` is recommended.
- `FRONTEND_URL` is where the backend redirects with `#token=...` after Google login.
- CORS for Socket.IO is already configured for `http://localhost:2323`.


## Install and run

### Backend (API + Socket.IO)

From the repository root:

```bash
npm install
npm start               # starts Fastify + Socket.IO on :3000
```

Useful backend scripts (root `package.json`):
- `start` – run the server (`pon-server.js`)
- `dev` – watch Tailwind, TS, and start the server together
- `build:css` – Tailwind build from `src/input.css` to `public/style.css`
- `build:ts` / `build:ts-once` – TypeScript compile for non‑React pages

The database file will be created at `backend/database.sqlite` on first run.

### Frontend (React + Vite)

In a second terminal:

```bash
cd frontend
npm install
npm run dev           # Vite dev server on :2323
```

Vite is configured to proxy API calls to `http://localhost:3000` (see `frontend/vite.config.js`).


## Features

- JWT auth (login, logout, me) and Google OAuth 2.0 flow
- Friends system (requests, accept/reject, online/offline signals)
- Real‑time game rooms via Socket.IO (1v1 and AI mode with difficulty)
- Match persistence + basic player stats (wins/losses)
- Tailwind styling, React components, and WebSocket‑driven UI updates


## Key API routes (Fastify)

All routes are defined in `pon-server.js` and implemented in `backend/auth.js`.

- `POST /api/auth/register` – Create user (username/password)
- `POST /api/auth/login` – Returns `{ token, user }` on success
- `POST /api/auth/logout` – Requires JWT (bearer). Ends one session
- `GET /api/auth/me` – Returns current user profile

- `GET /api/user/profile/:userId` – Public profile + last matches
- `PUT /api/user/profile` – Update own profile
- `PUT /api/user/profile/changePassword` – Change password

- `GET /api/user/friends` – List accepted friends
- `GET /api/user/friend-getFriendRequests` – Pending requests for me
- `POST /api/user/friend-request` – Send friend request by username
- `POST /api/user/friend-response` – Accept/Reject request

- `GET /api/user/match-history` – My match history (latest first)

- `GET /auth/google/callback` – Google OAuth callback (internal in flow)

Auth: send JWT as `Authorization: Bearer <token>` for protected routes.


## Socket.IO events (high level)

Client → Server:

---

## 🧪 Testing y Validación

### Testing del Backend

```bash
# Unit tests
npm test

# Test de autenticación
curl -X POST http://localhost:3000/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{"username":"test","password":"test123"}'
```

### Testing de Seguridad (ModSecurity WAF)

```bash
# Ejecutar batería de tests de seguridad
./srcs/scripts/99.test_modsec_rules.sh
```

---

## 🚨 Troubleshooting

### Problemas Comunes

- **EADDRINUSE**: Matar proceso con `lsof -ti:3000 | xargs kill -9`
- **JWT invalid**: Limpiar localStorage y re-login
- **Vault sealed**: Usar `vault operator unseal` con key de `/srcs/secrets/vault/unseal_key`
- **ModSecurity bloqueando**: Ajustar `paranoia_level` en `crs-setup.conf`

---

## 📚 Documentación Completa del Proyecto

### 📁 General
- [README Principal](./README.md) - Este archivo (información general del proyecto)

### 🔧 Backend
- [README Backend](./backend/README.md) - Documentación completa del servidor Node.js
- [README IA Implementation](./backend/AI_IMPLEMENTATION.md) - Módulo de Inteligencia Artificial (4 niveles, spin, counter-spin)
- [README Blockchain](./backend/blockchain/README.md) - Smart contracts y servicios blockchain
- [README Hardhat](./backend/blockchain/hardhat/README.md) - Entorno de desarrollo Hardhat
- [README Contratos Solidity](./backend/blockchain/hardhat/contracts/README.md) - Smart contract TournamentRegistry
- [README Scripts Deploy](./backend/blockchain/hardhat/scripts/README.md) - Scripts de despliegue en Avalanche

### 🎨 Frontend
- [README Frontend](./frontend/README.md) - Cliente React 19 + TypeScript + Vite completo
- [README Source Code](./frontend/src/README.md) - Código fuente de la aplicación
- [README Componentes](./frontend/src/Components/README.md) - Todos los componentes React
- [README Chat](./frontend/src/Components/Chat/README.md) - Sistema de mensajería en tiempo real
- [README Context](./frontend/src/Context/README.md) - Gestión de estado global (AuthContext, etc.)
- [README Middleware](./frontend/src/middleWare/README.md) - Rutas protegidas y autenticación
- [README Services](./frontend/src/services/README.md) - Capa de servicios API (blockchainService, etc.)
- [README Static Assets](./frontend/static/README.md) - Archivos estáticos servidos por Nginx

### 🛡️ Infraestructura
- [README Srcs](./srcs/README.md) - Configuración de servicios e infraestructura
- [README Configuración](./srcs/conf/README.md) - Nginx + ModSecurity + WAF
- [README Scripts](./srcs/scripts/README.md) - Scripts de inicialización y mantenimiento
- [README Secrets](./srcs/secrets/README.md) - Gestión centralizada de información sensible
- [README Vault](./srcs/secrets/vault/README.md) - HashiCorp Vault (tokens y claves)
- [README API AppRole](./srcs/secrets/api-approle/README.md) - Autenticación Vault para backend
- [README Certificados](./srcs/secrets/certs/README.md) - Certificados SSL/TLS

### 📊 Testing y Validación
- [test_auto.sh](./test_auto.sh) - Script de validación automática v3.0
- [test_result.md](./test_result.md) - Reporte de validación (generado automáticamente)

### 🔗 Navegación Rápida por Módulos

#### Desarrollo de Juego
- 🎮 [Game Logic](./backend/pon-server.js) - Servidor del juego (1071 líneas)
- 🤖 [IA Documentation](./backend/AI_IMPLEMENTATION.md) - Algoritmos de IA
- 🎨 [Game Component](./frontend/src/Components/Game.tsx) - Cliente del juego (1913 líneas)

#### Autenticación y Seguridad
- 🔐 [Auth Backend](./backend/auth.js) - JWT + OAuth2 (522 líneas)
- 🛡️ [ModSecurity Config](./srcs/conf/modsecurity/) - Reglas WAF
- 🔒 [Vault Setup](./srcs/secrets/vault/README.md) - Gestión de secretos

#### Chat y Social
- 💬 [Chat Backend](./backend/chat.js) - Lógica del chat (376 líneas)
- 💬 [Chat Frontend](./frontend/src/Components/Chat/README.md) - Componentes de chat
- 👥 [User Management](./backend/db.js) - Modelos de base de datos

#### Blockchain y Torneos
- ⛓️ [Smart Contract](./backend/blockchain/hardhat/contracts/README.md) - TournamentRegistry.sol
- 🚀 [Deploy Scripts](./backend/blockchain/hardhat/scripts/README.md) - Despliegue en Fuji
- 🎯 [Tournament Component](./frontend/src/Components/Tournaments.tsx) - UI de torneos

---

## 📜 Licencia

MIT License - Ver [LICENSE](LICENSE)

---

## 👥 Autores

**Equipo formado por: davigome, jesopan-, nporras-, rdel-olm & sternero - 42 Málaga (2025)

---

<div align="center">

### ⭐ Dale una estrella si te gusta el proyecto ⭐

**Hecho con ❤️ por el equipo Transcendence042**

</div>
