# 📜 Smart Contracts - TournamentRegistry

## 📋 Descripción General

Este directorio contiene el **smart contract Solidity** `TournamentRegistry.sol`, que implementa un sistema de registro inmutable de torneos en blockchain compatible con Avalanche.

## 📄 Archivo Principal

```
contracts/
└── TournamentRegistry.sol    # Contrato principal (236 líneas)
```

## 🎯 Propósito del Contrato

El contrato `TournamentRegistry` proporciona:

- ✅ **Registro Inmutable** - Los resultados de torneos no pueden ser modificados
- ✅ **Transparencia** - Cualquiera puede verificar resultados históricos
- ✅ **Trazabilidad** - Eventos blockchain para auditoría completa
- ✅ **Descentralización** - No depende de autoridades centrales

## 🏗️ Estructura del Contrato

### Datos Almacenados (Struct)

```solidity
struct TournamentRecord {
    uint256 recordId;           // ID único incremental
    string tournamentName;      // Nombre del torneo
    uint256 startTime;          // Timestamp de inicio (block.timestamp)
    uint256 endTime;            // Timestamp de finalización
    address champion;           // Dirección del ganador
    address[] players;          // Addresses de participantes
    uint256[] finalScores;      // Puntuaciones finales
    string[] playerAliases;     // Aliases/nombres de jugadores
    bool isFinalized;           // true = torneo completado
}
```

### State Variables

```solidity
// Mapeo de ID → Registro completo
mapping(uint256 => TournamentRecord) private tournamentRecords;

// Contador global de torneos
uint256 private recordCounter;
```

### Eventos

```solidity
event TournamentRegistered(
    uint256 indexed recordId,
    string tournamentName,
    uint256 timestamp,
    address indexed registeredBy
);

event TournamentFinalized(
    uint256 indexed recordId,
    address indexed champion,
    uint256 timestamp
);
```

## 🔧 Funciones Públicas

### 1. `registerTournament`

**Propósito:** Registra un nuevo torneo en la blockchain.

```solidity
function registerTournament(
    string memory _name,
    address[] memory _players,
    string[] memory _aliases
) public returns (uint256 newRecordId)
```

**Parámetros:**
- `_name` - Nombre del torneo (ej: "Summer Cup 2025")
- `_players` - Array de direcciones Ethereum de los jugadores
- `_aliases` - Array de aliases/nicknames (debe coincidir con `_players`)

**Retorna:**
- `newRecordId` - ID del registro creado

**Validaciones:**
- ✅ Nombre no vacío
- ✅ Mínimo 2 jugadores
- ✅ Longitud de `_players` == longitud de `_aliases`

**Eventos Emitidos:**
- `TournamentRegistered`

**Ejemplo de Uso:**
```javascript
const tx = await registry.registerTournament(
    "Christmas Tournament 2025",
    ["0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb", "0x8626f6940E2eb28930eFb4CeF49B2d1F2C9C1199"],
    ["Alice", "Bob"]
);
await tx.wait();
```

### 2. `finalizeTournament`

**Propósito:** Marca un torneo como finalizado y registra el ganador.

```solidity
function finalizeTournament(
    uint256 _recordId,
    address _champion,
    uint256[] memory _finalScores
) public
```

**Parámetros:**
- `_recordId` - ID del torneo a finalizar
- `_champion` - Dirección del ganador
- `_finalScores` - Puntuaciones finales de todos los jugadores

**Validaciones:**
- ✅ El torneo existe
- ✅ No está ya finalizado
- ✅ El campeón está entre los jugadores registrados
- ✅ Longitud de `_finalScores` coincide con número de jugadores

**Eventos Emitidos:**
- `TournamentFinalized`

**Ejemplo de Uso:**
```javascript
await registry.finalizeTournament(
    0,  // recordId
    "0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb",  // winner
    [100, 75]  // scores
);
```

### 3. `getTournament`

**Propósito:** Obtiene la información completa de un torneo.

```solidity
function getTournament(uint256 _recordId) 
    public 
    view 
    returns (TournamentRecord memory)
```

**Parámetros:**
- `_recordId` - ID del torneo a consultar

**Retorna:**
- Struct `TournamentRecord` completo

**Ejemplo de Uso:**
```javascript
const record = await registry.getTournament(0);
console.log("Tournament:", record.tournamentName);
console.log("Winner:", record.champion);
console.log("Players:", record.players);
```

### 4. `getAllTournaments`

**Propósito:** Obtiene todos los torneos registrados.

```solidity
function getAllTournaments() 
    public 
    view 
    returns (TournamentRecord[] memory)
```

**Retorna:**
- Array con todos los registros de torneos

**Nota:** ⚠️ Esta función puede ser costosa en gas si hay muchos torneos. Usar con precaución.

**Ejemplo de Uso:**
```javascript
const allTournaments = await registry.getAllTournaments();
console.log(`Total tournaments: ${allTournaments.length}`);
```

### 5. `getTournamentCount`

**Propósito:** Obtiene el número total de torneos registrados.

```solidity
function getTournamentCount() 
    public 
    view 
    returns (uint256)
```

**Retorna:**
- Contador de torneos (uint256)

