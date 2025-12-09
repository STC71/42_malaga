# 🎨 Frontend - Cliente React del Proyecto Transcendence

## 📋 Descripción General

Este directorio contiene el **cliente frontend** completo de la aplicación Transcendence. Implementa una SPA (Single Page Application) moderna con **React 19** + **TypeScript** + **Vite** + **Tailwind CSS**.

## 🗂️ Estructura del Proyecto

```
frontend/
├── index.html              # Entry point HTML
├── vite.config.js          # Configuración de Vite
├── tsconfig.json           # Configuración TypeScript
├── tailwind.config.js      # Configuración Tailwind CSS
├── postcss.config.js       # Configuración PostCSS
├── package.json            # Dependencias y scripts
├── Dockerfile              # Imagen Docker del frontend
├── healthz                 # Health check endpoint
├── ping                    # Ping endpoint
├── public/                 # Assets estáticos
├── static/                 # Archivos estáticos adicionales
├── dist/                   # Build de producción (generado)
└── src/                    # Código fuente
    ├── main.tsx           # Entry point de la aplicación
    ├── App.tsx            # Componente raíz
    ├── App.css            # Estilos del App
    ├── index.css          # Estilos globales
    ├── types.tsx          # Definiciones de tipos TypeScript
    ├── Components/        # Componentes React (ver README interno)
    ├── Context/           # Context API para estado global
    ├── middleWare/        # Middleware y utilidades
    └── services/          # Servicios (API, blockchain, etc.)
```

## 🚀 Tecnologías Principales

### Core
- **React 19.1.1** - Librería UI con las últimas features
- **TypeScript 5.9.3** - Tipado estático para JavaScript
- **Vite 7.1.7** - Build tool ultra-rápido con HMR

### Estilos
- **Tailwind CSS 3.3.5** - Framework CSS utility-first
- **PostCSS 8.5.6** - Procesador de CSS
- **Autoprefixer 10.4.21** - Prefijos CSS automáticos

### Routing & Estado
- **React Router DOM 7.9.4** - Navegación SPA
- **Context API** - Gestión de estado global

### Comunicación
- **Socket.IO Client 4.8.1** - WebSockets para tiempo real
- **Fetch API** - Peticiones HTTP al backend

### Extras
- **React Icons 5.5.0** - Iconos
- **React Confetti 6.4.0** - Efectos de celebración

## 📦 Scripts Disponibles

```bash
# Desarrollo
npm run dev              # Inicia servidor de desarrollo en puerto 2323
npm start                # Alias para desarrollo (port 2323)

# Producción
npm run build            # Compila para producción en /dist
npm run preview          # Preview del build de producción

# Calidad de código
npm run typecheck        # Verifica tipos TypeScript sin compilar
```

## 🏗️ Arquitectura del Frontend

### Componentes Principales

```
src/Components/
├── Login.tsx              # Pantalla de login y OAuth
├── Logout.tsx             # Cierre de sesión
├── Index.tsx              # Dashboard principal
├── Game.tsx               # Componente del juego Pong
├── Matches.tsx            # Sistema de matchmaking
├── Tournaments.tsx        # Gestión de torneos
├── Profile.tsx            # Perfil de usuario
├── Settings.tsx           # Configuración de cuenta
├── FriendsRequest.tsx     # Gestión de amigos
└── Chat/                  # Sistema de chat completo
    ├── ChatMain.tsx
    ├── ChatHeader.tsx
    ├── ChatSideBar.tsx
    ├── MessageInput.tsx
    ├── ConversationList.tsx
    ├── BlockUser.tsx
    └── BlockedUsersList.tsx
```

### Gestión de Estado (Context API)

```
src/Context/
├── AuthContext.tsx         # Autenticación y usuario
├── ComponentsContext.tsx   # Estado de componentes
└── TournamentContext.tsx   # Estado de torneos
```

### Middleware

```
src/middleWare/
└── middleWare.tsx          # Protección de rutas, validaciones
```

### Servicios

```
src/services/
└── blockchainService.ts    # Interacción con smart contracts
```

## 🎨 Sistema de Estilos

### Tailwind CSS

El proyecto usa **Tailwind CSS** para estilos utility-first. Configuración en `tailwind.config.js`:

```javascript
// Breakpoints responsive
sm: '640px'   // Mobile landscape
md: '768px'   // Tablet
lg: '1024px'  // Desktop
xl: '1280px'  // Large desktop
2xl: '1536px' // Extra large
```

### CSS Personalizado

- `App.css` - Estilos específicos del componente App
- `index.css` - Estilos globales y Tailwind imports

## 🔌 Comunicación con Backend

### HTTP Requests

```typescript
// Ejemplo de petición al backend
const response = await fetch('http://localhost:3000/api/auth/login', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  credentials: 'include',
  body: JSON.stringify({ username, password })
});
```

### WebSockets (Socket.IO)

