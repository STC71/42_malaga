import { ethers } from 'ethers';
import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

class BlockchainService {
    constructor() {
        try {
            console.log('🔗 Initializing Blockchain Service...');
            
            const rpcUrl = process.env.AVALANCHE_RPC_URL || 'https://api.avax-test.network/ext/bc/C/rpc';
            console.log('📡 Connecting to:', rpcUrl);
            
            this.provider = new ethers.JsonRpcProvider(rpcUrl);
            
            const contractAddressPath = path.join(__dirname, 'hardhat', 'contract-address.json');
            
            if (!fs.existsSync(contractAddressPath)) {
                console.error('❌ contract-address.json not found!');
                console.error('📍 Expected at:', contractAddressPath);
                throw new Error('Contract not deployed. Run: cd backend/blockchain/hardhat && npx hardhat run scripts/deploy.js --network fuji');
            }
            
            const contractData = JSON.parse(fs.readFileSync(contractAddressPath, 'utf8'));
            this.contractAddress = contractData.contractAddress;
            
            console.log('✅ Contract Address:', this.contractAddress);
            console.log('🔍 View on Snowtrace:', `https://testnet.snowtrace.io/address/${this.contractAddress}`);
            
            const artifactPath = path.join(__dirname, 'hardhat', 'artifacts', 'contracts', 'TournamentRegistry.sol', 'TournamentRegistry.json');
            
            if (!fs.existsSync(artifactPath)) {
                console.error('❌ Contract artifact not found!');
                throw new Error('Contract not compiled. Run: cd backend/blockchain/hardhat && npx hardhat compile');
            }
            
            const contractArtifact = JSON.parse(fs.readFileSync(artifactPath, 'utf8'));
            this.contractABI = contractArtifact.abi;
            
            const privateKey = process.env.PRIVATE_KEY;
            if (!privateKey) {
                console.error('❌ PRIVATE_KEY not set in environment!');
                throw new Error('Set PRIVATE_KEY in .env file');
            }
            
            this.wallet = new ethers.Wallet(privateKey, this.provider);
            console.log('👤 Wallet Address:', this.wallet.address);
            
            this.contract = new ethers.Contract(
                this.contractAddress,
                this.contractABI,
                this.wallet
            );

            this.initialized = true;
            
            this.checkBalance();
            
            console.log('✅ Blockchain Service initialized successfully!');
            
        } catch (error) {
            console.error('❌ Failed to initialize Blockchain Service:');
            console.error(error.message);
            this.initialized = false;
            throw error;
        }
    }
    
    async checkBalance() {
        try {
            const balance = await this.provider.getBalance(this.wallet.address);
            const balanceInAvax = ethers.formatEther(balance);
            console.log('💰 Wallet Balance:', balanceInAvax, 'AVAX');
            
            if (parseFloat(balanceInAvax) < 0.1) {
                console.warn('⚠️  Low balance! You may need more AVAX for transactions.');
            }
        } catch (error) {
            console.error('❌ Error checking balance:', error.message);
        }
    }

    generateAddressFromUsername(username) {
        if (!username || typeof username !== 'string') {
            throw new Error('Invalid username');
        }
        const hash = ethers.keccak256(ethers.toUtf8Bytes(username));
        const address = '0x' + hash.slice(26);
        return ethers.getAddress(address);
    }
    
    async registerTournament(tournamentName, players) {
        try {
            console.log('📤 Registering tournament on blockchain...');
            console.log('   Name:', tournamentName);
            console.log('   Players:', players.join(', '));

            const playerAddresses = players.map(username => 
                this.generateAddressFromUsername(username)
            );
            const aliases = players;
            
            const tx = await this.contract.registerTournament(
                tournamentName,
                playerAddresses,
                aliases
            );
            
            console.log('⏳ Transaction sent:', tx.hash);
            console.log('🔗 View on Snowtrace:', `https://testnet.snowtrace.io/tx/${tx.hash}`);
            
            const receipt = await tx.wait();
            
            console.log('✅ Transaction confirmed in block:', receipt.blockNumber);
            
            const event = receipt.logs.find(log => {
                try {
                    const parsed = this.contract.interface.parseLog(log);
                    return parsed.name === 'TournamentRegistered';
                } catch {
                    return false;
                }
            });
            
            let recordId = null;
            if (event) {
                const parsed = this.contract.interface.parseLog(event);
                recordId = parsed.args.recordId.toString();
                console.log('🆔 Tournament Record ID:', recordId);
            }
            
            return {
                success: true,
                recordId: recordId,
                transactionHash: tx.hash,
                blockNumber: receipt.blockNumber,
                gasUsed: receipt.gasUsed.toString()
            };
            
        } catch (error) {
            console.error('❌ Error registering tournament:', error.message);
            return {
                success: false,
                message: error.message
            };
        }
    }
    
