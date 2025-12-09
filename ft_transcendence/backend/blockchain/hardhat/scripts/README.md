# 🚀 Scripts de Despliegue - Blockchain Deployment

## 📋 Descripción General

Este directorio contiene los **scripts de despliegue** para el smart contract `TournamentRegistry` en redes blockchain compatibles con Avalanche.

## 📄 Archivo Principal

```
scripts/
└── deploy.js    # Script principal de despliegue (56 líneas)
```

## 🎯 Propósito

El script `deploy.js` automatiza el proceso completo de despliegue del contrato:

1. ✅ Valida configuración de red y wallet
2. ✅ Verifica balance de AVAX suficiente
3. ✅ Despliega el contrato `TournamentRegistry`
4. ✅ Espera confirmación en blockchain
5. ✅ Guarda información del despliegue en `contract-address.json`
6. ✅ Muestra enlace a explorador blockchain

## 🔧 Uso del Script

### Desplegar en Localhost (Desarrollo)

**Terminal 1 - Iniciar nodo local:**
```bash
cd backend/blockchain/hardhat
npm run node
```

**Terminal 2 - Desplegar:**
```bash
npm run deploy
# Equivalente a: hardhat run scripts/deploy.js --network localhost
```

### Desplegar en Avalanche Fuji (Testnet)

