# 🧠 Context - Contextos de React para Estado Global

## 📋 Descripción General

Este directorio contiene los **React Contexts** que gestionan el **estado global** de la aplicación. Utilizando el Context API de React, estos módulos proporcionan datos y funciones compartidas entre múltiples componentes sin necesidad de prop drilling.

## 🗂️ Estructura de Contextos

### 🔐 `AuthContext.tsx` - Contexto de Autenticación

**Propósito**: Gestionar el estado de autenticación del usuario en toda la aplicación.

#### 📦 Estado Proporcionado

```typescript
interface AuthContextType {
  user: User | null;              // Usuario autenticado (null si no logueado)
  token: string | null;           // JWT token para autenticación
  isAuthenticated: boolean;       // Booleano de conveniencia
  login: (credentials: LoginCredentials) => Promise<void>;
  logout: () => void;
  register: (userData: RegisterData) => Promise<void>;
  updateProfile: (updates: Partial<User>) => Promise<void>;
  loading: boolean;               // Cargando verificación de token
}

interface User {
  id: number;
  username: string;
  email: string;
  displayName: string;
  avatar?: string;
  stats: {
    wins: number;
    losses: number;
    winRate: number;
    elo: number;
  };
  createdAt: string;
}
```

#### 🔄 Ciclo de Vida

```
1. App.tsx → <AuthProvider> wrap
2. Al montar → verifyToken() con localStorage
3. Si token válido → fetch user data
4. setUser(userData) → isAuthenticated = true
5. Componentes hijos pueden usar useAuth()
```

#### 🔌 Implementación

```typescript
// AuthContext.tsx
import { createContext, useContext, useState, useEffect } from 'react';

const AuthContext = createContext<AuthContextType | undefined>(undefined);

export function AuthProvider({ children }: { children: React.ReactNode }) {
  const [user, setUser] = useState<User | null>(null);
  const [token, setToken] = useState<string | null>(
    localStorage.getItem('auth_token')
  );
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    if (token) {
      verifyAndFetchUser(token);
    } else {
      setLoading(false);
    }
  }, [token]);

  const verifyAndFetchUser = async (token: string) => {
    try {
      const response = await fetch('/api/auth/verify', {
        headers: { Authorization: `Bearer ${token}` }
      });
      if (response.ok) {
        const userData = await response.json();
        setUser(userData);
      } else {
        // Token inválido o expirado
        localStorage.removeItem('auth_token');
        setToken(null);
      }
    } catch (error) {
      console.error('Error verifying token:', error);
    } finally {
      setLoading(false);
    }
  };

  const login = async (credentials: LoginCredentials) => {
    const response = await fetch('/api/auth/login', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(credentials)
    });
    
    if (!response.ok) throw new Error('Login failed');
    
    const { token, user } = await response.json();
    localStorage.setItem('auth_token', token);
    setToken(token);
    setUser(user);
  };

  const logout = () => {
    localStorage.removeItem('auth_token');
    setToken(null);
    setUser(null);
    // Opcional: llamar a /api/auth/logout para invalidar token en backend
  };

  return (
    <AuthContext.Provider 
      value={{ 
        user, 
        token, 
        isAuthenticated: !!user, 
        login, 
        logout, 
        loading 
      }}
    >
      {children}
    </AuthContext.Provider>
  );
}

export function useAuth() {
  const context = useContext(AuthContext);
  if (!context) {
    throw new Error('useAuth must be used within AuthProvider');
  }
  return context;
}
```

#### 🎯 Uso en Componentes

```typescript
// Login.tsx
import { useAuth } from '../Context/AuthContext';

function Login() {
  const { login, isAuthenticated } = useAuth();
  const navigate = useNavigate();

  const handleSubmit = async (e: FormEvent) => {
    e.preventDefault();
    try {
      await login({ username, password });
      navigate('/index');
    } catch (error) {
      setError('Invalid credentials');
    }
  };

  if (isAuthenticated) {
    return <Navigate to="/index" />;
  }

  return <form onSubmit={handleSubmit}>...</form>;
}
```

#### 🔒 Seguridad

- **Token Storage**: localStorage (considerar httpOnly cookies para mayor seguridad)
- **Token Expiration**: Backend debe incluir `exp` claim en JWT
- **Refresh Tokens**: Implementar endpoint `/api/auth/refresh` para renovar sin re-login
- **HTTPS Only**: Nunca transmitir tokens por HTTP sin cifrar

---

### 🧩 `ComponentsContext.tsx` - Contexto de Componentes Globales

**Propósito**: Gestionar estado compartido entre componentes (socket, notificaciones, modales).

#### 📦 Estado Proporcionado

