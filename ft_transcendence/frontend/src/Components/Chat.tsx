import {useState, useEffect, useContext} from 'react'
import { AuthContext } from '../Context/AuthContext'
import ChatSideBar from './Chat/ChatSideBar'
import ChatMain from './Chat/ChatMain'
import type { AuthContextType, ComponentContextType} from '../types'
import { ComponentContext } from '../Context/ComponentsContext'

export default function Chat(){
	const [presentConversation,setPresentConversation] = useState<number>(0)
	const componentContext = useContext(ComponentContext) as ComponentContextType;
	const { conversations, setConversations } = componentContext;
	const authContext = useContext(AuthContext) as AuthContextType;
	const {token, language, lan} = authContext;
	const [loading, setLoading] = useState(false)


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
            'chatNoConversations': 'No conversations yet',
        };
        
        return fallbacks[key] || key;
    };

	const fetchConversations = async() =>{
		try{
			setLoading(true)
			const response = await fetch('/api/chat/conversations',{
				headers:{
					'Content-Type': 'application/json',
					'Authorization': `Bearer ${token}`,
					'Accept': 'application/json',
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
	},[])
	useEffect(() => {
		if (presentConversation !== 0 && !conversations.some(c => c.id === presentConversation)) {
			setPresentConversation(0);
		}
	}, [conversations, presentConversation]);
	return(
		<div className='relative h-full flex min-w-fit '>
			<div className='w-15'>
				<ChatSideBar presentConversation = {presentConversation} setPresentConversation={setPresentConversation} />
			</div>
			{loading && <p>Loading chat</p>}
			{!loading && conversations.length === 0 ? (
				<div className='text-white text-3xl flex-1 flex justify-center items-center'>
					{getText('chatNoConversations')}
				</div>
			)
			: (
				<div className='flex-1 w-20'>
					<ChatMain presentConversation = {presentConversation}/>
				</div>
			)}
		</div>
	)
}