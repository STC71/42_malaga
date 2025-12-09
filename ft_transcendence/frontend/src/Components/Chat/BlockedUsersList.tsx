import { useContext, useEffect, useState } from 'react'
import { AuthContext } from '../../Context/AuthContext'
import type { AuthContextType, ComponentContextType } from '../../types'
import { ComponentContext } from '../../Context/ComponentsContext'

interface BlockedUsersListProps{
	blockUserChange : boolean
}

export default function BlockedUsersList({blockUserChange}: BlockedUsersListProps) {
    const authContext = useContext(AuthContext) as AuthContextType;
    const {token, language, lan, getCsrfToken} = authContext;
    const [blockedUsers, setBlockedUsers] = useState<any[]>([]);
    const [loading, setLoading] = useState(false);

    const fetchBlockedUsers = async () => {
        setLoading(true);
        try {
            const res = await fetch('/api/chat/blocked', {
                headers: { 'Authorization': `Bearer ${token}`,'Accept': 'application/json' }
            });
            if (res.ok) {
                const data = await res.json();
                setBlockedUsers(data.blockedUsers.map((b: any) => b.Blocked));
            }
        } catch (err) {
            alert('Error al obtener bloqueados');
        } finally {
            setLoading(false);
        }
    };

    const handleUnblock = async (userId: number) => {
        setLoading(true);
        try {
			const csrfToken = getCsrfToken();
            const res = await fetch('/api/chat/blocked', {
                method: 'DELETE',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${token}`,
					'Accept': 'application/json',
					'X-CSRF-Token': csrfToken
                },
                body: JSON.stringify({ userId })
            });
            if (res.ok) {
                setBlockedUsers(prev => prev.filter(u => u.id !== userId));
            } else {
                const data = await res.json();
                alert(data.error || 'No se pudo desbloquear');
            }
        } catch (err) {
            alert('Error al desbloquear');
        } finally {
            setLoading(false);
        }
    };

    useEffect(() => {
        fetchBlockedUsers();
    }, [blockUserChange]);

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
            'chatBlocked': 'Blocked',
			'chatLoadingBlocked': 'Loading blocked users...',
			'chatUnblock': 'Unblock',
        };
        
        return fallbacks[key] || key;
    };
    return (
        <div className="m-2">
            <h3 className="font-bold p-3 m-8 bg-gradient-to-br from-orange-400 via-orange-500 to-yellow-400 rounded-xl">🚫  {getText('chatBlocked')}</h3>
            <div className='text-black max-h-64 overflow-y-auto flex flex-col items-center'>
                {loading && <p>{getText('chatLoadingBlocked')}</p>}
                {!loading && blockedUsers.length > 0 && (
                    blockedUsers.map((user: any) => (
                        <div
                            key={user.id}
                            className='p-3 m-2 bg-slate-400 rounded-xl hover:bg-orange-300 max-w-[300px] min-w-[200px] flex justify-left items-center'
                        >
                            <img
                                src={user.avatar || `https://ui-avatars.com/api/?name=${user.username}&size=128`}
                                alt={user.username}
                                className='relative rounded-full w-10 h-10 border-4 border-slate-700 group-hover:border-amber-500/50 object-cover transition-all duration-300'
                            />
                            <span className='ml-3 flex-1'>{user.displayName || user.username}</span>
                            <button
                                className="ml-2 px-3 py-1 rounded bg-green-500 hover:bg-green-600 text-white"
                                onClick={() => handleUnblock(user.id)}
                                disabled={loading}
                            >
                                {getText('chatUnblock')}
                            </button>
                        </div>
                    ))
                )}
            </div>
        </div>
    )
}