# 🛡️ MiddleWare - Middleware de Rutas Protegidas

## 📋 Descripción General

Este directorio contiene **middlewares** para React Router que protegen rutas privadas, validan autenticación y gestionan redirecciones. Implementan el patrón de **Higher-Order Component (HOC)** o **wrapper components** para encapsular lógica de autorización.

## 🗂️ Estructura

### `middleWare.tsx` - Middleware Principal

**Propósito**: Proteger rutas que requieren autenticación verificada.

## 🔐 Implementación de Middleware

### Componente ProtectedRoute

```typescript
// middleWare.tsx
import { Navigate, useLocation } from 'react-router-dom';
import { useAuth } from '../Context/AuthContext';

interface ProtectedRouteProps {
  children: React.ReactNode;
  redirectTo?: string;
  requiredRole?: 'user' | 'admin';
}

export function ProtectedRoute({ 
  children, 
  redirectTo = '/login',
  requiredRole 
}: ProtectedRouteProps) {
  const { isAuthenticated, user, loading } = useAuth();
  const location = useLocation();

  // Mostrar loader mientras verifica token
  if (loading) {
    return (
      <div className="flex items-center justify-center h-screen">
        <div className="animate-spin rounded-full h-32 w-32 border-t-2 border-b-2 border-blue-500"></div>
      </div>
    );
  }

  // Redirigir a login si no autenticado
  if (!isAuthenticated) {
    // Guardar la ruta intentada para redirect post-login
    return <Navigate to={redirectTo} state={{ from: location }} replace />;
  }

  // Verificar rol si se requiere
  if (requiredRole && user?.role !== requiredRole) {
    return <Navigate to="/unauthorized" replace />;
  }

  // Usuario autenticado → renderizar children
  return <>{children}</>;
}
```

### Variante: RequireAuth HOC

```typescript
// Alternative HOC pattern
export function requireAuth<P extends object>(
  Component: React.ComponentType<P>
) {
  return function ProtectedComponent(props: P) {
    const { isAuthenticated, loading } = useAuth();

    if (loading) return <LoadingSpinner />;
    if (!isAuthenticated) return <Navigate to="/login" />;

    return <Component {...props} />;
  };
}

// Uso
const ProtectedProfile = requireAuth(Profile);
```

## 🎯 Uso en Rutas

### Configuración de React Router

```typescript
// App.tsx
import { createBrowserRouter, RouterProvider } from 'react-router-dom';
import { ProtectedRoute } from './middleWare/middleWare';

const router = createBrowserRouter([
  {
    path: '/login',
    element: <Login />
  },
  {
    path: '/',
    element: (
      <ProtectedRoute>
        <Layout />  {/* Layout con sidebar + outlet */}
      </ProtectedRoute>
    ),
    children: [
      {
        index: true,
        element: <Index />  // Dashboard
      },
      {
        path: 'game',
        element: <Game />
      },
      {
        path: 'tournament',
        element: <Tournamenst />
      },
      {
        path: 'profile/:userId?',
        element: <Profile />
      },
      {
        path: 'matches',
        element: <Matches />
      },
      {
        path: 'friends',
        element: <FriendsRequest />
      },
      {
        path: 'chat',
        element: <Chat />
      },
      {
        path: 'settings',
        element: (
          <ProtectedRoute requiredRole="admin">
            <Settings />
          </ProtectedRoute>
        )
      }
    ]
  },
  {
    path: '/unauthorized',
    element: <Unauthorized />
  },
  {
    path: '*',
    element: <NotFound />
  }
]);

function App() {
  return (
    <AuthProvider>
      <ComponentsProvider>
        <RouterProvider router={router} />
      </ComponentsProvider>
    </AuthProvider>
  );
}
```

### Redirección Post-Login

```typescript
// Login.tsx
import { useAuth } from '../Context/AuthContext';
import { useNavigate, useLocation } from 'react-router-dom';

function Login() {
  const { login } = useAuth();
  const navigate = useNavigate();
  const location = useLocation();

  const handleLogin = async (credentials: LoginCredentials) => {
    await login(credentials);
    
    // Redirigir a la ruta originalmente intentada
    const from = location.state?.from?.pathname || '/';
    navigate(from, { replace: true });
  };

  return <form onSubmit={handleLogin}>...</form>;
}
```