    async finalizeTournament(recordId, champion, scores) {
        try {
            console.log('🏆 Finalizing tournament on blockchain...');
            console.log('   Record ID:', recordId);
            console.log('   Champion:', champion);

            const championAddress = this.generateAddressFromUsername(champion);
            
            const tx = await this.contract.finalizeTournament(
                recordId,
                championAddress,
                scores
            );
            
            console.log('⏳ Transaction sent:', tx.hash);
            console.log('🔗 View on Snowtrace:', `https://testnet.snowtrace.io/tx/${tx.hash}`);
            
            const receipt = await tx.wait();
            
            console.log('✅ Tournament finalized in block:', receipt.blockNumber);
            
            return {
                success: true,
                transactionHash: tx.hash,
                blockNumber: receipt.blockNumber
            };
            
        } catch (error) {
            console.error('❌ Error finalizing tournament:', error.message);
            return {
                success: false,
                message: error.message
            };
        }
    }
    
	async getTournament(recordId) {
		try {
			console.log(`📥 Fetching tournament ${recordId}...`);
			
			const result = await this.contract.getTournamentRecord(recordId);
			
			const startTime = result[2] ? Number(result[2]) : 0;
			const endTime = result[3] ? Number(result[3]) : 0;
			
			if (!result[6]) {
				console.warn('   ⚠️  finalScores is undefined');
			}
			if (!result[7]) {
				console.warn('   ⚠️  playerAliases is undefined');
			}

			return {
				recordId: result[0].toString(),
				tournamentName: result[1],
				startTime: startTime,
				endTime: endTime, 
				champion: result[4],
				players: result[5] || [],
				scores: (result[6] || []).map(s => s.toString()),
				aliases: result[7] || [],
				isFinalized: result[8]
			};
			
		} catch (error) {
			console.error(`❌ Error getting tournament ${recordId}:`, error.message);
			
			if (error.data) {
				console.error('   Error data:', error.data);
			}
			
			throw error;
		}
	}

    async getAllTournaments() {
        try {
            console.log('📋 Fetching all tournaments from blockchain...');
            
            const totalRecords = await this.contract.getTotalRecords();
            const count = Number(totalRecords);
            
            console.log(`📊 Total tournaments registered: ${count}`);
            
            if (count === 0) {
                console.log('ℹ️  No tournaments found in blockchain');
                return [];
            }
            
            const tournaments = [];
            
            for (let i = 0; i < count; i++) {
                try {
                    console.log(`   📥 Fetching tournament ${i + 1}/${count}...`);
                    const tournament = await this.getTournament(i);
                    tournaments.push(tournament);
                } catch (error) {
                    console.warn(`   ⚠️  Failed to fetch tournament ${i}: ${error.message}`);
                }
            }
            
            console.log(`✅ Successfully retrieved ${tournaments.length} of ${count} tournaments`);
            
            return tournaments;
            
        } catch (error) {
            console.error('❌ Error getting all tournaments:', error.message);
            throw error;
        }
    }
    
    async getPlayerStats(username) {
        if (!this.initialized) {
            throw new Error('Blockchain service not initialized');
        }

        try {
            console.log(`📊 Getting stats for player: ${username}`);
            
            const address = this.generateAddressFromUsername(username);
            console.log(`   Address: ${address}`);
            
            const stats = await this.contract.getPlayerStats(address);
            
            return {
                username: username,
                address: address,
                wins: Number(stats.wins),
                totalParticipations: Number(stats.totalParticipations)
            };
            
        } catch (error) {
            console.error(`❌ Error getting player stats: ${error.message}`);
            return { 
                username: username,
                address: null,
                wins: 0, 
                totalParticipations: 0 
            };
        }
    }
}

let blockchainServiceInstance = null;

export function getBlockchainService() {
    if (!blockchainServiceInstance) {
        blockchainServiceInstance = new BlockchainService();
    }
    return blockchainServiceInstance;
}