**Prerrequisitos:**
1. Configurar `PRIVATE_KEY` en `/srcs/secrets/.env`
2. Tener AVAX de prueba (obtener en [Faucet](https://faucet.avax.network/))

**Comando:**
```bash
npx hardhat run scripts/deploy.js --network fuji
```

### Desplegar en Hardhat Network (Testing Efímero)

```bash
npm run deploy:hardhat
# Red de testing efímera, se destruye al terminar
```

## 📊 Output del Script

### Ejemplo de Ejecución Exitosa

```bash
$ npm run deploy

🚀 Deploying TournamentRegistry to Avalanche Fuji...
📡 Network: fuji
⛓️  Chain ID: 43113
👤 Deploying with account: 0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb
💰 Account balance: 2.5 AVAX

📦 Deploying contract...

✅ TournamentRegistry deployed to: 0x8A791620dd6260079BF849Dc5567aDC3F2FdC318
📝 Contract info saved to: /backend/blockchain/hardhat/contract-address.json

🔍 View on Snowtrace:
   https://testnet.snowtrace.io/address/0x8A791620dd6260079BF849Dc5567aDC3F2FdC318

⏳ Wait ~30 seconds for contract to be indexed...

🎉 Deployment completed successfully!

💰 Remaining balance: 2.3 AVAX
```

### Ejemplo con Error (Sin AVAX)

```bash
🚀 Deploying TournamentRegistry to Avalanche Fuji...
📡 Network: fuji
⛓️  Chain ID: 43113
👤 Deploying with account: 0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb
💰 Account balance: 0 AVAX

❌ ERROR: Account has no AVAX
```

## 📄 Archivo Generado: contract-address.json

El script guarda automáticamente la información del despliegue:

**Ubicación:** `backend/blockchain/hardhat/contract-address.json`

**Estructura:**
```json
{
  "contractAddress": "0x8A791620dd6260079BF849Dc5567aDC3F2FdC318",
  "network": "fuji",
  "chainId": 43113,
  "deployedAt": "2025-12-05T10:30:45.123Z",
  "deployer": "0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb"
}
```

### Uso del Archivo

Este JSON es consumido por:

1. **Backend (`blockchain-service.js`)**
   ```javascript
   const contractInfo = JSON.parse(fs.readFileSync('./contract-address.json'));
   const contractAddress = contractInfo.contractAddress;
   ```

2. **Frontend (`blockchainService.ts`)**
   - Muestra dirección del contrato en UI
   - Genera enlaces a Snowtrace

## 🔍 Anatomía del Script

### 1. Importaciones

```javascript
const hre = require("hardhat");        // Hardhat Runtime Environment
const fs = require('fs');              // File system para guardar JSON
const path = require('path');          // Path utilities
```

### 2. Obtención de Configuración

```javascript
const [deployer] = await hre.ethers.getSigners();
console.log("👤 Deploying with account:", deployer.address);

const balance = await hre.ethers.provider.getBalance(deployer.address);
console.log("💰 Account balance:", hre.ethers.formatEther(balance), "AVAX");
```

### 3. Validación de Balance

```javascript
if (balance === 0n) {
  console.error("❌ ERROR: Account has no AVAX");
  process.exit(1);
}
```

**Importante:** El script verifica que haya fondos **antes** de intentar desplegar.

### 4. Despliegue del Contrato

```javascript
const TournamentRegistry = await hre.ethers.getContractFactory("TournamentRegistry");
const registry = await TournamentRegistry.deploy();

await registry.waitForDeployment();  // Espera confirmación en blockchain
const address = await registry.getAddress();
```

**ethers.js v6:** Usa `waitForDeployment()` y `getAddress()` (v5 usaba `deployed()` y `.address`)

### 5. Guardado de Información

```javascript
const deployInfo = {
  contractAddress: address,
  network: hre.network.name,
  chainId: hre.network.config.chainId,
  deployedAt: new Date().toISOString(),
  deployer: deployer.address
};

const outputPath = path.join(__dirname, '..', 'contract-address.json');
fs.writeFileSync(outputPath, JSON.stringify(deployInfo, null, 2));
```

### 6. Enlaces Útiles

```javascript
console.log("🔍 View on Snowtrace:");
console.log(`   https://testnet.snowtrace.io/address/${address}`);
```

## 🌐 Redes Disponibles

| Red | Network Flag | Chain ID | RPC URL |
|-----|--------------|----------|---------|
| **Localhost** | `--network localhost` | 31337 | http://127.0.0.1:8545 |
| **Hardhat** | `--network hardhat` | 31337 | In-memory |
| **Fuji** | `--network fuji` | 43113 | https://api.avax-test.network/ext/bc/C/rpc |

### Configuración en hardhat.config.js

```javascript
networks: {
  localhost: {
    url: "http://127.0.0.1:8545"
  },
  fuji: {
    url: process.env.AVALANCHE_RPC_URL || "https://api.avax-test.network/ext/bc/C/rpc",
    chainId: 43113,
    accounts: [process.env.PRIVATE_KEY]
  }
}
```

## 💰 Costos de Despliegue

### Gas Estimado

| Red | Costo en Gas | Costo en AVAX | Costo en USD* |
|-----|--------------|---------------|---------------|
| **Localhost** | ~1,500,000 | 0 (gratis) | $0 |
| **Hardhat** | ~1,500,000 | 0 (gratis) | $0 |
| **Fuji Testnet** | ~1,500,000 | ~0.00015 | $0 (testnet) |

*Valores aproximados. Fuji usa AVAX de prueba sin valor real.

### Obtener AVAX de Prueba

**Avalanche Fuji Faucet:**
- URL: https://faucet.avax.network/
- Cantidad: 2 AVAX (suficiente para ~10 despliegues)
- Cooldown: 24 horas

**Pasos:**
1. Ir a https://faucet.avax.network/
2. Seleccionar "C-Chain"
3. Pegar tu dirección de wallet
4. Completar CAPTCHA
5. Esperar ~10 segundos

## 🔧 Troubleshooting

### Error: "Cannot find module 'hardhat'"

**Causa:** Dependencias no instaladas.

**Solución:**
```bash
npm install
```

### Error: "Invalid private key"

**Causa:** `PRIVATE_KEY` mal configurada en `.env`

**Solución:**
```bash
# Verificar que exista el archivo
cat /sgoinfre/students/sternero/transcendence/srcs/secrets/.env

# Formato correcto:
PRIVATE_KEY=0x123456789abcdef...  # Debe empezar con 0x y tener 66 caracteres
```

### Error: "Account has no AVAX"

**Causa:** Wallet sin fondos.

**Solución:**
1. Obtener AVAX de [Fuji Faucet](https://faucet.avax.network/)
2. Verificar balance:
   ```javascript
   npx hardhat console --network fuji
   > const balance = await ethers.provider.getBalance("0xYOUR_ADDRESS");
   > ethers.formatEther(balance)
   ```

### Error: "Network fuji not found"

**Causa:** Configuración de red incorrecta.

**Solución:**
```bash
# Verificar hardhat.config.js
cat hardhat.config.js | grep -A 5 "fuji:"
```

### Despliegue Lento

**Causa:** Red congestionada o RPC lento.

**Solución:**
- Usar RPC alternativo en `hardhat.config.js`
- Aumentar timeout en configuración

## 🧪 Verificación del Despliegue

### Verificar en Blockchain Explorer

```bash
# URL generada automáticamente por el script
https://testnet.snowtrace.io/address/<CONTRACT_ADDRESS>
```

### Verificar desde Código

```javascript
// Hardhat console
npx hardhat console --network fuji

// Cargar contrato
const address = require('./contract-address.json').contractAddress;
const TournamentRegistry = await ethers.getContractFactory("TournamentRegistry");
const registry = TournamentRegistry.attach(address);

// Verificar funcionalidad
const count = await registry.getTournamentCount();
console.log("Tournament count:", count.toString());
```

## 📚 Scripts Adicionales (Opcional)

Puedes crear scripts adicionales en este directorio:

### `verify.js` - Verificar Contrato en Snowtrace

```javascript
const hre = require("hardhat");

async function main() {
  const address = require('../contract-address.json').contractAddress;
  
  await hre.run("verify:verify", {
    address: address,
    constructorArguments: []
  });
}

main().catch((error) => {
  console.error(error);
  process.exit(1);
});
```

### `interact.js` - Interactuar con Contrato

```javascript
const hre = require("hardhat");

async function main() {
  const address = require('../contract-address.json').contractAddress;
  const TournamentRegistry = await hre.ethers.getContractFactory("TournamentRegistry");
  const registry = TournamentRegistry.attach(address);
  
  // Registrar torneo de prueba
  const tx = await registry.registerTournament(
    "Test Tournament",
    [await hre.ethers.getSigner(0).getAddress()],
    ["TestPlayer"]
  );
  await tx.wait();
  
  console.log("Tournament registered!");
}

main();
```

## 📚 Documentación Relacionada

- [Hardhat Project](../README.md) - Configuración del entorno
- [Smart Contract](../contracts/README.md) - Documentación del contrato
- [Blockchain Service](../../README.md) - Integración con backend

## 🔗 Enlaces Útiles

- [Hardhat Deploy Plugin](https://github.com/wighawag/hardhat-deploy)
- [ethers.js Contract Deployment](https://docs.ethers.org/v6/getting-started/#starting-contracts)
- [Avalanche Deploy Guide](https://docs.avax.network/build/dapp/smart-contracts/deploy-a-smart-contract)
- [Snowtrace API](https://docs.snowtrace.io/)

## 🤝 Equipo de Desarrollo

- **sternero** - DevOps & automation lead
- **davigome** - Blockchain infrastructure
- **rdel-olm** - Testing & deployment
- **nporras-** - Smart contract integration
- **jesopan-** - Backend services

---

**🚀 Deployment Scripts** - TournamentRegistry Automation  
*Última actualización: Diciembre 2025*
