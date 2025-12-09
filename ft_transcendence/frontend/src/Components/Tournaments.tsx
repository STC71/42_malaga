import { ComponentContext } from "../Context/ComponentsContext"
import { AuthContext } from "../Context/AuthContext"
import { useContext, useEffect, useRef, useState } from "react"
import Confetti from 'react-confetti'
import { TournamentContext } from "../Context/TournamentContext";
import type { Tournament, TournamentGame } from "../Context/TournamentContext";
import type { User } from "../types";
import type { ReactElement } from "react";
import LocalTournament from "./LocalTournament";

interface BlockchainTournament {
    recordId: number;
    tournamentName: string;
    aliases: string[];
    scores: number[];
    isFinalized: boolean;
    startTime: number;
    endTime: number;
}

interface TournamentHistoryModalProps {
    tournaments: BlockchainTournament[];
    loading: boolean;
    onClose: () => void;
    onSelectTournament: (tournament: BlockchainTournament) => void;
}

interface TournamentDetailModalProps {
    tournament: BlockchainTournament;
    onClose: () => void;
}

interface TournamentGameProps {
    currentTournament: Tournament;
}

export const Tournaments = (): ReactElement => {
    const {socket} = useContext(ComponentContext)!;
    const {user, lan, language} = useContext(AuthContext)!;
    const [lobbyState, setLobbyState] = useState<Tournament[]>([]);
    const [createTournamentLog, setCreateTournamentLog] = useState<boolean>(false)
    const [tournamentNameState, setTournamentNameState] = useState<string>(`${user?.username || ''}'s tournament`)
    const [numOfPlayerState, setNumOfPlayerState] = useState<string>('');
    const {tournamentReady, currentTournament} = useContext(TournamentContext)!;
	const [showHistory, setShowHistory] = useState(false);
    const [historyLoading, setHistoryLoading] = useState(false);
    const [tournamentHistory, setTournamentHistory] = useState([]);
    const [selectedTournament, setSelectedTournament] = useState<BlockchainTournament | null>(null);
	const [localTournament,setLocalTournament] = useState<boolean>(false);
	const getText = (key: string): string => {
        if (!language) {
            console.warn('Language object is not available');
            return getFallback(key);
        }
        
        if (!lan) {
            console.warn('Language code (lan) is not available');
            return getFallback(key);
        }
        
        if (!(lan in language)) {
            console.warn(`Language '${lan}' is not available in language object`);
            return getFallback(key);
        }
        
        const languageData = language[lan];
        if (!languageData || typeof languageData !== 'object') {
            console.warn(`Language data for '${lan}' is null, undefined or not an object`);
            return getFallback(key);
        }
        
        if (!(key in languageData)) {
            console.warn(`Key '${key}' not found in language '${lan}'`);
            return getFallback(key);
        }
        
        const languageRecord = languageData as unknown as Record<string, unknown>;
        const value = languageRecord[key];
        
        if (value === undefined) {
            console.warn(`Value for key '${key}' is undefined`);
            return getFallback(key);
        }
        
        return typeof value === 'string' ? value : getFallback(key);
    };

    const getFallback = (key: string): string => {
        const fallbacks: Record<string, string> = {
			'Tournaments': 'Tournaments',
			'tournamentName': "Tournament's Name",
			'tournamentNumberOfPlayers': 'Number of Players',
			'tournamentNumberOfPlayersPlaceholder': 'Number of Players (4, 8, 16, ...)',
			'tournamentCreateNewTournament': 'Create New Tournament',
			'localTournament': 'Local tournament',
			'tournamentLeaveTournament': 'Leave Tournament',
			'tournamentHost': 'HOST',
			'tournamentAvailableSeat': 'Available Seat',
			'tournamentPlayersLabel': 'Players: ',
			'tournamentNoTournaments': 'No tournaments available. Create one!',
			'tournamentCreateTitle': 'Create Tournament',
			'tournamentTotalLobbies': 'Total lobbies: ',
			'tournamentCongratulations': 'CONGRATULATIONS',
			'tournamentYouAreWinner': 'YOU ARE THE WINNER!!!',
			'tournamentHasWon': 'HAS WON THE TOURNAMENT!!!',
			'tournamentFinal': 'FINAL',
			'tournamentSemifinals': 'SEMIFINALS',
			'tournamentQuarterfinals': 'QUARTERFINALS',
			'tournamentRoundOf16': 'ROUND OF 16',
			'tournamentRoundOf32': 'ROUND OF 32',
			'tournamentRoundOf64': 'ROUND OF 64',
			'tournamentPlayerBracket': '-player bracket',
			'tournamentNoTournamentFound': 'No tournament found',
			'tournamentVS': 'VS',
			'tournamentCloseTournament': 'CLOSE TOURNAMENT',
			'tournamentNamePlaceholder': "Enter Tournament's Name",
  			'tournamentScore': 'Score',
			'tournamentViewHistory': 'View History',
			'tournamentHistory': 'History',
        };
        
        return fallbacks[key] || key;
    };

    useEffect( () => {
        if (!socket) return;
        const handleTournamentsLobbies = (tournamentLobbies: Tournament[]) => {
            setLobbyState(tournamentLobbies);
        }

        socket.emit("CheckTournamentLobbies");
        socket.on("tournamentLobbyInfo", handleTournamentsLobbies)
        return () => {
            socket.off("tournamentLobbyInfo", handleTournamentsLobbies)
        }
    }, [socket])

	const loadHistory = async () => {
        setHistoryLoading(true);
        try {
            const response = await fetch('/api/blockchain/tournaments',{headers: {'Accept': 'application/json'}});
            const data = await response.json();
            
            if (data.success) {
                setTournamentHistory(data.tournaments || []);
            } else {
                console.error('Failed to load tournament history:', data.message);
            }
        } catch (error) {
            console.error('Error loading tournament history:', error);
        } finally {
            setHistoryLoading(false);
        }
    };

	const openHistory = () => {
        setShowHistory(true);
        loadHistory();
    };

    const createNewTournament = (): void => {
        const tournamentName = tournamentNameState.trim();
        if (tournamentName === '') {alert("The tournament name cannot be empty!"); return} 
        else if ((numOfPlayerState !== '4' && numOfPlayerState !== '8' && numOfPlayerState !== '16'  && numOfPlayerState !== '32'  && numOfPlayerState !== '64')) {alert("The number of Players must be (4, 8, 16, ...)"); return}
        const type = "elimination"
        socket?.emit("createTournament", tournamentName, numOfPlayerState, type)
        setCreateTournamentLog(false);
    }

    const handleGetOutOfTournament = (): void => {
        socket?.emit("removePlayerFromTournament", user?.id, currentTournament?.id)
    }

    const showTournamentInfo = (tournament: Tournament): void => {
        const name = tournament.name
        const playersIn = lobbyState.find(lobby => lobby.id === tournament.id)?.players.length;
        //alert(`this is the anme: ${name} this is how many players in: ${playersIn}`)
        socket?.emit("joinTournament", tournament.id, tournament.name, user?.id)
    }

    const checkNUmOfPlayers = (e: React.ChangeEvent<HTMLInputElement>): void => {
        const value = e.target.value;
        if (value === '' || /^\d+$/.test(value)) {
            if (value.length > 2)
            {
                setNumOfPlayerState(value.slice(0, 2))
                return;
            }
            setNumOfPlayerState(value)
        }
    }

    return (
		<>
		{localTournament ? <LocalTournament setLocalTournament = {setLocalTournament}/> : (
        <div className="min-h-screen bg-gradient-to-br from-slate-950 via-slate-900 to-slate-950 flex flex-col items-center py-12 px-4">
            <div className="w-full max-w-3xl mx-auto">
				<div className="flex justify-between items-center mb-10">
                    <h1 className="text-5xl font-bold text-transparent bg-clip-text bg-gradient-to-r from-red-400 via-red-600 to-red-800 tracking-tight drop-shadow-lg">{getText('Tournaments')}</h1>
                    {!tournamentReady && (
                        <button
                            onClick={openHistory}
                            className="px-4 py-2 bg-gradient-to-r from-blue-600 to-cyan-600 hover:from-blue-700 hover:to-cyan-700 text-white rounded-lg font-bold shadow-lg transition-all flex items-center gap-2"
                        >
                            <span>🏆</span>
                            <span className="hidden sm:inline">{getText('tournamentViewHistory')}</span>
                            <span className="sm:hidden">{getText('tournamentHistory')}</span>
                        </button>
                    )}
                </div>
                {
                    (!tournamentReady && createTournamentLog) &&
                    <div className="flex flex-col gap-6 bg-gradient-to-br from-slate-800 via-slate-800 to-slate-700 rounded-xl p-8 shadow-2xl border border-orange-600/10 w-full max-w-md mx-auto">
                        <label className="text-sm text-orange-200 font-semibold mb-2 uppercase tracking-wide">{getText('tournamentName')}</label>
                        <input
                            value={tournamentNameState}
                            onChange={(e) => setTournamentNameState(e.target.value)}
                            placeholder={getText('tournamentNamePlaceholder')}
                            className="px-4 py-3 rounded-lg bg-black/70 text-white placeholder-gray-400 border border-orange-600/20 focus:outline-none focus:ring-2 focus:ring-orange-400 font-semibold shadow"
                        />
                        <label className="text-sm text-orange-200 font-semibold mb-2 uppercase tracking-wide">{getText('tournamentNumberOfPlayers')}</label>
                        <input
                            value={numOfPlayerState}
                            onChange={(e) => checkNUmOfPlayers(e)}
                            className="px-4 py-3 rounded-lg bg-black/70 text-white placeholder-gray-400 border border-orange-600/20 focus:outline-none focus:ring-2 focus:ring-orange-400 font-semibold shadow"
                            placeholder={getText('tournamentNumberOfPlayersPlaceholder')}
                        />
                        <button
                            onClick={() => createNewTournament()}
                            className="w-full py-3 bg-gradient-to-r from-red-700/80 via-red-700 to-red-700/80 hover:from-red-600 hover:via-red-600/95 hover:to-red-600 text-white font-bold rounded-lg shadow-lg transition-all text-lg mt-2"
                        >
                            {getText('tournamentCreateNewTournament')}
                        </button>
                    </div>
                }
                {(!tournamentReady && !createTournamentLog) &&  (currentTournament  ? (
                    <div className="bg-gradient-to-br from-slate-800 via-slate-700 to-slate-800 border border-orange-600/10 rounded-xl p-8 shadow-2xl mb-8">
                        <div className="flex justify-between items-center mb-6">
                                <h2 className="text-2xl font-bold text-orange-300">{currentTournament.name}</h2>
                            <button onClick={handleGetOutOfTournament} className="px-4 py-2 bg-red-600 hover:bg-red-700 text-white rounded-lg font-semibold shadow transition-all">{getText('tournamentLeaveTournament')}</button>
                        </div>
                        <div className="grid grid-cols-2 md:grid-cols-4 gap-4">
                            {Array.from({ length: currentTournament.numberOfPlayers }).map((_, index) => {
                                const player = currentTournament.players[index];
                                return player ? (
                                        <div key={index} className={`bg-slate-900 border ${'border-orange-600'} rounded-lg p-4 flex flex-col items-center shadow hover:shadow-red-600/15 transition-all relative`}>
                                        <div className={`w-12 h-12 rounded-full flex items-center justify-center text-xl font-bold mb-2 ${player.host ? 'bg-gradient-to-br from-orange-600 to-red-600 text-white border-2 border-red-500 shadow-lg' : 'bg-slate-800 text-white'}`}>
                                            {player.username[0]?.toUpperCase()}
                                        </div>
                                        <div className={`font-semibold ${player.host ? 'text-orange-300' : 'text-white'}`}>{player.username}</div>
                                        {player.host === true && (
                                            <div className="absolute top-2 right-2 flex items-center gap-1">
                                                <span className="inline-block bg-gradient-to-r from-orange-600 to-red-600 text-white text-xs font-semibold px-2 py-1 rounded border border-red-500 shadow" title="Host">{getText('tournamentHost')}</span>
                                            </div>
                                        )}
                                    </div>
                                ) : (
                                    <div key={index} className="bg-slate-800 border border-gray-700 rounded-lg p-4 flex flex-col items-center justify-center text-gray-400 shadow">
                                        <span className="mt-2">{getText('tournamentAvailableSeat')}</span>
                                    </div>
                                );
                            })}
                        </div>
                    </div>
                ) : (
                    <>
                        {lobbyState.length > 0 ? (
                            <div className="grid grid-cols-1 md:grid-cols-2 gap-8 mb-10">
                                {lobbyState.map((lobby, index) => (
                                    <button onClick={() => showTournamentInfo(lobby)} key={index} className="bg-gradient-to-br from-slate-800 via-slate-800 to-slate-900 border border-orange-600/10 rounded-xl p-6 shadow-xl flex flex-col items-start hover:border-orange-500 hover:shadow-orange-500/10 transition-all">
                                        <div className="text-lg font-bold text-orange-400 mb-2">{lobby.name}</div>
                                        <div className="text-sm text-gray-300">{getText('tournamentPlayersLabel')}<span className="font-semibold text-white">{lobby.players.length}</span> / {lobby.numberOfPlayers}</div>
                                    </button>
                                ))}
                            </div>
                        ) : (
                            <div className="text-center py-16">
                                <p className="text-gray-400 text-lg mb-4">{getText('tournamentNoTournaments')}</p>
                            </div>
                        )}
                        <div className="flex flex-col items-center mt-8">
                            <button onClick={() => setCreateTournamentLog(true)} className="px-6 py-3 bg-gradient-to-r from-red-700/80 via-red-700 to-red-700/80 hover:from-orange-600 hover:to-red-500 text-white font-bold rounded-lg shadow-lg transition-all">{getText('tournamentCreateTitle')}</button>
                            <span className="mt-2 text-gray-400">{getText('tournamentTotalLobbies')}{lobbyState.length}</span>
							<button className="mt-5 p-3 bg-orange-400 hover:bg-orange-500 text-white font-bold rounded-xl"
								onClick={() => setLocalTournament(prev => !prev)}
							>
								{getText('localTournament')}
							</button>
                        </div>
                    </>
                ))}
                {
                    tournamentReady &&
                    <TournamentGame currentTournament={currentTournament!}/>
                }
				{/* ✅ Modal de Histórico */}
                {showHistory && (
                    <TournamentHistoryModal
                        tournaments={tournamentHistory}
                        loading={historyLoading}
                        onClose={() => setShowHistory(false)}
                        onSelectTournament={setSelectedTournament}
                    />
                )}

                {/* ✅ Modal de Detalles */}
                {selectedTournament && (
                    <TournamentDetailModal
                        tournament={selectedTournament}
                        onClose={() => setSelectedTournament(null)}
                    />
                )}
            </div>
        </div>)}
		</>
    )
}

