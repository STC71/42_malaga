# ⚡ Hardhat - Entorno de Desarrollo Blockchain

## 📋 Descripción General

Este directorio contiene el **proyecto Hardhat** completo para el desarrollo, testing y despliegue del smart contract `TournamentRegistry` en redes compatibles con Avalanche.

**Hardhat** es un entorno de desarrollo profesional para Ethereum y blockchains compatibles con EVM, proporcionando herramientas para compilar, desplegar, probar y depurar smart contracts.

## 🗂️ Estructura del Proyecto

```
hardhat/
├── hardhat.config.js         # Configuración principal de Hardhat
├── package.json              # Dependencias y scripts npm
├── contract-address.json     # Info del contrato desplegado (generado)
├── contracts/                # Smart contracts Solidity
│   └── TournamentRegistry.sol
├── scripts/                  # Scripts de despliegue y utilidades
│   └── deploy.js
├── artifacts/                # Compilados del contrato (generado)
│   ├── build-info/          # Metadata de compilación
│   └── contracts/           # ABIs y bytecode
└── cache/                    # Cache de Hardhat (generado)
    └── solidity-files-cache.json
```

## 🚀 Tecnologías y Dependencias

### Core
- **Hardhat 2.19.4** - Framework de desarrollo blockchain
- **@nomicfoundation/hardhat-toolbox 4.0.0** - Suite completa de herramientas

### Toolbox incluye:
- **ethers.js v6** - Librería para interactuar con Ethereum
- **Hardhat Chai Matchers** - Assertions para testing
- **Hardhat Network Helpers** - Utilidades para testing
- **Hardhat Verify** - Verificación automática en exploradores
- **Solidity Coverage** - Cobertura de tests
- **TypeScript** - Soporte para TypeScript

## ⚙️ Configuración (hardhat.config.js)

```javascript
{
  solidity: "0.8.19",           // Versión de Solidity
  networks: {
    fuji: {                     // Avalanche Fuji Testnet
      url: "https://api.avax-test.network/ext/bc/C/rpc",
      chainId: 43113,
      accounts: [PRIVATE_KEY]   // Cargada desde .env
    },
    hardhat: {                  // Red local para testing
      chainId: 31337
    },
    localhost: {                // Nodo local de Hardhat
      url: "http://127.0.0.1:8545"
    }
  }
}
```

### Variables de Entorno Requeridas

Ubicación: `/sgoinfre/students/sternero/transcendence/srcs/secrets/.env`

```bash
# Clave privada de la wallet (¡NUNCA hacer commit!)
PRIVATE_KEY=0x...

# RPC URL de Avalanche Fuji (opcional, usa default si no está)
AVALANCHE_RPC_URL=https://api.avax-test.network/ext/bc/C/rpc
```

## 📦 Scripts Disponibles

```bash
# Compilar contratos
npm run compile
# → Compila TournamentRegistry.sol
# → Genera artifacts/ y cache/

# Desplegar en red local
npm run deploy
# → Despliega en localhost (hardhat node)

# Desplegar en Hardhat Network
npm run deploy:hardhat
# → Despliega en red de testing efímera

# Iniciar nodo local
npm run node
# → Levanta blockchain local en 0.0.0.0:8545
# → Útil para desarrollo y testing

# Ejecutar tests
npm run test
# → Ejecuta test suite (si existen tests)

# Limpiar artifacts
npm run clean
# → Elimina artifacts/ y cache/
```

## 🔧 Uso Práctico

### 1. Compilar el Contrato

```bash
cd backend/blockchain/hardhat
npm install
npm run compile
```

**Output esperado:**
```
Compiled 1 Solidity file successfully
```

**Archivos generados:**
- `artifacts/contracts/TournamentRegistry.sol/TournamentRegistry.json` - ABI + bytecode
- `cache/solidity-files-cache.json` - Cache de compilación

### 2. Desplegar en Red Local (Desarrollo)

**Terminal 1 - Iniciar nodo:**
```bash
npm run node
```

**Terminal 2 - Desplegar:**
```bash
npm run deploy
```

**Output esperado:**
```
🚀 Deploying TournamentRegistry to Avalanche Fuji...
📡 Network: localhost
⛓️  Chain ID: 31337
👤 Deploying with account: 0x...
💰 Account balance: 10000.0 AVAX
✅ TournamentRegistry deployed to: 0x5FbDB2315678afecb367f032d93F642f64180aa3
📝 Contract info saved to: contract-address.json
```

