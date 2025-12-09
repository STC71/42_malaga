import { ComponentContext } from "../Context/ComponentsContext";
import { AuthContext } from "../Context/AuthContext";
import { useState, useContext } from 'react';
import { useNavigate } from "react-router-dom";
import { FaLock, FaUnlock } from "react-icons/fa";
import type { AuthContextType, ComponentContextType, GameRoom } from "../types";

const Matches: React.FC = (): React.ReactElement => {
    const componentContext = useContext(ComponentContext) as ComponentContextType | undefined;
    const authContext = useContext(AuthContext) as AuthContextType | undefined;
    
    if (!authContext || !componentContext) {
        throw new Error('Matches must be used within AuthContextProvider and ComponentContextProvider');
    }
    
    const { roomsRunning, setRoomIamIn, roomIamIn, socket, setWaitingForOpponent } = componentContext;
    const { user, language, lan } = authContext;
    const navigate = useNavigate();

    const safeRoomsRunning = roomsRunning || [];

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
            'matchesROOMSRUNNING': 'ROOMS RUNNING',
            'matchesNoActiveRooms': 'No Active Rooms',
            'matchesNoActiveRoomsMsg': 'There are currently no game rooms running. Be the first to create one!',
            'matchesNoActiveRoomsAdvice': 'Start a new game to see it appear here',
            'matchesAVAILABLE': 'AVAILABLE',
            'matchesROOMFULL': 'ROOM FULL',
            'matchesCannotJoin': 'Cannot Join',
            'matchesWaiting': 'waiting...',
            'matchesPlayer1': 'Player 1',
            'matchesClickToJoin': 'Click to Join'
        };
        
        return fallbacks[key] || key;
    };

    const joinRoom = (room: GameRoom, roomId: string): void => {
        if (!setWaitingForOpponent || !setRoomIamIn || !socket) {
            console.error('Required functions or socket not available');
            return;
        }

        // Check if player is already in this room
        if (room && (room.players.length > 1 || room.aiEnabled)) {
            setWaitingForOpponent(false);
        }
        
        if (roomIamIn === roomId) {
            navigate('/index/game');
            return;
        }

        // Check if player is allowed in this room
        if (room && user) {
            const isPlayerInRoom = room.players.some(player => player.userId === user.id);
            if (!isPlayerInRoom && (room.players.length === 2 || room.aiEnabled)) {
                return;
            }
        }

        socket.emit("joinRoomGame", roomId);
        setRoomIamIn(roomId);
        navigate('/index/game');
    };

    return ( 
        <div className="text-white flex flex-col justify-center items-center">
            <h1 className="mb-10 font-bold text-3xl">{getText('matchesROOMSRUNNING')}</h1>
            {safeRoomsRunning.length === 0 ? (
                <div className="flex flex-col items-center justify-center py-20 px-8">
                    <div className="bg-slate-800/50 rounded-2xl border border-slate-600 p-12 text-center max-w-md">
                        <div className="text-6xl mb-6 opacity-30">🎮</div>
                        <h2 className="text-2xl font-bold text-white mb-4">{getText('matchesNoActiveRooms')}</h2>
                        <p className="text-gray-400 text-lg mb-6">
                            {getText('matchesNoActiveRoomsMsg')}
                        </p>
                        <div className="text-sm text-slate-400">
                            {getText('matchesNoActiveRoomsAdvice')}
                        </div>
                    </div>
                </div>
            ) : (
                <div className="flex flex-wrap gap-4 w-full justify-center items-center">
                    {safeRoomsRunning.map((rooms, index) => {
                        return (
                            rooms.players.some(p => p.userId === user?.id) || (!rooms.aiEnabled && rooms.players.length < 2) ? 
                            (
                                <button 
                                    key={index} 
                                    className="relative w-64 h-72 bg-gradient-to-br from-slate-600 via-slate-700 to-slate-800 rounded-xl shadow-lg border border-slate-500 overflow-hidden hover:shadow-xl hover:scale-105 transition-all duration-300 group text-white"
                                    onClick={() => joinRoom(rooms, rooms.roomId)}
                                >
                                    {/* Available Status Banner */}
                                    <div className="absolute top-0 left-0 right-0 bg-green-500 text-white text-xs font-bold py-2 px-3 flex items-center justify-center gap-2">
                                        <FaUnlock className="w-3 h-3" />
                                        <span>{getText('matchesAVAILABLE')}</span>
                                    </div>
                                    
                                    {/* Main Content */}
                                    <div className="pt-10 px-6 pb-6 h-full flex flex-col justify-center items-center text-center">
                                        <h3 className="text-xl font-bold mb-4 truncate w-full">{rooms.roomId}</h3>
                                        
                                        <div className="bg-white/10 rounded-lg p-4 mb-6 w-full backdrop-blur-sm">
                                            <div className="flex items-center justify-center gap-3">
                                                <div className="text-sm font-medium truncate max-w-20">
                                                    {rooms.players.find(p => p.isPlayer1)?.username || 'Player 1'}
                                                </div>
                                                <div className="text-white/80 font-bold text-xs">VS</div>
                                                <div className="text-sm font-medium truncate max-w-20">
                                                    {rooms.aiEnabled ? '🤖 AI' : (rooms.players.find(p => !p.isPlayer1)?.username || getText('matchesWaiting'))}
                                                </div>
                                            </div>
                                        </div>
                                        
                                        <div className="text-xs text-green-200 opacity-80 group-hover:opacity-100 transition-opacity">
                                            {getText('matchesClickToJoin')}
                                        </div>
                                    </div>
                                </button>
                            ) 
                            :
                            (
                                <div
                                    key={index}
                                    className="relative w-64 h-72 bg-gradient-to-br from-slate-600 via-slate-700 to-slate-800 rounded-xl shadow-lg border border-slate-500 overflow-hidden text-white flex flex-col"
                                >
                                    {/* Lock Status Banner */}
                                    <div className="absolute top-0 left-0 right-0 bg-red-500 text-white text-xs font-bold py-2 px-3 flex items-center justify-center gap-2">
                                        <FaLock className="w-3 h-3" />
                                        <span>{getText('matchesROOMFULL')}</span>
                                    </div>
                                    {/* Main Content */}
                                    <div className="pt-10 px-6 pb-6 h-full flex flex-col justify-center items-center text-center">
                                        <h3 className="text-xl font-bold mb-4 truncate w-full">{rooms.roomId}</h3>
                                        <div className="bg-white/10 rounded-lg p-4 mb-6 w-full backdrop-blur-sm">
                                            <div className="flex items-center justify-center gap-3">
                                                <div className="text-sm font-medium truncate max-w-20">
                                                    {rooms.players.find(p => p.isPlayer1)?.username || getText('matchesPlayer1')}
                                                </div>
                                                <div className="text-white/80 font-bold text-xs">VS</div>
                                                <div className="text-sm font-medium truncate max-w-20">
                                                    {rooms.aiEnabled ? '🤖 AI' : (rooms.players.find(p => !p.isPlayer1)?.username || getText('matchesWaiting'))}
                                                </div>
                                            </div>
                                        </div>
                                        <div className="text-xs text-gray-400 opacity-80">
                                            {getText('matchesCannotJoin')}
                                        </div>
                                    </div>
                                    <div className="absolute inset-0 bg-black bg-opacity-20 pointer-events-none"></div>
                                </div>
                            )
                        );
                    })}
                </div>
            )}
        </div>
    );
};

export default Matches;