**Ejemplo de Uso:**
```javascript
const count = await registry.getTournamentCount();
console.log(`Total tournaments: ${count}`);
```

### 6. `getPlayerTournaments`

**Propósito:** Obtiene todos los torneos en los que participó un jugador.

```solidity
function getPlayerTournaments(address _player) 
    public 
    view 
    returns (uint256[] memory)
```

**Parámetros:**
- `_player` - Dirección del jugador

**Retorna:**
- Array de IDs de torneos

**Ejemplo de Uso:**
```javascript
const myAddress = "0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb";
const myTournaments = await registry.getPlayerTournaments(myAddress);
console.log(`Participated in ${myTournaments.length} tournaments`);
```

### 7. `getPlayerStats`

**Propósito:** Obtiene estadísticas agregadas de un jugador.

```solidity
function getPlayerStats(address _player) 
    public 
    view 
    returns (
        uint256 totalTournaments,
        uint256 tournamentsWon,
        uint256 totalScore
    )
```

**Parámetros:**
- `_player` - Dirección del jugador

**Retorna:**
- `totalTournaments` - Torneos jugados
- `tournamentsWon` - Torneos ganados
- `totalScore` - Puntuación acumulada total

**Ejemplo de Uso:**
```javascript
const [total, won, score] = await registry.getPlayerStats(playerAddress);
console.log(`Win Rate: ${(won/total*100).toFixed(1)}%`);
console.log(`Total Score: ${score}`);
```

## 🔐 Seguridad

### Modificadores y Validaciones

```solidity
// ✅ Validación de entrada
require(bytes(_name).length > 0, "Tournament name required");
require(_players.length >= 2, "Minimum 2 players required");

// ✅ Verificación de estado
require(!tournamentRecords[_recordId].isFinalized, "Tournament already finalized");

// ✅ Validación de participante
bool isValidChampion = false;
for (uint256 i = 0; i < players.length; i++) {
    if (players[i] == _champion) {
        isValidChampion = true;
        break;
    }
}
require(isValidChampion, "Champion must be a registered player");
```

### Consideraciones de Gas

| Operación | Gas Estimado | Optimización |
|-----------|--------------|--------------|
| `registerTournament` | ~150k - 300k | Depende del # de jugadores |
| `finalizeTournament` | ~100k - 200k | Depende del # de scores |
| `getTournament` (view) | 0 gas | Solo lectura |
| `getAllTournaments` (view) | 0 gas | Puede ser lento con muchos datos |
| `getPlayerStats` | 0 gas | Loop optimizado |

### Limitaciones Conocidas

1. **getAllTournaments()** puede fallar con muchos torneos (límite de gas)
   - **Solución:** Usar paginación o índices específicos

2. **No hay modificación de registros** (by design)
   - Los torneos finalizados son inmutables
   - Si hay error, debe registrarse un nuevo torneo

3. **No hay control de acceso** (cualquiera puede registrar)
   - Considerado feature (descentralizado)
   - Backend debe validar antes de escribir

## 🧪 Testing

### Casos de Prueba Recomendados

```javascript
describe("TournamentRegistry", function () {
  it("Should register a tournament with 2 players", async () => {
    // Test básico de registro
  });

  it("Should finalize tournament correctly", async () => {
    // Test de finalización
  });

  it("Should revert if champion is not a player", async () => {
    // Test de validación
  });

  it("Should track player stats correctly", async () => {
    // Test de estadísticas
  });

  it("Should emit events correctly", async () => {
    // Test de eventos
  });
});
```

## 📊 Integración con Backend

El backend interactúa con este contrato a través de:

```
backend/blockchain/blockchain-service.js
```

**Flujo de integración:**
1. Usuario crea torneo en frontend
2. Backend valida datos
3. Backend llama `registerTournament()` en el contrato
4. Blockchain emite evento `TournamentRegistered`
5. Backend guarda `recordId` en base de datos
6. Cuando torneo termina → `finalizeTournament()`

## 🔗 Versión de Solidity

```solidity
// SPDX-License-Identifier: MIT
pragma solidity ^0.8.19;
```

**Características usadas:**
- Solidity 0.8.19 (última estable compatible)
- String memory para gas efficiency
- Arrays dinámicos en memoria
- Structs complejos
- Eventos indexados para búsqueda rápida

## 📚 Documentación Relacionada

- [Hardhat Project](../README.md) - Configuración del entorno
- [Deploy Scripts](../scripts/README.md) - Scripts de despliegue
- [Blockchain Service](../../README.md) - Servicio backend

## 🔗 Enlaces Útiles

- [Solidity Docs](https://docs.soliditylang.org/)
- [OpenZeppelin Contracts](https://docs.openzeppelin.com/contracts/)
- [Avalanche C-Chain](https://docs.avax.network/learn/avalanche/avalanche-platform)
- [Ethers.js ABI Encoding](https://docs.ethers.org/v6/api/abi/)

## 🤝 Equipo de Desarrollo

- **nporras-** - Smart contract lead
- **davigome** - Blockchain architecture
- **rdel-olm** - Testing & auditing
- **jesopan-** - Backend integration
- **sternero** - Deployment automation

---

**📜 TournamentRegistry Smart Contract** - Versión 1.0.0  
*Última actualización: Diciembre 2025*
