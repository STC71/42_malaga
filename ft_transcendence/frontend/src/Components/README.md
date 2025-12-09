# 🎮 Components - Componentes React de la Aplicación

## 📋 Descripción General

Este directorio contiene todos los **componentes React** que conforman la interfaz de usuario de la aplicación Transcendence. Cada componente representa una sección funcional completa de la SPA (Single Page Application), implementando patrones modernos de React con TypeScript.

## 🗂️ Estructura de Componentes

### 🎯 Componentes de Navegación y Layout

#### `Index.tsx`
**Propósito**: Página de inicio/dashboard del usuario autenticado.

**Características**:
- Resumen de estadísticas personales
- Lista de partidas recientes
- Acceso rápido a funcionalidades principales
- Notificaciones y actividad de amigos

**Estado**: Lee datos de `AuthContext` para personalizar el dashboard.

---

#### `Login.tsx`
**Propósito**: Formulario de autenticación de usuarios.

**Funcionalidades**:
- Login con username/email + password
- Validación de campos en tiempo real
- Manejo de errores (credenciales inválidas)
- Redirección post-login a ruta protegida
- Opcional: Login con OAuth (Google, 42)

**Flujo**:
```typescript
1. Usuario ingresa credenciales
2. submit() → POST /api/auth/login
3. Backend verifica con bcrypt
4. Backend devuelve JWT token
5. Frontend almacena token en AuthContext
6. Redirección a /index
```

**Seguridad**: No almacena passwords en estado; envío directo al backend.

---

#### `Logout.tsx`
**Propósito**: Cierre de sesión y limpieza de estado.

**Proceso**:
1. Llama a `POST /api/auth/logout`
2. Backend invalida token (blacklist)
3. Frontend limpia `AuthContext.user`
4. Limpia localStorage/sessionStorage
5. Redirección a `/login`

**Nota**: Puede ser un componente o simplemente una función en `AuthContext`.

---

### 👤 Componentes de Usuario

#### `Profile.tsx`
**Propósito**: Visualización y edición del perfil de usuario.

**Secciones**:
- **Información Personal**: Avatar, username, displayName, bio
- **Estadísticas**: Victorias, derrotas, win rate, ELO/ranking
- **Historial**: Últimas 10 partidas jugadas
- **Amigos**: Lista de amigos con estado online

**Edición**: 
- Modal o modo edición inline
- Cambio de avatar (upload de imagen)
- Actualización de bio/displayName

**API**:
```typescript
GET  /api/users/:id          // Ver perfil
PUT  /api/users/me/profile   // Editar propio perfil
POST /api/users/avatar       // Upload de avatar
```

---

#### `Settings.tsx`
**Propósito**: Configuración de cuenta y preferencias.

**Opciones**:
- **Cuenta**: Cambiar password, email
- **Privacidad**: Perfil público/privado, mostrar actividad
- **Notificaciones**: Habilitar/deshabilitar por tipo
- **Apariencia**: Tema claro/oscuro, idioma
- **Avanzado**: Habilitar 2FA, descargar datos, eliminar cuenta

**Persistencia**: Cambios se guardan automáticamente o con botón "Guardar".

---

#### `FriendsRequest.tsx`
**Propósito**: Gestión de solicitudes de amistad.

**Funcionalidades**:
- **Pendientes**: Solicitudes recibidas (aceptar/rechazar)
- **Enviadas**: Solicitudes enviadas (cancelar)
- **Buscar usuarios**: Input para enviar nuevas solicitudes
- **Recomendaciones**: Usuarios sugeridos para agregar

**Tiempo real**: Usa Socket.IO para notificar nuevas solicitudes inmediatamente.

---

### 🎮 Componentes de Juego

#### `Game.tsx`
**Propósito**: Interfaz principal del juego de Pong.

**Características** (archivo principal de ~1900 líneas):
- Canvas de renderizado del juego
- Control de palas con teclado (↑/↓ o W/S)
- Sistema de partículas para efectos visuales
- Audio procedural con Web Audio API
- Estadísticas en tiempo real (hits, velocidad, rally)
- Sistema de replay con controles (play/pause/speed)
- Selector de oponente (AI/Human)
- 4 niveles de dificultad de IA
- Modal de fin de juego con resultados

**Comunicación**: Socket.IO bidireccional con `backend/pon-server.js`.

**Documentación extensa**: Ver `AI.md`, `S_IMPLEMENTACIONES.md`, `AI_EVALUATION.md` en raíz del proyecto.

---

#### `Tournamenst.jsx`
**Propósito**: Sistema de torneos de eliminación.

**Características**:
- Creación de torneos con N jugadores (potencias de 2)
- Bracket visualizado gráficamente
- Gestión de rondas (semifinales, final)
- Progreso automático tras cada partida
- Ganador destacado con confeti

**Tecnología**: 
- React Context: `TournamentContext.jsx`
- Animaciones: `react-confetti`
- Canvas para dibujar bracket

**Flujo**:
```
1. Crear torneo → Esperar jugadores
2. Iniciar → Generar bracket
3. Primera ronda → 4 partidas simultáneas
4. Ganadores avanzan → Segunda ronda
5. Final → Determinar campeón
```

---

### 📊 Componentes de Datos

#### `Matches.tsx`
**Propósito**: Historial completo de partidas del usuario.

**Visualización**:
- Tabla o lista de partidas
- Filtros: Fecha, oponente, resultado (victoria/derrota)
- Ordenamiento: Más recientes, más antiguas
- Paginación: 20 partidas por página