const TournamentHistoryModal = ({ tournaments, loading, onClose, onSelectTournament }: TournamentHistoryModalProps):ReactElement => {
    const [filter, setFilter] = useState('all');
    const [searchTerm, setSearchTerm] = useState('');
    const [currentPage, setCurrentPage] = useState(1);
    const itemsPerPage = 8;
	const {user, lan, language} = useContext(AuthContext)!;

	const getFallback = (key: string): string => {
        const fallbacks: Record<string, string> = {
            'tournamentBlockchainHistory': 'Blockchain Tournament History',
			'tournamentCount': "tournament",
			'tournamentCounts': "tournaments",
			'tournamentStoredOnAvalanche': 'Stored on Avalanche Fuji',
			'tournamentSearchPlaceholder': 'Search by tournament name or player...',
			'tournamentAll': '📋 All',
			'tournamentFinalized': '✅ Finalized',
			'tournamentPending': '⏳ Pending',
			'tournamentViewSnowtrace': 'View Snowtrace',
			'tournamentSnowtrace': 'Snowtrace',
			'tournamentLoadingBlockchain': '🔄 Loading blockchain data...',
			'tournamentLoadingMessage': 'This may take a few moments',
			'tournamentNoMatchFilters': 'No tournaments match your filters',
			'tournamentNoRegistered': 'No tournaments registered on blockchain yet',
			'tournamentPlayers': 'Players',
			'tournamentDate': 'Date',
			'tournamentDuration': 'Duration',
			'tournamentChampion': 'Champion',
			'tournamentPrevious': '← Previous',
			'tournamentPaginationStart': "Page",
			'tournamentPaginationMiddle': "of",
			'tournamentPaginationEnd': "",
			'tournamentNext': 'Next →',
			'chatClose': 'Close',
        };
        
        return fallbacks[key] || key;
    };

    const getText = (key: string): string => {
        if (!language) {
            console.warn('Language object is not available');
            return getFallback(key);
        }
        
        if (!lan) {
            console.warn('Language code (lan) is not available');
            return getFallback(key);
        }
        
        if (!(lan in language)) {
            console.warn(`Language '${lan}' is not available in language object`);
            return getFallback(key);
        }
        
        // Acceso seguro a la propiedad del idioma
        const languageData = language[lan];
        if (!languageData || typeof languageData !== 'object') {
            console.warn(`Language data for '${lan}' is null, undefined or not an object`);
            return getFallback(key);
        }
        
        // Verificar si la clave específica existe
        if (!(key in languageData)) {
            console.warn(`Key '${key}' not found in language '${lan}'`);
            return getFallback(key);
        }
        
        const languageRecord = languageData as unknown as Record<string, unknown>;
        const value = languageRecord[key];
        
        // Verificar que el valor existe y es string
        if (value === undefined) {
            console.warn(`Value for key '${key}' is undefined`);
            return getFallback(key);
        }
        
        return typeof value === 'string' ? value : getFallback(key);
    };
    const filteredTournaments = tournaments.filter(t => {
        const matchesFilter = 
            filter === 'all' ? true :
            filter === 'finalized' ? t.isFinalized :
            !t.isFinalized;
        
        const matchesSearch = 
            t.tournamentName.toLowerCase().includes(searchTerm.toLowerCase()) ||
            t.aliases?.some(a => a.toLowerCase().includes(searchTerm.toLowerCase()));
        
        return matchesFilter && matchesSearch;
    });

    const totalPages = Math.ceil(filteredTournaments.length / itemsPerPage);
    const startIndex = (currentPage - 1) * itemsPerPage;
    const paginatedTournaments = filteredTournaments.slice(startIndex, startIndex + itemsPerPage);

    return (
        <div 
            className="fixed inset-0 bg-black/80 flex items-center justify-center p-4 z-50 backdrop-blur-sm"
            onClick={onClose}
        >
            <div 
                className="bg-gradient-to-br from-slate-800 to-slate-900 rounded-xl max-w-5xl w-full max-h-[90vh] overflow-hidden border border-blue-500/30 shadow-2xl"
                onClick={(e) => e.stopPropagation()}
            >
                {/* Header */}
                <div className="flex justify-between items-center p-6 border-b border-gray-700 bg-gradient-to-r from-blue-900/30 to-cyan-900/30">
                    <div>
                        <h2 className="text-3xl font-bold text-transparent bg-clip-text bg-gradient-to-r from-blue-400 to-cyan-500 flex items-center gap-3">
                            <span>🔗</span>
                            <span>{getText('tournamentBlockchainHistory')}</span>
                        </h2>
                        <p className="text-sm text-gray-400 mt-1">
                            {filteredTournaments.length}  {filteredTournaments.length !== 1 ? getText('tournamentCounts') : getText('tournamentCount')} • {getText('tournamentStoredOnAvalanche')}
                        </p>
                    </div>
                    <button
                        onClick={onClose}
                        className="text-gray-400 hover:text-white text-3xl font-bold transition-colors hover:rotate-90 duration-300"
                    >
                        ×
                    </button>
                </div>

                {/* Filtros y Búsqueda */}
                <div className="p-4 bg-slate-900/50 border-b border-gray-700 space-y-3">
                    {/* Búsqueda */}
                    <div className="relative">
                        <input
                            type="text"
                            value={searchTerm}
                            onChange={(e) => {
                                setSearchTerm(e.target.value);
                                setCurrentPage(1);
                            }}
                            placeholder={getText('tournamentSearchPlaceholder')}
                            className="w-full px-4 py-2 pl-10 bg-slate-800 text-white rounded-lg border border-gray-700 focus:border-blue-500 focus:outline-none transition-colors"
                        />
                        <span className="absolute left-3 top-2.5 text-gray-400">🔍</span>
                    </div>

                    {/* Filtros */}
                    <div className="flex flex-wrap gap-2">
                        {['all', 'finalized', 'pending'].map((f) => (
                            <button
                                key={f}
                                onClick={() => {
                                    setFilter(f);
                                    setCurrentPage(1);
                                }}
                                className={`px-4 py-2 rounded-lg font-semibold transition-all ${
                                    filter === f
                                        ? 'bg-blue-600 text-white shadow-lg'
                                        : 'bg-slate-800 text-gray-400 hover:bg-slate-700'
                                }`}
                            >
                                {f === 'all' ? getText('tournamentAll') : f === 'finalized' ? getText('tournamentFinalized') : getText('tournamentPending')}
                            </button>
                        ))}
                        
                        {/* Link a Snowtrace */}
                        <a
                            href="https://testnet.snowtrace.io/address/0x7bEd67Bf730941761680600c12429f67d12e2c7E"
                            target="_blank"
                            rel="noopener noreferrer"
                            className="ml-auto px-4 py-2 bg-gradient-to-r from-orange-600 to-red-600 text-white rounded-lg font-semibold hover:shadow-lg transition-all flex items-center gap-2"
                        >
                            <span>🔗</span>
                            <span className="hidden sm:inline">{getText('tournamentViewSnowtrace')}</span>
                            <span className="sm:hidden">{getText('tournamentSnowtrace')}</span>
                        </a>
                    </div>
                </div>

                {/* Content */}
                <div className="p-6 overflow-y-auto max-h-[calc(90vh-280px)]">
                    {loading ? (
                        <div className="text-center py-12">
                            <div className="inline-block animate-spin rounded-full h-12 w-12 border-t-2 border-b-2 border-blue-500 mb-4"></div>
                            <div className="text-blue-400 text-xl">{getText('tournamentLoadingBlockchain')}</div>
                            <div className="text-gray-500 text-sm mt-2">{getText('tournamentLoadingMessage')}</div>
                        </div>
                    ) : paginatedTournaments.length === 0 ? (
                        <div className="text-center py-12">
                            <div className="text-6xl mb-4">🏆</div>
                            <div className="text-gray-400 text-lg">
                                {searchTerm || filter !== 'all' 
                                    ? getText('tournamentNoMatchFilters') 
                                    : getText('tournamentNoRegistered')}
                            </div>
                        </div>
                    ) : (
                        <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                            {paginatedTournaments.map((tournament) => {
                                const duration = tournament.isFinalized && tournament.endTime > 0
                                    ? Math.floor((tournament.endTime - tournament.startTime) / 60)
                                    : null;
                                
                                return (
                                    <div
                                        key={tournament.recordId}
                                        onClick={() => onSelectTournament(tournament)}
                                        className="bg-gradient-to-r from-slate-900 to-slate-800 rounded-lg p-4 border border-gray-700 hover:border-blue-500 transition-all cursor-pointer hover:shadow-lg hover:shadow-blue-500/20 group"
                                    >
                                        <div className="flex justify-between items-start mb-3">
                                            <div className="flex items-center gap-2 flex-1 min-w-0">
                                                <span className="px-2 py-1 bg-gradient-to-r from-blue-600 to-cyan-600 text-white text-xs font-bold rounded-full shadow flex-shrink-0">
                                                    #{tournament.recordId}
                                                </span>
                                                <h3 className="text-lg font-bold text-white group-hover:text-blue-400 transition-colors truncate">
                                                    {tournament.tournamentName}
                                                </h3>
                                            </div>
                                            <span className={`px-2 py-1 text-xs font-bold rounded-full shadow flex-shrink-0 ml-2 ${
                                                tournament.isFinalized
                                                    ? 'bg-gradient-to-r from-green-600 to-emerald-600 text-white'
                                                    : 'bg-gradient-to-r from-yellow-600 to-orange-600 text-white'
                                            }`}>
                                                {tournament.isFinalized ? '✅' : '⏳'}
                                            </span>
                                        </div>

                                        <div className="grid grid-cols-2 gap-3 text-sm">
                                            <div>
                                                <div className="text-gray-400 text-xs">{getText('tournamentPlayers')}</div>
                                                <div className="text-white font-bold flex items-center gap-1">
                                                    <span>👥</span>
                                                    <span>{tournament.aliases?.length || 0}</span>
                                                </div>
                                            </div>
                                            <div>
                                                <div className="text-gray-400 text-xs">{getText('tournamentDate')}</div>
                                                <div className="text-white font-bold text-xs">
                                                    {new Date(tournament.startTime * 1000).toLocaleDateString('en-US', { 
                                                        month: 'short', 
                                                        day: 'numeric',
                                                        year: '2-digit'
                                                    })}
                                                </div>
                                            </div>
                                            {duration !== null && (
                                                <div>
                                                    <div className="text-gray-400 text-xs">{getText('tournamentDuration')}</div>
                                                    <div className="text-white font-bold text-xs">
                                                        ⏱️ {duration}m
                                                    </div>
                                                </div>
                                            )}
                                            {tournament.isFinalized && tournament.aliases?.[0] && (
                                                <div>
                                                    <div className="text-gray-400 text-xs">{getText('tournamentChampion')}</div>
                                                    <div className="text-yellow-400 font-bold flex items-center gap-1 truncate text-xs">
                                                        <span>🏆</span>
                                                        <span className="truncate">{tournament.aliases[0]}</span>
                                                    </div>
                                                </div>
                                            )}
                                        </div>
                                    </div>
                                );
                            })}
                        </div>
                    )}
                </div>

                {/* Paginación */}
                {totalPages > 1 && (
                    <div className="p-4 border-t border-gray-700 bg-slate-900/50 flex justify-center items-center gap-2">
                        <button
                            onClick={() => setCurrentPage(p => Math.max(1, p - 1))}
                            disabled={currentPage === 1}
                            className="px-4 py-2 bg-slate-800 text-white rounded-lg disabled:opacity-50 disabled:cursor-not-allowed hover:bg-slate-700 transition-colors"
                        >
                            {getText('tournamentPrevious')}
                        </button>
                        <span className="text-gray-400 mx-4">
                            {getText('tournamentPaginationStart')} {currentPage} {getText('tournamentPaginationMiddle')} {totalPages} {getText('tournamentPaginationEnd')}
                        </span>
                        <button
                            onClick={() => setCurrentPage(p => Math.min(totalPages, p + 1))}
                            disabled={currentPage === totalPages}
                            className="px-4 py-2 bg-slate-800 text-white rounded-lg disabled:opacity-50 disabled:cursor-not-allowed hover:bg-slate-700 transition-colors"
                        >
                            {getText('tournamentNext')}
                        </button>
                    </div>
                )}
            </div>
        </div>
    );
};

