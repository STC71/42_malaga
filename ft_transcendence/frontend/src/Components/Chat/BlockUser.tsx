import { AuthContext } from '../../Context/AuthContext'
import { useContext, useState, useEffect, type SetStateAction, type Dispatch } from 'react'
import type { AuthContextType } from '../../types'

interface BlockUserProps {
    setBlockUser: Dispatch<SetStateAction<boolean>>,
    setBlockUserChange: Dispatch<SetStateAction<boolean>>
}

export default function BlockUser({ setBlockUser,setBlockUserChange }: BlockUserProps) {
    const authContext = useContext(AuthContext) as AuthContextType;
    const {token, language, lan, getCsrfToken} = authContext;
    const [friends, setFriends] = useState<any[]>([]);
    const [blocked, setBlocked] = useState<number[]>([]);
    const [loading, setLoading] = useState(false);

    const fetchFriends = async () => {
    	try {
            setLoading(true);
            const response = await fetch('/api/user/friends', {
                headers: { 'Authorization': `Bearer ${token}`,'Accept': 'application/json' }
            });
            if (response.ok) {
                const data = await response.json();
                setFriends(data.friends);
            }
        } catch (error) {
            console.error('Error fetching friends:', error);
        } finally {
            setLoading(false);
        }
    };

    const fetchBlocked = async () => {
        try {
            const response = await fetch('/api/chat/blocked', {
                headers: { 'Authorization': `Bearer ${token}`,'Accept': 'application/json' }
            });
            if (response.ok) {
                const data = await response.json();
                setBlocked(data.blockedUsers.map((u: any) => u.blockedUserId));
            }
        } catch (error) {
            console.error('Error fetching blocked users:', error);
        }
    };

    useEffect(() => {
        fetchFriends();
        fetchBlocked();
    }, []);

    const handleBlockUser = async (otherUserId: number) => {
        try {
			const csrfToken = getCsrfToken();
            setLoading(true);
            const response = await fetch('/api/chat/blocked', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${token}`,
					'Accept': 'application/json',
					'X-CSRF-Token': csrfToken
                },
                body: JSON.stringify({ userId: otherUserId })
            });
            const data = await response.json();
            if (response.ok && data.success) {
                setBlocked(prev => [...prev, otherUserId]);
				setBlockUserChange(prev => !prev)
            } else {
                alert(data.error || 'No se pudo bloquear al usuario');
            }
        } catch (error) {
            alert(`Error: ${error}`);
        } finally {
            setLoading(false);
        }
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
            'chatLoading': 'Loading...',
			'chatNewChatFriends': 'Friends',
			'chatNoFriendsYet': 'No friends yet',
			'chatBlock': 'Block',
			'chatBlocked': 'Blocked',
			'chatClose': 'Close',
        };
        
        return fallbacks[key] || key;
    };

    return (
        <div className="fixed inset-0 z-50 flex items-center justify-center bg-black bg-opacity-60">
            <div className='bg-slate-300 rounded-lg shadow-lg p-6 w-full max-w-md relative'>
                {loading && <h3>{getText('chatLoading')}</h3>}
                <button
                    className="absolute top-0 right-0 p-3 rounded-lg text-xl font-bold bg-slate-400 text-gray-600 hover:bg-red-500"
                    onClick={() => setBlockUser(false)}
                >
                    ×
                </button>
                <h2 className="text-lg font-bold mb-4 text-black">{getText('chatNewChatFriends')}</h2>
                <div className='text-black m-2'>
                    <div className='max-h-64 overflow-y-auto flex flex-col items-center'>
                        {friends.length === 0 && !loading && <p>{getText('chatNoFriendsYet')}</p>}
                        {friends.map((friend: any) => (
                            <div key={friend.id} className="flex items-center justify-between w-full max-w-[300px] min-w-[200px] bg-slate-400 rounded-xl p-2 m-2">
                                <span>{friend.displayName || friend.username}</span>
                                <button
                                    className={`ml-2 px-3 py-1 rounded ${blocked.includes(friend.id) ? 'bg-gray-400 cursor-not-allowed' : 'bg-red-500 hover:bg-red-600 text-white'}`}
                                    onClick={() => handleBlockUser(friend.id)}
                                    disabled={blocked.includes(friend.id) || loading}
                                >
                                    {blocked.includes(friend.id) ? getText('chatBlocked') : getText('chatBlock')}
                                </button>
                            </div>
                        ))}
                    </div>
                </div>
                <div className="flex justify-center">
                    <button
                        className="p-3 bg-slate-400 hover:bg-red-500 rounded-xl text-black"
                        onClick={() => setBlockUser(false)}
                    >
                        {getText('chatClose')}
                    </button>
                </div>
            </div>
        </div>
    )
}