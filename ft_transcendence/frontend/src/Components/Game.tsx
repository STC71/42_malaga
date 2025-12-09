// 🎮 COMPONENTE PRINCIPAL DEL JUEGO PONG AVANZADO - TODAS LAS FASES
// Este archivo contiene la implementación completa del cliente de juego
// Incluye: controles, renderizado, efectos visuales, audio, replay y estadísticas

import { useContext, useEffect, useRef, useState } from "react"
import { ComponentContext } from "../Context/ComponentsContext"
import { AuthContext } from "../Context/AuthContext"
import type { AuthContextType, ComponentContextType, GameRoom } from '../types'
import LocalGame from "./LocalGame";

// 🏗️ INTERFAZ DEL ESTADO DEL JUEGO - EXTENDIDA EN FASES 2 Y 3
// Define la estructura completa del estado que recibimos del servidor
interface GameState {
    player1: {
        x: number;
        y: number;
        width: number;
        height: number;
        score?: number;
        velocity?: number;
        lastY?: number;
    };
    player2: {
        x: number;
        y: number;
        width: number;
        height: number;
        score?: number;
        velocity?: number;
        lastY?: number;
        targetY?: number;
        aiData?: {
            confidence: number;
            spinDetected: boolean;
            spinType: 'topspin' | 'backspin' | null;
            predictedY: number;
            compensationApplied: number;
        };
    };
    ball: {
        x: number;
        y: number;
        radius: number;
        vx?: number;
        vy?: number;
        speed?: number;
        baseSpeed?: number;
        spin?: {
            type: 'topspin' | 'backspin';
            intensity: number;
            rotation: number;
            rotationSpeed: number;
            appliedBy?: string;
        } | null;
        rotation?: number;
    };
    players: Array<{
        userId: number;
        username: string;
        isPlayer1: boolean;
    }>;
    aiDifficulty?: string;
    rallyCount?: number;
    startTime?: number;
    lastHitTime?: number;
}

// 🎆 INTERFAZ DE PARTÍCULAS - FASE 4: SISTEMA DE EFECTOS VISUALES
// Define las propiedades de cada partícula para efectos espectaculares
interface Particle {
    x: number;           // Posición X actual
    y: number;           // Posición Y actual
    vx: number;          // Velocidad horizontal (píxeles/frame)
    vy: number;          // Velocidad vertical (píxeles/frame)
    life: number;        // Vida restante (0.0 - 1.0)
    maxLife: number;     // Vida máxima inicial
    size: number;        // Tamaño actual (se reduce con el tiempo)
    color: string;       // Color en formato CSS
    type: 'collision' | 'trail' | 'warp' | 'spark';  // Tipo de efecto
    alpha: number;       // Transparencia para fade-out
}

// 📹 INTERFAZ DE FRAME DE REPLAY - FASE 6: SISTEMA DE GRABACIÓN
// Cada frame captura el estado completo del juego para reproducción
interface ReplayFrame {
    timestamp: number;                           // Momento exacto de captura
    gameState: GameState;                       // Estado completo del juego
    isHighlight: boolean;                       // ¿Es un momento destacado?
    highlightType?: 'collision' | 'score' | 'spin' | 'highspeed' | undefined; // Tipo de highlight
}

// 📊 INTERFAZ DE ESTADÍSTICAS DE JUEGO - FASE 7: ANÁLISIS Y MÉTRICAS
// Recopila todas las métricas importantes durante la partida
interface GameStats {
    totalHits: number;        // Total de golpes en la partida
    player1Hits: number;      // Golpes del jugador 1
    player2Hits: number;      // Golpes del jugador 2 (o IA)
    topspinCount: number;     // Cantidad de topspins generados
    backspinCount: number;    // Cantidad de backspins generados
    maxSpeed: number;         // Velocidad máxima alcanzada
    avgSpeed: number;         // Velocidad promedio calculada
    speedSamples: number[];   // Muestras de velocidad (últimas 100)
    longestRally: number;     // Rally más largo (golpes consecutivos)
    totalDistance: number;    // Distancia total recorrida por la pelota
    gameDuration: number;     // Duración total del juego en ms
    startTime: number;        // Timestamp de inicio para cálculos
}

// 🗺️ INTERFAZ DE PUNTO DE HEATMAP - FASE 7: VISUALIZACIÓN DE ZONAS CALIENTES
// Cada punto representa una posición de la pelota con su intensidad
interface HeatmapPoint {
    x: number;          // Coordenada X en el canvas
    y: number;          // Coordenada Y en el canvas
    intensity: number;  // Intensidad basada en velocidad (0-1)
}

interface PlayersScores {
    player1Score: number;
    player1Name: string;
    player2Score: number;
    player2Name: string;
}

