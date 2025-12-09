import {useState, useRef, useContext, type SetStateAction,type Dispatch} from 'react'
import ConversationList from './ConversationList'
import BlockedUsersList from './BlockedUsersList'
import BlockUser from './BlockUser'
import NewChat from './NewChat'
import { AuthContext } from '../../Context/AuthContext'
import type { AuthContextType, ComponentContextType} from '../../types'
interface ChatSideBarProps{
	presentConversation: number;
	setPresentConversation: Dispatch<SetStateAction<number>>
}

export default function ChatSideBar({ presentConversation, setPresentConversation }: ChatSideBarProps){
	const [showConversation, setShowConversation] = useState(true)
	const [newChat, setNewChat] = useState(false)
	const [blockUser, setBlockUser] = useState(false)
	const [blockUserChange, setblockUserChange] = useState(false)
	const authContext = useContext(AuthContext) as AuthContextType;
	const {token, language, lan} = authContext;

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
            'chatNewChat': 'New Chat',
			'chatConversations': 'Conversations',
			'chatBlockedUsers': 'Blocked Users',
			'chatBlockUser': 'Block User',
        };
        
        return fallbacks[key] || key;
    };

	return (
		<div className="text-white bg-slate-300 h-full text-center p-3 flex-1 min-w-min">

			<button 
				onClick={() => !showConversation && setShowConversation(!showConversation)} 
				className={`font-bold ${showConversation ? "bg-green-500" : "bg-slate-500"} p-3 m-2 rounded-xl border-2 border-transparent hover:border-emerald-400 transition-all duration-300 shadow-lg hover:shadow-emerald-400/30`} >
				{getText('chatConversations')}
			</button>
			<button 
				onClick={() => showConversation && setShowConversation(!showConversation)} 
				className={`font-bold ${!showConversation ? "bg-red-500" : "bg-slate-500"} p-3 m-2 rounded-xl border-2 border-transparent hover:border-amber-400 transition-all duration-300 shadow-lg hover:shadow-amber-400/30`}>
				{getText('chatBlockedUsers')}
			</button>

			{showConversation ? <ConversationList presentConversation = {presentConversation} setPresentConversation={setPresentConversation}/> : <BlockedUsersList blockUserChange = {blockUserChange}/>}
			{showConversation ? (
			<>
				{newChat && <NewChat setNewChat = {setNewChat}/>}
				<button onClick={() => !newChat && setNewChat(!newChat)} className="font-bold bg-green-500 p-3 rounded-xl">
					+ {getText('chatNewChat')}
				</button>
			</>
			) : (
			<>
				{blockUser && <BlockUser setBlockUserChange = {setblockUserChange} setBlockUser={setBlockUser}/>}
				<button onClick={() => !blockUser && setBlockUser(!blockUser)} className="font-bold bg-red-500 p-3 rounded-xl">
					{getText('chatBlockUser')}
				</button>
			</>)}

		</div>
	)
}