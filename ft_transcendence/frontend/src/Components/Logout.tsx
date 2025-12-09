import { useContext, useEffect, useRef } from "react";
import { AuthContext } from "../Context/AuthContext";
import type { AuthContextType } from "../types";

const Logout: React.FC = (): React.ReactElement => {
    const authContext = useContext(AuthContext) as AuthContextType | undefined;
    
    if (!authContext) {
        throw new Error('Logout must be used within an AuthContextProvider');
    }
    
    const { setToken, setLoading, getCsrfToken } = authContext;
    const hasLoggedOut = useRef<boolean>(false);

    useEffect(() => {
        if (hasLoggedOut.current) return;
        hasLoggedOut.current = true;

        const handleLogout = async (): Promise<void> => {
            if (!setLoading) {
                console.error('setLoading function is not available');
                return;
            }
            
            setLoading(true);
            
            const token = localStorage.getItem('token');
            
            try {
				const csrfToken = getCsrfToken();
                if (token) {
                    const res = await fetch("/api/auth/logout", {
                        method: 'POST',
                        headers: {
                            "Authorization": `Bearer ${token}`,
							'Accept': 'application/json',
							'X-CSRF-Token': csrfToken
                        },
                    }); 
                    
                    if (!res.ok) {
                        console.warn('Logout request failed, but continuing with local cleanup');
                    }
                }
            } catch (err) {
                console.error('Logout request error:', err);
                // Continuar con la limpieza local aunque falle la petición al servidor
            } finally {
                // Limpiar token local siempre
                localStorage.removeItem('token');
                
                if (setToken) {
                    setToken(null);
                } else {
                    console.error('setToken function is not available');
                }
            }
        };

        handleLogout();
    }, [setToken, setLoading]);

    return (
        <div className="flex items-center justify-center min-h-screen bg-gradient-to-br from-slate-950 via-slate-900 to-slate-950">
            <div className="relative bg-gradient-to-br from-slate-800 via-slate-900 to-slate-950 border border-red-500/20 rounded-xl p-12 shadow-2xl shadow-red-500/10 text-center max-w-md overflow-hidden">
                {/* Accent line */}
                <div className="absolute top-0 left-0 right-0 h-1 bg-gradient-to-r from-transparent via-red-400/50 to-transparent"></div>
                
                <div className="text-6xl mb-6 opacity-70">🚪</div>
                <h1 className="text-3xl font-bold text-white mb-4">Logging out...</h1>
                <p className="text-gray-400 text-lg">
                    Thank you for playing! You're being safely signed out.
                </p>
                
                {/* Loading spinner */}
                <div className="mt-8 flex justify-center">
                    <div className="animate-spin rounded-full h-8 w-8 border-b-2 border-red-400"></div>
                </div>
            </div>
        </div>
    );
};

export default Logout;