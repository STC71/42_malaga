import { AuthContext } from '../../Context/AuthContext'
import { useContext, useState, useEffect, type SetStateAction,type Dispatch } from 'react'
import type { AuthContextType } from '../../types'
import ShowProfile from './ShowProfile'
import { ComponentContext } from '../../Context/ComponentsContext'
import type { ComponentContextType } from '../../types'

interface ConversationListProps{
	presentConversation: number;
	setPresentConversation: Dispatch<SetStateAction<number>>
}

interface ProfileData {
    username: string;
    displayName: string;
    email: string;
    avatar: string;
    wins: number;
    losses: number;
    winRate: number;
}

export default function ConversationList({presentConversation, setPresentConversation} : ConversationListProps){
	const componentContext = useContext(ComponentContext) as ComponentContextType;
	const { conversations, setConversations } = componentContext;
	const authContext = useContext(AuthContext) as AuthContextType;
	const {token,lan, language, getCsrfToken} = authContext;
	const [loading, setLoading] = useState(false)
	const [showProfile, setShowProfile] = useState(false);
	const [deletingId, setDeletingId] = useState<number | null>(null);
	const [selectedUser, setSelectedUser] = useState<ProfileData | null>(null);

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
			'chatConversationList': 'Conversation List',
			'chatLoadingConversations': 'Loading conversations',
			'chatDeleting': 'Deleting...',
			'chatDeleteConversation': 'Delete',
        };
        
        return fallbacks[key] || key;
    };

	const handleDeleteConversation = async (conversationId: number) => {
        setDeletingId(conversationId);
        try {
			const csrfToken = getCsrfToken();
            const res = await fetch(`/api/chat/conversations/${conversationId}`, {
                method: 'DELETE',
                headers: {
                    'Authorization': `Bearer ${token}`,
					'Accept': 'application/json',
					'X-CSRF-Token': csrfToken
                }
            });
            const data = await res.json();
            if (res.ok) {
            } else {
                alert(data.error || 'No se pudo eliminar la conversación');
            }
        } catch (err) {
            alert('Error al eliminar conversación');
        } finally {
            setDeletingId(null);
        }
    };
	const fetchConversations = async() =>{
		try{
			setLoading(true)
			const response = await fetch('/api/chat/conversations',{
				headers:{
					'Content-Type': 'application/json',
					'Authorization': `Bearer ${token}`,
					'Accept': 'application/json'
				}
			})
			if (response.ok){
				const data = await response.json()
				setConversations(data.conversations || []);
			}
		}catch(error){
			alert(`Error: ${error}`)
		}finally{
			setLoading(false)
		}
	}

	useEffect(() =>{
		fetchConversations()
	},[deletingId])
	return(
		<div className="m-2">
			<h3 className="font-bold p-3 m-8 bg-gradient-to-br from-emerald-400 via-emerald-500 to-green-400  rounded-xl">💬  {getText('chatConversationList')}</h3>
			<div className='text-black max-h-64 overflow-y-auto flex flex-col items-center'>
				{loading && <p>{getText('chatLoadingConversations')}</p>}
				{!loading && conversations.length > 0 && (
					conversations.map((conversation: any) => {
						const myId = authContext.user?.id;
						const otherUser =
							conversation.user1Id === myId
								? conversation.User2
								: conversation.User1;

						return (
							<div
								key={conversation.id}
								role = "button"
								className='p-3 m-2 bg-slate-400 rounded-xl hover:bg-violet-400 max-w-[300px] min-w-[200px] flex justify-left items-center m'
								onClick = {() => (presentConversation !== conversation.id && setPresentConversation(conversation.id))}
							>
								<img 
									src={otherUser.avatar || `https://ui-avatars.com/api/?name=${otherUser.username}&size=128`}
									alt={otherUser.username}
									className='relative rounded-full w-10 h-10 border-4 border-slate-700 group-hover:border-amber-500/50 object-cover transition-all duration-300'
								/>
								<span className='ml-3 font-bold underline underline-offset-4 decoration-emerald-300/60 cursor-pointer hover:decoration-emerald-400 hover:text-emerald-300 transition-colors'
									onClick = {(e) => {
										e.stopPropagation();
										setSelectedUser(otherUser);
										setShowProfile(true);
									}}
								>{otherUser.displayName || otherUser.username}</span>
								<div className='ml-auto'>
									<button
										className="ml-2 px-2 py-1 rounded bg-red-600 text-white text-sm"
										onClick={(e) => { e.stopPropagation(); handleDeleteConversation(conversation.id); }}
										disabled={deletingId === conversation.id}
									>
										{deletingId === conversation.id ? getText('chatDeleting') : getText('chatDeleteConversation')}
									</button>
								</div>
								

								{showProfile && <ShowProfile setShowProfile={setShowProfile} otherUser={selectedUser}/>}
							</div>
						);
					})
				)}
			</div>
			
		</div>
	)
}