import React, { useContext, useState, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { AuthContext } from "../Context/AuthContext";
import type { AuthContextType } from "../types";
import LocalGame from "./LocalGame";
import LocalTournament from "./LocalTournament";

// Interfaces para props tipadas
interface RegisterFormProps {
    setForm: (form: string) => void;
	verifyPassword: (password: string) => number;
}

interface LoginFormProps {
    setToken: (token: string) => void;
    setLoading: (loading: boolean) => void;
}

const languageOptions: Record<string, string> = {
    en: 'English',
    pt: 'Portuguese',
    fr: 'French',
    ja: 'Japanese',
    zh: 'Chinese',
    es: 'Spanish',
    ru: 'Russian',
    ar: 'Arabic',
};

const RegisterForm: React.FC<RegisterFormProps> = ({ setForm, verifyPassword }) => {

	const authContext = useContext(AuthContext) as AuthContextType;
	const {language, lan} = authContext
	const getFallback = (key: string): string => {
        const fallbacks: Record<string, string> = {
            'loginRegister': 'Register',
			'loginUsername': 'Username:',
			'loginEmailOptional': 'Email (optional):',
			'loginDisplayNameOptional': 'Display Name (optional):',
			'loginPassword': 'Password:',
			'loginUsernamePlaceholder': 'username...',
			'loginEmailPlaceholder': 'Email',
			'loginDisplayNamePlaceholder': 'DisplayName',
			'loginPasswordPlaceholder': 'Password...',
			'loginLogin': 'Login',
			'loginSignInGoogle': 'Sign in with Google',
			'loginSignIn42': 'Sign in with 42',
			'loginAuthentication': 'Authentication 🔒',
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

    const handleRegister = async (e: React.FormEvent<HTMLFormElement>): Promise<void> => {
        e.preventDefault();
        const formElement = e.currentTarget;
        const formData = new FormData(formElement);
        
        const data = {
            username: String(formData.get("username") || ""),
            email: String(formData.get("email") || ""),
            displayName: String(formData.get("displayName") || ""),
            password: String(formData.get("password") || ""),
        };

		if (verifyPassword(data.password)) {
			alert("12 characters minimum only in uppercases, lowercases, digits or these special characters: !@#$%^&*()-_=+[]{};:|,<.>/?`. And at least one of each.");
			return
		}

        try {
            const res = await fetch("/api/auth/register", {
                method: 'POST',
                headers: { "Content-Type": "application/json", "Accept": "application/json"},
                body: JSON.stringify(data),
            });
            
            if (res.ok) {
                alert("Registration successfully! You can now login");
                setForm('loginForm');
            } else {
                const result = await res.json();
                alert(result.error || "Registration failed");
            }
        } catch (err) {
            const error = err instanceof Error ? err.message : "Unknown error";
            alert("Connection Error: " + error);
        }
    };

	
    return (
        <form onSubmit={handleRegister} className="flex flex-col">
            <h1 className="text-xl font-semibold text-gray-800">{getText('loginRegister')}</h1>
            <div className="mt-3">
                <h2 className="py-2">{getText('loginUsername')}</h2>
                <input name="username" type="text" className="w-full border-2 p-3 rounded-md mb-4" placeholder={getText('loginUsernamePlaceholder')} required/>
                <h2 className="py-2">{getText('loginEmailOptional')}</h2>
                <input name="email" type="email" className="w-full border-2 p-3 rounded-md mb-4" placeholder={getText('loginEmailPlaceholder')}/>
                <h2 className="py-2">{getText('loginDisplayNameOptional')}</h2>
                <input name="displayName" type="text" className="w-full border-2 p-3 rounded-md mb-4" placeholder={getText('loginDisplayNamePlaceholder')}/>
                <h2 className="p-2">{getText('loginPassword')}</h2>
                <input name="password" type="password" className="w-full border-2 p-3 rounded-md mb-10" placeholder={getText('loginPasswordPlaceholder')} required/>
            </div>
            <button type="submit" className="text-xl mb-4 bg-indigo-600 p-3 rounded-md text-white hover:bg-indigo-700">
                {getText('loginRegister')}
            </button>
        </form>
    );
};

const LoginForm: React.FC<LoginFormProps> = ({ setToken, setLoading }) => {
    const navigate = useNavigate();
	const authContext = useContext(AuthContext) as AuthContextType;
	const {language, lan} = authContext
	const getFallback = (key: string): string => {
        const fallbacks: Record<string, string> = {
            'loginRegister': 'Register',
			'loginUsername': 'Username:',
			'loginEmailOptional': 'Email (optional):',
			'loginDisplayNameOptional': 'Display Name (optional):',
			'loginPassword': 'Password:',
			'loginUsernamePlaceholder': 'username...',
			'loginEmailPlaceholder': 'Email',
			'loginDisplayNamePlaceholder': 'DisplayName',
			'loginPasswordPlaceholder': 'Password...',
			'loginLogin': 'Login',
			'loginSignInGoogle': 'Sign in with Google',
			'loginSignIn42': 'Sign in with 42',
			'loginAuthentication': 'Authentication 🔒',
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
    const handleLogin = async (e: React.FormEvent<HTMLFormElement>): Promise<void> => {
        e.preventDefault();
        setLoading(true);
        
        const formElement = e.currentTarget; // CAMBIO: e.target -> e.currentTarget
        const formData = new FormData(formElement);
        
        const data = {
            username: String(formData.get("username") || ""),
            password: String(formData.get("password") || ""),
        };

        
        try {
            const res = await fetch('/api/auth/login', {
                method: 'POST',
                headers: { "Content-Type": "application/json" ,"Accept": "application/json"},
                body: JSON.stringify(data),
            });
            
            if (res.ok) {
                const result = await res.json();

				sessionStorage.setItem('sessionId', result.sessionId);

                localStorage.setItem('token', result.token);
				localStorage.setItem('csrfToken', result.csrfToken);
                setToken(result.token);
                navigate('/index/');
            }else if (res.status === 409) {
                const result = await res.json().catch(() => ({ error: "Already logged in" }));
                alert(result.message || result.error || "This account is already logged in. Please logout from other sessions first.");
            } else {
                const result = await res.json();
                alert(result.error || "Login failed");
            }
        } catch (err) {
            const error = err instanceof Error ? err.message : "Unknown error";
            alert("Connection Error: " + error);
        } finally {
            setLoading(false);
        }
    };

    return (
        <div className="flex flex-col">
            <form onSubmit={handleLogin} className="flex flex-col">
                <h1 className="text-xl font-semibold text-gray-800">{getText('loginLogin')}</h1>
                <div className="mt-3">
                    <h2 className="py-2">{getText('loginUsername')}</h2>
                    <input name="username" type="text" className="w-full border-2 p-3 rounded-md mb-4" placeholder={getText('loginUsernamePlaceholder')} required/>
                    <h2 className="p-2">{getText('loginPassword')}</h2>
                    <input name="password" type="password" className="w-full border-2 p-3 rounded-md mb-10" placeholder={getText('loginPasswordPlaceholder')} required/>
                </div>
                <button type="submit" className="text-xl bg-indigo-600 p-3 rounded-md text-white hover:bg-indigo-700">
                    {getText('loginLogin')}
                </button>
            </form>
            
            <div className="mt-4 text-center mb-4">
                <a
                    href="/auth/google" 
                    className="w-full inline-flex items-center justify-center gap-2 p-3 bg-red-600 text-white rounded-lg hover:bg-red-700 transition-colors font-semibold"
                    aria-label="Sign in with Google"
                >
                    <img
                        src="https://www.svgrepo.com/show/475656/google-color.svg"
                        alt="Google"
                        className="w-5 h-5"
                    />
                    {getText('loginSignInGoogle')}
                </a>
            </div>
			<div className="mt-2 text-center mb-4">
				<a
					href="/auth/42"
					className="w-full inline-flex items-center justify-center gap-2 p-3 bg-gray-500 text-white rounded-lg hover:bg-gray-600 transition-colors font-semibold"
					aria-label="Sign in with 42"
				>
					<img
						src="https://upload.wikimedia.org/wikipedia/commons/8/8d/42_Logo.svg"
						alt="42"
						className="w-5 h-5"
					/>
					{getText('loginSignIn42')}
				</a>
			</div>
        </div>
    );
};

const Login: React.FC = () => {
    const authContext = useContext(AuthContext) as AuthContextType | undefined;
    const [form, setForm] = useState<string>('loginForm');
    const navigate = useNavigate();
	const [localGame, setLocalGame] = useState<boolean>(false);
	const [localTournament, setLocalTournament] = useState<boolean>(false);
    if (!authContext) {
        throw new Error('Login must be used within an AuthContextProvider');
    }
    
    const { setToken, setLoading, verifyPassword, language, lan, setLan } = authContext;
	const getFallback = (key: string): string => {
        const fallbacks: Record<string, string> = {
            'loginRegister': 'Register',
			'loginUsername': 'Username:',
			'loginEmailOptional': 'Email (optional):',
			'loginDisplayNameOptional': 'Display Name (optional):',
			'loginPassword': 'Password:',
			'loginUsernamePlaceholder': 'username...',
			'loginEmailPlaceholder': 'Email',
			'loginDisplayNamePlaceholder': 'DisplayName',
			'loginPasswordPlaceholder': 'Password...',
			'loginLogin': 'Login',
			'loginSignInGoogle': 'Sign in with Google',
			'loginSignIn42': 'Sign in with 42',
			'loginAuthentication': 'Authentication 🔒',
			'localTournament': 'Local tournament',
			'localGame': 'Local game',
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
    
    if (!setToken || !setLoading) {
        throw new Error('AuthContext missing required functions');
    }

	const handleLanguageChange = (e: React.ChangeEvent<HTMLSelectElement>) => {
        const selectedLanguage = e.target.value;
        if(setLan) setLan(selectedLanguage); // Actualiza el idioma en AuthContext (y localStorage)
    };

    useEffect(() => {
        const urlParams = new URLSearchParams(window.location.search);
        const error = urlParams.get('error');
        const message = urlParams.get('message');
        
        if (error === 'already_logged_in') {
            alert(decodeURIComponent(message || 'This account is already logged in in another session'));
            window.history.replaceState({}, document.title, window.location.pathname);
            return;
        }
        if (window.location.hash.startsWith('#token=')) {
            const hash = window.location.hash.substring(1);
            const params = new URLSearchParams(hash);
            const token = params.get('token');
            const csrfToken = params.get('csrfToken');
            const sessionId = params.get('sessionId');
            
            if (token && sessionId) {
                setLoading(true);
                
                sessionStorage.setItem('sessionId', sessionId);
                
                localStorage.setItem('token', token);
                
                if (csrfToken) {
                    localStorage.setItem('csrfToken', csrfToken);
                }
                
                setToken(token);
                window.location.hash = '';
                navigate('/index/');
            } else {
                alert('OAuth login failed: Missing session information');
            }
        }
    }, [setToken, setLoading, navigate]);	
    return (
		<>
		{localGame && <LocalGame setLocalGame = {setLocalGame}/>}
		{localTournament && <LocalTournament setLocalTournament = {setLocalTournament}/>}
		{!localGame && !localTournament &&  
        <div className="bg-gradient-to-br from-indigo-400 via-indigo-500 to-purple-500 min-h-screen flex justify-center items-center">
			<div className="absolute top-4 left-4 z-10">
				<select
					value={lan}
					onChange={handleLanguageChange}
					className="bg-purple-600 text-white text-base px-4 py-3 rounded-md shadow-md focus:outline-none focus:ring-2 focus:ring-purple-400 hover:bg-purple-800 transition-colors"
				>
					{Object.entries(languageOptions).map(([code, name]) => (
						<option key={code} value={code}>
							{name}
						</option>
					))}
				</select>
			</div>
            <div className="bg-white flex flex-col justify-center w-full max-w-md rounded-lg px-8 py-6">
                <h1 className="flex justify-center text-3xl font-sans mb-6 font-bold">{getText('loginAuthentication')}</h1>
                
                <div className="flex justify-center py-4 mb-5">
                    <button
                        onClick={() => setForm('loginForm')}
                        className={`w-48 py-4 text-lg rounded-l-md focus:outline-none focus:ring-1 focus:ring-indigo-700 focus:z-10 transition-colors ${
                            form === 'loginForm' 
                                ? 'bg-indigo-600 text-white' 
                                : 'bg-slate-200 hover:bg-indigo-600 hover:text-white hover:ring-2 hover:ring-indigo-400 hover:z-10'
                        }`}
                    >
                        {getText('loginLogin')}
                    </button>

                    <button
                        onClick={() => setForm('registerForm')}
                        className={`w-48 py-4 text-lg rounded-r-md focus:outline-none focus:ring-1 focus:ring-indigo-700 focus:z-10 transition-colors ${
                            form === 'registerForm' 
                                ? 'bg-indigo-600 text-white' 
                                : 'bg-slate-200 hover:bg-indigo-600 hover:text-white hover:ring-2 hover:ring-indigo-400 hover:z-10'
                        }`}
                    >
                        {getText('loginRegister')}
                    </button>
                </div>
                
                {form === 'loginForm' && <LoginForm setToken={setToken} setLoading={setLoading}/>}
                {form === 'registerForm' && <RegisterForm setForm={setForm} verifyPassword={verifyPassword}/>}
				<div className="flex">
					<button className="p-3 bg-orange-400 hover:bg-orange-500 text-white rounded-xl"
						onClick={() => setLocalGame(prev => !prev)}
					>
						{getText('localGame')}
					</button>
					<button className="ml-auto p-3 bg-orange-400 hover:bg-orange-500 text-white rounded-xl"
						onClick={() => setLocalTournament(prev => !prev)}
					>
						{getText('localTournament')}
					</button>
				</div>
            </div>
        </div>}
		</>
    );
};

export default Login;