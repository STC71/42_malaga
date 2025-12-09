import { useContext, useState, useEffect, type SetStateAction,type Dispatch } from 'react'
import { AuthContext } from '../../Context/AuthContext'
import { ComponentContext } from '../../Context/ComponentsContext';
import type { AuthContextType, ComponentContextType } from '../../types'
import { useNavigate } from 'react-router-dom';
import ShowProfile from './ShowProfile'



interface ChatHeaderProps{
	presentConversation: number;
}

export default function ChatHeader({presentConversation}:ChatHeaderProps){

	const [conversation, setConversation] = useState<any>(null);
	const authContext = useContext(AuthContext) as AuthContextType;
	const componentContext = useContext(ComponentContext) as ComponentContextType;
	const {token, language, lan} = authContext;
	const {socket, roomIamIn, setRoomIamIn, blockedUsers, blockedByUsers,conversations, loadingBlocked} = componentContext;
	const [loading, setLoading] = useState(false);
	const [showProfile, setShowProfile] = useState(false)
	const [pvpInvitation, setPvpInvitation] = useState(false)
	const [showInvitation, setShowInvitation] = useState(false);

	const navigate = useNavigate();

	useEffect(() => {
		function handler(){
			setShowInvitation(true)
		}
		socket?.on("receiveInvitation", handler)
		return () => {
			socket?.off("receiveInvitation", handler)
		};
	}, [socket])
	useEffect(() => {
        if (!socket || !roomIamIn) return;
        socket.emit("roomImIn", roomIamIn);
    }, [roomIamIn, socket]);

	useEffect(() => {
		if (!socket) return;
		const handler = ({roomName} : any) => {
			
			socket.emit("joinRoomGame", roomName);
			if (setRoomIamIn) setRoomIamIn(roomName);
			navigate('/index/game')
		};
		socket.on("invitationAccepted", handler);
		return () => {
			socket?.off("invitationAccepted", handler)
		};
	}, [socket]);

	function handleInvitation(){
		if (!socket || !otherUser?.id) return;
  		socket.emit("sendInvitation", { toUserId: otherUser.id });
	}

	const createGamePvp = (): void => {
		if (!socket) return;
		const roomNameId = `${authContext.user?.username} vs ${otherUser.username}`
		socket.emit("createRoomInvitation", authContext.user?.username, otherUser.username);
		navigate('/index/game')
		socket.emit("joinRoomGame", roomNameId);
		if (setRoomIamIn)
			setRoomIamIn(roomNameId)
		socket.emit("sendAcceptedInvitation", otherUser.id, roomNameId)
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
            'chatInvitationToPlayWith': 'Invitation to play with ',
			'chatAccept': 'Accept',
			'chatReject': 'Reject',
			'chatLoading': 'Loading...',
			'chatPlay': 'Play',
        };
        
        return fallbacks[key] || key;
    };

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

	const invitation = () =>{
		return (
			<div className="fixed inset-0 z-50 flex items-center justify-center bg-black bg-opacity-60">
				<div className='bg-slate-300 rounded-lg shadow-lg p-6 w-full max-w-md relative text-black'>
					<h2 className='flex justify-center mb-5 font-bold'>{getText('chatInvitationToPlayWith')}<span className='font-bold animate-glow ml-3'>{otherUser.username}</span> </h2>
					<div className="flex justify-center space-x-5">
						
						<button
							className="p-3 bg-slate-400 font-bold hover:bg-green-500 text-green-600 rounded-xl  hover:text-black"
							onClick={() => {setShowInvitation(false);createGamePvp();}}
						>
							{getText('chatAccept')}
						</button>
						<button
							className="p-3 bg-slate-400 hover:bg-red-500 rounded-xl font-bold text-red-500 hover:text-black"
							onClick={() => setShowInvitation(false)}
						>
							{getText('chatReject')}
						</button>
					</div>
				</div>
			</div>
		)
	}

	const fetchConversation = async () =>{
		try{
			setLoading(true)
			const response = await fetch(`/api/chat/conversations/${presentConversation}`,{
				headers:{
					'Content-Type': 'application/json',
					'Authorization': `Bearer ${token}`,
					'Accept': 'application/json'
				}
			})
			if (response.ok){
				const data = await response.json()
				setConversation(data.conversation || [])
			}

		}catch(error){
			alert(`Error: ${error}`)
		}finally{
			setLoading(false)
		}
	}
	useEffect(() => {
		fetchConversation()
	},[presentConversation])
	if (!conversation) return <div>{getText('chatLoading')}</div>;

	const myId = authContext.user?.id;
	const otherUser =
	conversation.user1Id === myId ? conversation.User2 : conversation.User1;

	return (
		loading ? <h2>{getText('chatLoading')}</h2> : 
		<div className="bg-slate-600 p-5 flex items-center gap-4">
			<img 
				src={otherUser.avatar || `https://ui-avatars.com/api/?name=${otherUser.username}&size=128`}
				alt={otherUser.username}
				className='relative rounded-full w-14 h-14 border-4 border-slate-700 group-hover:border-amber-500/50 object-cover transition-all duration-300'
			/>
			<h2 className="text-2xl font-bold underline underline-offset-4 decoration-emerald-300/60 cursor-pointer hover:decoration-emerald-400 hover:text-emerald-300 transition-colors"
				onClick = {() => setShowProfile(true)}
			>{otherUser.displayName || otherUser.username}</h2>
			{showProfile && <ShowProfile setShowProfile={setShowProfile} otherUser ={otherUser} />}
			<button className='ml-auto p-4 bg-cyan-400 text-red-600 rounded-xl'
				onClick={() => handleInvitation()}
				disabled={isBlocked || loadingBlocked}
			>
				{getText('chatPlay')}
			</button>
			{showInvitation && invitation()}
		</div>
	);
}