import { useContext, useEffect, useRef, useState, type Dispatch, type SetStateAction } from "react";
import { AuthContext } from "../Context/AuthContext";
import type { AuthContextType } from '../types';

interface LocalTournamentProps {
    setLocalTournament: Dispatch<SetStateAction<boolean>>
}

interface Player {
    id: number;
    name: string;
    score: number;
    eliminated: boolean;
}

interface Match {
    id: string;
    player1: Player;
    player2: Player;
    round: 'semifinal' | 'final';
    matchNumber: number;
    winner: Player | null;
    completed: boolean;
}

interface GameState {
    player1: {
        x: number;
        y: number;
        width: number;
        height: number;
        score: number;
        velocity: number;
        lastY: number;
    };
    player2: {
        x: number;
        y: number;
        width: number;
        height: number;
        score: number;
        velocity: number;
        lastY: number;
    };
    ball: {
        x: number;
        y: number;
        radius: number;
        vx: number;
        vy: number;
        speed: number;
        baseSpeed: number;
        rotation: number;
        spin: {
            type: 'topspin' | 'backspin';
            intensity: number;
            rotation: number;
            rotationSpeed: number;
            appliedBy: 'player1' | 'player2';
        } | null;
    };
    gameStarted: boolean;
    gameEnded: boolean;
    winner: string | null;
    startTime: number;
    rallyCount: number;
    lastHitTime: number;
}

