import { useContext, useState, useEffect } from 'react'
import { AuthContext } from '../../Context/AuthContext'
import type { AuthContextType, ComponentContextType } from '../../types'
import { ComponentContext } from '../../Context/ComponentsContext';

interface MessageInputProps{
    presentConversation: number;
}

export default function MessageInput({ presentConversation } : MessageInputProps){
    const [message, setMessage] = useState<string>('')
    const componentContext = useContext(ComponentContext) as ComponentContextType;
	const { blockedUsers, blockedByUsers,conversations, loadingBlocked } = componentContext;
    const authContext = useContext(AuthContext) as AuthContextType;
    const {token, language, lan, getCsrfToken} = authContext;
	
	let otherUserId: number | null = null;
    if (presentConversation && conversations) {
        const conv = conversations.find(c => c.id === presentConversation);
        if (conv && authContext.user) {
            otherUserId = conv.user1Id === authContext.user.id ? conv.user2Id : conv.user1Id;
        }
    }
    
	const isBlocked = !!otherUserId && (
        blockedUsers.includes(otherUserId) || blockedByUsers.includes(otherUserId)
    );
    const handleSend = async(e:React.FormEvent) => {
        e.preventDefault();
        if (!message.trim()) return;
        if (isBlocked) {
            alert('Someone is blocked in this conversation');
            return;
        }
		if (message.length > 4000) {
			alert(`Your message must be less than 4000 characters. You are sending ${message.length} characters`)
			setMessage('')
			return;
		}
		const csrfToken = getCsrfToken();
        const response = await fetch(`/api/chat/conversations/${presentConversation}/messages`,{
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': `Bearer ${token}`,
				'Accept': 'application/json',
				'X-CSRF-Token': csrfToken				
            },
            body: JSON.stringify({message})
        });
        if (response.ok){
            setMessage('')
        }else{
            const data = await response.json();
            alert(data.error || 'Could not send the message')
        }
    }

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
            'chatMessagePlaceholder': 'Type your message...',
			'chatLoadingBlockState': 'Loading block status...',
			'chatSomeoneBlocked': 'Someone is blocked in this conversation',
			'chatSend': 'Send',
        };
        
        return fallbacks[key] || key;
    };

    return (
        <form className='flex w-full' onSubmit = {handleSend}>
            <input
                type = "text"
                className='flex-1 p-3 text-black rounded-xl'
                value = {message}
                onChange={e => setMessage(e.target.value)}
                placeholder={getText('chatMessagePlaceholder')}
                disabled={isBlocked || loadingBlocked}
            />
            <button
                type="submit"
                className='p-3 bg-slate-600 rounded-xl ml-2'
                disabled={isBlocked || loadingBlocked}
            >
                {getText('chatSend')}
            </button>
            {loadingBlocked && (
				<div className="text-gray-500 text-sm mt-2 ml-2 mr-2">{getText('chatLoadingBlockState')}</div>
			)}
			{isBlocked && !loadingBlocked && (
				<div className="text-red-600 font-bold mt-2 ml-2 mr-2">{getText('chatSomeoneBlocked')}</div>
			)}
        </form>
    )
}