const API_URL = `${window.location.origin}/api/blockchain`;

export interface Tournament {
    recordId: string;
    tournamentName: string;
    players: string[];
    aliases: string[];
    champion: string;
    scores: string[];
    timestamp: string;
    isFinalized: boolean;
}

export interface PlayerStats {
    totalTournaments: string;
    tournamentsWon: string;
    totalScore: string;
}

export interface BlockchainStatus {
    status: string;
    network: string;
    contractAddress: string;
    wallet: string;
    snowtraceUrl: string;
}

export const blockchainService = {
    async getStatus(): Promise<BlockchainStatus> {
        const response = await fetch(`${API_URL}/status`,{headers:{'Accept': 'application/json'}});
        if (!response.ok) {
            throw new Error('Failed to fetch blockchain status');
        }
        return response.json();
    },

    async getAllTournaments(): Promise<Tournament[]> {
        const response = await fetch(`${API_URL}/tournaments`,{headers:{'Accept': 'application/json'}});
        if (!response.ok) {
            throw new Error('Failed to fetch tournaments');
        }
        const data = await response.json();
        return data.tournaments;
    },

    async getTournament(id: string): Promise<Tournament> {
        const response = await fetch(`${API_URL}/tournaments/${id}`,{headers:{'Accept': 'application/json'}});
        if (!response.ok) {
            throw new Error('Failed to fetch tournament');
        }
        return response.json();
    },

    async getPlayerStats(alias: string): Promise<PlayerStats> {
        const response = await fetch(`${API_URL}/player/${alias}/stats`,{headers:{'Accept': 'application/json'}});
        if (!response.ok) {
            throw new Error('Failed to fetch player stats');
        }
        return response.json();
    }
};