```typescript
import io from 'socket.io-client';

// Conexión al servidor
const socket = io('http://localhost:3000', {
  withCredentials: true,
  transports: ['websocket', 'polling']
});

// Eventos
socket.emit('joinRoom', { roomId });
socket.on('gameUpdate', (data) => { /* ... */ });
```

## 🔐 Autenticación

### Flujo de Login

1. **Login Estándar**: Usuario/contraseña → `/api/auth/login`
2. **OAuth 2.0**: Google/42 → `/api/auth/google` → Callback
3. **Session**: Cookie segura HttpOnly con JWT
4. **Context**: Estado global en `AuthContext`

### Rutas Protegidas

El middleware verifica autenticación antes de renderizar componentes privados:

```typescript
// middleWare.tsx
if (!isAuthenticated) {
  return <Navigate to="/login" />;
}
```

## 🎮 Características del Frontend

### Sistema de Juego

- **Canvas Rendering**: Juego Pong en HTML5 Canvas
- **Real-time Updates**: Socket.IO para sincronización
- **AI Levels**: 4 niveles de dificultad
- **Replay System**: Grabación y reproducción de partidas
- **Spectator Mode**: Observar partidas en vivo

### Chat

- **Mensajería Directa**: Conversaciones 1-a-1
- **Rooms/Canales**: Salas de chat grupales
- **Bloqueo de Usuarios**: Lista de bloqueados
- **Notificaciones**: Mensajes no leídos
- **Emojis**: Soporte de emojis

### Perfil & Social

- **Estadísticas**: Win/Loss ratio, ranking
- **Historial de Partidas**: Partidas recientes
- **Sistema de Amigos**: Solicitudes y lista de amigos
- **Avatar**: Subida de imagen de perfil
- **Customización**: Nickname, preferencias

### Torneos

- **Creación**: Crear torneos con brackets
- **Inscripción**: Unirse a torneos
- **Visualización**: Ver brackets en tiempo real
- **Blockchain**: Registro en smart contract

## 🐳 Docker

### Dockerfile

```dockerfile
FROM node:20-alpine
WORKDIR /app
COPY package*.json ./
RUN npm ci
COPY . .
EXPOSE 2323
CMD ["npm", "run", "dev"]
```

### Variables de Entorno

```bash
PORT=2323                              # Puerto del servidor de desarrollo
VITE_BACKEND_URL=http://localhost:3000 # URL del backend
```

## 🔧 Configuración de Desarrollo

### Vite Configuration

```javascript
// vite.config.js
export default {
  server: {
    port: 2323,
    host: '0.0.0.0',
    proxy: {
      '/api': 'http://localhost:3000'
    }
  }
}
```

### TypeScript Configuration

```json
// tsconfig.json
{
  "compilerOptions": {
    "target": "ES2020",
    "jsx": "react-jsx",
    "module": "ESNext",
    "strict": true
  }
}
```

## 🚀 Inicio Rápido

### Desarrollo Local

```bash
# Instalar dependencias
npm install

# Iniciar servidor de desarrollo
npm run dev

# Abrir en navegador
# http://localhost:2323
```

### Producción

```bash
# Build para producción
npm run build

# Preview del build
npm run preview
```

### Docker

```bash
# Build imagen
docker build -t transcendence-frontend .

# Run contenedor
docker run -p 2323:2323 transcendence-frontend
```

## 📝 Convenciones de Código

### Componentes

- **PascalCase** para nombres de componentes
- **camelCase** para funciones y variables
- **TypeScript** para todo el código
- **Props interface** para cada componente

```typescript
interface GameProps {
  roomId: string;
  isSpectator: boolean;
}

const Game: React.FC<GameProps> = ({ roomId, isSpectator }) => {
  // ...
}
```

### Hooks

- Usar hooks de React (useState, useEffect, useContext)
- Custom hooks con prefijo `use`
- Extraer lógica compleja a custom hooks

### Estilos

- **Tailwind classes** como primera opción
- CSS modules para estilos específicos
- Evitar inline styles salvo casos excepcionales

## 🧪 Testing

```bash
# Verificar tipos TypeScript
npm run typecheck

# Lint
npm run lint

# Build test
npm run build
```

## 📚 Documentación Adicional

- [README Components](./src/Components/README.md) - Documentación de componentes
- [README Chat](./src/Components/Chat/README.md) - Sistema de chat
- [README Context](./src/Context/README.md) - Gestión de estado
- [README Middleware](./src/middleWare/README.md) - Middleware frontend

## 🤝 Equipo de Desarrollo

- **davigome** - Arquitectura y componentes principales
- **jesopan-** - Sistema de chat y comunicación real-time
- **nporras-** - UI/UX y diseño responsive
- **rdel-olm** - Integración backend y servicios
- **sternero** - Game engine y lógica de juego

## 📄 Licencia

Este proyecto es parte del curriculum de **42 School Málaga** (2025)

---

**🎮 Transcendence Frontend** - Versión 1.0.0  
*Última actualización: Diciembre 2025*
