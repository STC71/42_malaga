# 🔌 Services - Capa de Servicios del Frontend

## 📋 Descripción General

Este directorio contiene la **capa de servicios** del frontend, que abstrae toda la comunicación con el backend y servicios externos. Proporciona interfaces TypeScript tipadas para consumir APIs REST, WebSockets y servicios blockchain.

## 📄 Archivo Principal

```
services/
└── blockchainService.ts    # Servicio de comunicación con blockchain (62 líneas)
```

## 🎯 Arquitectura de Servicios

### Patrón de Diseño

Los servicios siguen el patrón **Service Layer**:

```
Frontend Components
       ↓
   Services Layer  ← (ESTAMOS AQUÍ)
       ↓
   Backend API
       ↓
   Database / Blockchain
```

**Ventajas:**
- ✅ **Separación de Responsabilidades** - Lógica de negocio separada de UI
- ✅ **Reutilización** - Mismos servicios usados por múltiples componentes
- ✅ **Testabilidad** - Fácil de mockear en tests
- ✅ **Tipado TypeScript** - Interfaces para requests/responses
- ✅ **Mantenibilidad** - Cambios de API centralizados

## 📦 blockchainService.ts

### Propósito

Proporciona métodos para interactuar con el **módulo blockchain** del backend, consultando información de torneos registrados en la blockchain de Avalanche.

### Interfaces TypeScript

```typescript
export interface Tournament {
    recordId: string;           // ID del registro en blockchain
    tournamentName: string;     // Nombre del torneo
    players: string[];          // Direcciones Ethereum de jugadores
    aliases: string[];          // Nicknames de jugadores
    champion: string;           // Dirección del ganador
    scores: string[];           // Puntuaciones finales
    timestamp: string;          // Timestamp de registro
    isFinalized: boolean;       // true = torneo completado
}

export interface PlayerStats {
    totalTournaments: string;   // Torneos jugados
    tournamentsWon: string;     // Torneos ganados
    totalScore: string;         // Puntuación total acumulada
}

export interface BlockchainStatus {
    status: string;             // "connected" | "disconnected"
    network: string;            // "fuji" | "localhost"
    contractAddress: string;    // Dirección del smart contract
    wallet: string;             // Dirección de la wallet del backend
    snowtraceUrl: string;       // URL al explorador blockchain
}
```

### Métodos Disponibles

#### 1. `getStatus()`

**Propósito:** Obtiene el estado de la conexión blockchain.

```typescript
async getStatus(): Promise<BlockchainStatus>
```

**Uso:**
```typescript
import { blockchainService } from '@/services/blockchainService';

const status = await blockchainService.getStatus();
console.log(`Connected to ${status.network}`);
console.log(`Contract: ${status.contractAddress}`);
```

**Endpoint Backend:**
```
GET /api/blockchain/status
```

**Response Ejemplo:**
```json
{
  "status": "connected",
  "network": "fuji",
  "contractAddress": "0x8A791620dd6260079BF849Dc5567aDC3F2FdC318",
  "wallet": "0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb",
  "snowtraceUrl": "https://testnet.snowtrace.io/address/0x8A791620..."
}
```

#### 2. `getAllTournaments()`

**Propósito:** Obtiene todos los torneos registrados en blockchain.

```typescript
async getAllTournaments(): Promise<Tournament[]>
```

**Uso:**
```typescript
const tournaments = await blockchainService.getAllTournaments();
console.log(`Total tournaments: ${tournaments.length}`);

tournaments.forEach(t => {
  console.log(`${t.tournamentName}: ${t.isFinalized ? 'Finished' : 'In Progress'}`);
});
```

**Endpoint Backend:**
```
GET /api/blockchain/tournaments
```

**Response Ejemplo:**
```json
{
  "tournaments": [
    {
      "recordId": "0",
      "tournamentName": "Summer Cup 2025",
      "players": ["0x742d...", "0x8626..."],
      "aliases": ["Alice", "Bob"],
      "champion": "0x742d...",
      "scores": ["100", "75"],
      "timestamp": "2025-06-15T10:00:00Z",
      "isFinalized": true
    }
  ]
}
```