export default function LocalTournament({ setLocalTournament }: LocalTournamentProps) {
    const authContext = useContext(AuthContext) as AuthContextType;
    const { language, lan } = authContext;

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
			'localTournamentTitle': '🏆 Local Tournament',
			'localTournamentDescription': '4 Players • Semifinals + Final • First to 5 points wins',
			'localTournamentSemifinal': '🏁 Semifinal ',
			'localTournamentFinal': '👑 FINAL',
			'localTournamentStartMatch': '🚀 START MATCH',
			'localTournamentWins': 'WINS!',
			'localTournamentScore': 'Score:',
			'localTournamentNextMatch': '➡️ NEXT MATCH',
			'localTournamentStartingFinal': 'Starting Final in 2s... 🏆',
			'localTournamentChampion': '🏆 CHAMPION!',
			'localTournamentExitTournament': '🚪 EXIT TOURNAMENT',
			'localTournamentAudioOn': '🔊 Audio ON',
			'localTournamentAudioOff': '🔇 Audio OFF',
			'localTournamentExit': '🚪 Exit Tournament',
			'localTournamentPlayer1': 'Player 1',
			'localTournamentPlayer2': 'Player 2',
			'localTournamentPlayer3': 'Player 3',
			'localTournamentPlayer4': 'Player 4',
			'chatLoading': 'Loading...',
			'matchSpeed': 'SPEED',
			'matchRally': 'RALLY',
        };
        
        return fallbacks[key] || key;
    };
    const initialPlayers: Player[] = [
        { id: 1, name: `${getText('localTournamentPlayer1')}`, score: 0, eliminated: false },
        { id: 2, name: `${getText('localTournamentPlayer2')}`, score: 0, eliminated: false },
        { id: 3, name: `${getText('localTournamentPlayer3')}`, score: 0, eliminated: false },
        { id: 4, name: `${getText('localTournamentPlayer4')}`, score: 0, eliminated: false }
    ];

    const [players] = useState<Player[]>(initialPlayers);

    const initialMatches: Match[] = [
        {
            id: 'semi1',
            player1: initialPlayers[0]!,
            player2: initialPlayers[1]!,
            round: 'semifinal',
            matchNumber: 1,
            winner: null,
            completed: false
        },
        {
            id: 'semi2',
            player1: initialPlayers[2]!,
            player2: initialPlayers[3]!,
            round: 'semifinal',
            matchNumber: 2,
            winner: null,
            completed: false
        }
    ];

    const [matches, setMatches] = useState<Match[]>(initialMatches);
    const [currentMatchIndex, setCurrentMatchIndex] = useState<number>(0);
    const [tournamentComplete, setTournamentComplete] = useState<boolean>(false);
    const [tournamentWinner, setTournamentWinner] = useState<Player | null>(null);

    const canvasRef = useRef<HTMLCanvasElement | null>(null);
    const keysPressed = useRef<Set<string>>(new Set());
    const animationFrameId = useRef<number | null>(null);
    const lastScoreTime = useRef<number>(0);
    const audioContext = useRef<AudioContext | null>(null);
    const soundEnabled = useRef<boolean>(true);
    const currentMatchIndexRef = useRef<number>(0);
    const matchesRef = useRef<Match[]>(initialMatches);
    
    const gameStateRef = useRef<GameState>({
        player1: { x: 10, y: 150, width: 10, height: 100, score: 0, velocity: 0, lastY: 150 },
        player2: { x: 780, y: 150, width: 10, height: 100, score: 0, velocity: 0, lastY: 150 },
        ball: { 
            x: 400, 
            y: 200, 
            radius: 10, 
            vx: 7,
            vy: 5,
            speed: 7,
            baseSpeed: 7,
            rotation: 0,
            spin: null
        },
        gameStarted: false,
        gameEnded: false,
        winner: null,
        startTime: Date.now(),
        rallyCount: 0,
        lastHitTime: Date.now()
    });

    const [displayState, setDisplayState] = useState<GameState>(gameStateRef.current);
    const [soundToggle, setSoundToggle] = useState<boolean>(true);

    useEffect(() => {
        currentMatchIndexRef.current = currentMatchIndex;
    }, [currentMatchIndex]);

    useEffect(() => {
        matchesRef.current = matches;
    }, [matches]);

    useEffect(() => {
        if (matches.length === 3 && 
            currentMatchIndex === 1 && 
            displayState.gameEnded && 
            !matches[2]?.completed) {
            
            
            const timer = setTimeout(() => {
                
                const newState: GameState = {
                    player1: { x: 10, y: 150, width: 10, height: 100, score: 0, velocity: 0, lastY: 150 },
                    player2: { x: 780, y: 150, width: 10, height: 100, score: 0, velocity: 0, lastY: 150 },
                    ball: { 
                        x: 400, 
                        y: 200, 
                        radius: 10, 
                        vx: 7,
                        vy: 5,
                        speed: 7,
                        baseSpeed: 7,
                        rotation: 0,
                        spin: null
                    },
                    gameStarted: false,
                    gameEnded: false,
                    winner: null,
                    startTime: Date.now(),
                    rallyCount: 0,
                    lastHitTime: Date.now()
                };
                
                gameStateRef.current = newState;
                keysPressed.current.clear();
                lastScoreTime.current = 0;
                
                currentMatchIndexRef.current = 2;
                setCurrentMatchIndex(2);
                setDisplayState(newState);
            }, 2000);
            
            return () => clearTimeout(timer);
        }
    }, [matches.length, currentMatchIndex, displayState.gameEnded, matches]);

    const initAudio = () => {
        if (!audioContext.current) {
            audioContext.current = new (window.AudioContext || (window as any).webkitAudioContext)();
        }
        return audioContext.current;
    };

    const playPaddleHit = (speed: number, hasSpin: boolean) => {
        if (!soundEnabled.current) return;
        const ctx = initAudio();
        
        const baseFreq = 200 + (speed / 25) * 600;
        const volume = Math.min(0.3 + (speed / 25) * 0.4, 0.7);
        
        const oscillator = ctx.createOscillator();
        const gainNode = ctx.createGain();
        
        oscillator.type = hasSpin ? 'sawtooth' : 'sine';
        oscillator.frequency.setValueAtTime(baseFreq, ctx.currentTime);
        oscillator.frequency.exponentialRampToValueAtTime(baseFreq * 0.5, ctx.currentTime + 0.1);
        
        gainNode.gain.setValueAtTime(volume, ctx.currentTime);
        gainNode.gain.exponentialRampToValueAtTime(0.01, ctx.currentTime + 0.15);
        
        oscillator.connect(gainNode);
        gainNode.connect(ctx.destination);
        
        oscillator.start(ctx.currentTime);
        oscillator.stop(ctx.currentTime + 0.15);
    };

    const playWallBounce = () => {
        if (!soundEnabled.current) return;
        const ctx = initAudio();
        
        const oscillator = ctx.createOscillator();
        const gainNode = ctx.createGain();
        
        oscillator.type = 'triangle';
        oscillator.frequency.setValueAtTime(150, ctx.currentTime);
        oscillator.frequency.exponentialRampToValueAtTime(80, ctx.currentTime + 0.1);
        
        gainNode.gain.setValueAtTime(0.2, ctx.currentTime);
        gainNode.gain.exponentialRampToValueAtTime(0.01, ctx.currentTime + 0.1);
        
        oscillator.connect(gainNode);
        gainNode.connect(ctx.destination);
        
        oscillator.start(ctx.currentTime);
        oscillator.stop(ctx.currentTime + 0.1);
    };

    const playSpinActivated = (spinType: 'topspin' | 'backspin') => {
        if (!soundEnabled.current) return;
        const ctx = initAudio();
        
        const oscillator = ctx.createOscillator();
        const gainNode = ctx.createGain();
        
        oscillator.type = 'sine';
        const startFreq = spinType === 'topspin' ? 600 : 400;
        const endFreq = spinType === 'topspin' ? 400 : 600;
        
        oscillator.frequency.setValueAtTime(startFreq, ctx.currentTime);
        oscillator.frequency.linearRampToValueAtTime(endFreq, ctx.currentTime + 0.2);
        
        gainNode.gain.setValueAtTime(0.25, ctx.currentTime);
        gainNode.gain.exponentialRampToValueAtTime(0.01, ctx.currentTime + 0.2);
        
        oscillator.connect(gainNode);
        gainNode.connect(ctx.destination);
        
        oscillator.start(ctx.currentTime);
        oscillator.stop(ctx.currentTime + 0.2);
    };

    const playScore = () => {
        if (!soundEnabled.current) return;
        const ctx = initAudio();
        
        const frequencies = [523, 659, 784];
        
        frequencies.forEach((freq, index) => {
            const oscillator = ctx.createOscillator();
            const gainNode = ctx.createGain();
            
            oscillator.type = 'square';
            oscillator.frequency.setValueAtTime(freq, ctx.currentTime + index * 0.1);
            
            gainNode.gain.setValueAtTime(0.3, ctx.currentTime + index * 0.1);
            gainNode.gain.exponentialRampToValueAtTime(0.01, ctx.currentTime + index * 0.1 + 0.15);
            
            oscillator.connect(gainNode);
            gainNode.connect(ctx.destination);
            
            oscillator.start(ctx.currentTime + index * 0.1);
            oscillator.stop(ctx.currentTime + index * 0.1 + 0.15);
        });
    };

    const resetBall = () => {
        const state = gameStateRef.current;
        state.ball.x = 400;
        state.ball.y = 200;
        state.ball.vx = (Math.random() > 0.5 ? 1 : -1) * 7;
        state.ball.vy = (Math.random() - 0.5) * 10;
        state.ball.speed = 7;
        state.ball.baseSpeed = 7;
        state.ball.rotation = 0;
        state.ball.spin = null;
        state.rallyCount = 0;
    };

    const updateGame = () => {
        const state = gameStateRef.current;
        
        if (!state.gameStarted || state.gameEnded) return;

        const SPEED = 8;
        const matchIndex = currentMatchIndexRef.current;
        const currentMatch = matchesRef.current[matchIndex];
        if (!currentMatch) {
            return;
        }

        const prevY1 = state.player1.y;
        const prevY2 = state.player2.y;

        if (keysPressed.current.has('w') || keysPressed.current.has('W')) {
            state.player1.y = Math.max(0, state.player1.y - SPEED);
        }
        if (keysPressed.current.has('s') || keysPressed.current.has('S')) {
            state.player1.y = Math.min(300, state.player1.y + SPEED);
        }

        if (keysPressed.current.has('ArrowUp')) {
            state.player2.y = Math.max(0, state.player2.y - SPEED);
        }
        if (keysPressed.current.has('ArrowDown')) {
            state.player2.y = Math.min(300, state.player2.y + SPEED);
        }

        const deltaTime = 1000 / 60;
        state.player1.velocity = (state.player1.y - prevY1) / deltaTime;
        state.player2.velocity = (state.player2.y - prevY2) / deltaTime;
        state.player1.lastY = state.player1.y;
        state.player2.lastY = state.player2.y;

        state.ball.speed = Math.min(20, 7 + (state.rallyCount * 0.3));

        const currentMagnitude = Math.sqrt(state.ball.vx ** 2 + state.ball.vy ** 2);
        if (currentMagnitude > 0) {
            const speedRatio = state.ball.speed / currentMagnitude;
            state.ball.vx *= speedRatio;
            state.ball.vy *= speedRatio;
        }

        if (state.ball.spin && state.ball.spin.intensity > 0.1) {
            const spinEffect = state.ball.spin.intensity * 0.08;
            
            if (state.ball.spin.type === 'topspin') {
                state.ball.vy += spinEffect;
            } else if (state.ball.spin.type === 'backspin') {
                state.ball.vy -= spinEffect * 0.8;
            }
            
            state.ball.spin.intensity *= 0.985;
            state.ball.spin.rotation += state.ball.spin.rotationSpeed;
            
            if (state.ball.spin.intensity < 0.1) {
                state.ball.spin = null;
            }
        }

        if (!state.ball.spin) {
            const speed = Math.sqrt(state.ball.vx ** 2 + state.ball.vy ** 2);
            state.ball.rotation += speed * 0.05;
        } else {
            state.ball.rotation = state.ball.spin.rotation;
        }

        state.ball.x += state.ball.vx;
        state.ball.y += state.ball.vy;

        if (state.ball.y - state.ball.radius <= 0 || state.ball.y + state.ball.radius >= 400) {
            state.ball.vy *= -1;
            playWallBounce();
            
            if (state.ball.spin) {
                if (state.ball.spin.type === 'topspin') {
                    state.ball.vy *= 0.9;
                    state.ball.vx *= 1.08;
                } else if (state.ball.spin.type === 'backspin') {
                    state.ball.vy *= 1.15;
                    state.ball.vx *= 0.95;
                }
                state.ball.spin.intensity *= 0.7;
            }
        }

        const now = Date.now();

        if (
            state.ball.x - state.ball.radius <= state.player1.x + state.player1.width &&
            state.ball.x - state.ball.radius >= state.player1.x &&
            state.ball.y + 7.5 >= state.player1.y &&
            state.ball.y - 7.5 <= state.player1.y + state.player1.height &&
            state.ball.vx < 0
        ) {
            state.ball.vx = Math.abs(state.ball.vx);
            state.ball.x = state.player1.x + state.player1.width + state.ball.radius;
            
            const paddleVelocity = state.player1.velocity;
            const minVelocityForSpin = 2;
            
            if (Math.abs(paddleVelocity) > minVelocityForSpin) {
                const spinIntensity = Math.min(Math.abs(paddleVelocity) / 15, 3);
                const spinType = paddleVelocity > 0 ? 'topspin' : 'backspin';
                
                state.ball.spin = {
                    type: spinType,
                    intensity: spinIntensity,
                    rotation: state.ball.rotation || 0,
                    rotationSpeed: spinIntensity * 0.3,
                    appliedBy: 'player1'
                };
                
                playSpinActivated(spinType);
            } else if (state.ball.spin) {
                state.ball.spin.intensity *= 0.6;
            }
            
            playPaddleHit(state.ball.speed, state.ball.spin !== null);
            state.rallyCount++;
            state.lastHitTime = now;
        }

        if (
            state.ball.x + state.ball.radius >= state.player2.x &&
            state.ball.x + state.ball.radius <= state.player2.x + state.player2.width &&
            state.ball.y + 7.5 >= state.player2.y &&
            state.ball.y - 7.5 <= state.player2.y + state.player2.height &&
            state.ball.vx > 0
        ) {
            state.ball.vx = -Math.abs(state.ball.vx);
            state.ball.x = state.player2.x - state.ball.radius;
            
            const paddleVelocity = state.player2.velocity;
            const minVelocityForSpin = 2;
            
            if (Math.abs(paddleVelocity) > minVelocityForSpin) {
                const spinIntensity = Math.min(Math.abs(paddleVelocity) / 15, 3);
                const spinType = paddleVelocity > 0 ? 'topspin' : 'backspin';
                
                state.ball.spin = {
                    type: spinType,
                    intensity: spinIntensity,
                    rotation: state.ball.rotation || 0,
                    rotationSpeed: spinIntensity * 0.3,
                    appliedBy: 'player2'
                };
                
                playSpinActivated(spinType);
            } else if (state.ball.spin) {
                state.ball.spin.intensity *= 0.6;
            }
            
            playPaddleHit(state.ball.speed, state.ball.spin !== null);
            state.rallyCount++;
            state.lastHitTime = now;
        }

        // Goals
        if (state.ball.x - state.ball.radius < 0 && now - lastScoreTime.current > 1000) {
            state.player2.score++;
            lastScoreTime.current = now;
            playScore();
            resetBall();
            setDisplayState({ ...state });
        } else if (state.ball.x + state.ball.radius > 800 && now - lastScoreTime.current > 1000) {
            state.player1.score++;
            lastScoreTime.current = now;
            playScore();
            resetBall();
            setDisplayState({ ...state });
        }

        if (state.player1.score >= 5) {
            state.gameEnded = true;
            state.winner = currentMatch.player1.name;
            setDisplayState({ ...state });
            handleMatchEnd('player1', matchIndex);
        } else if (state.player2.score >= 5) {
            state.gameEnded = true;
            state.winner = currentMatch.player2.name;
            setDisplayState({ ...state });
            handleMatchEnd('player2', matchIndex);
        }
    };

    const handleMatchEnd = (winner: 'player1' | 'player2', matchIndex: number) => {
        const currentMatch = matchesRef.current[matchIndex];
        if (!currentMatch) return;
        
        const winnerPlayer = winner === 'player1' ? currentMatch.player1 : currentMatch.player2;
        
        
        if (matchIndex === 1) {
            setMatches(prev => {
                const updated = [...prev];
                updated[matchIndex] = {
                    ...currentMatch,
                    winner: winnerPlayer,
                    completed: true
                };
                
                const semi1Winner = updated[0]?.winner;
                
                if (semi1Winner && winnerPlayer) {
                    updated.push({
                        id: 'final',
                        player1: semi1Winner,
                        player2: winnerPlayer,
                        round: 'final',
                        matchNumber: 3,
                        winner: null,
                        completed: false
                    });
                }
                
                return updated;
            });
        } else {
            setMatches(prev => {
                const updated = [...prev];
                updated[matchIndex] = {
                    ...currentMatch,
                    winner: winnerPlayer,
                    completed: true
                };
                return updated;
            });
            
            if (matchIndex === 2) {
                setTournamentWinner(winnerPlayer);
                setTournamentComplete(true);
            }
        }
    };

    const startNextMatch = () => {
        if (currentMatchIndex < matches.length - 1) {
            const newIndex = currentMatchIndex + 1;
            currentMatchIndexRef.current = newIndex;
            setCurrentMatchIndex(newIndex);
            resetGame();
        }
    };

    const resetGame = () => {
        gameStateRef.current = {
            player1: { x: 10, y: 150, width: 10, height: 100, score: 0, velocity: 0, lastY: 150 },
            player2: { x: 780, y: 150, width: 10, height: 100, score: 0, velocity: 0, lastY: 150 },
            ball: { 
                x: 400, 
                y: 200, 
                radius: 10, 
                vx: 7,
                vy: 5,
                speed: 7,
                baseSpeed: 7,
                rotation: 0,
                spin: null
            },
            gameStarted: false,
            gameEnded: false,
            winner: null,
            startTime: Date.now(),
            rallyCount: 0,
            lastHitTime: Date.now()
        };
        keysPressed.current.clear();
        lastScoreTime.current = 0;
        setDisplayState({ ...gameStateRef.current });
    };

    const startGame = () => {
        const matchIndex = currentMatchIndexRef.current;
        
        if (!matchesRef.current[matchIndex]) {
            return;
        }
        
        gameStateRef.current.gameStarted = true;
        gameStateRef.current.gameEnded = false;
        gameStateRef.current.startTime = Date.now();
        setDisplayState({ ...gameStateRef.current });
    };

    const toggleSound = () => {
        soundEnabled.current = !soundEnabled.current;
        setSoundToggle(soundEnabled.current);
    };

    const gameLoop = () => {
        const state = gameStateRef.current;
        
        updateGame();

        const canvas = canvasRef.current;
        if (!canvas) {
            animationFrameId.current = requestAnimationFrame(gameLoop);
            return;
        }

        const ctx = canvas.getContext('2d');
        if (!ctx) {
            animationFrameId.current = requestAnimationFrame(gameLoop);
            return;
        }

        ctx.fillStyle = '#000';
        ctx.fillRect(0, 0, 800, 400);

        ctx.strokeStyle = '#444';
        ctx.lineWidth = 2;
        ctx.setLineDash([10, 10]);
        ctx.beginPath();
        ctx.moveTo(400, 0);
        ctx.lineTo(400, 400);
        ctx.stroke();
        ctx.setLineDash([]);

        ctx.fillStyle = "white";
        ctx.fillRect(state.player1.x, state.player1.y, state.player1.width, state.player1.height);
        ctx.fillRect(state.player2.x, state.player2.y, state.player2.width, state.player2.height);

        ctx.save();
        ctx.translate(state.ball.x, state.ball.y);
        ctx.rotate(state.ball.rotation);
        
        ctx.fillStyle = '#ffffff';
        ctx.beginPath();
        ctx.arc(0, 0, state.ball.radius, 0, Math.PI * 2);
        ctx.fill();

        const numSpokes = 8;
        const spokeColor = state.ball.spin 
            ? (state.ball.spin.type === 'topspin' ? '#ff4444' : '#44ff44')
            : '#888888';
        
        ctx.strokeStyle = spokeColor;
        ctx.lineWidth = 2;
        
        for (let i = 0; i < numSpokes; i++) {
            const angle = (i / numSpokes) * Math.PI * 2;
            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(
                Math.cos(angle) * state.ball.radius * 0.8,
                Math.sin(angle) * state.ball.radius * 0.8
            );
            ctx.stroke();
        }
        
        if (state.ball.spin && state.ball.spin.intensity > 0.3) {
            ctx.fillStyle = spokeColor;
            ctx.beginPath();
            ctx.arc(0, 0, state.ball.radius * 0.3, 0, Math.PI * 2);
            ctx.fill();
            
            ctx.strokeStyle = '#ffffff';
            ctx.lineWidth = 2;
            ctx.beginPath();
            
            if (state.ball.spin.type === 'topspin') {
                ctx.moveTo(0, -state.ball.radius * 0.4);
                ctx.lineTo(0, state.ball.radius * 0.4);
                ctx.lineTo(-3, state.ball.radius * 0.2);
                ctx.moveTo(0, state.ball.radius * 0.4);
                ctx.lineTo(3, state.ball.radius * 0.2);
            } else {
                ctx.moveTo(0, state.ball.radius * 0.4);
                ctx.lineTo(0, -state.ball.radius * 0.4);
                ctx.lineTo(-3, -state.ball.radius * 0.2);
                ctx.moveTo(0, -state.ball.radius * 0.4);
                ctx.lineTo(3, -state.ball.radius * 0.2);
            }
            ctx.stroke();
        } else {
            ctx.fillStyle = '#666666';
            ctx.beginPath();
            ctx.arc(0, 0, state.ball.radius * 0.3, 0, Math.PI * 2);
            ctx.fill();
        }
        
        ctx.restore();

        if (state.ball.speed) {
            const speed = state.ball.speed;
            const maxSpeed = 20;
            const progress = Math.min(speed / maxSpeed, 1);
            
            const barWidth = 200;
            const barHeight = 20;
            const barX = (canvas.width - barWidth) / 2;
            const barY = 10;
            
            ctx.fillStyle = 'rgba(0, 0, 0, 0.5)';
            ctx.fillRect(barX, barY, barWidth, barHeight);
            
            const hue = 120 - (progress * 120);
            ctx.fillStyle = `hsl(${hue}, 100%, 50%)`;
            ctx.fillRect(barX, barY, barWidth * progress, barHeight);
            
            ctx.strokeStyle = progress > 0.8 ? '#ff0000' : '#ffffff';
            ctx.lineWidth = 2;
            ctx.strokeRect(barX, barY, barWidth, barHeight);
            
            ctx.fillStyle = '#ffffff';
            ctx.font = '12px Arial';
            ctx.textAlign = 'center';
            ctx.fillText(`${getText('matchSpeed')}: ${speed.toFixed(1)}`, canvas.width / 2, barY + 35);
            
            if (progress > 0.8 && Math.floor(Date.now() / 500) % 2 === 0) {
                ctx.fillStyle = 'rgba(255, 0, 0, 0.3)';
                ctx.fillRect(barX, barY, barWidth, barHeight);
            }
        }

        if (state.ball.spin && state.ball.spin.intensity > 0.5) {
            ctx.save();
            ctx.font = 'bold 16px monospace';
            ctx.textAlign = 'center';
            ctx.fillStyle = state.ball.spin.type === 'topspin' ? '#ff00ff' : '#00ffff';
            ctx.shadowBlur = 10;
            ctx.shadowColor = ctx.fillStyle;
            ctx.fillText(
                state.ball.spin.type === 'topspin' ? '⬇️ TOPSPIN' : '⬆️ BACKSPIN',
                400,
                380
            );
            ctx.restore();
        }

        if (state.rallyCount > 5) {
            ctx.save();
            ctx.font = 'bold 14px monospace';
            ctx.textAlign = 'left';
            ctx.fillStyle = '#ffff00';
            ctx.shadowBlur = 8;
            ctx.shadowColor = '#ffff00';
            ctx.fillText(`🔥 ${getText('matchRally')}: ${state.rallyCount}`, 20, 30);
            ctx.restore();
        }

        animationFrameId.current = requestAnimationFrame(gameLoop);
    };

    useEffect(() => {
        const handleKeyDown = (e: KeyboardEvent) => {
            if (['w', 'W', 's', 'S', 'ArrowUp', 'ArrowDown'].includes(e.key)) {
                e.preventDefault();
                keysPressed.current.add(e.key);
            }
        };

        const handleKeyUp = (e: KeyboardEvent) => {
            if (['w', 'W', 's', 'S', 'ArrowUp', 'ArrowDown'].includes(e.key)) {
                e.preventDefault();
                keysPressed.current.delete(e.key);
            }
        };

        window.addEventListener('keydown', handleKeyDown);
        window.addEventListener('keyup', handleKeyUp);

        return () => {
            window.removeEventListener('keydown', handleKeyDown);
            window.removeEventListener('keyup', handleKeyUp);
        };
    }, []);

    useEffect(() => {
        gameLoop();

        return () => {
            if (animationFrameId.current) {
                cancelAnimationFrame(animationFrameId.current);
            }
        };
    }, []);

    const currentMatch = matches[currentMatchIndex];
    if (!currentMatch) {
        return <div className="min-h-screen bg-gradient-to-br from-purple-900 via-indigo-900 to-blue-900 flex items-center justify-center">
            <div className="text-white text-2xl">{getText('chatLoading')}</div>
        </div>;
    }

    return (
        <div className="min-h-screen bg-gradient-to-br from-purple-900 via-indigo-900 to-blue-900 flex flex-col items-center justify-center p-8">
            <h1 className="text-5xl font-bold text-white mb-4 text-center">
                {getText('localTournamentTitle')}
            </h1>
            <p className="text-sm text-gray-300 mb-6 text-center">
                {getText('localTournamentDescription')}
            </p>

            {!displayState.gameStarted && !tournamentComplete && (
                <div className="mb-6 bg-gray-800/90 p-6 rounded-lg border-2 border-purple-500">
                    <h2 className="text-2xl font-bold text-purple-300 mb-4 text-center">
                        {currentMatch.round === 'semifinal' ? `${getText('localTournamentSemifinal')} ${currentMatch.matchNumber}` : getText('localTournamentFinal')}
                    </h2>
                    <div className="flex items-center justify-center gap-8 text-xl font-semibold">
                        <span className={`${currentMatch.player1.eliminated ? 'text-gray-500 line-through' : 'text-blue-400'}`}>
                            {currentMatch.player1.name}
                        </span>
                        <span className="text-white">VS</span>
                        <span className={`${currentMatch.player2.eliminated ? 'text-gray-500 line-through' : 'text-red-400'}`}>
                            {currentMatch.player2.name}
                        </span>
                    </div>
                </div>
            )}

            {displayState.gameStarted && !displayState.gameEnded && (
                <div className="mb-4 flex justify-center items-center">
                    <span className="bg-gradient-to-br from-purple-600 to-purple-950 w-96 h-16 gap-2 flex justify-evenly items-center rounded-2xl text-xl font-semibold text-white overflow-hidden">
                        <h1 className="text-2xl font-bold text-white/90">{currentMatch.player1.name}</h1>
                        <div className="gap">
                            <span className="mr-6 text-2xl font-bold">{displayState.player1.score}</span> 
                            : 
                            <span className="ml-6 text-2xl font-bold">{displayState.player2.score}</span>
                        </div>
                        <h1 className="text-2xl font-bold text-white/90">{currentMatch.player2.name}</h1>
                    </span>
                </div>
            )}

            <div className="relative">
                <canvas
                    ref={canvasRef}
                    width={800}
                    height={400}
                    className="bg-black border-4 border-purple-700 rounded-lg shadow-2xl"
                />

                {!displayState.gameStarted && !displayState.gameEnded && !tournamentComplete && (
                    <div className="absolute inset-0 flex items-center justify-center bg-black/70 rounded-lg">
                        <button
                            onClick={startGame}
                            className="px-12 py-6 bg-gradient-to-r from-purple-500 to-pink-600 hover:from-purple-400 hover:to-pink-500 text-white text-3xl font-bold rounded-lg shadow-lg transition-all duration-200 hover:scale-105 active:scale-95"
                        >
                            {getText('localTournamentStartMatch')}
                        </button>
                    </div>
                )}
                {displayState.gameEnded && !tournamentComplete && (
                    <div className="absolute inset-0 flex flex-col items-center justify-center bg-black/80 rounded-lg">
                        <h2 className="text-6xl font-bold text-yellow-400 mb-4 animate-pulse">
                            🏆 {displayState.player1.score >= 5 ? currentMatch.player1.name : currentMatch.player2.name} {getText('localTournamentWins')}
                        </h2>
                        <p className="text-2xl text-white mb-8">
                            {getText('localTournamentScore')} {displayState.player1.score} - {displayState.player2.score}
                        </p>
                        {currentMatchIndex === 0 && (
                            <button
                                onClick={startNextMatch}
                                className="px-8 py-4 bg-gradient-to-r from-green-500 to-emerald-600 hover:from-green-400 hover:to-emerald-500 text-white text-2xl font-bold rounded-lg shadow-lg transition-all duration-200 hover:scale-105"
                            >
                                {getText('localTournamentScore')}
                            </button>
                        )}
                        {currentMatchIndex === 1 && matches.length === 3 && (
                            <p className="text-xl text-purple-300 animate-pulse">
                                {getText('localTournamentStartingFinal')}
                            </p>
                        )}
                    </div>
                )}

                {tournamentComplete && (
                    <div className="absolute inset-0 flex flex-col items-center justify-center bg-black/90 rounded-lg">
                        <h2 className="text-7xl font-bold text-yellow-300 mb-4 animate-bounce">
                            {getText('localTournamentChampion')}
                        </h2>
                        <h3 className="text-5xl font-bold text-white mb-8">
                            {tournamentWinner?.name}
                        </h3>
                        <button
                            onClick={() => setLocalTournament(false)}
                            className="px-8 py-4 bg-gradient-to-r from-blue-500 to-purple-600 hover:from-blue-400 hover:to-purple-500 text-white text-2xl font-bold rounded-lg shadow-lg transition-all duration-200 hover:scale-105"
                        >
                            {getText('localTournamentExitTournament')}
                        </button>
                    </div>
                )}
            </div>

            <div className="mt-6 bg-gray-800/90 px-8 py-4 rounded-lg border-2 border-gray-600">
                <div className="flex gap-12 text-white text-lg">
                    <div className="flex items-center gap-3">
                        <span className="font-bold text-blue-400">{currentMatch.player1.name}:</span>
                        <kbd className="px-3 py-2 bg-gray-700 rounded border border-gray-500">W</kbd>
                        <kbd className="px-3 py-2 bg-gray-700 rounded border border-gray-500">S</kbd>
                    </div>
                    <div className="flex items-center gap-3">
                        <span className="font-bold text-red-400">{currentMatch.player2.name}:</span>
                        <kbd className="px-3 py-2 bg-gray-700 rounded border border-gray-500">↑</kbd>
                        <kbd className="px-3 py-2 bg-gray-700 rounded border border-gray-500">↓</kbd>
                    </div>
                </div>
            </div>

            <button
                onClick={toggleSound}
                className={`mt-4 px-6 py-4 rounded-lg font-bold transition-all duration-200 ${
                    soundToggle
                        ? 'bg-green-600 hover:bg-green-700 text-white'
                        : 'bg-gray-600 hover:bg-gray-700 text-gray-300'
                }`}
            >
                {soundToggle ? getText('localTournamentAudioOn') : getText('localTournamentAudioOff')}
            </button>
            
            <button 
                className="p-3 mt-5 bg-slate-400 hover:bg-red-500 rounded-xl text-black font-bold" 
                onClick={() => setLocalTournament(false)}
            >
                {getText('localTournamentExit')}
            </button>
        </div>
    );
}