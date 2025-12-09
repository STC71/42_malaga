# 🔗 Blockchain Integration Guide

Este proyecto utiliza **Avalanche Fuji Testnet** para almacenar torneos de forma inmutable en blockchain.

---

## 🎯 ¿Qué se Almacena en Blockchain?

Cada torneo registra:

- **Nombre del torneo**
- **Jugadores** (4, 8, 12 o 16 participantes)
- **Fecha de inicio** y **finalización**
- **Campeón** (ganador)
- **Puntuaciones finales** de todos los jugadores
- **Estado** (activo/finalizado)

Todo queda **permanentemente registrado** y es verificable públicamente.

---

## 🔧 Setup para Evaluadores

### **PASO 1: Obtener Private Key**

#### **Opción A: Crear Nueva Wallet (Recomendado)**

1. Ir a [Core Wallet](https://core.app/)
2. Click en **"Create New Wallet"**
3. Guardar la frase de recuperación (12 palabras)
4. Una vez dentro, ir a **Settings** → **Show Private Key**
5. Copiar la private key (empieza con `0x`)

#### **Opción B: Usar Wallet Existente**

1. Abrir [Core Wallet](https://core.app/)
2. Importar tu wallet con la frase de recuperación
3. Ir a **Settings** → **Show Private Key**
4. Copiar la private key

⚠️ **IMPORTANTE:** Esta wallet es solo para **testnet**. NO usar wallets con fondos reales.

---

### **PASO 2: Conseguir AVAX Testnet (Gratis)**

1. Copiar tu **dirección de wallet** (0x...) desde Core
2. Ir a [Avalanche Faucet](https://faucet.avax.network/)
3. Seleccionar **"Fuji Testnet"**
4. Pegar tu dirección
5. Completar el captcha
6. Click en **"Request 2 AVAX"**
7. Esperar ~30 segundos

**Verificar fondos:**
- Ir a [Snowtrace Fuji](https://testnet.snowtrace.io/)
- Buscar tu dirección
- Deberías ver **2 AVAX**

💰 **2 AVAX testnet = ~400 transacciones**

---

### **PASO 3: Configurar `.env`**

```bash
# Editar
nano srcs/secrets/.env
```

**Reemplazar:**

```env
# ANTES:
PRIVATE_KEY=your-private-key

# DESPUÉS:
PRIVATE_KEY=0xTU_PRIVATE_KEY_DE_CORE_WALLET_AQUI
```

**Ejemplo (NO usar esta):**

```env
PRIVATE_KEY=0xabc123def456789012345678901234567890123456789012345678901234567890
```

⚠️ **NUNCA subir tu `.env` a Git.**

---

### **PASO 4: Levantar Proyecto**

```bash
# Construir e iniciar
make

# O manualmente:
docker-compose up -d --build
```

---

### **PASO 5: Verificar Blockchain**

```bash
# Ver logs de inicialización
docker logs transcendence-backend | grep -A 10 "Blockchain"

# Deberías ver:
# 🔗 Initializing Blockchain Service...
# ✅ Contract Address: 0x7bEd67Bf730941761680600c12429f67d12e2c7E
# 👤 Wallet Address: 0xTU_WALLET...
# ✅ Blockchain Service initialized successfully!
# 💰 Wallet Balance: 2.0 AVAX
```

---

## 🎮 Uso del Sistema

### **1. Crear Torneo**

1. Login en la web: http://localhost:2323
2. Ir a **Tournaments** → **Create Tournament**
3. Ingresar nombre y seleccionar número de jugadores: **4, 8, 12 o 16**
4. Click en **Create**

---

### **2. Finalizar Torneo**

1. Jugar el torneo (Pong)
2. Al finalizar, se registran scores automáticamente
3. Click en **Finalize Tournament**

**Qué sucede:**
- Se envía otra transacción con:
  - Campeón (ganador)
  - Scores finales
  - Timestamp de finalización

---

### **3. Ver Historial**

1. Ir a **Tournaments** → **View History**
2. Ver todos los torneos con:
   - ✅ Estado (Activo/Finalizado)
   - 🏆 Campeón
   - 📊 Puntuaciones
   - 🔗 Link a Snowtrace

---

## 🔍 Verificar Transacciones en Snowtrace

### **Ver Contrato Completo:**

```
https://testnet.snowtrace.io/address/0x7bEd67Bf730941761680600c12429f67d12e2c7E
```

**Podrás ver:**
- Todas las transacciones del contrato
- Eventos emitidos (TournamentRegistered, TournamentFinalized)
- Balance del contrato
- Código fuente verificado

---

### **Ver Transacción Específica:**

Cada torneo muestra un link como:

```
https://testnet.snowtrace.io/tx/0xabc123...
```

**Información disponible:**
- Quién envió la transacción (tu wallet)
- Gas usado (costo)
- Input data (datos del torneo)
- Logs (eventos emitidos)

---

## 🆕 (Opcional) Desplegar Tu Propio Contrato

Si quieres experimentar desplegando un nuevo contrato:

```bash
# 1. Entrar al contenedor
docker exec -it transcendence-backend bash

# 2. Ir a carpeta de Hardhat
cd /app/blockchain/hardhat

# 3. Compilar contratos
npx hardhat compile

# 4. Desplegar en Fuji testnet
npx hardhat run scripts/deploy.js --network fuji

# Ejemplo de output:
# Deploying TournamentRegistry...
# TournamentRegistry deployed to: 0xNUEVA_DIRECCION
# Saved to contract-address.json

# 5. Salir del contenedor
exit

# 6. Actualizar .env con la nueva dirección
nano srcs/secrets/.env
# AVALANCHE_CONTRACT_ADDRESS=0xNUEVA_DIRECCION

# 7. Reiniciar backend
docker restart transcendence-backend
```

**Costo aproximado:** 0.05 AVAX (testnet)

---

## 📊 Estructura del Smart Contract

El contrato `TournamentRegistry.sol` soporta torneos de **tamaño variable** (4, 8, 12, 16 jugadores) usando arrays dinámicos.

### **Función: `registerTournament`**

```solidity
function registerTournament(
    string memory _name,
    address[] memory _players,      // ✅ Array dinámico (4, 8, 12, 16...)
    string[] memory _aliases        // ✅ Array dinámico
) public returns (uint256)
```

**Parámetros:**
- `_name`: Nombre del torneo
- `_players`: Array de direcciones (tamaño flexible)
- `_aliases`: Array de aliases correspondientes

**Validaciones:**
- ✅ Mínimo 2 jugadores
- ✅ Mismo número de players y aliases
- ✅ Nombre no vacío

**Retorna:** ID único del torneo (recordId)

**Ejemplo de uso:**

```javascript
// Torneo de 4 jugadores
await contract.registerTournament(
    "Finals 2024",
    ["0xabc...", "0xdef...", "0x123...", "0x456..."],
    ["Alice", "Bob", "Carol", "Dave"]
);

// Torneo de 8 jugadores
await contract.registerTournament(
    "Grand Championship",
    ["0x1...", "0x2...", "0x3...", "0x4...", "0x5...", "0x6...", "0x7...", "0x8..."],
    ["P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8"]
);
```

---

### **Función: `finalizeTournament`**

```solidity
function finalizeTournament(
    uint256 _recordId,
    address _champion,
    uint256[] memory _scores         // ✅ Array dinámico (debe coincidir con número de jugadores)
) public
```

**Parámetros:**
- `_recordId`: ID del torneo a finalizar
- `_champion`: Dirección del ganador
- `_scores`: Array de puntuaciones (mismo tamaño que jugadores)

**Validaciones:**
- ✅ El torneo existe
- ✅ No está ya finalizado
- ✅ El campeón está en la lista de jugadores
- ✅ El número de scores coincide con el número de jugadores

**Ejemplo de uso:**

```javascript
// Finalizar torneo de 4 jugadores
await contract.finalizeTournament(
    0,                    // recordId
    "0xabc...",          // champion
    [100, 80, 60, 40]    // scores de 4 jugadores
);

// Finalizar torneo de 8 jugadores
await contract.finalizeTournament(
    1,
    "0x123...",
    [150, 140, 130, 120, 110, 100, 90, 80]  // scores de 8 jugadores
);
```

---

### **Función: `getTournamentRecord`**

```solidity
function getTournamentRecord(uint256 _recordId) 
    public view returns (
        uint256 recordId,
        string memory tournamentName,
        uint256 startTime,
        uint256 endTime,
        address champion,
        address[] memory players,    // ✅ Array dinámico
        uint256[] memory scores,     // ✅ Array dinámico
        string[] memory aliases,     // ✅ Array dinámico
        bool isFinalized
    )
```

**Retorna:** Todos los datos del torneo con arrays de tamaño variable

---

### **Otras Funciones Útiles:**

#### **`getTotalRecords()`**
```solidity
function getTotalRecords() public view returns (uint256)
```
Retorna el número total de torneos registrados.

---

#### **`isPlayerInTournament()`**
```solidity
function isPlayerInTournament(uint256 _recordId, address _player) 
    public view returns (bool)
```
Verifica si un jugador participó en un torneo específico.

---

#### **`getPlayerHistory()`**
```solidity
function getPlayerHistory(address _player) 
    public view returns (uint256[] memory)
```
Retorna todos los IDs de torneos en los que participó un jugador.

---

#### **`getPlayerStats()`**
```solidity
function getPlayerStats(address _player) 
    public view returns (uint256 wins, uint256 totalParticipations)
```
Retorna estadísticas del jugador:
- `wins`: Número de torneos ganados
- `totalParticipations`: Total de participaciones

---

## 💾 Estructura de Datos

### **TournamentRecord (Struct)**

```solidity
struct TournamentRecord {
    uint256 recordId;           // ID único incremental
    string tournamentName;      // Nombre del torneo
    uint256 startTime;          // Timestamp de inicio (Unix)
    uint256 endTime;            // Timestamp de finalización
    address champion;           // Dirección del ganador
    address[] players;          // Array dinámico de jugadores
    uint256[] finalScores;      // Array dinámico de scores
    string[] playerAliases;     // Array dinámico de aliases
    bool isFinalized;           // true = finalizado, false = activo
}
```

**Características:**
- ✅ Soporta cualquier número de jugadores (mínimo 2)
- ✅ Todos los arrays tienen el mismo tamaño
- ✅ Inmutable una vez finalizado

---

## 🛠️ Troubleshooting

### **Error: "Insufficient funds for gas"**

**Solución:**

```bash
# Verificar balance
docker logs transcendence-backend | grep "Wallet Balance"

# Si es < 0.1 AVAX:
# 1. Ir a https://faucet.avax.network/
# 2. Solicitar más AVAX
# 3. Esperar 30 segundos
```

---

### **Error: "Contract not found"**

**Verificar:**

```bash
# 1. Ver dirección configurada
cat srcs/secrets/.env | grep AVALANCHE_CONTRACT_ADDRESS

# 2. Verificar que existe en Snowtrace
# Ir a: https://testnet.snowtrace.io/address/0x7bEd67...

# 3. Ver logs del backend
docker logs transcendence-backend | grep "Contract Address"
```

---

## 📚 Recursos Adicionales

### **Documentación:**

- [Avalanche Docs](https://docs.avax.network/)
- [Core Wallet](https://support.avax.network/en/collections/3391501-core-extension)
- [Hardhat Docs](https://hardhat.org/docs)
- [ethers.js Docs](https://docs.ethers.org/v6/)

### **Exploradores:**

- [Snowtrace Fuji (Testnet)](https://testnet.snowtrace.io/)
- [Avalanche Subnet Explorer](https://subnets-test.avax.network/)

### **Faucets:**

- [Avalanche Faucet](https://faucet.avax.network/)

---

## 🔐 Seguridad

### **✅ Buenas Prácticas:**

- ✅ Usar wallet separada para testnet
- ✅ NUNCA compartir tu PRIVATE_KEY
- ✅ Mantener `.env` en `.gitignore`

### **❌ NUNCA Hacer:**

- ❌ Subir `.env` a Git/GitHub
- ❌ Compartir tu PRIVATE_KEY en Discord/Slack
- ❌ Usar la misma wallet para testnet y mainnet
- ❌ Hardcodear la PRIVATE_KEY en el código

---

## 💡 Private Key de Evaluación (Solo para Testing)

Para la evaluación del proyecto usaremos una wallet de prueba preconfigurada:

**⚠️ WALLET DE PRUEBA (SOLO TESTNET):**

```env
PRIVATE_KEY=0xff1398467c95516f50d92765216109dca4f29246092eedb50bcce7a31aaabb46
```

**Dirección:** `0xD9950cA607D5959ba47243Bd887c506e582B077D`

**⚠️ ADVERTENCIA:**
- Esta private key es **PÚBLICA** en este documento
- Solo tiene fondos de **testnet** (sin valor real)
- Cualquiera puede usarla
- **NO usar para almacenar nada importante**