```typescript
interface ComponentsContextType {
  socket: Socket | null;                    // Instancia de Socket.IO
  notifications: Notification[];            // Cola de notificaciones
  activeModal: string | null;               // Modal actualmente abierto
  rooms: Room[];                            // Salas de juego disponibles
  onlineUsers: number[];                    // IDs de usuarios online
  
  // Métodos
  initSocket: () => void;
  disconnectSocket: () => void;
  addNotification: (notif: Notification) => void;
  clearNotifications: () => void;
  openModal: (modalId: string) => void;
  closeModal: () => void;
  refreshRooms: () => Promise<void>;
}

interface Room {
  id: string;
  name: string;
  host: User;
  players: number;
  maxPlayers: number;
  mode: 'AI' | 'PvP' | 'Tournament';
  status: 'waiting' | 'playing' | 'finished';
}

interface Notification {
  id: string;
  type: 'info' | 'success' | 'warning' | 'error';
  title: string;
  message: string;
  timestamp: number;
  duration?: number;  // Auto-dismiss después de X ms
}
```

#### 🔌 Socket.IO Integration

```typescript
// ComponentsContext.tsx
import { io, Socket } from 'socket.io-client';

export function ComponentsProvider({ children }: { children: React.ReactNode }) {
  const [socket, setSocket] = useState<Socket | null>(null);
  const { token, isAuthenticated } = useAuth();

  const initSocket = useCallback(() => {
    if (!token || socket) return;

    const newSocket = io('http://localhost:3000', {
      auth: { token },
      transports: ['websocket', 'polling']
    });

    newSocket.on('connect', () => {
      console.log('Socket connected:', newSocket.id);
      addNotification({
        id: Date.now().toString(),
        type: 'success',
        title: 'Conectado',
        message: 'Conexión establecida con el servidor',
        timestamp: Date.now(),
        duration: 3000
      });
    });

    newSocket.on('disconnect', () => {
      console.log('Socket disconnected');
    });

    newSocket.on('notification', (data: Notification) => {
      addNotification(data);
    });

    newSocket.on('user-online', (userId: number) => {
      setOnlineUsers(prev => [...prev, userId]);
    });

    newSocket.on('user-offline', (userId: number) => {
      setOnlineUsers(prev => prev.filter(id => id !== userId));
    });

    setSocket(newSocket);
  }, [token, socket]);

  useEffect(() => {
    if (isAuthenticated && !socket) {
      initSocket();
    }
    return () => {
      if (socket) {
        socket.disconnect();
      }
    };
  }, [isAuthenticated]);

  return (
    <ComponentsContext.Provider value={{ socket, ... }}>
      {children}
    </ComponentsContext.Provider>
  );
}
```

#### 🎨 Sistema de Notificaciones

```typescript
// Uso en cualquier componente
const { addNotification } = useComponents();

// Notificación de éxito
addNotification({
  id: crypto.randomUUID(),
  type: 'success',
  title: 'Partida creada',
  message: 'La sala de juego se ha creado exitosamente',
  timestamp: Date.now(),
  duration: 5000  // Auto-dismiss en 5 segundos
});

// Notificación de error persistente
addNotification({
  id: crypto.randomUUID(),
  type: 'error',
  title: 'Error de conexión',
  message: 'No se pudo conectar con el servidor',
  timestamp: Date.now()
  // Sin duration → persiste hasta que usuario la cierre
});
```

#### 🔔 Componente de Notificaciones

```typescript
// NotificationToast.tsx
function NotificationToast() {
  const { notifications, clearNotifications } = useComponents();

  useEffect(() => {
    // Auto-dismiss de notificaciones con duration
    notifications.forEach(notif => {
      if (notif.duration) {
        setTimeout(() => {
          removeNotification(notif.id);
        }, notif.duration);
      }
    });
  }, [notifications]);

  return (
    <div className="fixed top-4 right-4 z-50 space-y-2">
      {notifications.map(notif => (
        <div 
          key={notif.id}
          className={`p-4 rounded shadow-lg ${getColorClass(notif.type)}`}
        >
          <h4 className="font-bold">{notif.title}</h4>
          <p>{notif.message}</p>
        </div>
      ))}
    </div>
  );
}
```

---

### 🏆 `TournamentContext.jsx` - Contexto de Torneos

**Propósito**: Gestionar el estado de torneos de eliminación (bracket, rondas, progreso).

#### 📦 Estado Proporcionado

```javascript
interface TournamentContextType {
  currentTournament: Tournament | null;
  bracket: BracketNode[];
  currentRound: number;
  totalRounds: number;
  isActive: boolean;
  
  createTournament: (players: Player[]) => void;
  startTournament: () => void;
  advanceMatch: (matchId: string, winnerId: number) => void;
  resetTournament: () => void;
  getTournamentWinner: () => Player | null;
}

interface Tournament {
  id: string;
  name: string;
  players: Player[];
  status: 'setup' | 'active' | 'finished';
  createdAt: number;
}

interface BracketNode {
  matchId: string;
  round: number;
  position: number;
  player1: Player | null;
  player2: Player | null;
  winner: Player | null;
  nextMatchId: string | null;  // Match al que avanza el ganador
}
```

#### 🏗️ Generación de Bracket

