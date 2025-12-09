import { useState, useContext, useEffect } from "react";
import { ComponentContext } from "../Context/ComponentsContext";
import { AuthContext } from "../Context/AuthContext";
import type { AuthContextType } from "../types";

const Index: React.FC = (): React.ReactElement => {
    const authContext = useContext(AuthContext) as AuthContextType | undefined;
    
    if (!authContext) {
        throw new Error('Index must be used within an AuthContextProvider');
    }
    
    const { user, language, lan } = authContext;
    const [grettings, setGrettings] = useState<string[]>([]);
    const [welcome, setWelcome] = useState<string[]>([]);

    // 🔧 FUNCIÓN HELPER PARA ACCESO SEGURO A language[lan]
    const getLanguageText = (key: string): string => {
        if (!language || !lan || !language[lan]) {
            return key === 'grettings' ? `Hello ${user?.username || 'user1'}` : 'Welcome to the best time of your life!';
        }
        
        // Acceso seguro con verificación
        const languageData = language[lan];
        if (!languageData || typeof languageData !== 'object') {
            return key === 'grettings' ? `Hello ${user?.username || 'user1'}` : 'Welcome to the best time of your life!';
        }
        
        const languageRecord = languageData as unknown as Record<string, unknown>;
        const value = languageRecord[key];
        
        if (typeof value === 'string') {
            return value;
        }
        
        return key === 'grettings' ? `Hello ${user?.username || 'user1'}` : 'Welcome to the best time of your life!';
    };

    useEffect(() => {
        const greetingsText = getLanguageText('grettings');
        const welcomeText = getLanguageText('welcome');
        
        const splitGrettings = greetingsText.split("");
        const splitWelcome = welcomeText.split("");
        
        setGrettings(splitGrettings);
        setWelcome(splitWelcome);
    }, [user, lan, language]);

    return (
        <div className="text-white">
            <div className="flex flex-col justify-center items-center">
                <div className="flex mt-20">
                    {grettings.map((letter, index) => (
                        <div key={index} className="group relative p-1">
                            <h1 className="relative scale-150 text-8xl bg-clip-text text-transparent bg-gradient-to-br from-emerald-300 to-emerald-600/60 hover:animate-spin hover:bg-cyan-600 cursor-pointer">
                                {index > 0 && '\u00A0'}
                                {letter}
                            </h1>
                        </div>
                    ))}
                </div>
                <div className="flex mt-16">
                    {welcome.map((letter, index) => (
                        <div key={index} className="">
                            <h1 className="text-4xl bg-clip-text text-transparent bg-gradient-to-br from-emerald-300 to-emerald-600/60 hover:animate-spin cursor-default">
                                {index > 0 && '\u00A0'}
                                {letter}
                            </h1>
                        </div>
                    ))}
                </div>
            </div>
        </div>
    );
};

export default Index;