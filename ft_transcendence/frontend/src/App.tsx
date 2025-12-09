import { useContext, useState, useEffect, useRef } from 'react'
import { BrowserRouter, Routes, Navigate, Route, useNavigate } from 'react-router-dom'
import { AuthContextProvider, AuthContext } from './Context/AuthContext'
import { ComponentContext, ComponentContextProvider } from './Context/ComponentsContext'
import { TournamentContextProvider } from './Context/TournamentContext'
import { FaBell, FaSearch } from 'react-icons/fa'
import type { AuthContextType, ComponentContextType, NotificationItem } from './types'

import ProtectorOfThings from './middleWare/middleWare'
import Game from './Components/Game'
import Index from './Components/Index'
import Logout from './Components/Logout'
import Profile from './Components/Profile'
import Settings from './Components/Settings'
import Matches from './Components/Matches'
import FriendRequest from './Components/FriendsRequest'
import Login from './Components/Login'
import Chat from './Components/Chat'
import { Tournaments } from './Components/Tournaments'

import './index.css'



const Components: React.FC = (): React.ReactElement => {
    const navigate = useNavigate();
    const [inputSearch, setInputSearch] = useState<string>('');
    const [showNotifications, setShowNotifications] = useState<boolean>(false);
    const notificationRef = useRef<HTMLDivElement>(null);
    
    const authContext = useContext(AuthContext) as AuthContextType | undefined;
    const componentContext = useContext(ComponentContext) as ComponentContextType | undefined;
    
    if (!authContext || !componentContext) {
        throw new Error('Components must be used within AuthContextProvider and ComponentContextProvider');
    }
    
    const { language, lan } = authContext;
    const { notifications, setNotifications, notificationsList, setNotificationsList } = componentContext;

    const getLanguageText = (key: string): string => {
        if (!language || !lan || !language[lan]) {
            const fallbacks: Record<string, string> = {
                secondsAgo: 'seconds ago',
                minutesAgo: 'minutes ago',
                hoursAgo: 'hours ago',
                daysAgo: 'days ago',
                weeksAgo: 'weeks ago',
                Game: 'Game',
                Profile: 'Profile',
				Matches: 'Matches',
				Tournaments: 'Tournamentes',
				Chat:'Chat',
                FriendRequest: 'Friend Request',
                Settings: 'Settings',
                Logout: 'Logout',
                Searcher: 'Search...',
                Notifications: 'Notifications',
                NotyClearAll: 'Clear all',
                NotyNoNewNotications: 'No new notifications',
                NotyYoureCaughtUp: "You're all caught up!",
                NotyViewAllNotications: 'View all notifications'
            };
            return fallbacks[key] || key;
        }
        
        const languageData = language[lan];
        if (!languageData || typeof languageData !== 'object') {
            const fallbacks: Record<string, string> = {
                secondsAgo: 'seconds ago',
                minutesAgo: 'minutes ago',
                hoursAgo: 'hours ago',
                daysAgo: 'days ago',
                weeksAgo: 'weeks ago',
                Game: 'Game',
                Profile: 'Profile',
				Matches: 'Matches',
				Tournaments: 'Tournamentes',
				Chat:'Chat',
                FriendRequest: 'Friend Request',
                Settings: 'Settings',
                Logout: 'Logout',
                Searcher: 'Search...',
                Notifications: 'Notifications',
                NotyClearAll: 'Clear all',
                NotyNoNewNotications: 'No new notifications',
                NotyYoureCaughtUp: "You're all caught up!",
                NotyViewAllNotications: 'View all notifications'
            };
            return fallbacks[key] || key;
        }
        
        const languageRecord = languageData as unknown as Record<string, unknown>;
        const value = languageRecord[key];
        
        return typeof value === 'string' ? value : key;
    };

    const getTimeAgo = (diff: number): string => {
        const seconds = Math.floor(diff / 1000);
        const minutes = Math.floor(seconds / 60);
        const hours = Math.floor(minutes / 60);
        const days = Math.floor(hours / 24);
        const weeks = Math.floor(days / 7);

        if (seconds < 60) return (`${seconds} ${getLanguageText('secondsAgo')}`);
        else if (minutes < 60) return (`${minutes} ${getLanguageText('minutesAgo')}`);
        else if (hours < 24) return (`${hours} ${getLanguageText('hoursAgo')}`);
        else if (days < 7) return (`${days} ${getLanguageText('daysAgo')}`);
        else return (`${weeks} ${getLanguageText('weeksAgo')}`);
    };

    // Close dropdown when clicking outside
    useEffect(() => {
        const handleClickOutside = (event: MouseEvent): void => {
            if (notificationRef.current && !notificationRef.current.contains(event.target as Node)) {
                setShowNotifications(false);
            }
        };

        if (showNotifications) {
            document.addEventListener('mousedown', handleClickOutside);
        }

        return () => {
            document.removeEventListener('mousedown', handleClickOutside);
        };
    }, [showNotifications]);

    const handleNotifications = (): void => {
        setShowNotifications(!showNotifications);
    };

    const clearNotifications = (): void => {
        if (setNotifications) setNotifications(0);
        if (setNotificationsList) setNotificationsList([]);
        setShowNotifications(false);
    };

    const handleClickNotification = (notify: NotificationItem): void => {
        if (!notify.status) return;
        if (notify.type === 'friendRequest') {
            navigate('/index/friendRequest');
        }
        if (setNotifications) {
            setNotifications((notifications: number) => (notifications > 0 ? notifications - 1 : 0));
        }
        if (setNotificationsList && notificationsList) {
            setNotificationsList(notificationsList.map((notif: NotificationItem) => {
                if (notif.id === notify.id) {
                    return ({ ...notif, status: false });
                }
                return (notif);
            }));
        }
    };

    const deleteNotification = (id: number): void => {
        if (setNotificationsList && notificationsList) {
            setNotificationsList(notificationsList.filter((noti: NotificationItem) => noti.id !== id));
        }
    };

    return (
        <>
            <div className="min-h-screen bg-gradient-to-br from-slate-950 via-slate-900 to-slate-950">
                <div className='flex'>
                    {/* Modern Sidebar Navigation */}
                    <nav className='flex flex-col top-0 left-0 w-20 lg:w-24 min-h-screen bg-gradient-to-b from-slate-900 via-slate-800 to-slate-900 border-r border-emerald-500/10 shadow-2xl shadow-emerald-500/5'>
                        {/* Logo/Home */}
                        <button 
                            className='group relative w-full h-20 flex flex-col justify-center items-center text-3xl lg:text-4xl font-black border-b border-slate-700/50 hover:bg-gradient-to-r hover:from-emerald-500/10 hover:to-cyan-500/10 transition-all duration-300 overflow-hidden' 
                            onClick={() => navigate('/index')}
                        >
                            <span className="relative text-transparent bg-clip-text bg-gradient-to-r from-emerald-400 to-cyan-400 group-hover:from-emerald-300 group-hover:to-cyan-300 transition-all">42</span>
                        </button>

                        {/* Navigation Items */}
                        <button 
                            className='group relative w-full h-16 flex flex-col justify-center items-center text-xs lg:text-sm font-medium text-gray-400 hover:text-white hover:bg-gradient-to-r hover:from-emerald-500/10 hover:to-transparent border-l-2 border-transparent hover:border-emerald-400 transition-all duration-200' 
                            onClick={() => navigate('/index/game')}
                        >
                            <span className="text-xl mb-1">🎮</span>
                            <span className="hidden lg:block">{getLanguageText('Game')}</span>
                        </button>

                        <button 
                            className='group relative w-full h-16 flex flex-col justify-center items-center text-xs lg:text-sm font-medium text-gray-400 hover:text-white hover:bg-gradient-to-r hover:from-cyan-500/10 hover:to-transparent border-l-2 border-transparent hover:border-cyan-400 transition-all duration-200' 
                            onClick={() => navigate('/index/matches')}
                        >
                            <span className="text-xl mb-1">🏆</span>
                            <span className="hidden lg:block">{getLanguageText('Matches')}</span>
                        </button>


						<button 
							className='group relative w-full h-16 flex flex-col justify-center items-center text-xs lg:text-sm font-medium text-gray-400 hover:text-white hover:bg-gradient-to-r hover:from-cyan-500/10 hover:to-transparent border-l-2 border-transparent hover:border-cyan-400 transition-all duration-200' 
							onClick={() => navigate('/index/tournaments')}
							>
							<span className="text-xl mb-1">23</span>
							<span className="hidden lg:block">{getLanguageText('Tournaments')}</span>
						</button>

						<button 
							className='group relative w-full h-16 flex flex-col justify-center items-center text-xs lg:text-sm font-medium text-gray-400 hover:text-white hover:bg-gradient-to-r hover:from-purple-500/10 hover:to-transparent border-l-2 border-transparent hover:border-purple-400 transition-all duration-200' 
							onClick={() => navigate('/index/chat')}
						>
							<span className="text-xl mb-1">💬</span>
							<span className="hidden lg:block">{getLanguageText('Chat')}</span>
						</button>
                        <button 
                            className='group relative w-full h-16 flex flex-col justify-center items-center text-xs lg:text-sm font-medium text-gray-400 hover:text-white hover:bg-gradient-to-r hover:from-blue-500/10 hover:to-transparent border-l-2 border-transparent hover:border-blue-400 transition-all duration-200' 
                            onClick={() => navigate('/index/profile')}
                        >
                            <span className="text-xl mb-1">👤</span>
                            <span className="hidden lg:block">{getLanguageText('Profile')}</span>
                        </button>

                        <button 
                            className='group relative w-full h-16 flex flex-col justify-center items-center text-xs lg:text-sm font-medium text-gray-400 hover:text-white hover:bg-gradient-to-r hover:from-amber-500/10 hover:to-transparent border-l-2 border-transparent hover:border-amber-400 transition-all duration-200' 
                            onClick={() => navigate('/index/friendRequest')}
                        >
                            <span className="text-xl mb-1">👥</span>
                            <span className="hidden lg:block">{getLanguageText('FriendRequest')}</span>
                        </button>

                        <button 
                            className='group relative w-full h-16 flex flex-col justify-center items-center text-xs lg:text-sm font-medium text-gray-400 hover:text-white hover:bg-gradient-to-r hover:from-purple-500/10 hover:to-transparent border-l-2 border-transparent hover:border-purple-400 transition-all duration-200' 
                            onClick={() => navigate('/index/settings')}
                        >
                            <span className="text-xl mb-1">⚙️</span>
                            <span className="hidden lg:block">{getLanguageText('Settings')}</span>
                        </button>

                        {/* Logout at bottom */}
                        <div className="mt-auto border-t border-slate-700/50">
                            <button 
                                className='group relative w-full h-16 flex flex-col justify-center items-center text-xs lg:text-sm font-medium text-gray-400 hover:text-red-400 hover:bg-gradient-to-r hover:from-red-500/10 hover:to-transparent border-l-2 border-transparent hover:border-red-400 transition-all duration-200' 
                                onClick={() => navigate('/index/logout')}
                            >
                                <span className="text-xl mb-1">🚪</span>
                                <span className="hidden lg:block">{getLanguageText('Logout')}</span>
                            </button>
                        </div>
                    </nav>

                    <div className='flex-1 min-w-0 flex flex-col'>
                        {/* Modern Header */}
                        <div className='relative bg-gradient-to-r from-slate-900 via-slate-800 to-slate-900 h-16 flex items-center justify-between px-4 md:px-8 gap-4 border-b border-emerald-500/10 shadow-xl shadow-emerald-500/5'>
                            {/* Accent line */}
                            <div className="absolute bottom-0 left-0 right-0 h-px bg-gradient-to-r from-transparent via-emerald-400/30 to-transparent"></div>

                            {/* Search Bar */}
                            <div className='flex flex-1 max-w-md group'>
                                <div className='bg-slate-700 group-hover:bg-slate-600 transition-colors w-10 h-10 rounded-l-lg flex justify-center items-center border border-slate-600 group-focus-within:border-emerald-500/50'>
                                    <FaSearch className='text-gray-400 group-focus-within:text-emerald-400 transition-colors'/>
                                </div>
                                <input 
                                    value={inputSearch} 
                                    onChange={(e) => setInputSearch(e.target.value)} 
                                    placeholder={getLanguageText('Searcher')}
                                    className='flex-1 h-10 px-4 bg-slate-800 text-white placeholder-gray-500 rounded-r-lg border border-l-0 border-slate-600 focus:outline-none focus:border-emerald-500/50 focus:ring-2 focus:ring-emerald-500/20 transition-all'
                                />
                            </div>

                            {/* Notifications Bell with Dropdown */}
                            <div className='relative' ref={notificationRef}>
                                <button 
                                    onClick={handleNotifications} 
                                    className='group relative flex-shrink-0 w-12 h-12 rounded-lg bg-slate-700/50 hover:bg-slate-700 border border-slate-600 hover:border-emerald-500/50 flex items-center justify-center transition-all duration-200 hover:shadow-lg hover:shadow-emerald-500/20'
                                >
                                    <FaBell size={20} className='text-gray-400 group-hover:text-emerald-400 transition-colors'/>
                                    {(notifications || 0) > 0 && (
                                        <span className="absolute -top-1 -right-1 bg-gradient-to-r from-red-500 to-red-600 text-white text-xs font-bold rounded-full w-6 h-6 flex items-center justify-center animate-pulse shadow-lg shadow-red-500/50 border-2 border-slate-900">
                                            {notifications || 0}
                                        </span>
                                    )}
                                </button>

                                {/* Dropdown Notification Panel */}
                                {showNotifications && (
                                    <div className='absolute right-0 top-16 w-96 bg-gradient-to-br from-slate-800 via-slate-900 to-slate-950 border border-emerald-500/20 rounded-xl shadow-2xl shadow-emerald-500/10 z-50 overflow-hidden'>
                                        {/* Accent line */}
                                        <div className="absolute top-0 left-0 right-0 h-1 bg-gradient-to-r from-transparent via-emerald-400/50 to-transparent"></div>

                                        {/* Header */}
                                        <div className='flex items-center justify-between p-5 border-b border-slate-700/50 bg-slate-800/50'>
                                            <h3 className='text-xl font-bold text-white flex items-center gap-2'>
                                                <span className="text-emerald-400">🔔</span>
                                                {getLanguageText('Notifications')}
                                            </h3>
                                            {(notifications || 0) > 0 && (
                                                <button 
                                                    onClick={clearNotifications}
                                                    className='text-xs font-semibold text-emerald-400 hover:text-emerald-300 px-3 py-1.5 rounded-lg bg-emerald-500/10 hover:bg-emerald-500/20 border border-emerald-500/30 transition-all'
                                                >
                                                    {getLanguageText('NotyClearAll')}
                                                </button>
                                            )}
                                        </div>

                                        {/* Notifications List */}
                                        <div className='max-h-96 overflow-y-auto scrollbar-thin scrollbar-thumb-slate-700 scrollbar-track-slate-900'>
                                            {(notificationsList && notificationsList.length > 0) ? (
                                                notificationsList.map((notif: NotificationItem) => (
                                                    <div 
                                                        key={notif.id}
                                                        className={`group relative p-4 border-b border-slate-700/50 ${!notif.status ? 'bg-emerald-500/5' : 'bg-transparent'} hover:bg-slate-800/50 transition-all cursor-pointer`}
                                                        onClick={() => handleClickNotification(notif)}
                                                    >
                                                        <div className='flex items-start gap-3 pr-6'>
                                                            <div className={`w-2.5 h-2.5 rounded-full mt-1.5 flex-shrink-0 ${notif.status ? 'bg-emerald-400 shadow-lg shadow-emerald-400/50' : 'bg-gray-600'}`}></div>
                                                            <div className='flex-1'>
                                                                <p className='text-sm text-white leading-relaxed'>
                                                                    <span className='font-bold text-emerald-400'>{notif.user}</span>
                                                                    {' '}{notif.msg}
                                                                </p>
                                                                <p className='text-xs text-gray-500 mt-1.5 flex items-center gap-1'>
                                                                    <span>⏱️</span>
                                                                    {getTimeAgo(Date.now() - notif.time)}
                                                                </p>
                                                            </div>
                                                        </div>
                                                        <button 
                                                            className='absolute top-3 right-3 text-gray-600 hover:text-red-400 rounded-full w-6 h-6 flex justify-center items-center hover:bg-red-500/10 transition-all text-xs font-bold'
                                                            onClick={(e) => {
                                                                e.stopPropagation();
                                                                deleteNotification(notif.id);
                                                            }}
                                                        >
                                                            ✕
                                                        </button>
                                                    </div>
                                                ))
                                            ) : (
                                                <div className='p-12 text-center'>
                                                    <FaBell size={56} className='mx-auto mb-4 text-gray-700'/>
                                                    <p className="text-gray-400 font-medium">{getLanguageText('NotyNoNewNotications')}</p>
                                                    <p className="text-gray-600 text-sm mt-2">{getLanguageText('NotyYoureCaughtUp')}</p>
                                                </div>
                                            )}
                                        </div>

                                        {/* Footer */}
                                        {(notificationsList && notificationsList.length > 0) && (
                                            <div className='p-4 border-t border-slate-700/50 text-center bg-slate-800/30'>
                                                <button className='text-sm font-semibold text-cyan-400 hover:text-cyan-300 hover:underline transition-colors'>
                                                    {getLanguageText('NotyViewAllNotications')}
                                                </button>
                                            </div>
                                        )}
                                    </div>
                                )}
                            </div>
                        </div>

                        {/* Main Content Area */}
                        <div className='flex-1 overflow-y-auto bg-gradient-to-br from-slate-950 via-slate-900 to-slate-950'>
                            <Routes>
                                <Route index element={<Index/>}/>
                                <Route path='profile' element={<Profile/>}/>
                                <Route path='friendRequest' element={<FriendRequest/>} />
                                <Route path='game' element={<Game/>}/>
                                <Route path='matches' element={<Matches/>}/>
								<Route path='tournaments' element={<Tournaments/>}/>
								<Route path='chat' element={<Chat/>}/>
                                <Route path='settings' element={<Settings/>}/>
                                <Route path='logout' element={<Logout/>}/>
                            </Routes>
                        </div>
                    </div>
                </div>
            </div>
        </>
    );
};

const MainComponent: React.FC = (): React.ReactElement => {
    return (
        <Routes>
            <Route path='/login' element={<Login/>}/>
            <Route path='/index/*' element={
                <ProtectorOfThings>
                    <ComponentContextProvider>
						<TournamentContextProvider>
                        	<Components/>
						</TournamentContextProvider>
                    </ComponentContextProvider>
                </ProtectorOfThings>
            }
            />
            <Route path='*' element={<Navigate to={'/index/'}/>}/>
        </Routes>
    );
};

const App: React.FC = (): React.ReactElement => {
    return (
        <AuthContextProvider>
            <BrowserRouter>
                <MainComponent/>
            </BrowserRouter>
        </AuthContextProvider>
    );
};

export default App;