const TournamentDetailModal = ({ tournament, onClose }: TournamentDetailModalProps) => {
    
	const {user, lan, language} = useContext(AuthContext)!;

	const getFallback = (key: string): string => {
        const fallbacks: Record<string, string> = {
            'tournamentBlockchainHistory': 'Blockchain Tournament History',
			'tournamentCount': "tournament",
			'tournamentCounts': "tournaments",
			'tournamentStoredOnAvalanche': 'Stored on Avalanche Fuji',
			'tournamentSearchPlaceholder': 'Search by tournament name or player...',
			'tournamentAll': '📋 All',
			'tournamentFinalized': '✅ Finalized',
			'tournamentPending': '⏳ Pending',
			'tournamentViewSnowtrace': 'View Snowtrace',
			'tournamentSnowtrace': 'Snowtrace',
			'tournamentLoadingBlockchain': '🔄 Loading blockchain data...',
			'tournamentLoadingMessage': 'This may take a few moments',
			'tournamentNoMatchFilters': 'No tournaments match your filters',
			'tournamentNoRegistered': 'No tournaments registered on blockchain yet',
			'tournamentPlayers': 'Players',
			'tournamentDate': 'Date',
			'tournamentDuration': 'Duration',
			'tournamentChampion': 'Champion',
			'tournamentPrevious': '← Previous',
			'tournamentPaginationStart': "Page",
			'tournamentPaginationMiddle': "of",
			'tournamentPaginationEnd': "",
			'tournamentNext': 'Next →',
			'chatClose': 'Close',
			'tournamentBlockchainRecord': 'Blockchain Record',
			'tournamentRecordId': 'Record ID:',
			'tournamentStatus': 'Status:',
			'tournamentStartTime': 'Start Time:',
			'tournamentEndTime': 'End Time:',
			'tournamentMinutes': 'minutes',
			'tournamentViewOnSnowtrace': 'View on Snowtrace',
			'tournamentFinalRankings': '🏆 Final Rankings',
			'tournamentParticipants': '👥 Participants',
			'tournamentPoints': 'pts',
        };
        
        return fallbacks[key] || key;
    };

    const getText = (key: string): string => {
        if (!language) {
            console.warn('Language object is not available');
            return getFallback(key);
        }
        
        if (!lan) {
            console.warn('Language code (lan) is not available');
            return getFallback(key);
        }
        
        if (!(lan in language)) {
            console.warn(`Language '${lan}' is not available in language object`);
            return getFallback(key);
        }
        
        // Acceso seguro a la propiedad del idioma
        const languageData = language[lan];
        if (!languageData || typeof languageData !== 'object') {
            console.warn(`Language data for '${lan}' is null, undefined or not an object`);
            return getFallback(key);
        }
        
        // Verificar si la clave específica existe
        if (!(key in languageData)) {
            console.warn(`Key '${key}' not found in language '${lan}'`);
            return getFallback(key);
        }
        
        const languageRecord = languageData as unknown as Record<string, unknown>;
        const value = languageRecord[key];
        
        // Verificar que el valor existe y es string
        if (value === undefined) {
            console.warn(`Value for key '${key}' is undefined`);
            return getFallback(key);
        }
        
        return typeof value === 'string' ? value : getFallback(key);
    };
	
	return (
        <div 
            className="fixed inset-0 bg-black/80 flex items-center justify-center p-4 z-50 backdrop-blur-sm"
            onClick={onClose}
        >
            <div 
                className="bg-gradient-to-br from-slate-800 to-slate-900 rounded-xl max-w-2xl w-full border border-blue-500/30 shadow-2xl max-h-[90vh] overflow-y-auto"
                onClick={(e) => e.stopPropagation()}
            >
                {/* Header */}
                <div className="flex justify-between items-start p-6 border-b border-gray-700 bg-gradient-to-r from-blue-900/30 to-cyan-900/30 sticky top-0 z-10">
                    <div className="flex-1 min-w-0">
                        <h2 className="text-3xl font-bold text-white mb-2 truncate">
                            {tournament.tournamentName}
                        </h2>
                        <div className="flex flex-wrap items-center gap-2 text-sm">
                            <span className="px-3 py-1 bg-blue-600 text-white rounded-full font-semibold">
                                #{tournament.recordId}
                            </span>
                            <span className={`px-3 py-1 rounded-full font-semibold ${
                                tournament.isFinalized 
                                    ? 'bg-green-600 text-white' 
                                    : 'bg-yellow-600 text-white'
                            }`}>
                                {tournament.isFinalized ? getText('tournamentFinalized') : getText('tournamentPending')}
                            </span>
                        </div>
                    </div>
                    <button
                        onClick={onClose}
                        className="text-gray-400 hover:text-white text-2xl hover:rotate-90 transition-all duration-300 flex-shrink-0 ml-4"
                    >
                        ×
                    </button>
                </div>

                {/* Content */}
                <div className="p-6 space-y-6">
                    {/* Blockchain Info */}
                    <div className="bg-gradient-to-r from-blue-900/20 to-cyan-900/20 border border-blue-500/30 rounded-lg p-5">
                        <div className="text-blue-400 font-bold mb-4 flex items-center gap-2 text-lg">
                            <span>🔗</span>
                            <span>{getText('tournamentBlockchainRecord')}</span>
                        </div>
                        <div className="space-y-3 text-sm">
                            <div className="flex justify-between items-center">
                                <span className="text-gray-400">{getText('tournamentRecordId')}</span>
                                <span className="text-white font-mono font-bold">#{tournament.recordId}</span>
                            </div>
                            <div className="flex justify-between items-center">
                                <span className="text-gray-400">{getText('tournamentStatus')}</span>
                                <span className={tournament.isFinalized ? 'text-green-400 font-bold' : 'text-yellow-400 font-bold'}>
                                    {tournament.isFinalized ? getText('tournamentFinalized') : getText('tournamentPending')}
                                </span>
                            </div>
                            <div className="flex justify-between items-center">
                                <span className="text-gray-400">{getText('tournamentStartTime')}</span>
                                <span className="text-white font-semibold">
                                    {new Date(tournament.startTime * 1000).toLocaleString()}
                                </span>
                            </div>
                            {tournament.isFinalized && tournament.endTime > 0 && (
                                <>
                                    <div className="flex justify-between items-center">
                                        <span className="text-gray-400">{getText('tournamentEndTime')}</span>
                                        <span className="text-white font-semibold">
                                            {new Date(tournament.endTime * 1000).toLocaleString()}
                                        </span>
                                    </div>
                                    <div className="flex justify-between items-center">
                                        <span className="text-gray-400">{getText('tournamentDuration')}:</span>
                                        <span className="text-white font-semibold">
                                            ⏱️ {Math.floor((tournament.endTime - tournament.startTime) / 60)} {getText('tournamentDuration')}
                                        </span>
                                    </div>
                                </>
                            )}
                            <div className="pt-3 border-t border-blue-500/20">
                                <a
                                    href="https://testnet.snowtrace.io/address/0x7bEd67Bf730941761680600c12429f67d12e2c7E"
                                    target="_blank"
                                    rel="noopener noreferrer"
                                    className="flex items-center justify-center gap-2 px-4 py-2 bg-gradient-to-r from-orange-600 to-red-600 hover:from-orange-700 hover:to-red-700 text-white rounded-lg font-bold transition-all shadow-lg"
                                >
                                    <span>🔗</span>
                                    <span>{getText('tournamentViewSnowtrace')}</span>
                                    <span>↗</span>
                                </a>
                            </div>
                        </div>
                    </div>

                    {/* Players & Scores */}
                    <div>
                        <h3 className="text-2xl font-bold text-white mb-4 flex items-center gap-2">
                            {tournament.isFinalized ? getText('tournamentFinalRankings') : getText('tournamentParticipants')}
                        </h3>
                        <div className="space-y-2">
                            {tournament.aliases?.map((alias, index) => {
                                const isChampion = index === 0 && tournament.isFinalized;
                                return (
                                    <div
                                        key={index}
                                        className={`flex items-center justify-between p-4 rounded-lg transition-all ${
                                            isChampion
                                                ? 'bg-gradient-to-r from-yellow-600/30 to-orange-600/30 border-2 border-yellow-500 shadow-lg shadow-yellow-500/20'
                                                : 'bg-slate-800 hover:bg-slate-700'
                                        }`}
                                    >
                                        <div className="flex items-center gap-4 flex-1 min-w-0">
                                            <span className="text-3xl flex-shrink-0">
                                                {index === 0 && tournament.isFinalized ? '🥇' : 
                                                 index === 1 && tournament.isFinalized ? '🥈' : 
                                                 index === 2 && tournament.isFinalized ? '🥉' : 
                                                 `${index + 1}.`}
                                            </span>
                                            <div className={`w-12 h-12 flex-shrink-0 rounded-full flex items-center justify-center text-xl font-bold ${
                                                isChampion 
                                                    ? 'bg-gradient-to-br from-yellow-500 to-orange-600 text-white shadow-lg' 
                                                    : 'bg-slate-700 text-white'
                                            }`}>
                                                {alias[0]?.toUpperCase()}
                                            </div>
                                            <span className={`font-bold text-lg truncate ${
                                                isChampion ? 'text-yellow-300' : 'text-white'
                                            }`}>
                                                {alias}
                                                {isChampion && <span className="ml-2">👑</span>}
                                            </span>
                                        </div>
                                        {tournament.isFinalized && tournament.scores?.[index] !== undefined && (
                                            <span className={`font-mono font-bold text-lg flex-shrink-0 ml-4 ${
                                                isChampion ? 'text-yellow-300' : 'text-gray-400'
                                            }`}>
                                                {tournament.scores[index]} {getText('tournamentPoints')}
                                            </span>
                                        )}
                                    </div>
                                );
                            })}
                        </div>
                    </div>

                    {/* Close Button */}
                    <button
                        onClick={onClose}
                        className="w-full px-6 py-3 bg-gradient-to-r from-blue-600 to-cyan-600 hover:from-blue-700 hover:to-cyan-700 text-white rounded-lg font-bold transition-all shadow-lg"
                    >
                        {getText('chatClose')}
                    </button>
                </div>
            </div>
        </div>
    );
};

