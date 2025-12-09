import { useContext, useEffect, useState, useRef } from 'react'
import { AuthContext } from '../../Context/AuthContext'
import { ComponentContext } from '../../Context/ComponentsContext'
import type { AuthContextType, ComponentContextType } from '../../types'

interface MessageListProps{
    presentConversation: number;
}

interface Message {
    id: number;
    senderId: number;
    message: string;
    createdAt: string;
    Sender?: { username: string; displayName?: string };
}

export default function MessagesList({presentConversation}: MessageListProps){
    const authContext = useContext(AuthContext) as AuthContextType;
    const componentContext = useContext(ComponentContext) as ComponentContextType;
    const {token, language, lan} = authContext;
    const [loading, setLoading] = useState(false);
    const containerRef = useRef<HTMLDivElement>(null);

    const messages = componentContext?.chatMessages[presentConversation] || [];

    useEffect(() => {
        if (!token || !presentConversation) return;
        if (messages.length > 0) return;

        const fetchMessages = async () => {
            setLoading(true);
            try {
                const res = await fetch(`/api/chat/conversations/${presentConversation}/messages?page=1&limit=50`, {
                    headers: { 'Authorization': `Bearer ${token}`,'Accept': 'application/json' }
                });
                if (res.ok) {
                    const data = await res.json();
                    componentContext.setChatMessages(prev => ({
                        ...prev,
                        [presentConversation]: data.messages
                    }));
                }
            } finally {
                setLoading(false);
            }
        };
        fetchMessages();

    }, [presentConversation, token]);

    useEffect(() => {
        if (containerRef.current) {
            containerRef.current.scrollTop = containerRef.current.scrollHeight;
        }
    }, [messages]);

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
            'chatNoMessagesYet': 'No messages yet',
			'chatYou': 'You',
			'chatLoading': 'Loading...',
        };
        
        return fallbacks[key] || key;
    };

    return (
        <div
            ref={containerRef}
            className="flex-1 overflow-y-auto flex flex-col p-4"
            style={{ maxHeight: '73.5vh' }}
        >
            {messages.length === 0 && !loading && (
                <p className="text-center text-gray-400">{getText('chatNoMessagesYet')}</p>
            )}
            {messages.map(msg => (
                <div
                    key={msg.id}
                    className={`mb-2 p-2 rounded-xl max-w-sm ${
                        msg.senderId === authContext.user?.id
                            ? 'bg-emerald-400/30 self-end'
                            : 'bg-slate-400/30 self-start'
                    }`}
                >
                    <div className="text-xs text-gray-500">
                        {msg.Sender?.displayName || msg.Sender?.username || getText('chatYou')}
                    </div>
                    <div className="text-base break-words">{msg.message}</div>
                    <div className="text-xs text-right text-gray-400">
                        {new Date(msg.createdAt).toLocaleTimeString()}
                    </div>
                </div>
            ))}
            {loading && <div className="text-center text-gray-400">{getText('chatLoading')}</div>}
        </div>
    );
}