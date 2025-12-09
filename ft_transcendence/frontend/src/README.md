# 📂 Frontend/src - Código Fuente de la Aplicación React

## 📋 Descripción General

Este directorio contiene el **código fuente completo** de la SPA (Single Page Application) desarrollada en React 19 + TypeScript. Incluye componentes, contextos, middleware, tipos y puntos de entrada de la aplicación.

## 🗂️ Estructura de Archivos

```
src/
├── main.tsx              # Entry point de la aplicación
├── App.tsx               # Componente raíz con routing
├── App.css               # Estilos del componente App
├── index.css             # Estilos globales + TailwindCSS
├── types.tsx             # Definiciones de tipos TypeScript compartidos
├── ping                  # Archivo de health check (?)
├── Components/           # Componentes React de UI
│   ├── Index.tsx         # Dashboard principal
│   ├── Login.tsx         # Autenticación
│   ├── Game.tsx          # Juego Pong (1913 líneas)
│   ├── Chat.tsx          # Chat principal
│   ├── Profile.tsx       # Perfil de usuario
│   ├── Settings.tsx      # Configuración
│   ├── Matches.tsx       # Historial de partidas
│   ├── FriendsRequest.tsx # Gestión de amigos
│   ├── Tournamenst.jsx   # Torneos
│   ├── Logout.tsx        # Cierre de sesión
│   └── Chat/             # Subcomponentes de chat (10 archivos)
├── Context/              # React Contexts (estado global)
│   ├── AuthContext.tsx   # Autenticación y usuario
│   ├── ComponentsContext.tsx # Socket.IO y notificaciones
│   └── TournamentContext.jsx # Gestión de torneos
└── middleWare/           # Middleware de rutas protegidas
    └── middleWare.tsx    # ProtectedRoute component
```

## 🚀 Archivos Principales

### `main.tsx` - Entry Point

**Propósito**: Punto de entrada de la aplicación React. Renderiza el componente `App` en el DOM.

```typescript
import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App.tsx'
import './index.css'

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
)
```

**Características**:
- **React.StrictMode**: Activa advertencias de desarrollo (renderizado doble, detección de side effects)
- **root**: Monta la app en el elemento `<div id="root"></div>` de `index.html`
- **TypeScript**: Archivo `.tsx` con soporte completo de tipos

---

### `App.tsx` - Componente Raíz

**Tamaño**: ~404 líneas  
**Propósito**: Componente principal que configura routing, contextos y layout de la aplicación.

#### Estructura