interface TournamentGameProps {
    currentTournament: Tournament;
}

const TournamentGame = ({ currentTournament }: TournamentGameProps): ReactElement => {
    const { user, language, lan } = useContext(AuthContext)!;
    const { socket } = useContext(ComponentContext)!;
    const { tournamentJustStarted, tournamentGame } = useContext(TournamentContext)!;
    const canvasRef = useRef<HTMLCanvasElement | null>(null);

    const keysPressed = useRef<Set<string>>(new Set());
    const animationFrameId = useRef<number | null>(null);
    const localTournamentPaddleY = useRef<number>(150);
    // ✅ NUEVO: Guardar ID de sala activa
    const activeRoomId = useRef<string | null>(null);

    const [currentRound, setCurrentRound] = useState<string>('');
    const [showCloseTournamentButton, setShowCloseTournamentButton] = useState<boolean>(false);

useEffect(() => {

    const newRoomId = tournamentGame?.id;
    
    if (!socket) {
        console.warn('❌ Socket no disponible');
        return;
    }

    if (!newRoomId) {
        if (activeRoomId.current) {
        }
        return;
    }

    // Verificar si ya hay controles activos
    if (activeRoomId.current === newRoomId && animationFrameId.current) {
        return;
    }

    // Si es la misma sala pero NO hay animation loop (recarga), reinicializar
    if (activeRoomId.current === newRoomId && !animationFrameId.current) {
    }

    // Limpiar animation loop anterior si existe
    if (animationFrameId.current) {
        cancelAnimationFrame(animationFrameId.current);
        animationFrameId.current = null;
    }

    activeRoomId.current = newRoomId;

    const SPEED = 5;
    const isPlayer1 = tournamentGame.player1?.userId === user?.id;


    // Inicializar posición
    if (tournamentGame.tournamentGameState) {
        const initialY = isPlayer1 
            ? tournamentGame.tournamentGameState.player1.y 
            : tournamentGame.tournamentGameState.player2.y;
        localTournamentPaddleY.current = initialY;
    }

    const handleKeyDown = (e: KeyboardEvent) => {
        if (!['ArrowUp', 'ArrowDown'].includes(e.key)) return;
        e.preventDefault();
        keysPressed.current.add(e.key);
    };

    const handleKeyUp = (e: KeyboardEvent) => {
        if (['ArrowUp', 'ArrowDown'].includes(e.key)) {
            e.preventDefault();
            keysPressed.current.delete(e.key);
        }
    };

    // ✅ FIX: Variable fuera del closure
    let frameCount = 0;
    
    const animationLoop = () => {
        if (!activeRoomId.current) return;

        let direction = 0;
        if (keysPressed.current.has('ArrowUp')) direction = -1;
        if (keysPressed.current.has('ArrowDown')) direction = 1;

        if (direction !== 0) {
            localTournamentPaddleY.current = Math.max(0, Math.min(300, 
                localTournamentPaddleY.current + direction * SPEED));
            
            // Solo emitir cada 3 frames (~50ms @ 60fps = ~20 emits/s)
            frameCount++;
            if (frameCount % 3 === 0) {
                socket.emit('paddleTournamentGameMove', activeRoomId.current, 
                    localTournamentPaddleY.current, isPlayer1);
            }
        }

        animationFrameId.current = requestAnimationFrame(animationLoop);
    };

    window.addEventListener('keydown', handleKeyDown);
    window.addEventListener('keyup', handleKeyUp);
    
    // ✅ Iniciar animation loop una sola vez
    animationFrameId.current = requestAnimationFrame(animationLoop);

    return () => {
        window.removeEventListener('keydown', handleKeyDown);
        window.removeEventListener('keyup', handleKeyUp);
        if (animationFrameId.current) {
            cancelAnimationFrame(animationFrameId.current);
            animationFrameId.current = null;
        }
        keysPressed.current.clear();
    };
}, [socket, tournamentGame?.id, user?.id]);

	const getText = (key: string): string => {
        if (!language) {
            console.warn('Language object is not available');
            return getFallback(key);
        }
        
        if (!lan) {
            console.warn('Language code (lan) is not available');
            return getFallback(key);
        }
        
        if (!(lan in language)) {
            console.warn(`Language '${lan}' is not available in language object`);
            return getFallback(key);
        }
        
        const languageData = language[lan];
        if (!languageData || typeof languageData !== 'object') {
            console.warn(`Language data for '${lan}' is null, undefined or not an object`);
            return getFallback(key);
        }
        
        if (!(key in languageData)) {
            console.warn(`Key '${key}' not found in language '${lan}'`);
            return getFallback(key);
        }
        
        const languageRecord = languageData as unknown as Record<string, unknown>;
        const value = languageRecord[key];
        
        if (value === undefined) {
            console.warn(`Value for key '${key}' is undefined`);
            return getFallback(key);
        }
        
        return typeof value === 'string' ? value : getFallback(key);
    };

    const getFallback = (key: string): string => {
        const fallbacks: Record<string, string> = {
			'Tournaments': 'Tournaments',
			'tournamentName': "Tournament's Name",
			'tournamentNumberOfPlayers': 'Number of Players',
			'tournamentNumberOfPlayersPlaceholder': 'Number of Players (4, 8, 16, ...)',
			'tournamentCreateNewTournament': 'Create New Tournament',
			'tournamentLeaveTournament': 'Leave Tournament',
			'tournamentHost': 'HOST',
			'tournamentAvailableSeat': 'Available Seat',
			'tournamentPlayersLabel': 'Players: ',
			'tournamentNoTournaments': 'No tournaments available. Create one!',
			'tournamentCreateTitle': 'Create Tournament',
			'tournamentTotalLobbies': 'Total lobbies: ',
			'tournamentCongratulations': 'CONGRATULATIONS',
			'tournamentYouAreWinner': 'YOU ARE THE WINNER!!!',
			'tournamentHasWon': 'HAS WON THE TOURNAMENT!!!',
			'tournamentFinal': 'FINAL',
			'tournamentSemifinals': 'SEMIFINALS',
			'tournamentQuarterfinals': 'QUARTERFINALS',
			'tournamentRoundOf16': 'ROUND OF 16',
			'tournamentRoundOf32': 'ROUND OF 32',
			'tournamentRoundOf64': 'ROUND OF 64',
			'tournamentPlayerBracket': '-player bracket',
			'tournamentNoTournamentFound': 'No tournament found',
			'tournamentVS': 'VS',
			'tournamentCloseTournament': 'CLOSE TOURNAMENT',
			'tournamentNamePlaceholder': "Enter Tournament's Name",
  			'tournamentScore': 'Score',
        };
        
        return fallbacks[key] || key;
    };
    useEffect(() => {
        if (!currentTournament) return;

        const playersCount = currentTournament.players.length;
        let round = '';

        if (playersCount === 1) {
            const IamTheWinner = user?.username === currentTournament.players[0]?.username;
            if (IamTheWinner)
                round = `${getText('tournamentCongratulations')} ${currentTournament.players[0]?.username} ${getText('tournamentYouAreWinner')}`;
            else {
                round = `${currentTournament.players[0]?.username} ${getText('tournamentHasWon')}`;
            }
            setShowCloseTournamentButton(true);
        }
        else if (playersCount <= 2) round = getText('tournamentFinal');
        else if (playersCount <= 4) round = getText('tournamentSemifinals');
        else if (playersCount <= 8) round = getText('tournamentQuarterFinals');
        else if (playersCount <= 16) round = getText('tournamentRoundOf16');
        else if (playersCount <= 32) round = getText('tournamentRoundOf32');
        else if (playersCount <= 64) round = getText('tournamentRoundOf64');
        else round = `${playersCount}${getText('tournamentPlayerBracket')}`;

        setCurrentRound(round);
    }, [currentTournament?.players.length]);

	useEffect(() => {
		if (!tournamentGame || !tournamentGame.tournamentGameState) {
			return;
		}

		const gameState = tournamentGame.tournamentGameState;
		const canvas = canvasRef.current;
		if (!canvas) return;
		const ctx = canvas.getContext("2d");
		if (!ctx) return;

		ctx.clearRect(0, 0, canvas.width, canvas.height);

		// Center dashed line
		ctx.strokeStyle = "#444";
		ctx.lineWidth = 2;
		ctx.setLineDash([10, 10]);
		ctx.beginPath();
		ctx.moveTo(canvas.width / 2, 0);
		ctx.lineTo(canvas.width / 2, canvas.height);
		ctx.stroke();
		ctx.setLineDash([]);

		// Paddles
		ctx.fillStyle = "white";
		ctx.fillRect(
			gameState.player1.x,
			gameState.player1.y,
			gameState.player1.width,
			gameState.player1.height
		);
		ctx.fillRect(
			gameState.player2.x,
			gameState.player2.y,
			gameState.player2.width,
			gameState.player2.height
		);

		// 🌀 BALL WITH ROTATING SPOKES AND SPIN EFFECTS (igual que Game.tsx)
		ctx.save();
		ctx.translate(gameState.ball.x, gameState.ball.y);
		
		// Aplicar rotación
		const rotation = gameState.ball.rotation || 0;
		ctx.rotate(rotation);
		
		// Glow effect según velocidad
		const speed = gameState.ball.speed || 5;
		const glowIntensity = Math.min(speed / 20, 1);
		
		if (glowIntensity > 0.3) {
			ctx.shadowBlur = 20 * glowIntensity;
			ctx.shadowColor = gameState.ball.spin 
				? (gameState.ball.spin.type === 'topspin' ? '#ff4444' : '#44ff44')
				: '#ffffff';
		}
		
		// Cuerpo de la bola (blanco)
		ctx.fillStyle = '#ffffff';
		ctx.beginPath();
		ctx.arc(0, 0, gameState.ball.radius, 0, Math.PI * 2);
		ctx.fill();
		
		// 8 radios desde el centro
		const numSpokes = 8;
		const spokeColor = gameState.ball.spin 
			? (gameState.ball.spin.type === 'topspin' ? '#ff4444' : '#44ff44')
			: '#888888';
		
		ctx.strokeStyle = spokeColor;
		ctx.lineWidth = 2;
		
		for (let i = 0; i < numSpokes; i++) {
			const angle = (i / numSpokes) * Math.PI * 2;
			ctx.beginPath();
			ctx.moveTo(0, 0);
			ctx.lineTo(
				Math.cos(angle) * gameState.ball.radius * 0.8,
				Math.sin(angle) * gameState.ball.radius * 0.8
			);
			ctx.stroke();
		}
		
		// Círculo central con color según spin
		if (gameState.ball.spin && gameState.ball.spin.intensity > 0.3) {
			ctx.fillStyle = spokeColor;
			ctx.beginPath();
			ctx.arc(0, 0, gameState.ball.radius * 0.3, 0, Math.PI * 2);
			ctx.fill();
			
			// Indicador de dirección del spin
			ctx.strokeStyle = '#ffffff';
			ctx.lineWidth = 2;
			ctx.beginPath();
			
			if (gameState.ball.spin.type === 'topspin') {
				// Flecha hacia abajo
				ctx.moveTo(0, -gameState.ball.radius * 0.4);
				ctx.lineTo(0, gameState.ball.radius * 0.4);
				ctx.lineTo(-3, gameState.ball.radius * 0.2);
				ctx.moveTo(0, gameState.ball.radius * 0.4);
				ctx.lineTo(3, gameState.ball.radius * 0.2);
			} else {
				// Flecha hacia arriba
				ctx.moveTo(0, gameState.ball.radius * 0.4);
				ctx.lineTo(0, -gameState.ball.radius * 0.4);
				ctx.lineTo(-3, -gameState.ball.radius * 0.2);
				ctx.moveTo(0, -gameState.ball.radius * 0.4);
				ctx.lineTo(3, -gameState.ball.radius * 0.2);
			}
			ctx.stroke();
		} else {
			// Círculo central gris si no hay spin
			ctx.fillStyle = '#666666';
			ctx.beginPath();
			ctx.arc(0, 0, gameState.ball.radius * 0.3, 0, Math.PI * 2);
			ctx.fill();
		}
		
		ctx.restore();
		ctx.shadowBlur = 0;

		// Highlight player's paddle with green border
		const isPlayer1 = tournamentGame.player1.userId === user?.id;
		ctx.strokeStyle = '#0f0';
		ctx.lineWidth = 3;
		
		if (isPlayer1) {
			ctx.strokeRect(
				gameState.player1.x - 1,
				gameState.player1.y - 1,
				gameState.player1.width + 2,
				gameState.player1.height + 2
			);
		} else {
			ctx.strokeRect(
				gameState.player2.x - 1,
				gameState.player2.y - 1,
				gameState.player2.width + 2,
				gameState.player2.height + 2
			);
		}
	}, [tournamentGame, user]);

    /* const handleMouseMove = (e: React.MouseEvent<HTMLCanvasElement, MouseEvent>): void => {
        if (!socket) return;
        const canvas = canvasRef.current;
        if (!canvas) return;
        const rect = canvas.getBoundingClientRect();
        const mouseY = e.clientY - rect.top;
        const isPlayer1 = user?.id === tournamentGame?.player1.userId;
        socket.emit("paddleTournamentGameMove", tournamentGame?.id, mouseY, isPlayer1);
    } */

    const renderPlayerCard = (player: User | undefined): ReactElement | null => {
        if (!player) return null;

        const isHost = player.host === true;
        const borderColor = isHost ? 'border-red-600' : 'border-slate-700';
        const avatarStyle = isHost 
            ? 'bg-gradient-to-br from-orange-600 to-red-600 text-white border-2 border-red-500 shadow-lg' 
            : 'bg-slate-800 text-white';
        const nameColor = isHost ? 'text-orange-300' : 'text-white';

        return (
            <div className={`bg-slate-900 border ${borderColor} rounded-lg p-4 flex flex-col items-center shadow hover:shadow-red-600/15 transition-all relative w-40`}>
                <div className={`w-12 h-12 rounded-full flex items-center justify-center text-xl font-bold mb-2 ${avatarStyle}`}>
                    {player.username[0]?.toUpperCase()}
                </div>
                <div className={`font-semibold ${nameColor}`}>
                    {player.username}
                </div>
                {isHost && (
                    <div className="absolute top-2 right-2">
                        <span className="bg-gradient-to-r from-orange-600 to-red-600 text-white text-xs font-semibold px-2 py-1 rounded border border-red-500 shadow" title="Host">
                            {getText('tournamentHost')}
                        </span>
                    </div>
                )}
            </div>
        );
    };

    const renderMatchups = (): ReactElement => {
        if (!currentTournament) {
            return (
                <div className="text-white text-center">
                    {getText('tournamentNoTournamentFound')}
                </div>
            );
        }

        const numberOfPairs = currentTournament.players.length / 2;

        return (
            <div className="grid grid-cols-2">
                {Array.from({ length: numberOfPairs }).map((_, pairIndex) => {
                    const leftPlayer = currentTournament.players[pairIndex * 2];
                    const rightPlayer = currentTournament.players[pairIndex * 2 + 1];

                    return (
                        <div key={pairIndex} className="flex items-center justify-center gap-6 mb-6 col-span-2">
                            {renderPlayerCard(leftPlayer)}
                            <span className="text-3xl font-bold text-orange-400 mx-2 select-none">
                                {getText('tournamentVS')}
                            </span>
                            {renderPlayerCard(rightPlayer)}
                        </div>
                    );
                })}
            </div>
        );
    };

    const closeTournament = (): void => {
        setShowCloseTournamentButton(false);
        socket?.emit("removePlayerFromTournament", user?.id, currentTournament.id)
    }

    //The !! ensures isWinner is a boolean.
    const isWinner: boolean = !!currentRound && !!user && currentRound.includes(getText('tournamentYouAreWinner')) && currentRound.includes(user.username);

    return (
        <div className="text-white">
            {
                currentTournament.players.length === 1 && user?.username === currentTournament.players[0]?.username && <Confetti/>
            }
            {(!tournamentJustStarted && !tournamentGame) ? (
                <div>
                    <div className="text-center mb-6">
                        <span className={`${isWinner ? 'animate-bounce ' : ''}inline-flex items-center px-4 py-2 bg-gradient-to-r from-slate-800/70 to-slate-700/50 border border-gray-600 text-sm md:text-base text-slate-100 rounded-full font-semibold tracking-wider shadow-sm`}>
                            {currentRound}
                        </span>
                    </div>
                    {renderMatchups()}
                </div>
            ) : (
                <div className="text-center mb-4">
                    <span className={`${isWinner ? 'animate-bounce ' : ''}inline-flex items-center px-4 py-2 bg-gradient-to-r from-slate-800/70 to-slate-700/50 border border-gray-600 text-sm md:text-base text-slate-100 rounded-full font-semibold tracking-wider shadow-sm`}>
                        {currentRound}
                    </span>
                </div>
            )}

            {
                tournamentGame &&
                <div className="max-w-[840px] mx-auto bg-gradient-to-br from-slate-900/80 to-slate-800/60 border border-gray-700 rounded-xl p-4 shadow-xl text-slate-100">
                        <div className="flex items-center justify-between gap-4 mb-4">
                            <div className="flex items-center gap-3">
                                <div className={`w-10 h-10 rounded-full ${tournamentGame.player1.userId === user?.id ? 'bg-gradient-to-br from-orange-600 to-red-600' : 'bg-slate-700'} flex items-center justify-center text-white font-bold`}>
                                    {tournamentGame.player1.username[0]?.toUpperCase()}
                                </div>
                                <div className="text-sm">
                                    <div className="font-medium">{tournamentGame.player1.username}</div>
                                </div>
                            </div>

                            <div className="text-center">
                                <div className="text-xs text-slate-300">{getText('tournamentScore')}</div>
                                    <div className="text-xl md:text-2xl font-extrabold flex items-center justify-center gap-3">
                                        <span className="text-red-400">{tournamentGame.tournamentGameState.player1.score}</span>
                                        <span className="text-slate-400 font-semibold tracking-wide">{getText('tournamentVS')}</span>
                                        <span className="text-red-400">{tournamentGame.tournamentGameState.player2.score}</span>
                                    </div>
                            </div>

                            <div className="flex items-center gap-3">
                                <div className="text-sm text-right">
                                    <div className="font-medium">{tournamentGame.player2.username}</div>
                                </div>
                                <div className={`w-10 h-10 rounded-full ${tournamentGame.player2.userId === user?.id ? 'bg-gradient-to-br from-orange-600 to-red-600' : 'bg-slate-700'} flex items-center justify-center text-white font-bold`}>
                                    {tournamentGame.player2.username[0]?.toUpperCase()}
                                </div>
                            </div>
                        </div>
                </div>
            }

            {tournamentGame && (
                <div className="text-red-700 mt-4">
                    <div className="flex justify-center min-w-max">
                        <canvas 
                            className="bg-black border-4 border-gray-700 rounded-lg shadow-2xl cursor-none" 
                            ref={canvasRef} 
                            width={800} 
                            height={400} 
                            id="gameCanvas" 
                            // onMouseMove={handleMouseMove}
                            />
                    </div>
                </div>
            )}

            {
                showCloseTournamentButton && 
                <div className="flex justify-center items-center mt-12">
                    <button
                        onClick={closeTournament}
                        className="inline-flex items-center gap-3 px-6 py-3 bg-gradient-to-r from-red-700 to-red-600 hover:from-red-600 hover:to-red-500 text-white font-bold rounded-full shadow-2xl hover:shadow-red-700/40 transition focus:outline-none focus:ring-2 focus:ring-red-400 focus:ring-offset-2 disabled:opacity-50"
                    >
                        <span className="text-lg md:text-xl tracking-wider text-slate-800">{getText('tournamentCloseTournament')}</span>
                    </button>
                </div>
            }
        </div>
    );
};