import { useState, useEffect, useContext } from 'react';
import { AuthContext } from '../Context/AuthContext';
import { ComponentContext } from '../Context/ComponentsContext';
import type { AuthContextType, ComponentContextType } from '../types';

interface FriendRequestData {
    id: number;
    User: {
        username: string;
        avatar?: string;
    };
}

const FriendRequest: React.FC = (): React.ReactElement => {
    const [friendRequests, setFriendRequests] = useState<FriendRequestData[]>([]);
    const authContext = useContext(AuthContext) as AuthContextType | undefined;
    const componentContext = useContext(ComponentContext) as ComponentContextType | undefined;
    
    if (!authContext) {
        throw new Error('FriendRequest must be used within an AuthContextProvider');
    }
    
    const { token, language, lan,getCsrfToken } = authContext;
    const { socket } = componentContext || {};

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
            'profileNoFriendsYet': 'No Friend Requests',
            'frNoFriendRequestMsg': "Manage your incoming friend requests",
            'frWantsToBeYourFriend': 'Wants to be your friend',
            'frAcceptFriend': 'Accept',
            'frDeclineFriend': 'Decline',
            'frNoFriendRequest': 'No Friend Requests'
        };
        
        return fallbacks[key] || key;
    };

    const showFriendRequests = async (): Promise<void> => {
        try {
            const res = await fetch('/api/user/friend-getFriendRequests', {
                method: 'GET',
                headers: {'Authorization': `Bearer ${token}`,'Accept': 'application/json'}

            });
            if (res.ok) {
                const data = await res.json();
                const loggg = data.friendRequest;
                setFriendRequests(data.friendRequest);
            }
        } catch (err) {
            alert(err);
        }
    }

    const respondeFriendRequest = async (requestId: number, action: string): Promise<void> => {
        try {

			const csrfToken = getCsrfToken();
            const res = await fetch('/api/user/friend-response', {
                method: 'POST',
                headers: {"Content-Type": "application/json", Authorization: `Bearer ${token}`,'Accept': 'application/json','X-CSRF-Token': csrfToken },
                body: JSON.stringify({requestId, action})
            });
            if (res.ok) {
                alert(`friend Request ${action} succesfully`);
                showFriendRequests();
                
                // Si se acepta la solicitud, emitir evento para actualizar la lista de amigos
                if (action === 'accept' && socket) {
                    socket.emit('friendListUpdate');
                }
            }
        } catch (err) {
            alert(`Responde friend Request failed: ${err}`)
        }
    }

    useEffect(() => {
        showFriendRequests();
    }, [])

    return (
        <div className='flex-1 overflow-y-auto max-w-5xl mx-auto w-full p-6'> 
            {/* Header */}
            <div className="mb-8">
                <h1 className="text-4xl font-bold text-transparent bg-clip-text bg-gradient-to-r from-amber-400 to-orange-400 mb-2 tracking-tight flex items-center gap-3">
                    <span>👋</span>
                    {getText('profileNoFriendsYet')}
                </h1>
                <p className="text-gray-400 text-sm">{getText('frNoFriendRequestMsg') || "Manage your incoming friend requests"}</p>
            </div>

            {/* Friend Requests List */}
            <div className='flex flex-col gap-4'>
                {friendRequests.length !== 0 ? friendRequests.map((friend, index) => (
                    <div 
                        key={index} 
                        className='group relative bg-gradient-to-br from-slate-800 via-slate-900 to-slate-950 border border-amber-500/20 hover:border-amber-500/40 rounded-xl p-6 shadow-xl hover:shadow-amber-500/10 transition-all duration-300 overflow-hidden'
                    >
                        {/* Accent line */}
                        <div className="absolute top-0 left-0 right-0 h-1 bg-gradient-to-r from-transparent via-amber-400/50 to-transparent"></div>
                        
                        <div className='flex flex-row items-center gap-6'>
                            {/* Avatar with glow effect */}
                            <div className="relative flex-shrink-0">
                                <div className="absolute -inset-1 bg-gradient-to-r from-amber-500 to-orange-500 rounded-full opacity-30 group-hover:opacity-50 blur transition duration-300"></div>
                                <img 
                                    src={friend.User.avatar || `https://ui-avatars.com/api/?name=${friend.User.username}&size=128`}
                                    alt={friend.User.username}
                                    className='relative rounded-full w-20 h-20 border-4 border-slate-700 group-hover:border-amber-500/50 object-cover transition-all duration-300'
                                />
                            </div>
                            
                            {/* Username */}
                            <div className="flex-1">
                                <h2 className='text-2xl font-bold text-white group-hover:text-amber-400 transition-colors duration-200'>
                                    {friend.User.username}
                                </h2>
                                <p className="text-sm text-gray-400 mt-1">{getText('frWantsToBeYourFriend')}</p>
                            </div>
                            
                            {/* Action buttons */}
                            <div className='flex gap-3 flex-shrink-0'>
                                <button 
                                    onClick={() => respondeFriendRequest(friend.id, 'accept')} 
                                    className='group/btn bg-gradient-to-r from-emerald-600 to-emerald-500 hover:from-emerald-500 hover:to-emerald-400 text-white font-semibold px-6 py-3 rounded-lg transition-all duration-200 shadow-lg shadow-emerald-500/30 hover:shadow-emerald-500/50 hover:scale-105 active:scale-95 flex items-center gap-2'
                                >
                                    <span>✓</span>
                                    {getText('frAcceptFriend')}
                                </button>
                                <button  
                                    onClick={() => respondeFriendRequest(friend.id, 'reject')} 
                                    className='group/btn bg-gradient-to-r from-red-600 to-red-500 hover:from-red-500 hover:to-red-400 text-white font-semibold px-6 py-3 rounded-lg transition-all duration-200 shadow-lg shadow-red-500/30 hover:shadow-red-500/50 hover:scale-105 active:scale-95 flex items-center gap-2'
                                >
                                    <span>✕</span>
                                    {getText('frDeclineFriend')}
                                </button>
                            </div>
                        </div>
                    </div>
                )) :
                    <div className='relative bg-gradient-to-br from-slate-800 via-slate-900 to-slate-950 border border-slate-700/50 rounded-xl p-16 shadow-xl text-center overflow-hidden'> 
                        <div className="absolute top-0 left-0 right-0 h-1 bg-gradient-to-r from-transparent via-gray-600/50 to-transparent"></div>
                        
                        <div className="flex flex-col items-center justify-center">
                            <div className="text-7xl mb-6 opacity-50">📭</div>
                            <h1 className='text-2xl font-bold text-white/90 mb-2'>
                                {getText('frNoFriendRequest')}
                            </h1>
                            <p className="text-gray-400 max-w-md">
                                {getText('frNoFriendRequestMsg') || "You don't have any pending friend requests at the moment. When someone sends you a request, it will appear here."}
                            </p>
                        </div>
                    </div>
                }
            </div>
        </div>
    )
}

export default FriendRequest