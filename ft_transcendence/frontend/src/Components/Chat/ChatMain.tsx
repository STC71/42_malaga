import ChatHeader from "./ChatHeader"
import MessageInput from "./MessageInput"
import MessagesList from "./MessagesList"
import { useContext, useState, useEffect, type SetStateAction,type Dispatch } from 'react'
import { AuthContext } from '../../Context/AuthContext'
import { ComponentContext } from '../../Context/ComponentsContext';
import type { AuthContextType, ComponentContextType } from '../../types'
interface ChatMainProps{
	presentConversation: number;
}



export default function ChatMain({presentConversation} : ChatMainProps){
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
            'chatChooseConversation': 'Choose a conversation',
        };
        
        return fallbacks[key] || key;
    };

	return presentConversation !== 0 ? 
	(
		<div className="text-white  flex flex-col h-full min-w-min">
			<ChatHeader presentConversation={presentConversation}/>
			<div className="flex-1 overflow-y-auto">
				<MessagesList   presentConversation={presentConversation}/>			
			</div>
			<MessageInput presentConversation={presentConversation}/>
		</div>
	) : (
		<div className='text-white text-3xl h-full flex-1 flex justify-center items-center'>
					{getText('chatChooseConversation')}
		</div>
	)
}