## 🔒 Validaciones de Seguridad

### 1. Token Expiration Check

```typescript
// middleWare.tsx
export function ProtectedRoute({ children }: ProtectedRouteProps) {
  const { token, logout } = useAuth();

  useEffect(() => {
    if (token) {
      const decoded = jwtDecode<JWTPayload>(token);
      const expiresIn = (decoded.exp * 1000) - Date.now();

      if (expiresIn < 0) {
        // Token expirado
        logout();
        return;
      }

      // Auto-logout antes de expiración
      const timeoutId = setTimeout(() => {
        alert('Tu sesión ha expirado');
        logout();
      }, expiresIn);

      return () => clearTimeout(timeoutId);
    }
  }, [token]);

  // ... resto del código
}
```

### 2. Network Status Handling

```typescript
// middleWare.tsx
function ProtectedRoute({ children }: ProtectedRouteProps) {
  const [isOnline, setIsOnline] = useState(navigator.onLine);

  useEffect(() => {
    const handleOnline = () => setIsOnline(true);
    const handleOffline = () => setIsOnline(false);

    window.addEventListener('online', handleOnline);
    window.addEventListener('offline', handleOffline);

    return () => {
      window.removeEventListener('online', handleOnline);
      window.removeEventListener('offline', handleOffline);
    };
  }, []);

  if (!isOnline) {
    return (
      <div className="flex items-center justify-center h-screen">
        <div className="text-center">
          <h2>Sin conexión a Internet</h2>
          <p>Verifica tu conexión y recarga la página</p>
        </div>
      </div>
    );
  }

  // ... resto de validaciones
}
```

### 3. Rate Limiting Frontend

```typescript
// middleWare.tsx
const requestCounts = new Map<string, number>();

export function RateLimitedRoute({ 
  children, 
  maxRequests = 100, 
  windowMs = 60000 
}: RateLimitedRouteProps) {
  const { user } = useAuth();
  const [blocked, setBlocked] = useState(false);

  useEffect(() => {
    if (!user) return;

    const key = `rate_limit_${user.id}`;
    const count = requestCounts.get(key) || 0;

    if (count >= maxRequests) {
      setBlocked(true);
      setTimeout(() => {
        requestCounts.delete(key);
        setBlocked(false);
      }, windowMs);
    } else {
      requestCounts.set(key, count + 1);
    }
  }, [user]);

  if (blocked) {
    return <div>Demasiadas peticiones. Intenta en unos minutos.</div>;
  }

  return <>{children}</>;
}
```

## 📊 Flujo de Autenticación

```
Usuario visita /game
    ↓
<ProtectedRoute> intercepta
    ↓
¿loading? → Mostrar spinner
    ↓
¿isAuthenticated? 
    ├─ NO → <Navigate to="/login" state={{ from: '/game' }} />
    │           ↓
    │       Usuario ingresa credenciales
    │           ↓
    │       login() exitoso
    │           ↓
    │       navigate(location.state.from) → /game
    │
    └─ SÍ → ¿requiredRole?
              ├─ NO → Renderizar children (<Game />)
              └─ SÍ → ¿user.role === requiredRole?
                        ├─ SÍ → Renderizar children
                        └─ NO → <Navigate to="/unauthorized" />
```

## 🎨 Componentes de UI Auxiliares

### LoadingSpinner

```typescript
// LoadingSpinner.tsx
export function LoadingSpinner() {
  return (
    <div className="flex items-center justify-center h-screen bg-gray-900">
      <div className="relative">
        <div className="animate-spin rounded-full h-32 w-32 border-t-4 border-b-4 border-blue-500"></div>
        <div className="absolute top-1/2 left-1/2 transform -translate-x-1/2 -translate-y-1/2">
          <span className="text-white text-xl font-bold">Cargando...</span>
        </div>
      </div>
    </div>
  );
}
```

### Unauthorized Page