#### 3. `getTournament(id)`

**Propósito:** Obtiene información de un torneo específico.

```typescript
async getTournament(id: string): Promise<Tournament>
```

**Parámetros:**
- `id` - ID del registro en blockchain (string)

**Uso:**
```typescript
const tournament = await blockchainService.getTournament("0");
console.log(`Winner: ${tournament.champion}`);
console.log(`Scores: ${tournament.scores.join(', ')}`);
```

**Endpoint Backend:**
```
GET /api/blockchain/tournaments/:id
```

#### 4. `getPlayerStats(alias)`

**Propósito:** Obtiene estadísticas agregadas de un jugador.

```typescript
async getPlayerStats(alias: string): Promise<PlayerStats>
```

**Parámetros:**
- `alias` - Nickname del jugador

**Uso:**
```typescript
const stats = await blockchainService.getPlayerStats("Alice");
console.log(`Tournaments played: ${stats.totalTournaments}`);
console.log(`Tournaments won: ${stats.tournamentsWon}`);
console.log(`Total score: ${stats.totalScore}`);

const winRate = (parseInt(stats.tournamentsWon) / parseInt(stats.totalTournaments)) * 100;
console.log(`Win rate: ${winRate.toFixed(1)}%`);
```

**Endpoint Backend:**
```
GET /api/blockchain/player/:alias/stats
```

**Response Ejemplo:**
```json
{
  "totalTournaments": "5",
  "tournamentsWon": "3",
  "totalScore": "450"
}
```

### Manejo de Errores

Todos los métodos lanzan excepciones en caso de error:

```typescript
try {
  const tournaments = await blockchainService.getAllTournaments();
  // Procesar torneos...
} catch (error) {
  console.error('Failed to fetch tournaments:', error);
  // Mostrar mensaje de error al usuario
}
```

**Errores Comunes:**
- `Failed to fetch blockchain status` - Backend no disponible
- `Failed to fetch tournaments` - Blockchain desconectado
- `Failed to fetch player stats` - Jugador no encontrado

## 🔄 Integración con Componentes

### Ejemplo: Componente de Torneos

```typescript
// Components/Tournaments.tsx
import React, { useEffect, useState } from 'react';
import { blockchainService, Tournament } from '@/services/blockchainService';

export const Tournaments: React.FC = () => {
  const [tournaments, setTournaments] = useState<Tournament[]>([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    const loadTournaments = async () => {
      try {
        const data = await blockchainService.getAllTournaments();
        setTournaments(data);
      } catch (err) {
        setError('Failed to load tournaments');
        console.error(err);
      } finally {
        setLoading(false);
      }
    };

    loadTournaments();
  }, []);

  if (loading) return <div>Loading...</div>;
  if (error) return <div>Error: {error}</div>;

  return (
    <div>
      <h2>Blockchain Tournaments</h2>
      {tournaments.map(t => (
        <div key={t.recordId}>
          <h3>{t.tournamentName}</h3>
          <p>Status: {t.isFinalized ? '✅ Finished' : '⏳ In Progress'}</p>
          {t.isFinalized && <p>Champion: {t.champion}</p>}
        </div>
      ))}
    </div>
  );
};
```

## 🚀 Servicios Futuros (Expandible)

Este directorio puede crecer con más servicios:

```
services/
├── blockchainService.ts     # Actual
├── authService.ts           # Autenticación y sesiones
├── chatService.ts           # WebSocket chat
├── gameService.ts           # WebSocket juego
├── userService.ts           # CRUD de usuarios
├── tournamentService.ts     # CRUD de torneos (DB)
├── matchService.ts          # Matchmaking
├── profileService.ts        # Perfiles y estadísticas
├── friendService.ts         # Sistema de amigos
└── uploadService.ts         # Subida de avatares
```

### Template para Nuevos Servicios