const Game: React.FC = (): React.ReactElement => {
    const authContext = useContext(AuthContext) as AuthContextType;
    const componentContext = useContext(ComponentContext) as ComponentContextType;
    
    const { user, language, lan } = authContext;
    const { socket, roomsRunning, roomIamIn, setRoomIamIn, isAiEnabled, setIsAiEnabled, waitingForOpponent, setWaitingForOpponent } = componentContext;
    
    const [gameName, setGameName] = useState<string>(user?.username || '');
    const [roomsPlayerIsIn, setRoomPlayerIsIn] = useState<GameRoom[]>([]);
    const [gameState, setGameState] = useState<GameState | null>(null);
    const [playersScores, setPlayersScores] = useState<PlayersScores>({
        player1Score: 0,
        player1Name: '',
        player2Score: 0,
        player2Name: ''
    });
    const [chooseOponent, setChooseOponent] = useState<boolean>(false);
    const [oponent, setOponent] = useState<string>('robocot');
    const [difficultyLevel, setDifficultyLevel] = useState<string>('medium'); // 🎯 Dificultad por defecto
    const [createNewGame, setCreateNewGame] = useState<boolean>(false);
    const [showControls, setShowControls] = useState<boolean>(true);
    const [showAIOverlay, setShowAIOverlay] = useState<boolean>(true);
    const [ballTrail, setBallTrail] = useState<Array<{x: number, y: number, alpha: number}>>([]);
    const [particles, setParticles] = useState<Particle[]>([]);
    const [soundEnabled, setSoundEnabled] = useState<boolean>(true);
    const [ambientVolume, setAmbientVolume] = useState<number>(0.05); // 🔊 Volumen reducido para evitar sonido de motor
    const [isRecording, setIsRecording] = useState<boolean>(true);
    const [isReplaying, setIsReplaying] = useState<boolean>(false);
    const [replaySpeed, setReplaySpeed] = useState<number>(1);
    const [replayFrame, setReplayFrame] = useState<number>(0);
    const [showReplayControls, setShowReplayControls] = useState<boolean>(false);
    const [showStats, setShowStats] = useState<boolean>(false);
    const [gameStats, setGameStats] = useState<GameStats>({
        totalHits: 0,
        player1Hits: 0,
        player2Hits: 0,
        topspinCount: 0,
        backspinCount: 0,
        maxSpeed: 0,
        avgSpeed: 0,
        speedSamples: [],
        longestRally: 0,
        totalDistance: 0,
        gameDuration: 0,
        startTime: Date.now()
    });

    const canvasRef = useRef<HTMLCanvasElement>(null);
    const keysPressed = useRef<Set<string>>(new Set());
    const lastBallPos = useRef<{x: number, y: number}>({x: 400, y: 200});
    const lastCollisionTime = useRef<number>(0);
    const animationFrameId = useRef<number | null>(null);
    const audioContext = useRef<AudioContext | null>(null);
    const ambientOscillator = useRef<OscillatorNode | null>(null);
    const ambientGain = useRef<GainNode | null>(null);
    const replayBuffer = useRef<ReplayFrame[]>([]);
    const maxReplayFrames = useRef<number>(600); // 10 segundos a 60fps
    const replayIntervalId = useRef<number | null>(null);
    const heatmapData = useRef<HeatmapPoint[]>([]);
    const lastHitBy = useRef<'player1' | 'player2' | null>(null);
    const prevGameState = useRef<GameState | null>(null);
    const localPaddleY = useRef<number>(150); // 🎮 Posición local del paddle para predicción
	const [localGame, setLocalGame] = useState<boolean>(false);

    // 🎆 SISTEMA DE PARTÍCULAS - FASE 4: GENERADOR DE EFECTOS VISUALES
    // Crea partículas con diferentes comportamientos según el tipo de evento
    const createParticles = (
        x: number,      // Posición X de origen
        y: number,      // Posición Y de origen
        count: number,  // Número de partículas a crear
        type: 'collision' | 'trail' | 'warp' | 'spark',  // Tipo de efecto
        color?: string, // Color personalizado (opcional)
        speed?: number  // Velocidad base (opcional)
    ): Particle[] => {
        const newParticles: Particle[] = [];
        const baseSpeed = speed || 3;
        
        // 🔄 GENERAR PARTÍCULAS CON DISTRIBUCIÓN CIRCULAR
        for (let i = 0; i < count; i++) {
            // 📐 ÁNGULO DE DISPERSIÓN: circular con variación aleatoria
            const angle = (Math.PI * 2 * i) / count + (Math.random() - 0.5) * 0.5;
            // ⚡ VELOCIDAD: base con variación aleatoria ±50%
            const velocity = baseSpeed * (0.5 + Math.random() * 0.5);
            
            // 🎨 CONFIGURACIÓN POR TIPO DE PARTÍCULA
            let particleColor = color || '#ffffff';
            let maxLife = 30;     // Frames de vida por defecto
            let size = 3;         // Tamaño por defecto
            
            switch (type) {
                case 'collision':
                    // 💥 EXPLOSIONES DE COLISIÓN: Grandes, amarillas, duraderas
                    particleColor = color || '#ffff00';
                    maxLife = 40;     // Vida larga para impacto visual
                    size = 4 + Math.random() * 3;  // Tamaño variable 4-7
                    break;
                case 'trail':
                    // 🌟 ESTELAS DE VELOCIDAD: Pequeñas, rápidas
                    maxLife = 20;     // Vida corta para efecto de estela
                    size = 2;         // Tamaño pequeño y uniforme
                    break;
                case 'warp':
                    // 🌀 EFECTOS WARP: Cian, medianos
                    particleColor = color || '#00ffff';
                    maxLife = 25;     // Vida media
                    size = 2 + Math.random() * 2;  // Tamaño variable 2-4
                    break;
                case 'spark':
                    // ⚡ CHISPAS: Naranjas, medianas, para paredes
                    particleColor = color || '#ff8800';
                    maxLife = 30;     // Vida estándar
                    size = 2 + Math.random() * 2;  // Tamaño variable 2-4
                    break;
            }
            
            // ➕ CREAR Y AÑADIR NUEVA PARTÍCULA
            newParticles.push({
                x,
                y,
                vx: Math.cos(angle) * velocity,    // Componente X de velocidad
                vy: Math.sin(angle) * velocity,    // Componente Y de velocidad
                life: maxLife,                     // Vida inicial = vida máxima
                maxLife,                           // Para calcular alpha posteriormente
                size,
                color: particleColor,
                type,
                alpha: 1                           // Opacidad inicial completa
            });
        }
        
        return newParticles;
    };

    // 🔄 ACTUALIZADOR DE FÍSICA DE PARTÍCULAS - FASE 4
    // Aplica física realista: movimiento, gravedad, resistencia del aire y ciclo de vida
    const updateParticles = (currentParticles: Particle[]): Particle[] => {
        return currentParticles
            .map(p => ({
                ...p,
                x: p.x + p.vx,              // 📍 NUEVA POSICIÓN X
                y: p.y + p.vy,              // 📍 NUEVA POSICIÓN Y
                vy: p.vy + 0.15,            // 🌍 GRAVEDAD: acelera hacia abajo
                vx: p.vx * 0.98,            // 💨 RESISTENCIA DEL AIRE: reduce velocidad X
                life: p.life - 1,           // ⏳ ENVEJECIMIENTO: reduce vida
                alpha: p.life / p.maxLife   // 👻 TRANSPARENCIA: fade-out gradual
            }))
            .filter(p => p.life > 0 && p.y < 450); // 🗑️ ELIMINAR partículas muertas o fuera del canvas
    };

    const renderParticles = (ctx: CanvasRenderingContext2D, currentParticles: Particle[]) => {
        currentParticles.forEach(p => {
            ctx.save();
            ctx.globalAlpha = p.alpha;
            
            if (p.type === 'warp') {
                // Efecto warp - l\u00ednea alargada
                ctx.strokeStyle = p.color;
                ctx.lineWidth = p.size;
                ctx.beginPath();
                ctx.moveTo(p.x - p.vx * 2, p.y - p.vy * 2);
                ctx.lineTo(p.x, p.y);
                ctx.stroke();
            } else if (p.type === 'spark') {
                // Chispas - forma de estrella
                ctx.fillStyle = p.color;
                ctx.shadowBlur = 10;
                ctx.shadowColor = p.color;
                ctx.beginPath();
                ctx.arc(p.x, p.y, p.size, 0, Math.PI * 2);
                ctx.fill();
            } else {
                // Part\u00edculas normales
                ctx.fillStyle = p.color;
                if (p.type === 'collision') {
                    ctx.shadowBlur = 5;
                    ctx.shadowColor = p.color;
                }
                ctx.beginPath();
                ctx.arc(p.x, p.y, p.size, 0, Math.PI * 2);
                ctx.fill();
            }
            
            ctx.restore();
        });
    };

    // 🔊 SOUND SYSTEM FUNCTIONS
    // 🔊 INICIALIZADOR DE AUDIO - FASE 5: SISTEMA DE SONIDO PROCEDURAL
    // Crea el contexto de Web Audio API de forma segura
    const initAudio = () => {
        if (!audioContext.current) {
            // Compatibilidad con navegadores que usan prefijo webkit
            audioContext.current = new (window.AudioContext || (window as any).webkitAudioContext)();
        }
        return audioContext.current;
    };

    // 🏓 SONIDO DE GOLPE DE PALA - FASE 5
    // Genera sonido dinámico basado en velocidad y presencia de spin
    const playPaddleHit = (speed: number, hasSpin: boolean) => {
        if (!soundEnabled) return;  // ❌ Salir si audio está desactivado
        const ctx = initAudio();
        
        // 🎵 CÁLCULO DE FRECUENCIA DINÁMICA
        // Velocidad baja = sonido grave (200Hz), velocidad alta = sonido agudo (800Hz)
        const baseFreq = 200 + (speed / 25) * 600;
        const volume = Math.min(0.3 + (speed / 25) * 0.4, 0.7);
        
        // 🎛️ CREAR OSCILADOR Y CONTROL DE VOLUMEN
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
        
        // Efecto de "click" adicional para impactos fuertes
        if (speed > 15) {
            const noiseBuffer = ctx.createBuffer(1, ctx.sampleRate * 0.05, ctx.sampleRate);
            const data = noiseBuffer.getChannelData(0);
            for (let i = 0; i < data.length; i++) {
                data[i] = (Math.random() * 2 - 1) * 0.3;
            }
            
            const noiseSource = ctx.createBufferSource();
            const noiseGain = ctx.createGain();
            
            noiseSource.buffer = noiseBuffer;
            noiseGain.gain.setValueAtTime(0.2, ctx.currentTime);
            noiseGain.gain.exponentialRampToValueAtTime(0.01, ctx.currentTime + 0.05);
            
            noiseSource.connect(noiseGain);
            noiseGain.connect(ctx.destination);
            
            noiseSource.start(ctx.currentTime);
        }
    };

    const playWallBounce = () => {
        if (!soundEnabled) return;
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
        if (!soundEnabled) return;
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

    const playScore = (isPlayer1: boolean) => {
        if (!soundEnabled) return;
        const ctx = initAudio();
        
        // Melodía corta para puntuación
        const frequencies = isPlayer1 ? [523, 659, 784] : [392, 330, 262]; // C-E-G vs G-E-C
        
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

    const updateAmbientSound = (intensity: number) => {
        if (!soundEnabled || !audioContext.current) return;
        
        const ctx = audioContext.current;
        
        if (!ambientOscillator.current) {
            // Crear oscilador de ambiente
            ambientOscillator.current = ctx.createOscillator();
            ambientGain.current = ctx.createGain();
            
            ambientOscillator.current.type = 'sine';
            ambientOscillator.current.frequency.setValueAtTime(60, ctx.currentTime);
            
            ambientGain.current.gain.setValueAtTime(0, ctx.currentTime);
            
            ambientOscillator.current.connect(ambientGain.current);
            ambientGain.current.connect(ctx.destination);
            
            ambientOscillator.current.start();
        }
        
        if (ambientGain.current) {
            // Volumen basado en intensidad (0-1)
            const targetVolume = intensity * ambientVolume * 0.15;
            ambientGain.current.gain.linearRampToValueAtTime(targetVolume, ctx.currentTime + 0.1);
            
            // Frecuencia aumenta con intensidad
            if (ambientOscillator.current) {
                const targetFreq = 60 + intensity * 80;
                ambientOscillator.current.frequency.linearRampToValueAtTime(targetFreq, ctx.currentTime + 0.1);
            }
        }
    };

    const startAmbientSound = () => {
        if (!audioContext.current) {
            audioContext.current = new (window.AudioContext || (window as any).webkitAudioContext)();
        }
        
        const ctx = audioContext.current;
        
        if (!ambientOscillator.current) {
            ambientOscillator.current = ctx.createOscillator();
            ambientGain.current = ctx.createGain();
            
            ambientOscillator.current.type = 'sine';
            ambientOscillator.current.frequency.setValueAtTime(60, ctx.currentTime);
            
            ambientGain.current.gain.setValueAtTime(0, ctx.currentTime);
            
            ambientOscillator.current.connect(ambientGain.current);
            ambientGain.current.connect(ctx.destination);
            
            ambientOscillator.current.start();
        }
    };

    const stopAmbientSound = () => {
        if (ambientGain.current && audioContext.current) {
            ambientGain.current.gain.linearRampToValueAtTime(0, audioContext.current.currentTime + 0.5);
        }
        
        if (ambientOscillator.current) {
            setTimeout(() => {
                if (ambientOscillator.current) {
                    ambientOscillator.current.stop();
                    ambientOscillator.current = null;
                }
                if (ambientGain.current) {
                    ambientGain.current = null;
                }
            }, 500);
        }
    };

    // 📹 REPLAY SYSTEM FUNCTIONS
    const recordFrame = (state: GameState) => {
        if (!isRecording || isReplaying) return;
        
        const ballSpeed = state.ball.speed || 0;
        const hasSpin = state.ball.spin && state.ball.spin.intensity > 1;
        const isHighSpeed = ballSpeed > 18;
        
        // Detectar highlights
        let isHighlight = false;
        let highlightType: 'collision' | 'score' | 'spin' | 'highspeed' | undefined;
        
        if (hasSpin) {
            isHighlight = true;
            highlightType = 'spin';
        } else if (isHighSpeed) {
            isHighlight = true;
            highlightType = 'highspeed';
        }
        
        const frame: ReplayFrame = {
            timestamp: Date.now(),
            gameState: JSON.parse(JSON.stringify(state)), // Deep clone
            isHighlight,
            highlightType
        };
        
        replayBuffer.current.push(frame);
        
        // Limitar tamaño del buffer (FIFO)
        if (replayBuffer.current.length > maxReplayFrames.current) {
            replayBuffer.current.shift();
        }
    };

    const startReplay = () => {
        if (replayBuffer.current.length === 0) return;
        
        setIsReplaying(true);
        setIsRecording(false);
        setReplayFrame(0);
        setShowReplayControls(true);
        
        // Pausar sonido ambiente
        stopAmbientSound();
    };

    const stopReplay = () => {
        setIsReplaying(false);
        setIsRecording(true);
        setReplayFrame(0);
        
        if (replayIntervalId.current) {
            clearInterval(replayIntervalId.current);
            replayIntervalId.current = null;
        }
    };

    const playReplay = () => {
        if (replayIntervalId.current) return; // Ya está reproduciendo
        
        const frameInterval = (1000 / 60) / replaySpeed; // 60fps ajustado por velocidad
        
        replayIntervalId.current = window.setInterval(() => {
            setReplayFrame(prev => {
                const next = prev + 1;
                if (next >= replayBuffer.current.length) {
                    if (replayIntervalId.current) {
                        clearInterval(replayIntervalId.current);
                        replayIntervalId.current = null;
                    }
                    return prev;
                }
                return next;
            });
        }, frameInterval);
    };

    const pauseReplay = () => {
        if (replayIntervalId.current) {
            clearInterval(replayIntervalId.current);
            replayIntervalId.current = null;
        }
    };

    const seekReplay = (frameNumber: number) => {
        pauseReplay();
        setReplayFrame(Math.max(0, Math.min(frameNumber, replayBuffer.current.length - 1)));
    };

    const jumpToHighlight = (direction: 'next' | 'prev') => {
        const currentFrame = replayFrame;
        const highlights = replayBuffer.current
            .map((frame, index) => ({ frame, index }))
            .filter(({ frame }) => frame.isHighlight);
        
        if (highlights.length === 0) return;
        
        if (direction === 'next') {
            const nextHighlight = highlights.find(({ index }) => index > currentFrame);
            if (nextHighlight) {
                seekReplay(nextHighlight.index);
            }
        } else {
            const prevHighlight = highlights.reverse().find(({ index }) => index < currentFrame);
            if (prevHighlight) {
                seekReplay(prevHighlight.index);
            }
        }
    };

    const clearReplayBuffer = () => {
        replayBuffer.current = [];
        setReplayFrame(0);
        stopReplay();
    };

    useEffect(() => {
        const rooms = roomsRunning?.filter((room: GameRoom) =>
            room.players.some(player => player.userId === user?.id)
        ) || [];
        setRoomPlayerIsIn(rooms);
    }, [roomsRunning, user?.id]);

    useEffect(() => {
        if (!gameState) {
            if (setWaitingForOpponent) setWaitingForOpponent(true);
            return;
        }
        
        // 📹 REPLAY: Determinar qué estado renderizar
        const stateToRender: GameState = (isReplaying && replayBuffer.current[replayFrame]) 
            ? replayBuffer.current[replayFrame].gameState 
            : gameState;
        
        // 📹 RECORDING: Grabar frame si no está en replay
        if (!isReplaying) {
            recordFrame(gameState);
        }
        
        const canvas = canvasRef.current;
        if (!canvas) return;
        const ctx = canvas.getContext("2d");
        if (!ctx) return;

        // 💥 SCREEN SHAKE en colisiones de alta velocidad
        const currentBallSpeed = stateToRender.ball.speed || 5;
        if (currentBallSpeed > 18) {
            const shakeIntensity = Math.min((currentBallSpeed - 18) / 7, 1) * 3;
            ctx.translate(
                (Math.random() - 0.5) * shakeIntensity,
                (Math.random() - 0.5) * shakeIntensity
            );
        }

        ctx.clearRect(0, 0, canvas.width, canvas.height);

        // center dashed line
        ctx.strokeStyle = "#444";
        ctx.lineWidth = 2;
        ctx.setLineDash([10, 10]);
        ctx.beginPath();
        ctx.moveTo(canvas.width / 2, 0);
        ctx.lineTo(canvas.width / 2, canvas.height);
        ctx.stroke();
        ctx.setLineDash([]);

        // 🎮 PADDLES - Con predicción del lado del cliente para el jugador humano
        const playerIsP1 = stateToRender.players.find(p => p.userId === user?.id)?.isPlayer1;
        
        // Player 1 paddle (usar localPaddleY si es el jugador humano)
        const player1Y = (playerIsP1 && keysPressed.current.size > 0) 
            ? localPaddleY.current 
            : stateToRender.player1.y;
        
        ctx.fillStyle = "white";
        ctx.fillRect(
            stateToRender.player1.x,
            player1Y,
            stateToRender.player1.width,
            stateToRender.player1.height
        );
        
        // Player 2 paddle (usar localPaddleY si es el jugador humano)
        const player2Y = (!playerIsP1 && keysPressed.current.size > 0) 
            ? localPaddleY.current 
            : stateToRender.player2.y;
        
        ctx.fillRect(
            stateToRender.player2.x,
            player2Y,
            stateToRender.player2.width,
            stateToRender.player2.height
        );

        // 🌀 BALL WITH ROTATING SPOKES AND SPIN EFFECTS
        ctx.save();
        
        // Trail/Estela de la bola
        if (stateToRender.ball.spin && stateToRender.ball.spin.intensity > 0.5) {
            const trailLength = Math.min(Math.floor(stateToRender.ball.spin.intensity * 5), 15);
            const newTrail = [...ballTrail, { x: stateToRender.ball.x, y: stateToRender.ball.y, alpha: 1 }];
            
            // Limitar longitud del trail
            if (newTrail.length > trailLength) {
                newTrail.shift();
            }
            
            // Dibujar trail
            newTrail.forEach((point, index) => {
                const alpha = (index / newTrail.length) * 0.4;
                const size = gameState.ball.radius * (index / newTrail.length);
                const spinColor = gameState.ball.spin!.type === 'topspin' ? '#ff4444' : '#44ff44';
                
                ctx.fillStyle = `${spinColor}${Math.floor(alpha * 255).toString(16).padStart(2, '0')}`;
                ctx.beginPath();
                ctx.arc(point.x, point.y, size, 0, Math.PI * 2);
                ctx.fill();
            });
            
            setBallTrail(newTrail);
        } else if (ballTrail.length > 0) {
            // Fade out trail
            setBallTrail([]);
        }
        
        // Posicionar en el centro de la bola
        ctx.translate(gameState.ball.x, gameState.ball.y);
        
        // Aplicar rotación
        const rotation = gameState.ball.rotation || 0;
        ctx.rotate(rotation);
        
        // Glow effect según velocidad
        const speed = gameState.ball.speed || 5;
        const glowIntensity = Math.min(speed / 20, 1);
        
        if (glowIntensity > 0.3) {
            ctx.shadowBlur = 20 * glowIntensity;
            ctx.shadowColor = gameState.ball.spin 
                ? (gameState.ball.spin.type === 'topspin' ? '#ff4444' : '#44ff44')
                : '#ffffff';
        }
        
        // Cuerpo de la bola (blanco)
        ctx.fillStyle = '#ffffff';
        ctx.beginPath();
        ctx.arc(0, 0, gameState.ball.radius, 0, Math.PI * 2);
        ctx.fill();
        
        // 8 radios desde el centro
        const numSpokes = 8;
        const spokeColor = gameState.ball.spin 
            ? (gameState.ball.spin.type === 'topspin' ? '#ff4444' : '#44ff44')
            : '#888888';
        
        ctx.strokeStyle = spokeColor;
        ctx.lineWidth = 2;
        
        for (let i = 0; i < numSpokes; i++) {
            const angle = (i / numSpokes) * Math.PI * 2;
            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(
                Math.cos(angle) * gameState.ball.radius * 0.8,
                Math.sin(angle) * gameState.ball.radius * 0.8
            );
            ctx.stroke();
        }
        
        // Círculo central con color según spin
        if (gameState.ball.spin && gameState.ball.spin.intensity > 0.3) {
            ctx.fillStyle = spokeColor;
            ctx.beginPath();
            ctx.arc(0, 0, gameState.ball.radius * 0.3, 0, Math.PI * 2);
            ctx.fill();
            
            // Indicador de dirección del spin
            ctx.strokeStyle = '#ffffff';
            ctx.lineWidth = 2;
            ctx.beginPath();
            
            if (gameState.ball.spin.type === 'topspin') {
                // Flecha hacia abajo
                ctx.moveTo(0, -gameState.ball.radius * 0.4);
                ctx.lineTo(0, gameState.ball.radius * 0.4);
                ctx.lineTo(-3, gameState.ball.radius * 0.2);
                ctx.moveTo(0, gameState.ball.radius * 0.4);
                ctx.lineTo(3, gameState.ball.radius * 0.2);
            } else {
                // Flecha hacia arriba
                ctx.moveTo(0, gameState.ball.radius * 0.4);
                ctx.lineTo(0, -gameState.ball.radius * 0.4);
                ctx.lineTo(-3, -gameState.ball.radius * 0.2);
                ctx.moveTo(0, -gameState.ball.radius * 0.4);
                ctx.lineTo(3, -gameState.ball.radius * 0.2);
            }
            ctx.stroke();
        } else {
            // Círculo central gris si no hay spin
            ctx.fillStyle = '#666666';
            ctx.beginPath();
            ctx.arc(0, 0, gameState.ball.radius * 0.3, 0, Math.PI * 2);
            ctx.fill();
        }
        
        ctx.restore();
        
        // 🎆 PARTICLE GENERATION & DETECTION
        const currentTime = Date.now();
        const ballSpeed = gameState.ball.speed || 5;
        
        // Detectar colisiones con palas
        const ballHitPaddle1 = (
            gameState.ball.x - gameState.ball.radius <= gameState.player1.x + gameState.player1.width &&
            gameState.ball.y >= gameState.player1.y &&
            gameState.ball.y <= gameState.player1.y + gameState.player1.height
        );
        
        const ballHitPaddle2 = (
            gameState.ball.x + gameState.ball.radius >= gameState.player2.x &&
            gameState.ball.y >= gameState.player2.y &&
            gameState.ball.y <= gameState.player2.y + gameState.player2.height
        );
        
        // Generar part\u00edculas en colisi\u00f3n con pala
        if ((ballHitPaddle1 || ballHitPaddle2) && currentTime - lastCollisionTime.current > 100) {
            lastCollisionTime.current = currentTime;
            const collisionX = ballHitPaddle1 ? gameState.player1.x + gameState.player1.width : gameState.player2.x;
            const collisionY = gameState.ball.y;
            
            // Explosion de colisi\u00f3n
            const spinColor = gameState.ball.spin?.type === 'topspin' ? '#ff4444' : gameState.ball.spin?.type === 'backspin' ? '#44ff44' : '#ffff00';
            const collisionParticles = createParticles(collisionX, collisionY, 15, 'collision', spinColor, ballSpeed * 0.8);
            
            // Chispas adicionales si hay spin
            if (gameState.ball.spin && gameState.ball.spin.intensity > 1) {
                const sparkParticles = createParticles(collisionX, collisionY, 8, 'spark', spinColor, ballSpeed * 1.2);
                setParticles(prev => [...prev, ...collisionParticles, ...sparkParticles]);
            } else {
                setParticles(prev => [...prev, ...collisionParticles]);
            }
        }
        
        // Detectar colisiones con bordes (superior/inferior)
        const ballHitTopWall = gameState.ball.y - gameState.ball.radius <= 0;
        const ballHitBottomWall = gameState.ball.y + gameState.ball.radius >= canvas.height;
        
        if ((ballHitTopWall || ballHitBottomWall) && currentTime - lastCollisionTime.current > 100) {
            lastCollisionTime.current = currentTime;
            
            // 🔊 SOUND: Wall bounce
            playWallBounce();
            
            const wallY = ballHitTopWall ? 0 : canvas.height;
            const sparkParticles = createParticles(gameState.ball.x, wallY, 10, 'spark', '#ff8800', ballSpeed * 0.6);
            setParticles(prev => [...prev, ...sparkParticles]);
        }
        
        // Trail de velocidad (solo a velocidades altas)
        if (ballSpeed > 12) {
            const trailColor = ballSpeed > 18 ? '#00ffff' : '#ffffff';
            const trailParticles = createParticles(gameState.ball.x, gameState.ball.y, 2, 'trail', trailColor, 0.5);
            setParticles(prev => [...prev, ...trailParticles]);
        }
        
        // Efecto WARP a velocidades extremas (>20)
        if (ballSpeed > 20) {
            const warpParticles = createParticles(lastBallPos.current.x, lastBallPos.current.y, 5, 'warp', '#00ffff', ballSpeed * 0.3);
            setParticles(prev => [...prev, ...warpParticles]);
        }
        
        // Actualizar \u00faltima posici\u00f3n
        lastBallPos.current = { x: gameState.ball.x, y: gameState.ball.y };
        
        // Actualizar y renderizar part\u00edculas
        const updatedParticles = updateParticles(particles);
        renderParticles(ctx, updatedParticles);
        setParticles(updatedParticles);
        
        // 🔊 AMBIENT SOUND - intensidad basada en velocidad
        const speedIntensity = Math.min(ballSpeed / 25, 1);
        updateAmbientSound(speedIntensity);
        
        // 📊 STATISTICS: Track speed, spin usage, position for heatmap
        setGameStats(prev => {
            const newStats = { ...prev };
            
            // Track speed stats
            newStats.speedSamples.push(ballSpeed);
            if (newStats.speedSamples.length > 100) newStats.speedSamples.shift(); // Keep last 100
            newStats.maxSpeed = Math.max(newStats.maxSpeed, ballSpeed);
            newStats.avgSpeed = newStats.speedSamples.reduce((a, b) => a + b, 0) / newStats.speedSamples.length;
            
            // Track spin usage
            if (gameState.ball.spin && gameState.ball.spin.intensity > 0.5) {
                if (gameState.ball.spin.type === 'topspin') {
                    newStats.topspinCount++;
                } else if (gameState.ball.spin.type === 'backspin') {
                    newStats.backspinCount++;
                }
            }
            
            // Track ball distance traveled
            const dx = gameState.ball.x - lastBallPos.current.x;
            const dy = gameState.ball.y - lastBallPos.current.y;
            const distance = Math.sqrt(dx * dx + dy * dy);
            newStats.totalDistance += distance;
            
            // Track game duration
            newStats.gameDuration = Date.now() - newStats.startTime;
            
            return newStats;
        });
        
        // 📍 HEATMAP: Add current ball position
        heatmapData.current.push({
            x: gameState.ball.x,
            y: gameState.ball.y,
            intensity: ballSpeed / 25 // Normalize intensity
        });
        
        // Keep heatmap data manageable (max 1000 points)
        if (heatmapData.current.length > 1000) {
            heatmapData.current.shift();
        }
        
        // 🌀 SPIN INDICATOR (top right)
        if (gameState.ball.spin && gameState.ball.spin.intensity > 0.5) {
            const spinX = canvas.width - 120;
            const spinY = 15;
            
            ctx.fillStyle = 'rgba(0, 0, 0, 0.7)';
            ctx.fillRect(spinX, spinY, 110, 45);
            
            const spinColor = gameState.ball.spin.type === 'topspin' ? '#ff4444' : '#44ff44';
            const spinLabel = gameState.ball.spin.type === 'topspin' ? 'TOPSPIN ⬇️' : 'BACKSPIN ⬆️';
            
            ctx.fillStyle = spinColor;
            ctx.font = 'bold 12px Arial';
            ctx.textAlign = 'left';
            ctx.fillText(spinLabel, spinX + 8, spinY + 18);
            
            // Barra de intensidad
            ctx.fillStyle = 'rgba(255, 255, 255, 0.3)';
            ctx.fillRect(spinX + 8, spinY + 25, 94, 8);
            
            ctx.fillStyle = spinColor;
            ctx.fillRect(spinX + 8, spinY + 25, 94 * Math.min(gameState.ball.spin.intensity / 3, 1), 8);
            
            ctx.strokeStyle = spinColor;
            ctx.lineWidth = 1;
            ctx.strokeRect(spinX + 8, spinY + 25, 94, 8);
        }

        // 🤖 AI VISUALIZATION OVERLAY
        if (showAIOverlay && gameState.aiDifficulty && gameState.player2.aiData && (gameState.ball.vx || 0) > 0) {
            const aiData = gameState.player2.aiData;
            const paddle = gameState.player2;
            const ball = gameState.ball;
            
            // Color según dificultad
            const difficultyColors: Record<string, string> = {
                easy: '#4ade80',      // green
                medium: '#fbbf24',    // yellow
                hard: '#f87171',      // red
                impossible: '#a855f7' // purple
            };
            const aiColor = difficultyColors[gameState.aiDifficulty] || '#ffffff';
            
            // 📍 PREDICTION LINE - L\u00ednea de predicción de la IA
            if (aiData.predictedY !== undefined) {
                ctx.save();
                ctx.strokeStyle = aiColor;
                ctx.lineWidth = 2;
                ctx.setLineDash([5, 5]);
                ctx.globalAlpha = 0.6;
                
                // L\u00ednea desde la bola hasta la predicci\u00f3n
                ctx.beginPath();
                ctx.moveTo(ball.x, ball.y);
                ctx.lineTo(paddle.x + paddle.width / 2, aiData.predictedY + paddle.height / 2);
                ctx.stroke();
                
                // C\u00edrculo en la predicci\u00f3n
                ctx.setLineDash([]);
                ctx.beginPath();
                ctx.arc(paddle.x + paddle.width / 2, aiData.predictedY + paddle.height / 2, 8, 0, Math.PI * 2);
                ctx.stroke();
                
                ctx.restore();
            }
            
            // 🎯 CONFIDENCE BAR - Barra de confianza de la IA (lado derecho)
            const confX = canvas.width - 15;
            const confY = 100;
            const confHeight = 150;
            const confWidth = 8;
            
            // Barra de fondo
            ctx.fillStyle = 'rgba(0, 0, 0, 0.5)';
            ctx.fillRect(confX, confY, confWidth, confHeight);
            
            // Barra de confianza (de abajo hacia arriba)
            const confidence = aiData.confidence || 0.5;
            const filledHeight = confHeight * confidence;
            
            ctx.fillStyle = aiColor;
            ctx.fillRect(confX, confY + confHeight - filledHeight, confWidth, filledHeight);
            
            // Borde
            ctx.strokeStyle = aiColor;
            ctx.lineWidth = 1;
            ctx.strokeRect(confX, confY, confWidth, confHeight);
            
            // Label
            ctx.fillStyle = aiColor;
            ctx.font = 'bold 10px Arial';
            ctx.textAlign = 'center';
            ctx.fillText('AI', confX + confWidth / 2, confY - 5);
            ctx.font = '9px Arial';
            ctx.fillText(`${Math.round(confidence * 100)}%`, confX + confWidth / 2, confY + confHeight + 12);
            
            // 🚨 SPIN DETECTION ALERT
            if (aiData.spinDetected && aiData.spinType) {
                const alertX = canvas.width - 150;
                const alertY = 70;
                
                // Fondo pulsante
                const pulse = Math.sin(Date.now() / 200) * 0.3 + 0.7;
                ctx.fillStyle = `rgba(255, 100, 100, ${pulse * 0.8})`;
                ctx.fillRect(alertX, alertY, 130, 30);
                
                // Icono y texto
                const spinColor = aiData.spinType === 'topspin' ? '#ff4444' : '#44ff44';
                ctx.fillStyle = spinColor;
                ctx.font = 'bold 11px Arial';
                ctx.textAlign = 'left';
                
                const spinIcon = aiData.spinType === 'topspin' ? '⬇️' : '⬆️';
                const spinText = aiData.spinType === 'topspin' ? 'TOPSPIN' : 'BACKSPIN';
                ctx.fillText(`🎯 ${spinIcon} ${spinText} DETECTED!`, alertX + 5, alertY + 18);
                
                // Compensation indicator
                if (aiData.compensationApplied !== 0) {
                    ctx.font = '9px Arial';
                    ctx.fillStyle = '#ffffff';
                    const compText = aiData.compensationApplied > 0 ? '▼ Adjusted' : '▲ Adjusted';
                    ctx.fillText(compText, alertX + 85, alertY + 18);
                }
                
                // Borde
                ctx.strokeStyle = spinColor;
                ctx.lineWidth = 2;
                ctx.strokeRect(alertX, alertY, 130, 30);
            }
            
            // 🎮 AI MODE INDICATOR (top left corner)
            const modeX = 10;
            const modeY = 70;
            
            ctx.fillStyle = 'rgba(0, 0, 0, 0.7)';
            ctx.fillRect(modeX, modeY, 110, 35);
            
            ctx.fillStyle = aiColor;
            ctx.font = 'bold 13px Arial';
            ctx.textAlign = 'left';
            ctx.fillText(`${getText('gameAI')}: ${gameState.aiDifficulty.toUpperCase()}`, modeX + 8, modeY + 20);
            
            // Mostrar si puede hacer counter-spin (solo impossible)
            if (gameState.aiDifficulty === 'impossible') {
                ctx.font = '9px Arial';
                ctx.fillStyle = '#fbbf24';
                ctx.fillText('⚡ COUNTER-SPIN ACTIVE', modeX + 8, modeY + 30);
            }
        }

        // 🎮 SPEED INDICATOR (top center)
        if (gameState.ball?.speed) {
            const speed = gameState.ball.speed;
            const maxSpeed = difficultyLevel === 'easy' ? 8 : difficultyLevel === 'hard' ? 20 : 14;
            const progress = Math.min(speed / maxSpeed, 1);
            
            // Background bar
            const barWidth = 200;
            const barHeight = 20;
            const barX = (canvas.width - barWidth) / 2;
            const barY = 10;
            
            ctx.fillStyle = 'rgba(0, 0, 0, 0.5)';
            ctx.fillRect(barX, barY, barWidth, barHeight);
            
            // Progress bar with color gradient
            const hue = 120 - (progress * 120); // Green to Red
            ctx.fillStyle = `hsl(${hue}, 100%, 50%)`;
            ctx.fillRect(barX, barY, barWidth * progress, barHeight);
            
            // Border
            ctx.strokeStyle = progress > 0.8 ? '#ff0000' : '#ffffff';
            ctx.lineWidth = 2;
            ctx.strokeRect(barX, barY, barWidth, barHeight);
            
            // Text
            ctx.fillStyle = '#ffffff';
            ctx.font = '12px Arial';
            ctx.textAlign = 'center';
            ctx.fillText(`${getText('matchSpeed')}: ${speed.toFixed(1)}`, canvas.width / 2, barY + 35);
            
            // Warning if near max
            if (progress > 0.8 && Math.floor(Date.now() / 500) % 2 === 0) {
                ctx.fillStyle = 'rgba(255, 0, 0, 0.3)';
                ctx.fillRect(barX, barY, barWidth, barHeight);
            }
        }

        // 🎮 RALLY COUNTER (top left)
        if (gameState.rallyCount && gameState.rallyCount > 3) {
            ctx.fillStyle = 'rgba(0, 0, 0, 0.7)';
            ctx.fillRect(10, 10, 120, 40);
            ctx.fillStyle = '#ffff00';
            ctx.font = 'bold 16px Arial';
            ctx.textAlign = 'left';
            ctx.fillText(`${getText('matchRally')}: ${gameState.rallyCount}`, 20, 35);
        }

        // 🗺️ HEATMAP VISUALIZATION
        if (showStats && heatmapData.current.length > 50) {
            ctx.save();
            ctx.globalAlpha = 0.3;
            
            // Create gradient for each point
            heatmapData.current.forEach(point => {
                const gradient = ctx.createRadialGradient(point.x, point.y, 0, point.x, point.y, 20);
                const intensity = point.intensity;
                gradient.addColorStop(0, `rgba(255, ${Math.floor(255 * (1 - intensity))}, 0, 0.6)`);
                gradient.addColorStop(1, 'rgba(255, 255, 0, 0)');
                
                ctx.fillStyle = gradient;
                ctx.fillRect(point.x - 20, point.y - 20, 40, 40);
            });
            
            ctx.restore();
        }

        // 📊 STATISTICS OVERLAY
        if (showStats) {
            const statsX = 10;
            const statsY = 60;
            const statsWidth = 180;
            const statsHeight = 200;
            
            // Background
            ctx.fillStyle = 'rgba(0, 0, 0, 0.85)';
            ctx.fillRect(statsX, statsY, statsWidth, statsHeight);
            ctx.strokeStyle = '#00ff00';
            ctx.lineWidth = 2;
            ctx.strokeRect(statsX, statsY, statsWidth, statsHeight);
            
            // Title
            ctx.fillStyle = '#00ff00';
            ctx.font = 'bold 14px Arial';
            ctx.textAlign = 'left';
            ctx.fillText('📊 GAME STATISTICS', statsX + 10, statsY + 20);
            
            // Stats content
            ctx.font = '11px Arial';
            ctx.fillStyle = '#ffffff';
            let yOffset = statsY + 40;
            const lineHeight = 16;
            
            // Total hits
            ctx.fillText(`Total Hits: ${gameStats.totalHits}`, statsX + 10, yOffset);
            yOffset += lineHeight;
            
            // Player hits breakdown
            ctx.fillStyle = '#88ff88';
            ctx.fillText(`  P1: ${gameStats.player1Hits}`, statsX + 10, yOffset);
            yOffset += lineHeight;
            ctx.fillStyle = '#ff8888';
            ctx.fillText(`  P2: ${gameStats.player2Hits}`, statsX + 10, yOffset);
            yOffset += lineHeight + 4;
            
            // Speed stats
            ctx.fillStyle = '#ffffff';
            ctx.fillText(`Max Speed: ${gameStats.maxSpeed.toFixed(1)}`, statsX + 10, yOffset);
            yOffset += lineHeight;
            ctx.fillText(`Avg Speed: ${gameStats.avgSpeed.toFixed(1)}`, statsX + 10, yOffset);
            yOffset += lineHeight + 4;
            
            // Spin usage
            ctx.fillStyle = '#ff4444';
            ctx.fillText(`Topspin: ${gameStats.topspinCount}`, statsX + 10, yOffset);
            yOffset += lineHeight;
            ctx.fillStyle = '#44ff44';
            ctx.fillText(`Backspin: ${gameStats.backspinCount}`, statsX + 10, yOffset);
            yOffset += lineHeight + 4;
            
            // Rally record
            ctx.fillStyle = '#ffff00';
            ctx.fillText(`Longest Rally: ${gameStats.longestRally}`, statsX + 10, yOffset);
            yOffset += lineHeight;
            
            // Distance traveled
            ctx.fillStyle = '#ffffff';
            const distanceKm = (gameStats.totalDistance / 1000).toFixed(2);
            ctx.fillText(`Distance: ${distanceKm}km`, statsX + 10, yOffset);
            yOffset += lineHeight;
            
            // Game duration
            const durationSec = Math.floor(gameStats.gameDuration / 1000);
            const minutes = Math.floor(durationSec / 60);
            const seconds = durationSec % 60;
            ctx.fillText(`Time: ${minutes}:${seconds.toString().padStart(2, '0')}`, statsX + 10, yOffset);
        }

        const isPlayer1 = gameState.players.find(player => player.userId === user?.id)?.isPlayer1;
        if (isPlayer1) {
            ctx.strokeStyle = '#0f0';
            ctx.lineWidth = 3;
            ctx.strokeRect(gameState.player1.x - 1, gameState.player1.y - 1, gameState.player1.width + 2, gameState.player1.height + 2);
        } else {
            ctx.strokeStyle = '#0f0';
            ctx.lineWidth = 3;
            ctx.strokeRect(gameState.player2.x - 1, gameState.player2.y - 1, gameState.player2.width + 2, gameState.player2.height + 2);
        }
        const player1Name = gameState.players.find(player => player.isPlayer1)?.username;
        const player2Name = gameState.players.find(player => !player.isPlayer1)?.username;
        
        const newPlayer1Score = gameState.player1?.score || 0;
        const newPlayer2Score = gameState.player2?.score || 0;

        if (newPlayer1Score > playersScores.player1Score) {
            playScore(true);
        } else if (newPlayer2Score > playersScores.player2Score) {
            playScore(false);
        }
        
        setPlayersScores({ 
            player1Score: newPlayer1Score, 
            player1Name: player1Name || '', 
            player2Score: newPlayer2Score, 
            player2Name: player2Name || ''
        });
        
        if (difficultyLevel !== gameState.aiDifficulty && gameState.aiDifficulty)
            setDifficultyLevel(gameState.aiDifficulty);
        if (waitingForOpponent && setWaitingForOpponent) setWaitingForOpponent(false);
        
        // 🎮 Sincronizar posición local con servidor (sin sobrescribir durante input activo)
        if (gameState && user?.id) {
            const isPlayer1 = gameState.players.find(p => p.userId === user.id)?.isPlayer1;
            const serverY = isPlayer1 ? gameState.player1.y : gameState.player2.y;
            
            // Solo actualizar si no hay teclas presionadas (evita jitter)
            if (keysPressed.current.size === 0) {
                localPaddleY.current = serverY;
            }
        }
    }, [gameState, roomIamIn, difficultyLevel, waitingForOpponent, setWaitingForOpponent, user?.id]);


	useEffect(() => {
		if (!socket) return;

		// Escuchar reconexion exitosa
		const handleReconnection = (data: {
			roomId: string;
			isPlayer1: boolean;
			aiEnabled: boolean;
			gameState: any;
		}) => {
			if (setRoomIamIn) {
				setRoomIamIn(data.roomId);
			}
			// Sincronizar posicion de paddle si es necesario
			if (data.gameState) {
				if (data.isPlayer1) {
					localPaddleY.current = data.gameState.player1.y;
				} else {
					localPaddleY.current = data.gameState.player2.y;
				}
			}
		};

		socket.on('reconnectedToRoom', handleReconnection);

		return () => {
			socket.off('reconnectedToRoom', handleReconnection);
		};
	}, [socket, setRoomIamIn]);

    // 🎮 KEYBOARD CONTROLS - Client-Side Prediction
    useEffect(() => {
        if (!socket || !roomIamIn || waitingForOpponent || !gameState) {
            return;
        }

        const SPEED = 8; // 🚀 Velocidad suave y responsive

        const handleKeyDown = (e: KeyboardEvent) => {
            if (!['ArrowUp', 'ArrowDown'].includes(e.key)) return;
            e.preventDefault();
            keysPressed.current.add(e.key);
        };

        const handleKeyUp = (e: KeyboardEvent) => {
            if (['ArrowUp', 'ArrowDown'].includes(e.key)) {
                e.preventDefault();
                keysPressed.current.delete(e.key);
            }
        };

        // Loop optimizado - actualiza posición local y envía al servidor
        const sendPaddleMovement = () => {
            let direction = 0;

            if (keysPressed.current.has('ArrowUp')) direction = -1;
            if (keysPressed.current.has('ArrowDown')) direction = 1;

            if (direction !== 0) {
                // Actualizar posición local inmediatamente (client-side prediction)
                localPaddleY.current = Math.max(0, Math.min(300, localPaddleY.current + direction * SPEED));
                
                // Enviar al servidor
                socket.emit('paddleMove', { y: localPaddleY.current, room: roomIamIn });
            }

            animationFrameId.current = requestAnimationFrame(sendPaddleMovement);
        };

        window.addEventListener('keydown', handleKeyDown);
        window.addEventListener('keyup', handleKeyUp);
        animationFrameId.current = requestAnimationFrame(sendPaddleMovement);

        return () => {
            window.removeEventListener('keydown', handleKeyDown);
            window.removeEventListener('keyup', handleKeyUp);
            if (animationFrameId.current) {
                cancelAnimationFrame(animationFrameId.current);
            }
            keysPressed.current.clear();
        };
    }, [socket, roomIamIn, waitingForOpponent]);

    const createGame = (): void => {
        if (gameName === '') return;
        if (!socket) return;
        const mode = oponent === 'robocot' ? 'AI' : 'Human';
        
        // 🎯 Generar nombre único para la sala para evitar conflictos al recrear

        //Is the mode is AI setWaitingForOpponent false so the user can start playing!!!
        if (mode === 'AI') {
            if (setWaitingForOpponent) setWaitingForOpponent(false);
        } else if (mode === 'Human') {
            if (setWaitingForOpponent) setWaitingForOpponent(true);
        }

        socket.emit("createRoom", gameName, { mode });
        
        // 🎯 Si es modo IA, establecer dificultad inmediatamente después de crear sala
        if (mode === 'AI') {
            setTimeout(() => {
                socket.emit('setDifficulty', { level: difficultyLevel }, gameName);
            }, 100);
        }
        
        setGameName('');
        joinRoom(null, gameName);
    };

    // Emit roomImIn when room changes
    useEffect(() => {
        if (!socket || !roomIamIn) return;
        socket.emit("roomImIn", roomIamIn);
    }, [roomIamIn, socket]);

    // Listen for roomJoinedInfo once
    useEffect(() => {
        if (!socket) return;
        
        const handleRoomJoinedInfo = (data: any): void => {
            if (setIsAiEnabled) setIsAiEnabled(data.aiEnabled);
        };
        
        socket.on("roomJoinedInfo", handleRoomJoinedInfo);
        
        return () => {
            socket.off("roomJoinedInfo", handleRoomJoinedInfo);
        };
    }, [socket, setIsAiEnabled]);

    useEffect(() => {
        if (!socket) {
            return;
        }
        
        
        const handleGameUpdate = (data: any, roomTorender: any): void => {
            // 📊 STATISTICS: Detect collision with paddles by velocity direction change
            if (prevGameState.current && data.ball) {
                const prev = prevGameState.current;
                const curr = data;
                
                // Detect paddle collision (velocity X direction changes)
                if (prev.ball.vx && curr.ball.vx && Math.sign(prev.ball.vx) !== Math.sign(curr.ball.vx)) {
                    const hitByPlayer = curr.ball.vx > 0 ? 'player1' : 'player2';
                    
                    setGameStats(prevStats => {
                        const newStats = { ...prevStats };
                        newStats.totalHits++;
                        if (hitByPlayer === 'player1') newStats.player1Hits++;
                        else newStats.player2Hits++;
                        
                        // Rally tracking
                        if (lastHitBy.current && lastHitBy.current !== hitByPlayer) {
                            const currentRally = Math.floor(newStats.totalHits / 2);
                            newStats.longestRally = Math.max(newStats.longestRally, currentRally);
                        }
                        
                        return newStats;
                    });
                    
                    lastHitBy.current = hitByPlayer;
                    
                    // 🔊 Play paddle hit sound (solo si está habilitado)
                    if (soundEnabled) {
                        const speed = curr.ball.speed || 5;
                        const hasSpin = curr.ball.spin && curr.ball.spin.intensity > 0.5;
                        playPaddleHit(speed, hasSpin);
                    }
                }
            }
            
            // 🔊 Update ambient sound (solo si está habilitado)
            if (soundEnabled && data.ball) {
                updateAmbientSound(data.ball.speed || 5);
            }
            
            prevGameState.current = data;
            setGameState(data);
        };
        
        socket.on("gameUpdate", handleGameUpdate);
        
        return () => {
            socket.off("gameUpdate", handleGameUpdate);
            stopAmbientSound();
        };
    }, [socket, soundEnabled]);

    // 🏁 Listen for game ended event
    useEffect(() => {
		if (!socket) return;
		
		const handleGameEnded = (data: any): void => {
			
			// ✅ VERIFICAR QUE ES NUESTRA SALA
			if (data.roomId !== roomIamIn) {
				return;
			}
			
			// Stop sounds
			stopAmbientSound();
			
			setTimeout(() => {
				// 1. Desconectar del socket
				if (socket && roomIamIn) {
					socket.emit('leaveRoom', roomIamIn);
				}
				
				// 2. Limpiar estados locales
				setGameState(null);
				localPaddleY.current = 150;
				keysPressed.current.clear();
				
				// 3. Resetear scores y stats
				setPlayersScores({
					player1Score: 0,
					player1Name: '',
					player2Score: 0,
					player2Name: ''
				});
				setGameStats({
					totalHits: 0,
					player1Hits: 0,
					player2Hits: 0,
					topspinCount: 0,
					backspinCount: 0,
					maxSpeed: 0,
					avgSpeed: 0,
					speedSamples: [],
					longestRally: 0,
					totalDistance: 0,
					gameDuration: 0,
					startTime: Date.now()
				});
				
				// 4. Resetear estados de UI
				if (setRoomIamIn) setRoomIamIn('');
				if (setIsAiEnabled) setIsAiEnabled(false);
				if (setWaitingForOpponent) setWaitingForOpponent(false);
				if (setCreateNewGame) setCreateNewGame(false);
				
			}, 2000); // ✅ 2 segundos para ver el marcador final
		};
		
		socket.on("gameEnded", handleGameEnded);
		
		return () => {
			socket.off("gameEnded", handleGameEnded);
		};
	}, [socket, roomIamIn, setRoomIamIn, setIsAiEnabled, setWaitingForOpponent, setCreateNewGame]);

    // Cleanup del AudioContext al desmontar
    useEffect(() => {
        return () => {
            if (ambientOscillator.current) {
                ambientOscillator.current.stop();
                ambientOscillator.current = null;
            }
            if (audioContext.current) {
                audioContext.current.close();
                audioContext.current = null;
            }
        };
    }, []);

    // Mouse controls removidos - solo teclado
    // const handleMouseMove = (e: React.MouseEvent<HTMLCanvasElement>): void => {
    //     if (!socket) return;
    //     const canvas = canvasRef.current;
    //     if (!canvas) return;
    //     const rect = canvas.getBoundingClientRect();
    //     const mouseY = e.clientY - rect.top;
    //     socket.emit("paddleMove", { y: mouseY, room: roomIamIn });
    // };

    const setDifficulty = (level: string): void => {
        if (!socket) return;
        socket.emit('setDifficulty', { level }, roomIamIn);
    };

    const joinRoom = (room: GameRoom | null, roomId: string): void => {
        //check if player is already in this room
        setCreateNewGame(false);
        if (roomIamIn === roomId) { return; }

        //check if player is allow in this room
        if (room && user) {
            const isPlayerInRoom = room.players.some(player => player.userId === user.id);
            if (!isPlayerInRoom && (room.players.length === 2 || room.aiEnabled)) return;
        }
        if (!socket) return;
        socket.emit("joinRoomGame", roomId);
        //setRoomIamIn to triger socket.emit("roomImIn", roomIamIn) so the server knows which room should update
        if (setRoomIamIn) setRoomIamIn(roomId);

        if (room && setWaitingForOpponent) {
            if ((room.players.length > 1 || room.aiEnabled)) {
                //alert(`Setting waitForOpponent to false in room: ${roomId}`)
                setWaitingForOpponent(false);
            } else {
                //alert(`Setting waitForOpponent to true in room: ${roomId}`)
                setWaitingForOpponent(true);
            }
        }
        if (setWaitingForOpponent) setWaitingForOpponent(true);
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
            'gamePongGame': 'Pong Game',
			'localGame': 'Local game',
			'gameOpponent': 'Opponent',
			'gameStartGame': 'Start Game',
			'gameRoomName': 'Room Name',
			'gameEnterRoomName': 'Enter room name...',
			'gameSelectDifficulty': 'Select Difficulty',
			'gameEasy': 'Easy',
			'gameMedium': 'Medium',
			'gameHard': 'Hard',
			'gameWaitingForOpponent': 'Waiting for opponent...',
			'gameGetReadyToPlay': '🎮 Get ready to play!',
			'gameCreateNewRoom': 'Create New Room',
			'gameWaiting': 'waiting...',
			'gameAI': '🤖 AI',
			'gameHuman': '👤 Human',
			'gameAIDifficultyLevel': '🎚️ AI Difficulty Level',
			'gameEasyEmoji': '🌱 Easy',
			'gameMediumEmoji': '⚡ Medium',
			'gameHardEmoji': '🔥 Hard',
			'gameImpossible': '💀 IMPOSSIBLE',
			'gameSelectDifficultyBeforeStarting': 'Select difficulty before starting the game',
			'gameActive': 'ACTIVE',
			'gameBack': '← Back',
			'gameAIDifficulty': 'AI Difficulty: ',
			'gameAIOverlayOn': '🤖 AI Overlay: ON',
			'gameAIOverlayOff': '🤖 AI Overlay: OFF',
			'gameSoundOn': '🔊 Sound: ON',
			'gameSoundOff': '🔇 Sound: OFF',
			'gameStatsOn': '📊 Stats: ON',
			'gameStatsOff': '📊 Stats: OFF',
			'gamePlayer1': 'Player 1:',
			'gamePlayer2': 'Player 2:',
			'gameControls': 'Controls:',
			'gameMovePaddle': 'Move paddle',
			'gameProTip': '🌀 Pro Tip:',
			'gameMovePaddleForSpin': 'Move paddle while hitting to apply spin!',
			'gameTopspin': '⬇️ Topspin',
			'gameMoveDown': '(move down) |',
			'gameBackspin': '⬆️ Backspin',
			'gameMoveUp': '(move up)',
			'gameVisualEffects': '🎆 Visual Effects:',
			'gameCollisionParticles': '💥 Collision particles',
			'gameOnPaddleHits': 'on paddle hits',
			'gameSparks': '✨ Sparks',
			'gameOnWallBounces': 'on wall bounces',
			'gameWarpEffect': '🚀 Warp effect',
			'gameAtExtremeSpeeds': 'at extreme speeds (>20)',
			'gameScreenShake': '📳 Screen shake',
			'gameAtHighSpeeds': 'at high speeds (>18)',
			'matchRally': 'RALLY',
        };
        
        return fallbacks[key] || key;
    };
    return (
        <div>
			{localGame ? (<LocalGame setLocalGame = {setLocalGame}/>) : (<>
            <h1 className="text-4xl font-bold text-white mb-8 text-center">{getText('gamePongGame')}</h1>
            
            {/* 🎯 PANEL DE CREACIÓN/CONFIGURACIÓN */}
			<div className="mb-6 flex flex-col items-center justify-center">
				{roomsPlayerIsIn.length === 0 ? (
					// ✅ NUEVO: Mostrar formulario cuando NO hay salas
					<div className="flex flex-col gap-6 w-full max-w-2xl">
						{/* Selector de oponente */}
						<div className="relative px-8 py-4 bg-gray-700 hover:bg-gray-600 text-white text-2xl font-semibold rounded-lg shadow-lg flex justify-center">
							<button onClick={() => setChooseOponent(!chooseOponent)} className="w-full flex items-center justify-center gap-3">
								<span>{getText('gameOpponent')}:</span>
								<span className="px-4 py-1 bg-gradient-to-r from-amber-500 to-orange-500 rounded-full text-lg font-bold">
									{oponent === 'robocot' ? getText('gameAI') : getText('gameHuman')}
								</span>
							</button>
							{chooseOponent &&
								<div className="absolute w-full flex flex-col -bottom-36 bg-gray-800 rounded-lg gap-1 z-50">
									<button onClick={() => { setChooseOponent(false); setOponent('robocot') }} className={`bg-gray-700 py-3 rounded-lg hover:bg-gray-600 border-4 ${oponent === 'robocot' ? 'border-pong-green/80' : 'border-gray-600'}`}>{getText('gameAI')}</button>
									<button onClick={() => { setChooseOponent(false); setOponent('human') }} className={`bg-gray-700 py-3 rounded-lg hover:bg-gray-600 border-4 ${oponent === 'human' ? 'border-pong-green/80' : 'border-gray-600'}`}>{getText('gameHuman')}</button>
								</div>
							}
						</div>
						
						{/* Selector de dificultad (solo AI) */}
						{oponent === 'robocot' &&
							<div className="flex flex-col items-center gap-3 p-6 bg-gray-800 rounded-lg border-2 border-amber-500/30">
								<h3 className="text-white text-xl font-bold mb-2">{getText('gameAIDifficultyLevel')}</h3>
								<div className="flex flex-wrap justify-center gap-3">
									<button 
										onClick={() => setDifficultyLevel('easy')} 
										className={`px-6 py-3 text-base font-bold rounded-lg transition-all ${difficultyLevel === 'easy' ? 'bg-green-500 text-white scale-110 shadow-lg shadow-green-500/50' : 'bg-gray-700 text-gray-300 hover:bg-gray-600'}`}
									>
										{getText('gameEasyEmoji')}
									</button>
									<button 
										onClick={() => setDifficultyLevel('medium')} 
										className={`px-6 py-3 text-base font-bold rounded-lg transition-all ${difficultyLevel === 'medium' ? 'bg-orange-500 text-white scale-110 shadow-lg shadow-orange-500/50' : 'bg-gray-700 text-gray-300 hover:bg-gray-600'}`}
									>
										{getText('gameMediumEmoji')}
									</button>
									<button 
										onClick={() => setDifficultyLevel('hard')} 
										className={`px-6 py-3 text-base font-bold rounded-lg transition-all ${difficultyLevel === 'hard' ? 'bg-red-500 text-white scale-110 shadow-lg shadow-red-500/50' : 'bg-gray-700 text-gray-300 hover:bg-gray-600'}`}
									>
										{getText('gameHardEmoji')}
									</button>
									<button 
										onClick={() => setDifficultyLevel('impossible')} 
										className={`px-6 py-3 text-base font-bold rounded-lg transition-all ${difficultyLevel === 'impossible' ? 'bg-purple-600 text-white scale-110 shadow-lg shadow-purple-500/50 animate-pulse' : 'bg-gray-700 text-gray-300 hover:bg-gray-600'}`}
									>
										{getText('gameImpossible')}
									</button>
								</div>
								<p className="text-gray-400 text-sm mt-2">{getText('gameSelectDifficultyBeforeStarting')}</p>
							</div>
						}
						
						{/* Input de nombre de sala */}
						<div className="flex flex-col gap-2 bg-gray-800 rounded-lg p-4">
							<label className="text-white/80 text-sm font-semibold">{getText('gameRoomName')}</label>
							<input 
								className="px-4 py-3 rounded-lg border-2 border-gray-600 bg-white/90 text-black placeholder-gray-400 focus:outline-none focus:ring-2 focus:ring-amber-500 focus:border-transparent text-lg" 
								value={gameName} 
								onChange={(e) => setGameName(e.target.value)}
								placeholder={getText('gameEnterRoomName')}
							/>
						</div>
						
						{/* Botón de start */}
						<button 
							onClick={() => createGame()}
							className="px-8 py-3 bg-gradient-to-r from-green-500 to-emerald-600 hover:from-green-400 hover:to-emerald-500 text-white text-xl font-bold rounded-lg shadow-lg shadow-green-500/50 transition-all duration-200 hover:scale-105 active:scale-95"
						>
							🚀 {getText('gameStartGame')}
						</button>

					</div>
				) : (
					// ✅ NUEVO: Mostrar lista de salas cuando YA hay salas activas
					<div className="flex flex-wrap gap-3 justify-center">
						{/* Lista de salas en las que participa */}
						{roomsPlayerIsIn.map((room, index) => (
							<button 
								key={index} 
								onClick={() => joinRoom(room, room.roomId)}
								className={`group relative w-64 h-28 bg-gradient-to-br from-slate-700 via-slate-800 to-slate-900 hover:from-slate-600 hover:via-slate-700 hover:to-slate-800 border border-emerald-500/30 hover:border-emerald-400/50 text-white rounded-lg shadow-lg hover:shadow-emerald-500/20 transition-all duration-200 overflow-hidden ${roomIamIn === room.roomId ? 'ring-4 ring-green-500' : ''}`}
							>
								{/* Línea de acento */}
								<div className="absolute top-0 left-0 right-0 h-1 bg-gradient-to-r from-transparent via-emerald-400/50 to-transparent"></div>
								
								{/* Indicador de estado */}
								<div className="absolute top-3 right-3">
									<span className="flex h-2.5 w-2.5">
										<span className="animate-ping absolute h-full w-full rounded-full bg-emerald-400 opacity-75"></span>
										<span className="relative rounded-full h-2.5 w-2.5 bg-emerald-500"></span>
									</span>
								</div>
								
								{/* Contenido */}
								<div className="relative h-full flex flex-col justify-center items-start px-4 pt-2">
									<h1 className="text-xl font-bold mb-1 truncate w-full text-white">{room.roomId}</h1>
									<div className="text-sm text-gray-300 truncate w-full">
										{room.players.find(p => p.isPlayer1)?.username} 
										<span className="text-emerald-400 mx-1">vs</span> 
										{room.aiEnabled 
											? '🤖' 
											: room.players.find(p => !p.isPlayer1)?.username 
												? room.players.find(p => !p.isPlayer1)?.username 
												: <span className="animate-pulse">{getText('gameWaiting')}</span>
										}
									</div>
								</div>
								
								{/* Badge de sala actual */}
								{roomIamIn === room.roomId && (
									<div className="absolute bottom-2 left-2">
										<span className="px-2 py-1 bg-green-500 text-white text-xs font-bold rounded">
											{getText('gameActive')}
										</span>
									</div>
								)}
							</button>
						))}
						
						{/* Botón para crear nueva sala */}
						<button 
							onClick={() => setCreateNewGame(true)} 
							className="group relative w-64 h-28 bg-gradient-to-br from-slate-700 via-slate-800 to-slate-900 hover:from-slate-600 hover:via-slate-700 hover:to-slate-800 border-2 border-dashed border-amber-500/40 hover:border-amber-400/60 text-white rounded-lg shadow-lg hover:shadow-amber-500/20 transition-all duration-200 overflow-hidden"
						>
							{/* Línea de acento */}
							<div className="absolute top-0 left-0 right-0 h-1 bg-gradient-to-r from-transparent via-amber-400/50 to-transparent"></div>
							
							{/* Icono + */}
							<div className="absolute top-3 right-3">
								<span className="text-xl text-amber-400/70 group-hover:text-amber-400">+</span>
							</div>
							
							{/* Contenido */}
							<div className="relative h-full flex flex-col justify-center items-center px-4 pt-2">
								<div className="text-3xl mb-2 opacity-70 group-hover:opacity-90 transition-opacity">🎮</div>
								<h1 className="text-lg font-semibold text-center text-gray-300 group-hover:text-white transition-colors">
									{getText('gameCreateNewRoom')}
								</h1>
							</div>
						</button>
					</div>
				)}
			</div>
			{(createNewGame && roomsPlayerIsIn.length > 0) && (
				<div className="mb-6 flex flex-col items-center justify-center">
					<div className="flex flex-col gap-6 w-full max-w-2xl">
						{/* Selector de oponente */}
						<div className="relative px-8 py-4 bg-gray-700 hover:bg-gray-600 text-white text-2xl font-semibold rounded-lg shadow-lg flex justify-center">
							<button onClick={() => setChooseOponent(!chooseOponent)} className="w-full flex items-center justify-center gap-3">
								<span>{getText('gameOpponent')}:</span>
								<span className="px-4 py-1 bg-gradient-to-r from-amber-500 to-orange-500 rounded-full text-lg font-bold">
									{oponent === 'robocot' ? getText('gameAI') : getText('gameHuman')}
								</span>
							</button>
							{chooseOponent &&
								<div className="absolute w-full flex flex-col -bottom-36 bg-gray-800 rounded-lg gap-1 z-50">
									<button onClick={() => { setChooseOponent(false); setOponent('robocot') }} className={`bg-gray-700 py-3 rounded-lg hover:bg-gray-600 border-4 ${oponent === 'robocot' ? 'border-pong-green/80' : 'border-gray-600'}`}>{getText('gameAI')}</button>
									<button onClick={() => { setChooseOponent(false); setOponent('human') }} className={`bg-gray-700 py-3 rounded-lg hover:bg-gray-600 border-4 ${oponent === 'human' ? 'border-pong-green/80' : 'border-gray-600'}`}>{getText('gameHuman')}</button>
								</div>
							}
						</div>
						
						{/* Selector de dificultad (solo AI) */}
						{oponent === 'robocot' &&
							<div className="flex flex-col items-center gap-3 p-6 bg-gray-800 rounded-lg border-2 border-amber-500/30">
								<h3 className="text-white text-xl font-bold mb-2">{getText('gameAIDifficultyLevel')}</h3>
								<div className="flex flex-wrap justify-center gap-3">
									<button onClick={() => setDifficultyLevel('easy')} className={`px-6 py-3 text-base font-bold rounded-lg transition-all ${difficultyLevel === 'easy' ? 'bg-green-500 text-white scale-110 shadow-lg shadow-green-500/50' : 'bg-gray-700 text-gray-300 hover:bg-gray-600'}`}>{getText('gameEasyEmoji')}</button>
									<button onClick={() => setDifficultyLevel('medium')} className={`px-6 py-3 text-base font-bold rounded-lg transition-all ${difficultyLevel === 'medium' ? 'bg-orange-500 text-white scale-110 shadow-lg shadow-orange-500/50' : 'bg-gray-700 text-gray-300 hover:bg-gray-600'}`}>{getText('gameMediumEmoji')}</button>
									<button onClick={() => setDifficultyLevel('hard')} className={`px-6 py-3 text-base font-bold rounded-lg transition-all ${difficultyLevel === 'hard' ? 'bg-red-500 text-white scale-110 shadow-lg shadow-red-500/50' : 'bg-gray-700 text-gray-300 hover:bg-gray-600'}`}>{getText('gameHardEmoji')}</button>
									<button onClick={() => setDifficultyLevel('impossible')} className={`px-6 py-3 text-base font-bold rounded-lg transition-all ${difficultyLevel === 'impossible' ? 'bg-purple-600 text-white scale-110 shadow-lg shadow-purple-500/50 animate-pulse' : 'bg-gray-700 text-gray-300 hover:bg-gray-600'}`}>{getText('gameImpossible')}</button>
								</div>
								<p className="text-gray-400 text-sm mt-2">{getText('gameSelectDifficultyBeforeStarting')}</p>
							</div>
						}
						
						{/* Input de nombre de sala */}
						<div className="flex flex-col gap-2 bg-gray-800 rounded-lg p-4">
							<label className="text-white/80 text-sm font-semibold">{getText('gameRoomName')}</label>
							<input 
								className="px-4 py-3 rounded-lg border-2 border-gray-600 bg-white/90 text-black placeholder-gray-400 focus:outline-none focus:ring-2 focus:ring-amber-500 focus:border-transparent text-lg" 
								value={gameName} 
								onChange={(e) => setGameName(e.target.value)}
								placeholder={getText('gameEnterRoomName')}
							/>
						</div>
						
						{/* Botones */}
						<div className="flex gap-3 justify-center">
							<button 
								onClick={() => setCreateNewGame(false)}
								className="px-6 py-3 bg-gray-600 hover:bg-gray-500 text-white text-lg font-semibold rounded-lg shadow-lg transition-all duration-200 hover:scale-105 active:scale-95"
							>
								{getText('gameBack')}
							</button>
							<button 
								onClick={() => createGame()}
								className="px-8 py-3 bg-gradient-to-r from-green-500 to-emerald-600 hover:from-green-400 hover:to-emerald-500 text-white text-xl font-bold rounded-lg shadow-lg shadow-green-500/50 transition-all duration-200 hover:scale-105 active:scale-95"
							>
								🚀 {getText('gameStartGame')}
							</button>
						</div>
					</div>
				</div>
			)}
            {/* 🎮 AREA DE JUEGO */}
            {roomIamIn && !createNewGame && (
                <div>
                    {/* Mensaje de espera */}
                    {waitingForOpponent && (
                        <div className="flex flex-col justify-center items-center py-12 gap-4">
                            <div className="text-center">
                                <h2 className="text-2xl font-bold text-white">{getText('gameWaitingForOpponent')}</h2>
                            </div>
                            <div className="text-center">
                                <p className="text-cyan-300 text-sm animate-pulse">{getText('gameGetReadyToPlay')}</p>
                            </div>
                        </div>
                    )}
                    
                    {/* Marcador y controles (solo cuando el juego ya empezó) */}
                    {!waitingForOpponent && (
                        <div>
                            {/* Marcador */}
                            <div className="mb-4 flex justify-center items-center">
                                <span className="bg-gradient-to-br from-blue-600 to-blue-950 w-6/12 h-16 gap-2 flex justify-evenly items-center rounded-2xl text-xl font-semibold text-white overflow-hidden">
                                    <h1 className="text-2xl font-bold text-white/90">{playersScores.player1Name}</h1>
                                    <div className="gap">
                                        <span className="mr-6 text-2xl font-bold">{playersScores.player1Score}</span> 
                                        : 
                                        <span className="ml-6 text-2xl font-bold">{playersScores.player2Score}</span>
                                    </div>
                                    <h1>{isAiEnabled ? '🤖' : playersScores.player2Name}</h1>
                                </span>
                            </div>
                            
                            {/* Controles durante el juego */}
                            {gameState && (
                                <div className="mb-6">
                                    <div className="flex flex-col items-center gap-4 mb-6">
                                        {/* Nivel de dificultad actual */}
                                        {isAiEnabled && (
                                            <div className="px-6 py-2 bg-gradient-to-r from-purple-600 to-indigo-600 text-white rounded-lg shadow-lg">
                                                <span className="font-bold">{getText('gameAIDifficulty')}{difficultyLevel.toUpperCase()}</span>
                                            </div>
                                        )}
                                        
                                        {/* Botones de control */}
                                        <div className="flex flex-wrap gap-3 justify-center">
                                            <button 
                                                onClick={() => setShowAIOverlay(!showAIOverlay)}
                                                className={`px-6 py-2 text-sm font-semibold rounded-lg shadow-md transition-all duration-200 active:scale-95 ${
                                                    showAIOverlay 
                                                        ? 'bg-gradient-to-r from-cyan-500 to-blue-500 text-white hover:from-cyan-400 hover:to-blue-400' 
                                                        : 'bg-gray-700 text-gray-300 hover:bg-gray-600'
                                                }`}
                                            >
                                                {showAIOverlay ? getText('gameAIOverlayOn') : getText('gameAIOverlayOff')}
                                            </button>
                                            
                                            <button 
                                                onClick={() => {
                                                    const newState = !soundEnabled;
                                                    setSoundEnabled(newState);
                                                    if (newState) {
                                                        startAmbientSound();
                                                    } else {
                                                        stopAmbientSound();
                                                    }
                                                }}
                                                className={`px-6 py-2 text-sm font-semibold rounded-lg shadow-md transition-all duration-200 active:scale-95 ${
                                                    soundEnabled 
                                                        ? 'bg-gradient-to-r from-green-500 to-emerald-500 text-white hover:from-green-400 hover:to-emerald-400' 
                                                        : 'bg-gray-700 text-gray-300 hover:bg-gray-600'
                                                }`}
                                            >
                                                {soundEnabled ? getText('gameSoundOn') : getText('gameSoundOff')}
                                            </button>
                                            
                                            <button 
                                                onClick={() => setShowStats(!showStats)}
                                                className={`px-6 py-2 text-sm font-semibold rounded-lg shadow-md transition-all duration-200 active:scale-95 ${
                                                    showStats 
                                                        ? 'bg-gradient-to-r from-yellow-500 to-orange-500 text-white hover:from-yellow-400 hover:to-orange-400' 
                                                        : 'bg-gray-700 text-gray-300 hover:bg-gray-600'
                                                }`}
                                            >
                                                {showStats ? getText('gameStatsOn') : getText('gameStatsOff')}
                                            </button>
                                        </div>
                                    </div>
                                </div>
                            )}
                        </div>
                    )}
                    
                    {/* Canvas de juego */}
                    <div className="overflow-x-auto">
                        <div className="flex flex-col items-center gap-4">
                            <div className="flex justify-center min-w-max">
                                <canvas 
                                    className="bg-black border-4 border-gray-700 rounded-lg shadow-2xl" 
                                    ref={canvasRef} 
                                    width={800} 
                                    height={400} 
                                    id="gameCanvas"
                                />
                            </div>
                            
                            {/* Controles info */}
                            {showControls && (
                                <div className="bg-gray-800/90 px-6 py-3 rounded-lg border-2 border-gray-600 relative">
                                    <button 
                                        onClick={() => setShowControls(false)}
                                        className="absolute -top-2 -right-2 bg-red-500 hover:bg-red-600 text-white rounded-full w-6 h-6 flex items-center justify-center text-xs font-bold"
                                    >
                                        ✕
                                    </button>
                                    <div className="flex flex-col gap-2">
                                        <div className="flex gap-8 text-white text-sm">
                                            {!isAiEnabled ? (
                                                <>
                                                    <div className="flex items-center gap-2">
                                                        <span className="font-bold text-blue-400">{getText('gamePlayer1')}</span>
                                                        <kbd className="px-2 py-1 bg-gray-700 rounded border border-gray-500">W</kbd>
                                                        <kbd className="px-2 py-1 bg-gray-700 rounded border border-gray-500">S</kbd>
                                                    </div>
                                                    <div className="flex items-center gap-2">
                                                        <span className="font-bold text-red-400">{getText('gamePlayer2')}</span>
                                                        <kbd className="px-2 py-1 bg-gray-700 rounded border border-gray-500">↑</kbd>
                                                        <kbd className="px-2 py-1 bg-gray-700 rounded border border-gray-500">↓</kbd>
                                                    </div>
                                                </>
                                            ) : (
                                                <div className="flex items-center gap-2">
                                                    <span className="font-bold text-green-400">{getText('gameControls')}</span>
                                                    <kbd className="px-2 py-1 bg-gray-700 rounded border border-gray-500">↑</kbd>
                                                    <kbd className="px-2 py-1 bg-gray-700 rounded border border-gray-500">↓</kbd>
                                                    <span className="text-gray-400 ml-2">{getText('gameMovePaddle')}</span>
                                                </div>
                                            )}
                                        </div>
                                        <div className="text-xs text-gray-400 border-t border-gray-600 pt-2">
                                            <span className="font-bold text-yellow-400">{getText('gameProTip')}</span> {getText('gameMovePaddleForSpin')}
                                            <div className="mt-1">
                                                <span className="text-red-400">{getText('gameTopspin')}</span> {getText('gameMoveDown')} <span className="text-green-400">{getText('gameBackspin')}</span> {getText('gameMoveUp')}
                                            </div>
                                            <div className="mt-2 pt-2 border-t border-gray-700">
                                                <span className="font-bold text-cyan-400">{getText('gameVisualEffects')}</span>
                                                <div className="mt-1 space-y-0.5">
                                                    <div>💥 <span className="text-yellow-300">{getText('gameCollisionParticles')}</span> {getText('gameOnPaddleHits')}</div>
                                                    <div>✨ <span className="text-orange-300">{getText('gameSparks')}</span> {getText('gameOnWallBounces')}</div>
                                                    <div>🚀 <span className="text-cyan-300">{getText('gameWarpEffect')}</span> {getText('gameAtExtremeSpeeds')}</div>
                                                    <div>📳 <span className="text-purple-300">{getText('gameScreenShake')}</span> {getText('gameAtHighSpeeds')}</div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            )}
                        </div>
                    </div>
                </div>
            )}
			<div className="flex justify-center mt-6">
				<button 
					className="p-3 bg-orange-400 hover:bg-orange-500 text-white rounded-xl font-semibold"
					onClick={() => setLocalGame(prev => !prev)}
				>
					{getText('localGame')}
				</button>
			</div>
			</>)}
        </div>
    )
}

export default Game