```typescript
// Unauthorized.tsx
export function Unauthorized() {
  const navigate = useNavigate();

  return (
    <div className="flex flex-col items-center justify-center h-screen">
      <h1 className="text-6xl font-bold text-red-500">403</h1>
      <p className="text-2xl mt-4">No tienes permisos para acceder a esta página</p>
      <button 
        onClick={() => navigate('/')}
        className="mt-8 px-6 py-3 bg-blue-500 text-white rounded hover:bg-blue-600"
      >
        Volver al inicio
      </button>
    </div>
  );
}
```

## 🔗 Integración con Backend

### Validación de Token en Backend

```javascript
// backend/auth.js (middleware de Fastify)
fastify.decorate('authenticate', async (request, reply) => {
  try {
    const token = request.headers.authorization?.split(' ')[1];
    
    if (!token) {
      return reply.code(401).send({ error: 'Token no proporcionado' });
    }

    const decoded = jwt.verify(token, process.env.JWT_SECRET);
    request.user = await User.findByPk(decoded.userId);

    if (!request.user) {
      return reply.code(401).send({ error: 'Usuario no encontrado' });
    }
  } catch (error) {
    return reply.code(401).send({ error: 'Token inválido' });
  }
});

// Uso en rutas
fastify.get('/api/profile', {
  preHandler: [fastify.authenticate]
}, async (request, reply) => {
  return { user: request.user };
});
```

## 🧪 Testing

### Test de ProtectedRoute

```typescript
// middleWare.test.tsx
import { render, screen } from '@testing-library/react';
import { MemoryRouter } from 'react-router-dom';
import { AuthProvider } from '../Context/AuthContext';
import { ProtectedRoute } from './middleWare';

describe('ProtectedRoute', () => {
  it('should redirect to login when not authenticated', () => {
    // Mock AuthContext con isAuthenticated = false
    render(
      <MemoryRouter initialEntries={['/protected']}>
        <AuthProvider>
          <ProtectedRoute>
            <div>Protected Content</div>
          </ProtectedRoute>
        </AuthProvider>
      </MemoryRouter>
    );

    expect(screen.queryByText('Protected Content')).not.toBeInTheDocument();
  });

  it('should render children when authenticated', () => {
    // Mock AuthContext con isAuthenticated = true
    render(
      <MemoryRouter initialEntries={['/protected']}>
        <AuthProvider>
          <ProtectedRoute>
            <div>Protected Content</div>
          </ProtectedRoute>
        </AuthProvider>
      </MemoryRouter>
    );

    expect(screen.getByText('Protected Content')).toBeInTheDocument();
  });
});
```

## 🚀 Mejoras Futuras

### 1. Session Management

```typescript
// Implementar refresh token automático
const refreshToken = async () => {
  const response = await fetch('/api/auth/refresh', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ refreshToken: localStorage.getItem('refresh_token') })
  });
  
  const { token } = await response.json();
  localStorage.setItem('auth_token', token);
  return token;
};
```

### 2. Biometric Authentication

```typescript
// WebAuthn API para login biométrico
if (window.PublicKeyCredential) {
  const credential = await navigator.credentials.create({
    publicKey: {
      challenge: new Uint8Array(32),
      rp: { name: "Transcendence" },
      user: {
        id: new Uint8Array(16),
        name: user.email,
        displayName: user.username
      },
      pubKeyCredParams: [{ alg: -7, type: "public-key" }]
    }
  });
}
```

### 3. Multi-Factor Authentication

```typescript
// Verificación de código 2FA
export function TwoFactorRoute({ children }: { children: React.ReactNode }) {
  const { user } = useAuth();
  const [verified, setVerified] = useState(false);

  if (user?.has2FA && !verified) {
    return <TwoFactorModal onVerify={() => setVerified(true)} />;
  }

  return <>{children}</>;
}
```

---

**Ubicación**: `/frontend/src/middleWare/`  
**Tecnologías**: React Router v7, React Context API, JWT Decode  
**Documentación relacionada**: 
- `../Context/AuthContext.tsx` - Proveedor de autenticación
- `/backend/auth.js` - Middleware de autenticación del servidor
- `../App.tsx` - Configuración de rutas
