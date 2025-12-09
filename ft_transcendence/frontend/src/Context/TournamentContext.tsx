import { ComponentContext } from "./ComponentsContext";
import { AuthContext } from "./AuthContext";
import React, { useState, useEffect, createContext, useContext } from 'react';
import type {ReactNode} from 'react'
import type { User } from '../types';
import { blockchainService } from '../services/blockchainService';

export interface Tournament {
    id: number;
    name: string;
    numberOfPlayers: number;
    players: User[];
    tournamentStarted: boolean;
    blockchainRecordId?: number;
    [key: string]: any;
}

export interface TournamentGame {
    player1: any;
    player2: any;
    tournamentGameState: any;
    [key: string]: any;
}

export interface TournamentContextType {
    tournamentReady: boolean;
    setTournamentReady: React.Dispatch<React.SetStateAction<boolean>>;
    currentTournament: Tournament | null;
    tournamentJustStarted: boolean;
    tournamentGame: TournamentGame | null;
    blockchainReady: boolean;
    blockchainRecordId:number | null;

}

interface BlockchainData {
    recordId: number;
    [key: string]: any;
}

export const TournamentContext = createContext<TournamentContextType | null>(null);

interface TournamentContextProviderProps {
    children: ReactNode;
}

export function TournamentContextProvider({ children }: TournamentContextProviderProps): React.ReactElement {
    const { socket } = useContext(ComponentContext)!;
    const { user } = useContext(AuthContext)!;

    // Properly parse localStorage
    const [currentTournament, setCurrentTournament] = useState<Tournament | null>(() => {
        try {
            const stored = localStorage.getItem("currentTournament");
            if (!stored) return null;
            if (stored === "[object Object]") {
                localStorage.removeItem("currentTournament");
                return null;
            }
            return JSON.parse(stored);
        } catch (error) {
            console.error("Failed to parse tournament from localStorage:", error);
            localStorage.removeItem("currentTournament");
            return null;
        }
    });

    const [tournamentReady, setTournamentReady] = useState<boolean>(() => {
        return localStorage.getItem("tournamentReady") === "true";
    });

    const [tournamentJustStarted, setTournamentJustStarted] = useState<boolean>(() => {
        return localStorage.getItem("tournamentJustStarted") === "true";
    });

    const [tournamentGame, setTournamentGame] = useState<TournamentGame | null>(null);

    const [blockchainReady, setBlockchainReady] = useState<boolean>(false);
    const [blockchainRecordId, setBlockchainRecordId] = useState<number | null>(null);

    useEffect(() => {
        checkBlockchainStatus();
    }, []);

    const checkBlockchainStatus = async (): Promise<void> => {
        try {
            const status = await blockchainService.getStatus();
            setBlockchainReady(status.status === 'connected');
        } catch (error) {
            console.error('Error getting blockchain status:', error);
            setBlockchainReady(false);
        }
    };

    useEffect(() => {
        if (!socket) return;

        const handleTournamentMatchStart = ({ opponent, name }: { opponent: string, name: string }) => {
            alert(`¡Tu partido contra ${opponent} en el torneo ${name} va a empezar!`);
        };

        socket.on("tournamentMatchStart", handleTournamentMatchStart);

        return () => {
            socket.off("tournamentMatchStart", handleTournamentMatchStart);
        };
    }, [socket]);

    useEffect(() => {
        if (!socket || !user) return;

        const handleCurrentTournament = (tournament : Tournament | null) => {
            setCurrentTournament(tournament);
            

            if (tournament && tournament.players) {
                const isFull = tournament.players.length === Number(tournament.numberOfPlayers);
                if (isFull || tournament.tournamentStarted) {
                    localStorage.setItem("tournamentReady", "true");
                    localStorage.setItem("currentTournament", JSON.stringify(tournament));
                    setTournamentReady(true);
                    
                    
                    if (tournament.blockchainRecordId !== undefined && tournament.blockchainRecordId !== null) {
                        setBlockchainRecordId(tournament.blockchainRecordId);
                    }
                    
                    socket.emit("startTournamentNow", tournament.id);
                }
            } else if (tournament === null) {
                localStorage.removeItem("tournamentReady");
                localStorage.removeItem("currentTournament");
                localStorage.removeItem("tournamentJustStarted");
                setTournamentJustStarted(false);
                setTournamentReady(false);
                setBlockchainRecordId(null);
            }
        }

        const handleBlockchainRegistered = (data: BlockchainData) => {
            setBlockchainRecordId(data.recordId);
        };

        const handleTournamentJustStarted = (showDelay: boolean) => {
            setTournamentJustStarted(showDelay);
            if (showDelay)
                localStorage.setItem("tournamentJustStarted", "true");
            else 
                localStorage.removeItem("tournamentJustStarted");
        }

        const handleTournamentGameStarted = (data: {
            player1: any;
            player2: any;
            id: string;
            tournamentGameState: any;
        }) => {
            setTournamentGame(data);
        };

		const handletournamentGameUpdate = (tournamentGameState: any) => {
			// Solo actualizar el estado del juego, mantener player1, player2, id
			setTournamentGame(prev => {
				if (!prev) return null;
				return {
					...prev,
					tournamentGameState: tournamentGameState
				};
			});
		}

        const handletournamentGameFinish = () => {
            setTournamentGame(null);
        }

        const handleNotifyPlayersTournamentGameEnded = (tournamentGameRoomId: number, winnerId: number) => {
            socket.emit("closeTournamentGame", tournamentGameRoomId, winnerId)
        }

        const handleTournamentGameEnded = (data: {
            roomId: string;
            winner: string;
            winnerId: number;
            loser: string;
            finalScore: { player1: number; player2: number };
        }) => {
            
            setTournamentGame(null);
            
            socket.emit("closeTournamentGame", data.roomId, data.winnerId);
        };

        socket.on("getCurrentTournament", handleCurrentTournament);
        socket.on("tournamentRegisteredOnBlockchain", handleBlockchainRegistered);
        socket.on("tournamentJustStarted", handleTournamentJustStarted);
        socket.on("tournamentGameStarted", handleTournamentGameStarted);
        socket.on("updateTournamentGame", handletournamentGameUpdate);
        socket.on("tournamentGameFinish", handletournamentGameFinish);
        socket.on("tournamentGameEnded", handleTournamentGameEnded);
        socket.on("notifyPlayersTournamentGameEnded", handleNotifyPlayersTournamentGameEnded);

        return () => {
            socket.off("getCurrentTournament", handleCurrentTournament);
            socket.off("tournamentRegisteredOnBlockchain", handleBlockchainRegistered);
            socket.off("tournamentJustStarted", handleTournamentJustStarted);
            socket.off("tournamentGameStarted", handleTournamentGameStarted);
            socket.off("updateTournamentGame", handletournamentGameUpdate);
            socket.off("tournamentGameFinish", handletournamentGameFinish);
            socket.off("tournamentGameEnded", handleTournamentGameEnded);
            socket.off("notifyPlayersTournamentGameEnded", handleNotifyPlayersTournamentGameEnded);
        }
    }, [socket, user])

    return (
        <TournamentContext.Provider value={{
            tournamentReady, 
            setTournamentReady, 
            currentTournament, 
            tournamentJustStarted, 
            tournamentGame,
            blockchainReady,
            blockchainRecordId,
        }}>
            {children}
        </TournamentContext.Provider>
    )
}