**Datos mostrados**:
- Fecha y hora
- Oponente (nombre + avatar)
- Resultado (4-2, 5-3, etc.)
- Duración de la partida
- Estadísticas: Total hits, máxima velocidad

**Exportación**: Botón para descargar CSV con historial completo.

---

### 💬 Componente de Chat

#### `Chat.tsx`
**Propósito**: Interfaz de mensajería instantánea.

**Arquitectura**:
- Componente contenedor que orquesta subcomponentes
- Delega rendering a componentes del directorio `Chat/`
- Gestiona estado global del chat activo

**Subcomponentes**: Ver [Chat/README.md](./Chat/README.md) para detalles completos de:
- ChatMain, ChatSideBar, MessagesList, MessageInput
- ChatHeader, ConversationList, NewChat
- ShowProfile, BlockUser, BlockedUsersList

**Comunicación**: Socket.IO con eventos `send-message`, `new-message`, `typing`.

---

## 🔄 Flujo de Navegación

```
App.tsx (root)
  ├─→ Login.tsx (si no autenticado)
  │
  └─→ Layout con sidebar (si autenticado)
       ├─→ Index.tsx (default)
       ├─→ Game.tsx
       ├─→ Tournamenst.jsx
       ├─→ Profile.tsx
       ├─→ Matches.tsx
       ├─→ FriendsRequest.tsx
       ├─→ Chat.tsx
       ├─→ Settings.tsx
       └─→ Logout.tsx
```

## 🎨 Patrones y Tecnologías

### Hooks Utilizados

```typescript
// Estado local
useState<T>(initialValue)

// Efectos secundarios (fetch, sockets)
useEffect(() => {...}, [deps])

// Contextos globales
useContext(AuthContext)
useContext(ComponentContext)
useContext(TournamentContext)

// Referencias DOM
useRef<HTMLCanvasElement>(null)

// Navegación programática
const navigate = useNavigate()
```

### Gestión de Estado

```
Estado Local (useState)
    ↓
Contextos Globales (Context API)
    ├─→ AuthContext: user, token, logout
    ├─→ ComponentsContext: socket, rooms, notifications
    └─→ TournamentContext: currentTournament, bracket
    ↓
Backend State (API REST + Socket.IO)
```

### Estilizado

- **TailwindCSS**: Utility-first CSS framework
- **Clases dinámicas**: `className={isActive ? 'bg-blue-500' : 'bg-gray-300'}`
- **Animaciones**: Tailwind transitions + CSS custom animations
- **Responsive**: Breakpoints `sm:`, `md:`, `lg:`, `xl:`

## 🔗 Integración con Backend

### REST API Endpoints

Cada componente consume endpoints específicos:

```typescript
// Login.tsx
POST /api/auth/login
POST /api/auth/register

// Profile.tsx
GET  /api/users/:id
PUT  /api/users/me/profile

// Matches.tsx
GET  /api/matches?userId=:id&limit=20&offset=0

// FriendsRequest.tsx
GET  /api/friends/requests
POST /api/friends/send
PUT  /api/friends/respond/:id

// Settings.tsx
PUT  /api/users/me/settings
POST /api/users/me/change-password

// Chat.tsx
GET  /api/conversations
GET  /api/messages/:conversationId
POST /api/conversations/create
```

### Socket.IO Events

Componentes en tiempo real:

```typescript
// Game.tsx
socket.emit('createRoom', roomName, { mode: 'AI' })
socket.emit('paddleMove', { y: newY })
socket.on('gameUpdate', (gameState) => {...})

// Chat.tsx
socket.emit('join-chat', conversationId)
socket.emit('send-message', { text })
socket.on('new-message', (message) => {...})

// FriendsRequest.tsx
socket.on('friend-request', (request) => {...})
socket.on('friend-online', ({ userId }) => {...})

// Tournamenst.jsx
socket.emit('join-tournament', tournamentId)
socket.on('tournament-started', (bracket) => {...})
socket.on('match-ended', ({ winner }) => {...})
```

## 📦 Dependencias Principales

```json
{
  "react": "^19.1.1",
  "react-dom": "^19.1.1",
  "react-router-dom": "^7.9.4",
  "socket.io-client": "^4.8.1",
  "react-icons": "^5.5.0",
  "react-confetti": "^6.4.0"
}
```

## 🧪 Testing

```bash
# Unit tests de componentes
npm test Components/Login.test.tsx

# Integration tests con mock de API
npm test Components/Game.integration.test.tsx

# E2E tests con Cypress
npx cypress run --spec "cypress/e2e/game-flow.cy.ts"
```

## 🚀 Mejoras Futuras

### Optimización
- [ ] Lazy loading de componentes pesados (`React.lazy`)
- [ ] Memoización de componentes con `React.memo`
- [ ] Virtualización de listas largas (`react-window`)

### Funcionalidades
- [ ] PWA: Notificaciones push
- [ ] Modo offline con caché de datos
- [ ] Compartir partidas en redes sociales
- [ ] Logros/achievements system

### Accesibilidad
- [ ] ARIA labels completos
- [ ] Navegación por teclado
- [ ] Soporte para lectores de pantalla
- [ ] Alto contraste y texto grande

---

**Ubicación**: `/frontend/src/Components/`  
**Tecnologías**: React 19, TypeScript, TailwindCSS, Socket.IO Client  
**Documentación relacionada**: 
- [Chat/README.md](./Chat/README.md) - Subcomponentes de mensajería
- `../Context/README.md` - Contextos globales
- `../types.tsx` - Interfaces TypeScript compartidas
- `/AI.md`, `/S_IMPLEMENTACIONES.md` - Documentación de IA del juego