```typescript
import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom';
import { AuthProvider } from './Context/AuthContext';
import { ComponentsProvider } from './Context/ComponentsContext';
import { TournamentProvider } from './Context/TournamentContext';
import { ProtectedRoute } from './middleWare/middleWare';

// Componentes
import Login from './Components/Login';
import Index from './Components/Index';
import Game from './Components/Game';
import Chat from './Components/Chat';
import Profile from './Components/Profile';
import Settings from './Components/Settings';
import Matches from './Components/Matches';
import FriendsRequest from './Components/FriendsRequest';
import Tournamenst from './Components/Tournamenst';
import Logout from './Components/Logout';

function App() {
  return (
    <AuthProvider>
      <ComponentsProvider>
        <TournamentProvider>
          <BrowserRouter>
            <Routes>
              {/* Ruta pública */}
              <Route path="/login" element={<Login />} />
              
              {/* Rutas protegidas */}
              <Route
                path="/"
                element={
                  <ProtectedRoute>
                    <Layout />
                  </ProtectedRoute>
                }
              >
                <Route index element={<Index />} />
                <Route path="game" element={<Game />} />
                <Route path="tournament" element={<Tournamenst />} />
                <Route path="profile/:userId?" element={<Profile />} />
                <Route path="matches" element={<Matches />} />
                <Route path="friends" element={<FriendsRequest />} />
                <Route path="chat" element={<Chat />} />
                <Route path="settings" element={<Settings />} />
                <Route path="logout" element={<Logout />} />
              </Route>

              {/* Catch-all redirect */}
              <Route path="*" element={<Navigate to="/" replace />} />
            </Routes>
          </BrowserRouter>
        </TournamentProvider>
      </ComponentsProvider>
    </AuthProvider>
  );
}

// Layout con sidebar y outlet
function Layout() {
  return (
    <div className="flex h-screen bg-gray-900">
      <Sidebar />
      <main className="flex-1 overflow-auto">
        <Outlet />  {/* Renderiza ruta hija activa */}
      </main>
    </div>
  );
}

function Sidebar() {
  const { user } = useAuth();
  const navigate = useNavigate();

  return (
    <aside className="w-64 bg-gray-800 text-white p-4">
      <div className="mb-8">
        <h1 className="text-2xl font-bold">Transcendence</h1>
        <p className="text-sm text-gray-400">{user?.username}</p>
      </div>
      
      <nav className="space-y-2">
        <NavLink to="/">Dashboard</NavLink>
        <NavLink to="/game">Jugar</NavLink>
        <NavLink to="/tournament">Torneos</NavLink>
        <NavLink to="/profile">Perfil</NavLink>
        <NavLink to="/matches">Historial</NavLink>
        <NavLink to="/friends">Amigos</NavLink>
        <NavLink to="/chat">Chat</NavLink>
        <NavLink to="/settings">Configuración</NavLink>
        <NavLink to="/logout">Cerrar Sesión</NavLink>
      </nav>
    </aside>
  );
}

export default App;
```

#### Características

- **React Router v7**: Sistema de routing basado en componentes
- **Nested Routes**: Layout compartido para rutas protegidas
- **Protected Routes**: Middleware de autenticación
- **Context Providers**: Wrapping en cascada (Auth → Components → Tournament)
- **Lazy Loading**: Potencial para `React.lazy()` en componentes pesados

---

### `types.tsx` - Definiciones de Tipos TypeScript

**Propósito**: Centralizar todas las **interfaces y tipos** compartidos entre componentes.

#### Tipos Principales