```javascript
// TournamentContext.jsx
function generateBracket(players) {
  // Validar que sea potencia de 2
  if (!isPowerOfTwo(players.length)) {
    throw new Error('El número de jugadores debe ser potencia de 2');
  }

  const rounds = Math.log2(players.length);
  const bracket = [];

  // Primera ronda: matchear jugadores
  for (let i = 0; i < players.length; i += 2) {
    bracket.push({
      matchId: `round1-match${i/2}`,
      round: 1,
      position: i / 2,
      player1: players[i],
      player2: players[i + 1],
      winner: null,
      nextMatchId: `round2-match${Math.floor(i/4)}`
    });
  }

  // Rondas siguientes: matches vacíos
  for (let r = 2; r <= rounds; r++) {
    const matchesInRound = Math.pow(2, rounds - r);
    for (let m = 0; m < matchesInRound; m++) {
      bracket.push({
        matchId: `round${r}-match${m}`,
        round: r,
        position: m,
        player1: null,
        player2: null,
        winner: null,
        nextMatchId: r < rounds ? `round${r+1}-match${Math.floor(m/2)}` : null
      });
    }
  }

  return bracket;
}
```

#### 🎮 Flujo de Torneo

```javascript
// Crear torneo
const { createTournament, startTournament } = useTournament();

const players = [
  { id: 1, username: 'Alice' },
  { id: 2, username: 'Bob' },
  { id: 3, username: 'Charlie' },
  { id: 4, username: 'David' }
];

createTournament(players);  // Genera bracket de 2 rondas

// Iniciar primera ronda
startTournament();  // status: 'setup' → 'active'

// Al terminar un match
advanceMatch('round1-match0', 1);  // Alice gana
// → Alice avanza a round2-match0.player1

advanceMatch('round1-match1', 3);  // Charlie gana
// → Charlie avanza a round2-match0.player2

// Semifinal
advanceMatch('round2-match0', 1);  // Alice gana
// → Alice es campeona del torneo
// → status: 'active' → 'finished'
```

#### 🎨 Visualización del Bracket

```jsx
// Tournamenst.jsx
function TournamentBracket() {
  const { bracket, currentRound } = useTournament();

  const groupedByRound = bracket.reduce((acc, match) => {
    if (!acc[match.round]) acc[match.round] = [];
    acc[match.round].push(match);
    return acc;
  }, {});

  return (
    <div className="flex gap-8">
      {Object.entries(groupedByRound).map(([round, matches]) => (
        <div key={round} className="flex flex-col gap-4">
          <h3>Ronda {round}</h3>
          {matches.map(match => (
            <MatchCard 
              key={match.matchId} 
              match={match}
              isActive={match.round === currentRound}
            />
          ))}
        </div>
      ))}
    </div>
  );
}
```

#### 🏅 Confetti de Victoria

```javascript
// Al detectar ganador final
useEffect(() => {
  const winner = getTournamentWinner();
  if (winner) {
    setShowConfetti(true);
    addNotification({
      type: 'success',
      title: '¡Torneo Completado!',
      message: `${winner.username} es el campeón`
    });
  }
}, [currentTournament?.status]);
```

---

## 🔗 Integración entre Contextos

### Dependencias

```
TournamentContext → usa useAuth() para validar permisos
ComponentsContext → usa useAuth() para inicializar socket
AuthContext → independiente (base)
```

### Composición en App.tsx

```typescript
function App() {
  return (
    <AuthProvider>
      <ComponentsProvider>
        <TournamentProvider>
          <RouterProvider router={router} />
        </TournamentProvider>
      </ComponentsProvider>
    </AuthProvider>
  );
}
```

## 🛠️ Hooks Personalizados

Cada contexto exporta un hook custom:

```typescript
// AuthContext.tsx
export function useAuth() { ... }

// ComponentsContext.tsx
export function useComponents() { ... }

// TournamentContext.jsx
export function useTournament() { ... }
```

**Ventaja**: Validación automática de uso dentro de Provider.

## 🧪 Testing de Contextos

```typescript
// AuthContext.test.tsx
import { renderHook, act } from '@testing-library/react';

describe('AuthContext', () => {
  it('should login user successfully', async () => {
    const { result } = renderHook(() => useAuth(), {
      wrapper: AuthProvider
    });

    await act(async () => {
      await result.current.login({
        username: 'testuser',
        password: 'password123'
      });
    });

    expect(result.current.isAuthenticated).toBe(true);
    expect(result.current.user).toBeDefined();
  });
});
```

## 📊 Flujo de Datos

```
Backend API/Socket
    ↓
Context Providers (estado global)
    ↓
useAuth() / useComponents() / useTournament() (hooks)
    ↓
Componentes React (UI)
```

## 🚀 Mejoras Futuras

- [ ] **Persistencia**: Guardar estado de torneo en localStorage
- [ ] **Optimización**: Usar `useReducer` en lugar de múltiples `useState`
- [ ] **DevTools**: Integrar Redux DevTools para debugging
- [ ] **TypeScript**: Migrar `TournamentContext.jsx` a `.tsx`
- [ ] **Testing**: Aumentar cobertura a 80%+

---

**Ubicación**: `/frontend/src/Context/`  
**Tecnologías**: React Context API, Socket.IO Client, TypeScript  
**Documentación relacionada**: 
- `../Components/README.md` - Componentes que consumen contextos
- `../types.tsx` - Interfaces TypeScript compartidas
- `/backend/pon-server.js` - Socket.IO events del servidor
