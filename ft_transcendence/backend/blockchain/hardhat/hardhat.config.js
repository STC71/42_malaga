import { config } from 'dotenv';
import path from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Intentar cargar .env (puede no existir en build time)
config({ path: path.resolve(__dirname, '../../../srcs/secrets/.env') });

import '@nomicfoundation/hardhat-toolbox';

// ✅ PRIVATE_KEY dummy para compilación (no se usa para compilar)
const PRIVATE_KEY = process.env.PRIVATE_KEY || '0x0000000000000000000000000000000000000000000000000000000000000001';

/** @type import('hardhat/config').HardhatUserConfig */
export default {
  solidity: "0.8.19",
  networks: {
    fuji: {
      url: process.env.AVALANCHE_RPC_URL || "https://api.avax-test.network/ext/bc/C/rpc",
      chainId: 43113,
      accounts: [PRIVATE_KEY]
    }
  }
};