```typescript
// types.tsx

// ========== USER ==========
export interface User {
  id: number;
  username: string;
  email: string;
  displayName: string;
  avatar?: string;
  bio?: string;
  stats: UserStats;
  createdAt: string;
  updatedAt: string;
}

export interface UserStats {
  wins: number;
  losses: number;
  winRate: number;
  elo: number;
  totalGames: number;
  currentStreak: number;
}

// ========== AUTHENTICATION ==========
export interface LoginCredentials {
  username: string;
  password: string;
}

export interface RegisterData extends LoginCredentials {
  email: string;
  displayName: string;
}

export interface AuthToken {
  token: string;
  refreshToken: string;
  expiresIn: number;
}

// ========== GAME ==========
export interface GameState {
  roomId: string;
  players: [Player, Player];
  ball: Ball;
  score: Score;
  status: GameStatus;
  timestamp: number;
}

export type GameStatus = 'waiting' | 'playing' | 'paused' | 'finished';

export interface Player {
  id: string;
  username: string;
  paddle: Paddle;
  isAI: boolean;
}

export interface Paddle {
  y: number;
  height: number;
  width: number;
  speed: number;
}

export interface Ball {
  x: number;
  y: number;
  vx: number;
  vy: number;
  radius: number;
  speed: number;
}

export interface Score {
  player1: number;
  player2: number;
}

// ========== MATCH ==========
export interface Match {
  id: number;
  player1: User;
  player2: User;
  winner: User;
  scorePlayer1: number;
  scorePlayer2: number;
  duration: number;  // segundos
  mode: MatchMode;
  replayData?: ReplayData;
  createdAt: string;
}

export type MatchMode = 'PvP' | 'AI' | 'Tournament';

export interface ReplayData {
  frames: GameState[];
  fps: number;
}

// ========== CHAT ==========
export interface Conversation {
  id: number;
  name?: string;
  isGroup: boolean;
  participants: User[];
  lastMessage?: Message;
  unreadCount: number;
  createdAt: string;
}

export interface Message {
  id: number;
  conversationId: number;
  sender: User;
  text: string;
  attachments?: string[];
  isEdited: boolean;
  createdAt: string;
}

export interface BlockedUser {
  id: number;
  blockedUser: User;
  createdAt: string;
}

// ========== FRIENDS ==========
export interface FriendRequest {
  id: number;
  sender: User;
  receiver: User;
  status: FriendRequestStatus;
  createdAt: string;
}

export type FriendRequestStatus = 'pending' | 'accepted' | 'rejected';

export interface Friendship {
  id: number;
  friend: User;
  isOnline: boolean;
  lastSeen?: string;
  createdAt: string;
}

// ========== TOURNAMENT ==========
export interface Tournament {
  id: string;
  name: string;
  players: User[];
  bracket: BracketNode[];
  currentRound: number;
  totalRounds: number;
  status: TournamentStatus;
  winner?: User;
  createdAt: string;
}

export type TournamentStatus = 'setup' | 'active' | 'finished';

export interface BracketNode {
  matchId: string;
  round: number;
  position: number;
  player1: User | null;
  player2: User | null;
  winner: User | null;
  nextMatchId: string | null;
}

// ========== NOTIFICATIONS ==========
export interface Notification {
  id: string;
  type: NotificationType;
  title: string;
  message: string;
  timestamp: number;
  duration?: number;
  action?: NotificationAction;
}

export type NotificationType = 'info' | 'success' | 'warning' | 'error';

export interface NotificationAction {
  label: string;
  onClick: () => void;
}

// ========== SOCKET.IO EVENTS ==========
export interface ServerToClientEvents {
  'gameUpdate': (state: GameState) => void;
  'gameOver': (result: MatchResult) => void;
  'new-message': (message: Message) => void;
  'user-typing': (data: { userId: number; username: string }) => void;
  'friend-request': (request: FriendRequest) => void;
  'friend-online': (data: { userId: number }) => void;
  'tournament-update': (bracket: BracketNode[]) => void;
  'notification': (notification: Notification) => void;
}

export interface ClientToServerEvents {
  'createRoom': (name: string, options: RoomOptions) => void;
  'joinRoom': (roomId: string) => void;
  'paddleMove': (data: { y: number }) => void;
  'send-message': (data: { conversationId: number; text: string }) => void;
  'join-chat': (conversationId: number) => void;
  'typing': (data: { conversationId: number }) => void;
}

export interface RoomOptions {
  mode: MatchMode;
  difficulty?: 'easy' | 'medium' | 'hard' | 'expert';
  maxPlayers?: number;
}

// ========== API RESPONSES ==========
export interface ApiResponse<T> {
  success: boolean;
  data?: T;
  error?: string;
  message?: string;
}

export interface PaginatedResponse<T> {
  data: T[];
  total: number;
  page: number;
  limit: number;
  hasMore: boolean;
}
```

---

### `index.css` - Estilos Globales

**Propósito**: Definir estilos globales y configuración de TailwindCSS.

