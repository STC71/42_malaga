# 🔗 Blockchain Integration Guide

This project uses **Avalanche Fuji Testnet** to store tournaments immutably on blockchain.

---

## 🎯 What Gets Stored on Blockchain?

Each tournament records:

- **Tournament name**
- **Players** (4, 8, 12, or 16 participants)
- **Start and end dates**
- **Champion** (winner)
- **Final scores** of all players
- **Status** (active/finalized)

Everything is **permanently recorded** and publicly verifiable.

---

## 🔧 Setup for Evaluators

### **STEP 1: Get Private Key**

#### **Option A: Create New Wallet (Recommended)**

1. Go to [Core Wallet](https://core.app/)
2. Click **"Create New Wallet"**
3. Save the recovery phrase (12 words)
4. Once inside, go to **Settings** → **Show Private Key**
5. Copy the private key (starts with `0x`)

#### **Option B: Use Existing Wallet**

1. Open [Core Wallet](https://core.app/)
2. Import your wallet with the recovery phrase
3. Go to **Settings** → **Show Private Key**
4. Copy the private key

⚠️ **IMPORTANT:** This wallet is for **testnet only**. DO NOT use wallets with real funds.

---

### **STEP 2: Get AVAX Testnet Tokens (Free)**

1. Copy your **wallet address** (0x...) from Core
2. Go to [Avalanche Faucet](https://faucet.avax.network/)
3. Select **"Fuji Testnet"**
4. Paste your address
5. Complete the captcha
6. Click **"Request 2 AVAX"**
7. Wait ~30 seconds

**Verify funds:**
- Go to [Snowtrace Fuji](https://testnet.snowtrace.io/)
- Search for your address
- You should see **2 AVAX**

💰 **2 AVAX testnet = ~400 transactions**

---

### **STEP 3: Configure `.env`**

```bash
# Edit the file
nano srcs/secrets/.env
```

**Replace:**

```env
# BEFORE:
PRIVATE_KEY=your-private-key

# AFTER:
PRIVATE_KEY=0xYOUR_PRIVATE_KEY_FROM_CORE_WALLET_HERE
```

**Example (DO NOT use this one):**

```env
PRIVATE_KEY=0xabc123def456789012345678901234567890123456789012345678901234567890
```

⚠️ **NEVER commit your `.env` to Git.**

---

### **STEP 4: Launch Project**

```bash
# Build and start
make

# Or manually:
docker-compose up -d --build
```

---

### **STEP 5: Verify Blockchain**

```bash
# View initialization logs
docker logs transcendence-backend | grep -A 10 "Blockchain"

# You should see:
# 🔗 Initializing Blockchain Service...
# ✅ Contract Address: 0x7bEd67Bf730941761680600c12429f67d12e2c7E
# 👤 Wallet Address: 0xYOUR_WALLET...
# ✅ Blockchain Service initialized successfully!
# 💰 Wallet Balance: 2.0 AVAX
```

---

## 🎮 System Usage

### **1. Create Tournament**

1. Login to the web app: http://localhost:2323
2. Go to **Tournaments** → **Create Tournament**
3. Enter name and select number of players: **4, 8, 12, or 16**
4. Click **Create**

---

### **2. Finalize Tournament**

1. Play the tournament (Pong)
2. Upon completion, scores are automatically registered
3. Click **Finalize Tournament**

**What happens:**
- A transaction is sent with:
  - Champion (winner)
  - Final scores
  - Finalization timestamp

---

### **3. View History**

1. Go to **Tournaments** → **View History**
2. See all tournaments with:
   - ✅ Status (Active/Finalized)
   - 🏆 Champion
   - 📊 Scores
   - 🔗 Link to Snowtrace

---

## 🔍 Verify Transactions on Snowtrace

### **View Complete Contract:**

```
https://testnet.snowtrace.io/address/0x7bEd67Bf730941761680600c12429f67d12e2c7E
```

**You can see:**
- All contract transactions
- Emitted events (TournamentRegistered, TournamentFinalized)
- Contract balance
- Verified source code

---

### **View Specific Transaction:**

Each tournament displays a link like:

```
https://testnet.snowtrace.io/tx/0xabc123...
```

**Available information:**
- Who sent the transaction (your wallet)
- Gas used (cost)
- Input data (tournament data)
- Logs (emitted events)

---

## 🆕 (Optional) Deploy Your Own Contract

If you want to experiment by deploying a new contract:

```bash
# 1. Enter the container
docker exec -it transcendence-backend bash

# 2. Navigate to Hardhat folder
cd /app/blockchain/hardhat

# 3. Compile contracts
npx hardhat compile

# 4. Deploy to Fuji testnet
npx hardhat run scripts/deploy.js --network fuji

# Example output:
# Deploying TournamentRegistry...
# TournamentRegistry deployed to: 0xNEW_ADDRESS
# Saved to contract-address.json

# 5. Exit container
exit

# 6. Update .env with new address
nano srcs/secrets/.env
# AVALANCHE_CONTRACT_ADDRESS=0xNEW_ADDRESS

# 7. Restart backend
docker restart transcendence-backend
```

**Approximate cost:** 0.05 AVAX (testnet)

---

## 📊 Smart Contract Structure

The `TournamentRegistry.sol` contract supports tournaments of **variable size** (4, 8, 12, 16 players) using dynamic arrays.

### **Function: `registerTournament`**

```solidity
function registerTournament(
    string memory _name,
    address[] memory _players,      // ✅ Dynamic array (4, 8, 12, 16...)
    string[] memory _aliases        // ✅ Dynamic array
) public returns (uint256)
```

**Parameters:**
- `_name`: Tournament name
- `_players`: Array of addresses (flexible size)
- `_aliases`: Array of corresponding aliases

**Validations:**
- ✅ Minimum 2 players
- ✅ Same number of players and aliases
- ✅ Non-empty name

**Returns:** Unique tournament ID (recordId)

**Usage example:**

```javascript
// 4-player tournament
await contract.registerTournament(
    "Finals 2024",
    ["0xabc...", "0xdef...", "0x123...", "0x456..."],
    ["Alice", "Bob", "Carol", "Dave"]
);

// 8-player tournament
await contract.registerTournament(
    "Grand Championship",
    ["0x1...", "0x2...", "0x3...", "0x4...", "0x5...", "0x6...", "0x7...", "0x8..."],
    ["P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8"]
);
```

---

### **Function: `finalizeTournament`**

```solidity
function finalizeTournament(
    uint256 _recordId,
    address _champion,
    uint256[] memory _scores         // ✅ Dynamic array (must match number of players)
) public
```

**Parameters:**
- `_recordId`: ID of tournament to finalize
- `_champion`: Winner's address
- `_scores`: Array of scores (same size as players)

**Validations:**
- ✅ Tournament exists
- ✅ Not already finalized
- ✅ Champion is in the player list
- ✅ Number of scores matches number of players

**Usage example:**

```javascript
// Finalize 4-player tournament
await contract.finalizeTournament(
    0,                    // recordId
    "0xabc...",          // champion
    [100, 80, 60, 40]    // scores for 4 players
);

// Finalize 8-player tournament
await contract.finalizeTournament(
    1,
    "0x123...",
    [150, 140, 130, 120, 110, 100, 90, 80]  // scores for 8 players
);
```

---

### **Function: `getTournamentRecord`**

```solidity
function getTournamentRecord(uint256 _recordId) 
    public view returns (
        uint256 recordId,
        string memory tournamentName,
        uint256 startTime,
        uint256 endTime,
        address champion,
        address[] memory players,    // ✅ Dynamic array
        uint256[] memory scores,     // ✅ Dynamic array
        string[] memory aliases,     // ✅ Dynamic array
        bool isFinalized
    )
```

**Returns:** All tournament data with variable-sized arrays

---

### **Other Useful Functions:**

#### **`getTotalRecords()`**
```solidity
function getTotalRecords() public view returns (uint256)
```
Returns the total number of registered tournaments.

---

#### **`isPlayerInTournament()`**
```solidity
function isPlayerInTournament(uint256 _recordId, address _player) 
    public view returns (bool)
```
Checks if a player participated in a specific tournament.

---

#### **`getPlayerHistory()`**
```solidity
function getPlayerHistory(address _player) 
    public view returns (uint256[] memory)
```
Returns all tournament IDs in which a player participated.

---

#### **`getPlayerStats()`**
```solidity
function getPlayerStats(address _player) 
    public view returns (uint256 wins, uint256 totalParticipations)
```
Returns player statistics:
- `wins`: Number of tournaments won
- `totalParticipations`: Total participations

---

## 💾 Data Structure

### **TournamentRecord (Struct)**

```solidity
struct TournamentRecord {
    uint256 recordId;           // Unique incremental ID
    string tournamentName;      // Tournament name
    uint256 startTime;          // Start timestamp (Unix)
    uint256 endTime;            // Finalization timestamp
    address champion;           // Winner's address
    address[] players;          // Dynamic array of players
    uint256[] finalScores;      // Dynamic array of scores
    string[] playerAliases;     // Dynamic array of aliases
    bool isFinalized;           // true = finalized, false = active
}
```

**Features:**
- ✅ Supports any number of players (minimum 2)
- ✅ All arrays have the same size
- ✅ Immutable once finalized

---

## 🛠️ Troubleshooting

### **Error: "Insufficient funds for gas"**

**Solution:**

```bash
# Check balance
docker logs transcendence-backend | grep "Wallet Balance"

# If < 0.1 AVAX:
# 1. Go to https://faucet.avax.network/
# 2. Request more AVAX
# 3. Wait 30 seconds
```

---

### **Error: "Contract not found"**

**Verify:**

```bash
# 1. View configured address
cat srcs/secrets/.env | grep AVALANCHE_CONTRACT_ADDRESS

# 2. Verify it exists on Snowtrace
# Go to: https://testnet.snowtrace.io/address/0x7bEd67...

# 3. View backend logs
docker logs transcendence-backend | grep "Contract Address"
```

---

## 📚 Additional Resources

### **Documentation:**

- [Avalanche Docs](https://docs.avax.network/)
- [Core Wallet](https://support.avax.network/en/collections/3391501-core-extension)
- [Hardhat Docs](https://hardhat.org/docs)
- [ethers.js Docs](https://docs.ethers.org/v6/)

### **Explorers:**

- [Snowtrace Fuji (Testnet)](https://testnet.snowtrace.io/)
- [Avalanche Subnet Explorer](https://subnets-test.avax.network/)

### **Faucets:**

- [Avalanche Faucet](https://faucet.avax.network/)

---

## 🔐 Security

### **✅ Best Practices:**

- ✅ Use separate wallet for testnet
- ✅ NEVER share your PRIVATE_KEY
- ✅ Keep `.env` in `.gitignore`

### **❌ NEVER:**

- ❌ Commit `.env` to Git/GitHub
- ❌ Share your PRIVATE_KEY on Discord/Slack
- ❌ Use the same wallet for testnet and mainnet
- ❌ Hardcode PRIVATE_KEY in code

---

## 💡 Evaluation Private Key (Testing Only)

For project evaluation, we will use a preconfigured test wallet:

**⚠️ TEST WALLET (TESTNET ONLY):**

```env
PRIVATE_KEY=0xff1398467c95516f50d92765216109dca4f29246092eedb50bcce7a31aaabb46
```

**Address:** `0xD9950cA607D5959ba47243Bd887c506e582B077D`

**⚠️ WARNING:**
- This private key is **PUBLIC** in this document
- Only has **testnet** funds (no real value)
- Anyone can use it
- **DO NOT use for anything important**
