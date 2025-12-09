import { createContext, useContext, useState, useRef, useEffect } from "react";
import type { ReactNode } from "react";
import { AuthContext } from "./AuthContext";
import type { AuthContextType, ComponentContextType, GameRoom, NotificationItem, LanguageContent } from "../types";
import { io, Socket } from 'socket.io-client';

export const ComponentContext = createContext<ComponentContextType | undefined>(undefined);

interface ComponentContextProviderProps {
    children: ReactNode;
}

interface SocketEventData {
    roomImIn?: string;
    isPlayerInRoom?: boolean;
    aiEnabled?: boolean;
    from?: string;
}

export function ComponentContextProvider({ children }: ComponentContextProviderProps): React.ReactElement {
    const [notifications, setNotifications] = useState<number>(0);
    const [notificationsList, setNotificationsList] = useState<NotificationItem[]>([]);
    const [roomsRunning, setRoomsRunning] = useState<GameRoom[]>([]);
    const [roomIamIn, setRoomIamIn] = useState<string>('');
    const [isAiEnabled, setIsAiEnabled] = useState<boolean>(false);
    const [waitingForOpponent, setWaitingForOpponent] = useState<boolean>(false); // Cambiado a false para permitir controles desde el inicio
    const [chatMessages, setChatMessages] = useState<{ [conversationId: number]: any[] }>({});
	const [conversations, setConversations] = useState<any[]>([]);
	const [blockedUsers, setBlockedUsers] = useState<number[]>([]);
	const [blockedByUsers, setBlockedByUsers] = useState<number[]>([]);
	const [loadingBlocked, setLoadingBlocked] = useState<boolean>(true);

    const authContext = useContext(AuthContext) as AuthContextType | undefined;

    
    if (!authContext) {
        throw new Error('ComponentContextProvider must be used within AuthContextProvider');
    }
    
    const { token, user, language, lan } = authContext;
    const socketRef = useRef<Socket | null>(null);

    const getLanguageText = (key: keyof LanguageContent): string => {
        // Verificar que language existe y es un objeto
        if (!language || typeof language !== 'object') {
            return 'has sent you a friend request'; // fallback en inglés
        }
        
        // Verificar que lan existe y es una clave válida en language
        if (!lan || !(lan in language)) {
            return 'has sent you a friend request'; // fallback en inglés
        }
        
        // Acceso seguro a la propiedad
        const languageContent = language[lan];
        if (!languageContent || typeof languageContent !== 'object') {
            return 'has sent you a friend request'; // fallback en inglés
        }
        
        // Retornar el valor o fallback
        return languageContent[key] || 'has sent you a friend request';
    };

    // Socket connection management
    useEffect(() => {
        // Connect socket when user is authenticated
        if (user && token) {
            socketRef.current = io(window.location.origin, {
                auth: {
                    token: token
                },
                autoConnect: true,
				transports: ['websocket', 'polling'],
                upgrade: true,
                secure: true,
                rejectUnauthorized: false,
				reconnection:true,
				reconnectionAttempts:5,
				reconnectionDelay:1000,
				reconnectionDelayMax:5000,
				timeout:20000
            });

            // Socket event listeners
            socketRef.current.on('connect', () => {
            });

            socketRef.current.on("startConnection", (data: SocketEventData) => {
                if (!data.isPlayerInRoom) {
                    setRoomIamIn('');
                    setIsAiEnabled(false);
                }
                if (data.roomImIn) {
                    setRoomIamIn(data.roomImIn);
                }
                setIsAiEnabled(data.aiEnabled || false);
            });

            socketRef.current.on('disconnect', () => {
            });

            socketRef.current.on('error', (error: Error) => {
                console.error('Socket error:', error);
            });

            socketRef.current.on("lobbyUpdate", (roomsRunningLobby: GameRoom[]) => {
                setRoomsRunning(roomsRunningLobby);
            });
			socketRef.current.on('sessionReplaced', (data: { message: string }) => {
				
				alert(data.message || 'Your session has been replaced by a new login.');
				
				// Limpiar estado local
				sessionStorage.removeItem('sessionId');
				
				// Desconectar socket
				if (socketRef.current) {
					socketRef.current.disconnect();
					socketRef.current = null;
				}
				
				// Redirigir al login
				window.location.href = '/login';
			});
            // Cleanup on unmount or when user logs out
            return () => {
                if (socketRef.current) {
					socketRef.current.off('sessionReplaced');
                    socketRef.current.disconnect();
                    socketRef.current = null;
                }
            };
        }
    }, [user, token]);

	//SendMessage from chat
	useEffect(() => {
        if (!socketRef.current) return;

        // Handler para mensajes de chat recibidos por socket
        const handleChatMessage = ({ conversationId, message }: { conversationId: number, message: any }) => {
            setChatMessages(prev => ({
                ...prev,
                [conversationId]: [...(prev[conversationId] || []), message]
            }));
        };

        socketRef.current.on('chatMessage', handleChatMessage);

        // Limpieza al desmontar o cambiar de usuario/token
        return () => {
            if (socketRef.current) {
                socketRef.current.off('chatMessage', handleChatMessage);
            }
        };
    }, [token, user]);

	// New chat from chat
	useEffect(() => {
        if (!socketRef.current) return;

        // Escuchar nueva conversación
        const handleNewConversation = ({ conversation }: { conversation: any }) => {
            setConversations(prev => {
                // Evita duplicados
                if (prev.some(c => c.id === conversation.id)) return prev;
                return [conversation, ...prev];
            });
        };

        socketRef.current.on('chatNewConversation', handleNewConversation);

        return () => {
            if (socketRef.current) {
                socketRef.current.off('chatNewConversation', handleNewConversation);
            }
        };
    }, [token, user]);

	// Delete chat from chat
	useEffect(() => {
		if (!socketRef.current) return;

		const handleConversationDeleted = ({ conversationId }: { conversationId: number }) => {
			setConversations(prev => prev.filter(c => c.id !== conversationId));
			// Opcional: si la conversación eliminada estaba activa, puedes resetear presentConversation aquí si lo gestionas en el contexto
		};

		socketRef.current.on('chatConversationDeleted', handleConversationDeleted);

		return () => {
			if (socketRef.current) {
				socketRef.current.off('chatConversationDeleted', handleConversationDeleted);
			}
		};
	}, [token,user]);

	//Block/Unblock user from chat
	useEffect(() => {
		if (!socketRef.current) return;

		const handleBlocked = ({ blockedUserId }: { blockedUserId: number }) => {
			setBlockedUsers(prev => [...prev, blockedUserId]);
		};

		const handleBlockedBy = ({ blockedById }: { blockedById: number }) => {
			setBlockedByUsers(prev => [...prev, blockedById]);
		};

		const handleUnblocked = ({ unblockedUserId }: { unblockedUserId: number }) => {
			setBlockedUsers(prev => prev.filter(id => id !== unblockedUserId));
		};

		const handleUnblockedBy = ({ unblockedById }: { unblockedById: number }) => {
			setBlockedByUsers(prev => prev.filter(id => id !== unblockedById));
		};

		socketRef.current.on('chatBlocked', handleBlocked);
		socketRef.current.on('chatBlocked', handleBlockedBy);
		socketRef.current.on('chatUnblocked', handleUnblocked);
		socketRef.current.on('chatUnblocked', handleUnblockedBy);

		return () => {
			if (socketRef.current) {
				socketRef.current.off('chatBlocked', handleBlocked);
				socketRef.current.off('chatBlocked', handleBlockedBy);
				socketRef.current.off('chatUnblocked', handleUnblocked);
				socketRef.current.off('chatUnblocked', handleUnblockedBy);
			}
		};
	}, [token,user]);

	useEffect(() => {
		if (!user || !token) return;

		setLoadingBlocked(true);

		// Fetch ambos en paralelo
		Promise.all([
			fetch('/api/chat/blocked', {
				headers: { Authorization: `Bearer ${token}` ,'Accept': 'application/json'}
			}).then(res => res.json()),
			fetch('/api/chat/blocked-by', {
				headers: { Authorization: `Bearer ${token}` ,'Accept': 'application/json'}
			}).then(res => res.json())
		])
		.then(([blockedData, blockedByData]) => {
			setBlockedUsers(blockedData.blockedUsers.map((u: any) => u.blockedUserId));
			setBlockedByUsers(blockedByData.blockedByUsers || []);
		})
		.finally(() => setLoadingBlocked(false));
	}, [user, token]);

    // Separate useEffect for friend request listener with dependencies
    useEffect(() => {
        if (!socketRef.current) return;

        const handleSendFriendRequest = (data: SocketEventData) => {
            setNotifications(notifications => notifications + 1);
            setNotificationsList(prevList => [...prevList, {
                id: Date.now(),
                user: data.from || 'Unknown', 
                msg: getLanguageText('NotyHasSendYouAFriendRequest'),
                time: Date.now(), 
                type: 'friendRequest', 
                status: true
            }]);
        };

        socketRef.current.on("sendFriendRequest", handleSendFriendRequest);

        return () => {
            if (socketRef.current) {
                socketRef.current.off("sendFriendRequest", handleSendFriendRequest);
            }
        };
    }, [token, user, lan, language]);

    // Update notification messages when language changes
    useEffect(() => {
        if (!language || !lan) return;
        
        setNotificationsList(prevList => 
            prevList.map(notify => {
                if (notify.type === 'friendRequest') {
                    return { 
                        ...notify, 
                        msg: getLanguageText('NotyHasSendYouAFriendRequest') 
                    };
                }
                return notify;
            })
        );
    }, [lan, language]);

    // Game ended listener with roomIamIn dependency
    useEffect(() => {
        if (!socketRef.current || !roomIamIn) return;

        const handleGameEnded = (roomId: string) => {
            
            if (roomId === roomIamIn) {
                setRoomIamIn('');
            }
        };

        socketRef.current.on("gameEnded", handleGameEnded);

        return () => {
            if (socketRef.current) {
                socketRef.current.off("gameEnded", handleGameEnded);
            }
        };
    }, [roomIamIn]);

    const contextValue: ComponentContextType = {
        notifications, 
        setNotifications,
        socket: socketRef.current,
        notificationsList,
        setNotificationsList,
        roomsRunning,
        setRoomsRunning,
        roomIamIn,
        setRoomIamIn,
        isAiEnabled,
        setIsAiEnabled,
        waitingForOpponent,
        setWaitingForOpponent,
		chatMessages,
		setChatMessages,
		conversations,
		setConversations,
		blockedUsers,
		setBlockedUsers,
		blockedByUsers,
		setBlockedByUsers,
		loadingBlocked,
    };

    return (
        <ComponentContext.Provider value={contextValue}>
            {children}
        </ComponentContext.Provider>
    );
}