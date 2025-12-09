
import { useState,type SetStateAction, type Dispatch, useContext } from "react"
import { AuthContext } from '../../Context/AuthContext'
import type { AuthContextType } from '../../types'
interface ProfileData {
    username: string;
    displayName: string;
    email: string;
    avatar: string;
    wins: number;
    losses: number;
    winRate: number;
}

interface ShowProfileProps{
	setShowProfile: Dispatch<SetStateAction<boolean>>,
	otherUser: ProfileData | null
}

export default function ShowProfile({setShowProfile, otherUser} : ShowProfileProps){

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
			'chatClose': 'Close',
			'chatShowProfileGameStats': 'Game Statistics',
			'chatShowProfileWins': 'Wins',
			'chatShowProfileLosses': 'Losses',
			'chatShowProfileWinRate': 'Win Rate',
        };
        
        return fallbacks[key] || key;
    };

	return (
		<div className="fixed inset-0 z-50 flex items-center justify-center bg-black bg-opacity-60">
			<div className="bg-slate-300 rounded-lg shadow-lg p-6 w-full max-w-md relative">
				<div className="relative group flex justify-center">
                    <div
                        className="absolute w-20 h-20 rounded-full bg-gradient-to-r from-emerald-500 to-cyan-500 opacity-40 blur-3xl transform scale-x-110 transition-opacity duration-300 group-hover:opacity-70"
                        aria-hidden="true"
                    />
                    <img
                        src={otherUser?.avatar || `https://ui-avatars.com/api/?name=${otherUser?.username}&size=192`}
                        alt="Avatar"
                        className="relative z-10 w-16 h-16 rounded-full border-4 border-slate-700 object-cover shadow-xl transition-transform duration-200 hover:scale-105"
                    />
                </div>
				<div className="flex-col text-center text-black flex-1 justify-center mt-3">
					<h2 >@{otherUser?.username}</h2>
					<h2 >{!!otherUser?.displayName && otherUser?.displayName}</h2>
					<h2>{!!otherUser?.email && otherUser?.email}</h2>
				</div>
				<section className="mb-6">
					<h2 className="text-xl font-bold text-black mb-4 flex items-center gap-2">
						<span className="text-emerald-400">📊</span>
						{getText('chatShowProfileGameStats')}
					</h2>

					{/* versión compacta de los tres panels */}
					<div className="grid grid-cols-1 sm:grid-cols-3 gap-3">
						{/* Wins */}
						<div className="group relative bg-gradient-to-br from-emerald-900/20 to-slate-900 border border-emerald-500/20 rounded-lg text-center p-4 shadow-md hover:shadow-emerald-500/10 transition-all duration-200">
							<div className="absolute top-0 left-0 right-0 h-0.5 bg-gradient-to-r from-transparent via-emerald-400/40 to-transparent"></div>
							<div className="absolute inset-0 bg-emerald-500/5 opacity-0 group-hover:opacity-60 transition-opacity duration-200 rounded-lg"></div>
							<h3 className="relative text-2xl font-black text-emerald-400 mb-1">{otherUser?.wins || 0}</h3>
							<p className="relative text-xs font-semibold text-gray-300 uppercase tracking-wider">{getText('chatShowProfileWins')}</p>
						</div>

						{/* Losses */}
						<div className="group relative bg-gradient-to-br from-red-900/20 to-slate-900 border border-red-500/20 rounded-lg text-center p-4 shadow-md hover:shadow-red-500/10 transition-all duration-200">
							<div className="absolute top-0 left-0 right-0 h-0.5 bg-gradient-to-r from-transparent via-red-400/40 to-transparent"></div>
							<div className="absolute inset-0 bg-red-500/5 opacity-0 group-hover:opacity-60 transition-opacity duration-200 rounded-lg"></div>
							<h3 className="relative text-2xl font-black text-red-400 mb-1">{otherUser?.losses || 0}</h3>
							<p className="relative text-xs font-semibold text-gray-300 uppercase tracking-wider">{getText('chatShowProfileLosses')}</p>
						</div>

						{/* Win rate */}
						<div className="group relative bg-gradient-to-br from-cyan-900/20 to-slate-900 border border-cyan-500/20 rounded-lg text-center p-4 shadow-md hover:shadow-cyan-500/10 transition-all duration-200">
							<div className="absolute top-0 left-0 right-0 h-0.5 bg-gradient-to-r from-transparent via-cyan-400/40 to-transparent"></div>
							<div className="absolute inset-0 bg-cyan-500/5 opacity-0 group-hover:opacity-60 transition-opacity duration-200 rounded-lg"></div>
							<h3 className="relative text-2xl font-black text-cyan-400 mb-1">{otherUser && otherUser.wins && otherUser.losses
							? ((otherUser.wins / (otherUser.wins + otherUser.losses) * 100).toFixed(0))
							: 0}%</h3>
							<p className="relative text-xs font-semibold text-gray-300 uppercase tracking-wider">{getText('chatShowProfileWinRate')}</p>
						</div>
					</div>
				</section>
				<div className="flex justify-center">
					<button
						className="p-3 bg-slate-400 hover:bg-red-500 rounded-xl  text-black"
						onClick={() => setShowProfile(false)}
					>
						{getText('chatClose')}
					</button>
				</div>
			</div>
		</div>
	)
}