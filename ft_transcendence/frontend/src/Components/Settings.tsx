import { useContext, useState, useRef, useEffect } from 'react';
import { AuthContext } from '../Context/AuthContext';
import type { AuthContextType } from '../types';


interface Language {
    code: string;
    label: string;
    flag: string;
}

const Settings: React.FC = (): React.ReactElement => {
    const authContext = useContext(AuthContext) as AuthContextType | undefined;
    
    if (!authContext) {
        throw new Error('Settings must be used within an AuthContextProvider');
    }
    
    const { language, lan, setLan, token, verifyPassword, getCsrfToken} = authContext;
	const [showChangePassword, setShowChangePassword] = useState(false);
	const changePasswordRef = useRef<HTMLFormElement | null>(null);

	useEffect(() => {
        if (showChangePassword && changePasswordRef.current) {
            changePasswordRef.current.scrollIntoView({ behavior: 'smooth', block: 'start' });
        }
    }, [showChangePassword]);
    const getFallback = (key: string): string => {
        const fallbacks: Record<string, string> = {
            'Settings': 'Settings',
            'setSelectLanguage': 'Select Language',
            'setCurrentLanguage': 'Current Language',
            'changePassword': 'Change Password',
			'securitySettings': 'Security Settings',
			'securityCurrentPassword': 'Current password:',
			'securityCurrentPasswordPlaceholder': 'Current password...',
			'securityNewPassword': 'New password:',
			'securityNewPasswordPlaceholder': 'New password...',
			'securityRepeatNewPassword': 'Repeat new password:',
			'securityRepeatNewPasswordPlaceholder': 'Repeat new password...',
			'securityChange': 'Change',
			'chatClose': 'Close',
        };
        
        return fallbacks[key] || key;
    };

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
        
        // Acceso seguro a la propiedad del idioma
        const languageData = language[lan];
        if (!languageData || typeof languageData !== 'object') {
            console.warn(`Language data for '${lan}' is null, undefined or not an object`);
            return getFallback(key);
        }
        
        // Verificar si la clave específica existe
        if (!(key in languageData)) {
            console.warn(`Key '${key}' not found in language '${lan}'`);
            return getFallback(key);
        }
        
        const languageRecord = languageData as unknown as Record<string, unknown>;
        const value = languageRecord[key];
        
        // Verificar que el valor existe y es string
        if (value === undefined) {
            console.warn(`Value for key '${key}' is undefined`);
            return getFallback(key);
        }
        
        return typeof value === 'string' ? value : getFallback(key);
    };

    const languages: Language[] = [
		{ code: 'es', label: 'Español', flag: '🇪🇸' },
        { code: 'en', label: 'English', flag: '🇬🇧' },
        { code: 'fr', label: 'Français', flag: '🇫🇷' },
        { code: 'pt', label: 'Português', flag: '🇵🇹' },
        { code: 'ja', label: '日本語', flag: '🇯🇵' },
        { code: 'ar', label: 'العربية', flag: '🇸🇦' },
        { code: 'zh', label: '中文', flag: '🇨🇳' },
        { code: 'ru', label: 'Русский', flag: '🇷🇺' }
    ];

    const handleLanguageChange = (languageCode: string): void => {
        if (setLan) {
            setLan(languageCode);
            localStorage.setItem('language', languageCode);
        } else {
            console.warn('setLan function is not available');
        }
    };

    const handleChangePassword = async (e: React.FormEvent<HTMLFormElement>): Promise<void>  => {
		e.preventDefault();
		const formElement = e.currentTarget;
		const formData = new FormData(formElement);

		const data = {
			currentPassword: String(formData.get("currentPassword") || ""),
			newPassword: String(formData.get("newPassword") || ""),
			repeatNewPassword: String(formData.get("repeatNewPassword") || ""),
		}

		if (data.repeatNewPassword != data.newPassword || verifyPassword(data.newPassword)) {
			alert("12 characters minimum only in uppercases, lowercases, digits or these special characters: !@#$%^&*()-_=+[]{};:|,<.>/?`. And at least one of each.");
			return
		}


		try{
			const csrfToken = getCsrfToken();
			const response = await(fetch('/api/user/profile/changePassword', {
				method: 'PUT',
				headers: {
					'Content-Type': 'application/json',
					Authorization: `Bearer ${token}`,
					'Accept': 'application/json',
					'X-CSRF-Token': csrfToken
				},
				body: JSON.stringify({oldPassword: data.currentPassword, newPassword: data.newPassword}),
			}))
			if (response.ok){
				alert("Password changed succesfully");
			}else{
				const result = await response.json();
				alert(result.error || "Failed to change password")
			}
		}catch(err){
			alert({err});
		}
		
		setShowChangePassword(false);
    };

    // Función helper para encontrar idioma actual de forma segura
    const getCurrentLanguage = (): { label: string; flag: string } => {
        const defaultLang = { label: 'English', flag: '🇬🇧' };
        
        if (!lan) return defaultLang;
        
        const foundLang = languages.find(l => l.code === lan);
        return foundLang || defaultLang;
    };

    const currentLang = getCurrentLanguage();

    return (
        <div className='flex justify-center items-start p-6 w-full'>
            <div className='w-full max-w-2xl'>
                {/* Header */}
                <div className="mb-8">
                    <h2 className='text-4xl font-bold text-transparent bg-clip-text bg-gradient-to-r from-purple-400 to-cyan-400 mb-2 tracking-tight flex items-center gap-3'>
                        <span>⚙️</span>
                        {getText('Settings')}
                    </h2>
                    <div className="h-1 w-24 bg-gradient-to-r from-purple-500 to-cyan-500 rounded-full"></div>
                </div>

                {/* Language Selection Section */}
                <section className='relative bg-gradient-to-br from-slate-800 via-slate-900 to-slate-950 border border-purple-500/20 rounded-xl p-8 shadow-2xl shadow-purple-500/10 mb-8 overflow-hidden'>
                    <div className="absolute top-0 left-0 right-0 h-1 bg-gradient-to-r from-transparent via-purple-400/50 to-transparent"></div>
                    
                    <h3 className='text-2xl font-bold text-white mb-6 flex items-center gap-3'>
                        <span className="text-purple-400">🌍</span>
                        {getText('setSelectLanguage')}
                    </h3>
                    
                    <div className='grid grid-cols-2 md:grid-cols-4 gap-4 mb-8'>
                        {languages.map((lang) => (
                            <button
                                key={lang.code}
                                onClick={() => handleLanguageChange(lang.code)}
                                className={`
                                    group relative flex flex-col items-center justify-center gap-3 p-6 rounded-xl 
                                    border-2 transition-all duration-300 hover:scale-105 active:scale-95 overflow-hidden
                                    ${lan === lang.code 
                                        ? 'border-purple-400 bg-gradient-to-br from-purple-500/20 to-cyan-500/10 text-purple-300 shadow-lg shadow-purple-500/30' 
                                        : 'border-slate-600 bg-gradient-to-br from-slate-700 to-slate-800 text-gray-300 hover:border-slate-500 hover:from-slate-600 hover:to-slate-700'
                                    }
                                `}
                            >
                                {lan === lang.code && (
                                    <div className="absolute top-2 right-2">
                                        <div className="w-3 h-3 bg-purple-400 rounded-full animate-pulse shadow-lg shadow-purple-400/50"></div>
                                    </div>
                                )}
                                
                                <span className='text-5xl group-hover:scale-110 transition-transform duration-200'>{lang.flag}</span>
                                <span className='font-bold text-lg'>{lang.code.toUpperCase()}</span>
                                <span className='text-sm text-center leading-tight'>{lang.label}</span>
                            </button>
                        ))}
                    </div>

                    {/* Current Selection Display */}
                    <div className='bg-gradient-to-r from-slate-900 to-slate-800 rounded-xl p-6 border border-slate-700/50'>
                        <div className="flex items-center gap-3">
                            <span className="text-cyan-400 text-xl">✨</span>
                            <p className='text-sm text-gray-400'>
                                {getText('setCurrentLanguage')}: 
                                <span className='text-white font-bold ml-2 text-lg'>
                                    {currentLang.label}
                                </span>
                                <span className="ml-2 text-2xl">
                                    {currentLang.flag}
                                </span>
                            </p>
                        </div>
                    </div>
                </section>

                {/* Change Password Section */}
                <section className='relative bg-gradient-to-br from-slate-800 via-slate-900 to-slate-950 border border-cyan-500/20 rounded-xl p-8 shadow-2xl shadow-cyan-500/10 overflow-hidden'>
                    <div className="absolute top-0 left-0 right-0 h-1 bg-gradient-to-r from-transparent via-cyan-400/50 to-transparent"></div>
                    
                    <h3 className='text-2xl font-bold text-white mb-6 flex items-center gap-3'>
                        <span className="text-cyan-400">🔐</span>
                        {getText('securitySettings')}
                    </h3>
                    
                    <button 
                        onClick={() => setShowChangePassword(prev => !prev)}
                        className="group w-full bg-gradient-to-r from-cyan-600 to-cyan-500 hover:from-cyan-500 hover:to-cyan-400 text-white font-bold py-4 px-8 rounded-xl transition-all duration-200 shadow-lg shadow-cyan-500/30 hover:shadow-cyan-500/50 hover:scale-[1.02] active:scale-95 flex items-center justify-center gap-3"
                    >
                        <span className="text-xl group-hover:rotate-12 transition-transform duration-200">🔑</span>
                        {getText('changePassword')}
                    </button>
					{showChangePassword && (
						<form ref={changePasswordRef} className='flex flex-col' onSubmit={handleChangePassword}>
							<h2 className='mt-3 mb-3 text-xl text-white'>{getText('securityCurrentPassword')}</h2>
							<input name="currentPassword" type ="password" placeholder={getText('securityCurrentPasswordPlaceholder')}
								className='w-full border-2 p-3 rounded-md mb-4'
							></input>
							<h2 className='mt-3 mb-3 text-xl text-white'>{getText('securityNewPassword')}</h2>
							<input name="newPassword" type ="password" placeholder={getText('securityNewPasswordPlaceholder')}
								className='w-full border-2 p-3 rounded-md mb-4'
							></input>
							<h2 className='mt-3 mb-3 text-xl text-white'>{getText('securityRepeatNewPassword')}</h2>
							<input name="repeatNewPassword" type ="password" placeholder={getText('securityRepeatNewPasswordPlaceholder')}
								className='w-full border-2 p-3 rounded-md mb-4'
							></input>
							<div className='flex'>
								<button type="submit" className="text-xl mb-4 bg-green-600 p-3 rounded-md text-white hover:bg-green-700">
									{getText('securityChange')}
								</button>
								<button type = "button" className="text-xl mb-4 ml-10 bg-red-600 p-3 rounded-md text-white hover:bg-red-700" onClick={() => setShowChangePassword(prev => !prev)}>
									{getText('chatClose')}
								</button>
							</div>
							
						</form>
					)}
                </section>
            </div>
        </div>
    );
};

export default Settings;