```typescript
// services/exampleService.ts

const API_URL = `${window.location.origin}/api/example`;

export interface ExampleData {
    id: string;
    name: string;
}

export const exampleService = {
    async getAll(): Promise<ExampleData[]> {
        const response = await fetch(`${API_URL}`, {
            headers: { 'Accept': 'application/json' }
        });
        if (!response.ok) {
            throw new Error('Failed to fetch data');
        }
        return response.json();
    },

    async getById(id: string): Promise<ExampleData> {
        const response = await fetch(`${API_URL}/${id}`, {
            headers: { 'Accept': 'application/json' }
        });
        if (!response.ok) {
            throw new Error('Failed to fetch data');
        }
        return response.json();
    },

    async create(data: Omit<ExampleData, 'id'>): Promise<ExampleData> {
        const response = await fetch(`${API_URL}`, {
            method: 'POST',
            headers: { 
                'Content-Type': 'application/json',
                'Accept': 'application/json'
            },
            body: JSON.stringify(data)
        });
        if (!response.ok) {
            throw new Error('Failed to create data');
        }
        return response.json();
    }
};
```

## 📝 Convenciones de Código

### Naming Conventions

- ✅ Archivos: `camelCase.ts` (ej: `blockchainService.ts`)
- ✅ Interfaces: `PascalCase` (ej: `Tournament`, `PlayerStats`)
- ✅ Servicios exportados: `camelCase` (ej: `blockchainService`)
- ✅ Métodos: `camelCase` (ej: `getAllTournaments`)

### TypeScript Best Practices

```typescript
// ✅ BIEN: Interfaces exportadas
export interface Tournament { ... }

// ✅ BIEN: Async/await con Promise tipado
async getStatus(): Promise<BlockchainStatus> { ... }

// ✅ BIEN: Headers explícitos
headers: { 'Accept': 'application/json' }

// ❌ MAL: Any types
async getData(): Promise<any> { ... }

// ❌ MAL: Sin manejo de errores
const data = await fetch(url).then(r => r.json());
```

### Headers HTTP

Siempre incluir headers apropiados:

```typescript
// GET requests
headers: { 'Accept': 'application/json' }

// POST/PUT requests
headers: { 
    'Content-Type': 'application/json',
    'Accept': 'application/json'
}

// Con autenticación (si aplica)
headers: { 
    'Accept': 'application/json',
    'Authorization': `Bearer ${token}`
}
```

## 🧪 Testing

### Unit Tests (Ejemplo)

```typescript
// services/__tests__/blockchainService.test.ts
import { blockchainService } from '../blockchainService';

// Mock fetch
global.fetch = jest.fn();

describe('blockchainService', () => {
  beforeEach(() => {
    (fetch as jest.Mock).mockClear();
  });

  it('should fetch blockchain status', async () => {
    (fetch as jest.Mock).mockResolvedValueOnce({
      ok: true,
      json: async () => ({
        status: 'connected',
        network: 'fuji'
      })
    });

    const status = await blockchainService.getStatus();
    expect(status.network).toBe('fuji');
  });

  it('should handle errors', async () => {
    (fetch as jest.Mock).mockResolvedValueOnce({
      ok: false
    });

    await expect(blockchainService.getStatus()).rejects.toThrow();
  });
});
```

## 📚 Documentación Relacionada

- [Frontend README](../../README.md) - Documentación general del frontend
- [Backend API](../../../backend/README.md) - Endpoints del backend
- [Blockchain Service](../../../backend/blockchain/README.md) - Servicio blockchain backend
- [Components](../Components/README.md) - Componentes que usan estos servicios

## 🔗 Enlaces Útiles

- [Fetch API](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API)
- [TypeScript Handbook](https://www.typescriptlang.org/docs/handbook/intro.html)
- [React Query](https://tanstack.com/query/latest) - Librería recomendada para data fetching
- [Axios](https://axios-http.com/) - Alternativa a fetch con más features

## 🤝 Equipo de Desarrollo

- **rdel-olm** - Service layer architecture
- **davigome** - Blockchain service integration
- **jesopan-** - API communication patterns
- **nporras-** - TypeScript interfaces
- **sternero** - Testing & documentation

---

**🔌 Services Layer** - Frontend API Communication  
*Última actualización: Diciembre 2025*