### 3. Desplegar en Avalanche Fuji Testnet

**Prerrequisitos:**
1. Tener AVAX en Fuji testnet ([Faucet](https://faucet.avax.network/))
2. Configurar `PRIVATE_KEY` en `.env`

**Comando:**
```bash
npx hardhat run scripts/deploy.js --network fuji
```

**Verificar en Snowtrace:**
```
https://testnet.snowtrace.io/address/<CONTRACT_ADDRESS>
```

### 4. Interactuar con el Contrato (Consola)

```bash
npx hardhat console --network localhost
```

```javascript
const TournamentRegistry = await ethers.getContractFactory("TournamentRegistry");
const registry = await TournamentRegistry.attach("0x5FbDB2...");

// Registrar torneo
const tx = await registry.registerTournament(
  "Summer Tournament 2025",
  ["0xAddress1", "0xAddress2"],
  ["Player1", "Player2"]
);
await tx.wait();

// Leer registro
const record = await registry.getTournament(0);
console.log(record);
```

## 📄 Archivos Generados

### contract-address.json

Generado automáticamente después del despliegue:

```json
{
  "contractAddress": "0x5FbDB2315678afecb367f032d93F642f64180aa3",
  "network": "fuji",
  "chainId": 43113,
  "deployedAt": "2025-12-05T10:30:00.000Z",
  "deployer": "0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb"
}
```

Este archivo es usado por:
- `backend/blockchain/blockchain-service.js` - Para conectar al contrato
- `frontend/src/services/blockchainService.ts` - Para mostrar info

## 🧪 Testing (Opcional)

Crear `test/TournamentRegistry.test.js`:

```javascript
const { expect } = require("chai");
const { ethers } = require("hardhat");

describe("TournamentRegistry", function () {
  it("Should register a tournament", async function () {
    const TournamentRegistry = await ethers.getContractFactory("TournamentRegistry");
    const registry = await TournamentRegistry.deploy();
    
    await registry.registerTournament(
      "Test Tournament",
      [await ethers.getSigner(0).getAddress()],
      ["TestPlayer"]
    );
    
    const record = await registry.getTournament(0);
    expect(record.tournamentName).to.equal("Test Tournament");
  });
});
```

**Ejecutar:**
```bash
npm run test
```

## 🌐 Redes Soportadas

| Red | Chain ID | RPC URL | Explorador |
|-----|----------|---------|------------|
| **Hardhat** | 31337 | http://127.0.0.1:8545 | N/A |
| **Localhost** | 31337 | http://127.0.0.1:8545 | N/A |
| **Avalanche Fuji** | 43113 | https://api.avax-test.network/ext/bc/C/rpc | [Snowtrace Testnet](https://testnet.snowtrace.io) |

## 🔍 Troubleshooting

### Error: "Account has no AVAX"

**Solución:**
- Obtener AVAX de prueba en [Fuji Faucet](https://faucet.avax.network/)
- Verificar que `PRIVATE_KEY` en `.env` sea correcta

### Error: "Cannot find module 'hardhat'"

**Solución:**
```bash
npm install
```

### Error: "Invalid private key"

**Solución:**
- Verificar formato: debe empezar con `0x` y tener 66 caracteres
- Verificar que `.env` esté en `/srcs/secrets/.env`

### Compilación lenta

**Solución:**
```bash
npm run clean  # Limpia cache
npm run compile
```

## 📚 Documentación Relacionada

- [Smart Contract TournamentRegistry](./contracts/README.md) - Documentación del contrato Solidity
- [Scripts de Despliegue](./scripts/README.md) - Documentación de deploy.js
- [Blockchain Service](../README.md) - Servicio backend de blockchain

## 🔗 Enlaces Útiles

- [Hardhat Docs](https://hardhat.org/docs)
- [Avalanche Docs](https://docs.avax.network/)
- [Snowtrace (Explorer)](https://snowtrace.io/)
- [Fuji Faucet](https://faucet.avax.network/)
- [ethers.js v6 Docs](https://docs.ethers.org/v6/)

## 🤝 Equipo de Desarrollo

- **davigome** - Arquitectura blockchain
- **jesopan-** - Integración backend
- **nporras-** - Smart contract development
- **rdel-olm** - Testing y deployment
- **sternero** - DevOps y configuración

---

**⚡ Hardhat Project** - TournamentRegistry Smart Contract  
*Última actualización: Diciembre 2025*