```css
/* index.css */

/* Tailwind base, components, utilities */
@tailwind base;
@tailwind components;
@tailwind utilities;

/* Variables CSS personalizadas */
:root {
  --color-primary: #3b82f6;
  --color-secondary: #8b5cf6;
  --color-success: #10b981;
  --color-danger: #ef4444;
  --color-warning: #f59e0b;
  --color-bg-dark: #111827;
  --color-bg-light: #1f2937;
}

/* Reset y estilos base */
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

body {
  font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', 
               'Roboto', 'Oxygen', 'Ubuntu', 'Cantarell', sans-serif;
  background-color: var(--color-bg-dark);
  color: white;
  line-height: 1.6;
}

/* Scrollbar personalizado */
::-webkit-scrollbar {
  width: 8px;
  height: 8px;
}

::-webkit-scrollbar-track {
  background: #1f2937;
}

::-webkit-scrollbar-thumb {
  background: #4b5563;
  border-radius: 4px;
}

::-webkit-scrollbar-thumb:hover {
  background: #6b7280;
}

/* Animaciones custom */
@keyframes fadeIn {
  from { opacity: 0; }
  to { opacity: 1; }
}

@keyframes slideIn {
  from { transform: translateY(-20px); opacity: 0; }
  to { transform: translateY(0); opacity: 1; }
}

.animate-fadeIn {
  animation: fadeIn 0.3s ease-in;
}

.animate-slideIn {
  animation: slideIn 0.4s ease-out;
}

/* Canvas de juego */
canvas {
  display: block;
  background: #000;
  border: 2px solid var(--color-primary);
  border-radius: 8px;
}

/* Transiciones suaves */
button, a {
  transition: all 0.2s ease;
}

button:hover, a:hover {
  transform: translateY(-2px);
}

button:active, a:active {
  transform: translateY(0);
}
```

### `App.css` - Estilos del Componente App

```css
/* App.css */

#root {
  width: 100%;
  height: 100vh;
  overflow: hidden;
}

.sidebar {
  box-shadow: 2px 0 10px rgba(0, 0, 0, 0.5);
}

.nav-link {
  display: flex;
  align-items: center;
  gap: 12px;
  padding: 12px 16px;
  border-radius: 8px;
  text-decoration: none;
  color: #d1d5db;
  font-weight: 500;
}

.nav-link:hover {
  background-color: #374151;
  color: white;
}

.nav-link.active {
  background-color: #3b82f6;
  color: white;
}

.main-content {
  padding: 24px;
  overflow-y: auto;
}
```

---

### `ping` - Health Check File

**Propósito**: Archivo probablemente usado para health checks o testing (contenido desconocido sin lectura).

**Nota**: Podría ser un archivo de texto plano con "pong" como respuesta, o un script. Requiere verificación.

---

## 🔗 Flujo de Inicialización

```
1. Browser carga index.html
      ↓
2. Vite carga main.tsx
      ↓
3. ReactDOM.createRoot renderiza <App />
      ↓
4. <AuthProvider> se monta
      ↓
   - Verifica token en localStorage
   - Llama a /api/auth/verify
   - Setea user si token válido
      ↓
5. <ComponentsProvider> se monta
      ↓
   - Inicializa Socket.IO con token
   - Registra event handlers globales
      ↓
6. <TournamentProvider> se monta
      ↓
   - Inicializa estado de torneos
      ↓
7. <BrowserRouter> activa routing
      ↓
8. Si usuario autenticado → Layout + ruta activa
   Si no autenticado → Redirect a /login
```

## 📦 Integración con Build Tool (Vite)

```javascript
// vite.config.js (en /frontend/)
import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

export default defineConfig({
  plugins: [react()],
  server: {
    port: 5173,
    host: true,  // Necesario para Docker
    proxy: {
      '/api': {
        target: 'http://localhost:3000',
        changeOrigin: true
      },
      '/socket.io': {
        target: 'http://localhost:3000',
        ws: true
      }
    }
  },
  build: {
    outDir: 'dist',
    sourcemap: true
  }
})
```

## 🧪 Testing

```bash
# Unit tests
npm test src/Components/Login.test.tsx

# Component tests con Testing Library
npm test src/Components/Game.test.tsx

# E2E con Cypress
npx cypress run --spec "cypress/e2e/full-game-flow.cy.ts"
```

---

**Ubicación**: `/frontend/src/`  
**Tecnologías**: React 19, TypeScript, React Router v7, TailwindCSS  
**Documentación relacionada**: 
- `Components/README.md` - Detalle de componentes
- `Context/README.md` - Contextos globales
- `middleWare/README.md` - Rutas protegidas
- `/backend/` - API REST consumida
