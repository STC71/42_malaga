import fastify from 'fastify';
import { Server } from 'socket.io';
import fastifyStatic from '@fastify/static';
import formBody from '@fastify/formbody';
import cors from '@fastify/cors';
import jwt from '@fastify/jwt';
import cookie from '@fastify/cookie';
import path from 'path';
import { fileURLToPath } from 'url';
import multipart from '@fastify/multipart'
import { readFileSync } from 'fs';
import { getBlockchainService } from './blockchain/blockchain-service.js';
//Oauth2.0
import { auth42Callback,authGoogleCallback } from './auth.js';

import oauthPlugin from '@fastify/oauth2';
import dotenv from 'dotenv'

import {
//  authGoogleCallback,
  register, 
  login, 
  logout, 
  me, 
  authenticate, 
  updateProfile, 
  getUserProfile, 
  sendFriendRequest, 
  respondToFriendRequest,

  challenge,
  respondChallenge,

  getFriendRequests, 
  getFriends, 
  getMatchHistory, 
  changePassword,
  getCsrfToken,
  logMatchToDB
} from './auth.js';
import { initializeDatabase, Match, User, Friendship } from './db.js';
import { Op } from 'sequelize';
import { SocketAddress } from 'net';

import {
	createConversation,
	getConversations,
	getConversationById,
	deleteConversation,
	sendMessage,
	getMessages,
	blockUser,
	getBlockedUsers,
	getBlockedByUsers,
	unblockUser
} from './chat.js'

import { create } from 'domain';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);
const envPath = path.resolve(__dirname, '../srcs/secrets/.env');

dotenv.config({ path: envPath });
const httpsOptions = {
  key: readFileSync('/app/certs/privkey.pem'),
  cert: readFileSync('/app/certs/fullchain.pem')
};

const app = fastify({ logger: true, https: httpsOptions});
let blockchainService = null;
let blockchainReady = false;
// Register plugins
await app.register(cors, { 
  origin: true,
  methods: ['GET', 'POST', 'PUT', 'DELETE', 'OPTIONS'],
  credentials: true
});

await app.register(formBody);
await app.register(jwt, { 
  secret: process.env.JWT_SECRET || 'supersecretkey' 
});


// Serve static files
app.register(fastifyStatic, {
    root: path.join(__dirname, 'public')
});



await app.register(cookie, {
  secret: process.env.COOKIE_SECRET || 'fallback-secret-very-insecure',
  parseOptions: {
    httpOnly: true,
    secure: true,      
    sameSite: 'lax',
	path: '/',
  }
});

await app.register(multipart, {
  limits: {
    fieldNameSize: 100,              // Nombre del campo
    fieldSize: 1000,                 // Valor de campos texto (1KB)
    fields: 10,                      // Máximo número de campos no-file
    fileSize: 20 * 1024 * 1024,      // 20MB por archivo
    files: 1,                        // Solo 1 archivo a la vez
    headerPairs: 2000                // Headers del multipart
  },
  attachFieldsToBody: false          // NO parsear automáticamente
});

//Oauth Google
await app.register(oauthPlugin, {
	name: 'googleOAuth2',
	scope: ['openid', 'email', 'profile'],
	credentials: {
		client: {
		id: process.env.GOOGLE_CLIENT_ID,
		secret: process.env.GOOGLE_CLIENT_SECRET,
		},
		auth: oauthPlugin.GOOGLE_CONFIGURATION,
	},
	startRedirectPath: '/auth/google',
	callbackUri: process.env.GOOGLE_CALLBACK_URL || 'https://localhost:8443/auth/google/callback',
	cookie: {
		path: '/',
		secure: true,
		httpOnly: true,
		sameSite: 'lax',
	}
});

//Oauth 42
await app.register(oauthPlugin,{
	name: 'fortyTwoOauth2',
	scope:['public'],
	credentials:{
		client:{
			id:process.env.FT_OAUTH_CLIENT_ID,
			secret:process.env.FT_CLIENT_SECRET,
		},
		auth:{
			authorizeHost: 'https://api.intra.42.fr',
			authorizePath: '/oauth/authorize',
			tokenHost: 'https://api.intra.42.fr',
			tokenPath: '/oauth/token',
		},
	},
	startRedirectPath: '/auth/42',
	callbackUri: 'https://localhost:8443/auth/42/callback',
	cookie: {
		path: '/',
		secure: true,
		httpOnly: true,
		sameSite: 'lax',
	}
})


app.get('/api/auth/csrf-token', { preHandler: authenticate }, getCsrfToken);

// Auth routes
//app.get('/auth/google/callback', authGoogleCallback);
app.post('/api/auth/register', register);
app.post('/api/auth/login', login);
app.post('/api/auth/logout', { preHandler: authenticate }, logout);
app.get('/api/auth/me', { preHandler: authenticate }, me);

// Health check route
app.get('/health', async (request, reply) => {
    return { status: 'ok', message: 'Pong server is running' };
});

// User management routes
app.get('/api/user/profile', { preHandler: authenticate }, me); // Get current user's profile (reuse me endpoint)
app.put('/api/user/profile', { preHandler: authenticate }, updateProfile);
app.put('/api/user/profile/changePassword', { preHandler: authenticate }, changePassword);
app.get('/api/user/profile/:userId', { preHandler: authenticate }, getUserProfile);
app.get('/api/user/friends', { preHandler: authenticate }, getFriends);
app.get('/api/user/friend-getFriendRequests', { preHandler: authenticate }, getFriendRequests);

app.post('/api/user/challenge', { preHandler: authenticate }, challenge);
app.post('/api/user/friends/challengeRespond', { preHandler: authenticate }, respondChallenge);

app.post('/api/user/friend-request', { preHandler: authenticate }, sendFriendRequest);
app.post('/api/user/friend-response', { preHandler: authenticate }, respondToFriendRequest);
app.get('/api/user/match-history', { preHandler: authenticate }, getMatchHistory);

//OAUTH

app.get('/auth/42/callback', auth42Callback);
app.get('/auth/google/callback', authGoogleCallback);

// Chat routes

app.post('/api/chat/conversations', {preHandler: authenticate}, createConversation);
app.get('/api/chat/conversations', {preHandler: authenticate}, getConversations);
app.get('/api/chat/conversations/:id', {preHandler:authenticate}, getConversationById);
app.delete('/api/chat/conversations/:id',{preHandler:authenticate},deleteConversation)
app.post('/api/chat/conversations/:conversationId/messages', {preHandler: authenticate}, sendMessage);
app.get('/api/chat/conversations/:conversationId/messages', {preHandler: authenticate}, getMessages);
app.post('/api/chat/blocked', {preHandler: authenticate}, blockUser)
app.get('/api/chat/blocked',{preHandler: authenticate}, getBlockedUsers);
app.get('/api/chat/blocked-by', { preHandler: authenticate }, getBlockedByUsers);
app.delete('/api/chat/blocked', { preHandler: authenticate }, unblockUser);
// Debug endpoint to check user status
app.get('/api/debug/user-status/:userId', async (request, reply) => {
  try {
    const { userId } = request.params;
    const user = await User.findByPk(userId, {
      attributes: ['id', 'username', 'isOnline', 'sessions', 'lastSeen']
    });
    
    if (!user) {
      return reply.code(404).send({ error: 'User not found' });
    }
    
    const isInOnlineUsers = app.onlineUsers.has(parseInt(userId));
    const socketId = app.onlineUsers.get(parseInt(userId));
    
    reply.send({
      user: user.toJSON(),
      isInOnlineUsers,
      socketId,
      onlineUsersCount: app.onlineUsers.size,
      allOnlineUsers: Array.from(app.onlineUsers.keys())
    });
  } catch (error) {
    reply.code(500).send({ error: 'Failed to get user status' });
  }
});

// Create Socket.IO server
const io = new Server(app.server, {
    cors: {
        origin:'*',
        methods: ["GET", "POST"],
        credentials: true
    },
	transports: ['websocket', 'polling'],
    upgrade: true,
    allowUpgrades: true,
    perMessageDeflate: false,
    // Configuración adicional para HTTPS
    cookie: {
        name: 'io',
        path: '/',
        httpOnly: true,
        sameSite: 'none',
        secure: true
    }
});

app.decorate('io', io);

// Game rooms
//gameRooms is an object so it store data as key-value pairs 
var gameRooms = {};
var nextRoomId = 1;
let freeRoomIds = [];
var roomPlayersAreIn = {};

//tournaments
var tournaments = {};
var tournamentGameRooms = {}; 

setInterval

//The shift() method returns and removes the first element in the array
function createRoomId() {
    if (freeRoomIds.length > 0) {
        return `room${freeRoomIds.shift()}`; // reuse smallest available
    }
    return `room${nextRoomId++}`;
}

function releaseRoomId(roomId) {
    const num = parseInt(roomId.replace("room", ""));
    if (!isNaN(num)) {
        freeRoomIds.push(num);
//The main purpose of "(a, b) => a - b" is to sort the array numerically in ascending order.
        freeRoomIds.sort((a, b) => a - b); // keep ascending order
    }
}

function createGameState() {
    return {
        ball: { 
            x: 400, 
            y: 200, 
            vx: 2, 
            vy: 2, 
            radius: 10,
            speed: 2,              // 🎮 Velocidad actual
            baseSpeed: 2,          // 🎮 Velocidad base (se actualizará según dificultad)
            spin: null,            // 🌀 Sistema de spin: { type, intensity, rotation, decay }
            rotation: 0            // 🌀 Ángulo de rotación visual
        },
        player1: { 
            x: 10, 
            y: 150, 
            width: 10, 
            height: 100, 
            score: 0,
            lastY: 150,            // 🎮 Para calcular velocidad de movimiento
            velocity: 0            // 🎮 Velocidad de paleta (para spin futuro)
        },
        player2: { 
            x: 780, 
            y: 150, 
            width: 10, 
            height: 100, 
            score: 0, 
            targetY: 150,
            lastY: 150,            // 🎮 Para calcular velocidad de movimiento
            velocity: 0            // 🎮 Velocidad de paleta (para spin futuro)
        },
        gameEnded: false,
        startTime: Date.now(),     // 🎮 Para aceleración progresiva
        rallyCount: 0,             // 🎮 Contador de golpes consecutivos
        lastHitTime: Date.now()    // 🎮 Para detectar rally
    };
}

function createTournamentGameState() {
    return {
        ball: { 
            x: 400, 
            y: 200, 
            vx: 5,
            vy: 3.5, 
            radius: 10,
            speed: 5,
            baseSpeed: 5,
            spin: null,
            rotation: 0
        },
        player1: { 
            x: 10, 
            y: 150, 
            width: 10, 
            height: 100, 
            score: 0,
            lastY: 150,
            velocity: 0
        },
        player2: { 
            x: 780, 
            y: 150, 
            width: 10, 
            height: 100, 
            score: 0,
            lastY: 150,
            velocity: 0
        },
        gameEnded: false,
        startTime: Date.now(),
        rallyCount: 0,
        lastHitTime: Date.now()
    };
}

//entries is a method of Object that returns an array of [key, value] pairs for all properties in an object.
function getLobbyInfo() {
console.log(Object.entries(gameRooms))
    return Object.entries(gameRooms).map(([id, room]) => ({
        roomId: id,
        players: room.players,
        aiEnabled: room.aiEnabled
    }));
}

function getTournamentLobbyInfo() {

    console.log("Getting Tournament Lobby Info:", tournaments);
    //just send the tournaments that are availble
    //Not send tournaments that already started
    const tournamentsAvailbles = Object.entries(tournaments).filter(([id, tournament]) => tournament.tournamentStarted !== true);
    return tournamentsAvailbles.map(([id, tournament]) => ({
        id,
        ...tournament
    }));
}

//Is not neccesary to delete the old gameRooms if any because assigning will overwrite it.
//this fucntion is not used
//function findAvailableRoom() {
//    for (let roomId in gameRooms) {
//        if (gameRooms[roomId].players.length < 2) return roomId;
//    }
//    const newRoomId =  createRoomId();
//    gameRooms[newRoomId] = { 
//        players: [], 
//        gameState: createGameState(),
//        startTime: Date.now()
//    };
//    return newRoomId;
//}

// Game loop
setInterval(async () => {
    for (let roomId in gameRooms) {
        const room = gameRooms[roomId];

        if (room.players.length === 2 || room.aiEnabled === true) {		
			if (room.aiEnabled) {
                // Actualizar lógica de IA y luego mover la pala
                refreshAILogic(room);
                updateAIPaddle(room.gameState.player2, room.aiDifficulty, room.gameState.ball);
            }	
            await updateGame(room.gameState, roomId);
            const isPlayerInRoom = checkPlayerIsInRoom(room.players, roomId);
            if (isPlayerInRoom)
            {
                //console.log("Game updatinnnnngngnngng!!!")
                isPlayerInRoom.forEach(p => {
                    io.to(p.userId).emit('gameUpdate', {...room.gameState, players: room.players, aiDifficulty: room.aiDifficulty}, roomId);
                })
            }
        }

        if (room.players.length === 0) {
            // Make all sockets leave the Socket.IO room before deleting
            io.in(roomId).socketsLeave(roomId);
            
            delete gameRooms[roomId];
            releaseRoomId(roomId);
            io.emit("lobbyUpdate", getLobbyInfo());
        }
    }
}, 1000/60);

let tournamentFrameCount = 0;
setInterval(async () => {
    for (let tournamentRoomId in tournamentGameRooms) {
        const tournamentGameRoom = tournamentGameRooms[tournamentRoomId];
        if (tournamentGameRoom.player1 && tournamentGameRoom.player2) {
            try {
                updateTournamentGame(tournamentGameRoom.tournamentGameState, tournamentRoomId)
                io.to(tournamentRoomId).emit('updateTournamentGame', tournamentGameRoom.tournamentGameState);
                if (tournamentFrameCount % 180 === 0) {
                    console.log(`🎮 Game loop [${tournamentRoomId}]: Ball(${Math.floor(tournamentGameRoom.tournamentGameState.ball.x)},${Math.floor(tournamentGameRoom.tournamentGameState.ball.y)}) Score: ${tournamentGameRoom.tournamentGameState.player1.score}-${tournamentGameRoom.tournamentGameState.player2.score}`);
                }
            } catch (error) {
                console.error(`❌ Error in tournament game loop for ${tournamentRoomId}:`, error);
            }
        }
    }
    tournamentFrameCount++;
}, 1000/60)

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

const checkPlayerIsInRoom = (players, roomId) => {
    return players.map(p => (roomId === roomPlayersAreIn[p.userId] ? p : null)).filter(p => p !== null);
}

// ---------------- AI Logic ----------------

// 🤖 CONFIGURACIÓN DE INTELIGENCIA ARTIFICIAL - FASE 3
// Define las capacidades de la IA según la dificultad seleccionada
// Incluye detección y compensación de spin (efectos de rotación) implementados en Fase 2 y 3
const DIFFICULTY_SETTINGS = {
    // FÁCIL: IA básica sin conocimiento de spin
    easy: { 
        paddleSpeed: 3,         // Velocidad lenta de movimiento de pala
        errorRange: 40,         // Gran margen de error en predicciones (40 píxeles)
        refreshRate: 1500,      // Actualiza lógica cada 1.5 segundos (lenta)
        spinDetection: 0.0,     // 0% - No detecta spin del jugador
        spinCompensation: 0.0,  // 0% - No compensa efectos de spin
        canCounterSpin: false   // No puede generar counter-spin
    }, 
    // MEDIO: IA con conocimiento básico de spin
    medium: { 
        paddleSpeed: 5,         // Velocidad moderada de pala
        errorRange: 20,         // Margen de error medio (20 píxeles)
        refreshRate: 1000,      // Actualiza cada segundo
        spinDetection: 0.3,     // 30% - Detecta spin ocasionalmente
        spinCompensation: 0.3,  // 30% - Compensa parcialmente el spin
        canCounterSpin: false   // Aún no puede hacer counter-spin
    }, 
    // DIFÍCIL: IA avanzada con buena detección de spin
    hard: { 
        paddleSpeed: 8,         // Velocidad alta de pala
        errorRange: 5,          // Margen de error pequeño (5 píxeles)
        refreshRate: 500,       // Actualiza cada 0.5 segundos (rápida)
        spinDetection: 0.7,     // 70% - Detecta spin frecuentemente
        spinCompensation: 0.7,  // 70% - Compensa bien el spin detectado
        canCounterSpin: false   // Todavía no counter-spin
    }, 
    // IMPOSIBLE: IA perfecta con counter-spin
    impossible: { 
        paddleSpeed: 10,        // Velocidad máxima de pala
        errorRange: 2,          // Margen de error mínimo (2 píxeles)
        refreshRate: 300,       // Actualiza cada 0.3 segundos (muy rápida)
        spinDetection: 1.0,     // 100% - Siempre detecta spin del jugador
        spinCompensation: 1.0,  // 100% - Compensa perfectamente el spin
        canCounterSpin: true    // ¡Puede generar spin contrario! (técnica avanzada)
    }
};

// 🎮 CONFIGURACIÓN DE VELOCIDADES PROGRESIVAS - FASE 1
// Esta configuración define cómo evoluciona la velocidad de la pelota en cada dificultad
// La velocidad aumenta con el tiempo Y con la cantidad de rallies (golpes consecutivos)
const SPEED_CONFIG = {
    // FÁCIL: Progresión lenta para principiantes
    easy: {
        initialSpeed: 3,            // Velocidad inicial suave (3 unidades/frame)
        maxSpeed: 8,               // Velocidad máxima alcanzable
        accelerationRate: 0.05,    // Incremento pequeño por intervalo de tiempo
        accelerationInterval: 8000, // Cada 8 segundos aumenta la velocidad (lento)
        rallyBonus: 0.3            // Bonus mínimo por rallies largos
    },
    // MEDIO: Balance entre accesibilidad y desafío
    medium: {
        initialSpeed: 5,           // Velocidad inicial moderada
        maxSpeed: 14,              // Velocidad máxima considerable
        accelerationRate: 0.1,     // Incremento moderado por intervalo
        accelerationInterval: 5000, // Cada 5 segundos (ritmo medio)
        rallyBonus: 0.5            // Bonus moderado por rallies
    },
    // DIFÍCIL: Para jugadores experimentados
    hard: {
        initialSpeed: 7,           // Velocidad inicial alta
        maxSpeed: 20,              // Velocidad máxima muy alta
        accelerationRate: 0.15,    // Incremento considerable por intervalo
        accelerationInterval: 3000, // Cada 3 segundos (ritmo rápido)
        rallyBonus: 0.7            // Bonus alto por rallies largos
    },
    // IMPOSIBLE: Desafío extremo con IA perfecta
    impossible: {
        initialSpeed: 9,           // Velocidad inicial muy alta
        maxSpeed: 25,              // Velocidad máxima extrema
        accelerationRate: 0.2,     // Incremento máximo por intervalo
        accelerationInterval: 2000, // Cada 2 segundos (ritmo brutal)
        rallyBonus: 1.0            // Bonus máximo - cada rally suma mucho
    }
};

// 🧠 FUNCIÓN DE LÓGICA DE IA - FASE 3: DETECCIÓN Y COMPENSACIÓN DE SPIN
// Esta función actualiza la lógica de pensamiento de la IA según la dificultad
// Implementa detección probabilística de spin y compensación de trayectorias
function refreshAILogic(room) {
    // Obtener configuración específica de la dificultad actual
    const settings = DIFFICULTY_SETTINGS[room.aiDifficulty];
    const { errorRange, spinDetection, spinCompensation } = settings;
    const ball = room.gameState.ball;
    const paddle = room.gameState.player2;

    // 🔄 INICIALIZACIÓN DE DATOS DE IA
    // Si la IA no tiene datos de estado, los creamos con valores por defecto
    if (!paddle.aiData) {
        paddle.aiData = {
            confidence: 0.5,           // Confianza en la predicción (0-1)
            spinDetected: false,       // ¿Ha detectado spin en la pelota?
            spinType: null,            // Tipo de spin detectado ('topspin'/'backspin')
            predictedY: 200,           // Posición Y predicha donde llegará la pelota
            compensationApplied: 0     // Cantidad de compensación aplicada por spin
        };
    }

    if (ball.vx > 0) { // Ball moving towards AI
        const timeToReach = (paddle.x - ball.x) / ball.vx;
        let predictedY = ball.y + ball.vy * timeToReach;

        // 🌀 SISTEMA DE DETECCIÓN DE SPIN - FASE 3
        // Resetear detección en cada frame
        paddle.aiData.spinDetected = false;
        paddle.aiData.spinType = null;
        paddle.aiData.compensationApplied = 0;
        
        if (ball.spin && ball.spin.intensity > 0.5) {
            // AI detecta spin según su nivel de habilidad
            const detectionChance = spinDetection;
            if (Math.random() < detectionChance) {
                paddle.aiData.spinDetected = true;
                paddle.aiData.spinType = ball.spin.type;
                
                // 🎯 COMPENSACIÓN DE SPIN
                const spinEffect = ball.spin.intensity * timeToReach;
                if (ball.spin.type === 'topspin') {
                    // Topspin hace que la bola caiga más
                    const compensation = spinEffect * 0.08 * 60 * spinCompensation;
                    predictedY += compensation;
                    paddle.aiData.compensationApplied = compensation;
                } else if (ball.spin.type === 'backspin') {
                    // Backspin hace que la bola suba
                    const compensation = spinEffect * 0.064 * 60 * spinCompensation;
                    predictedY -= compensation;
                    paddle.aiData.compensationApplied = -compensation;
                }
                
                // Mayor confianza cuando detecta spin
                paddle.aiData.confidence = 0.7 + (spinDetection * 0.3);
            } else {
                // No detectó el spin - predicción errónea
                paddle.aiData.confidence = 0.3;
            }
        } else {
            // No hay spin o es muy débil
            paddle.aiData.confidence = 0.5 + (spinDetection * 0.2);
        }

        // Límites del canvas
        predictedY = Math.max(0, Math.min(400 - paddle.height, predictedY));
        
        // Error aleatorio basado en dificultad
        const error = Math.random() * errorRange - errorRange / 2;
        paddle.targetY = predictedY + error;
        paddle.aiData.predictedY = predictedY;
    } else {
        // Ball moving away - return to center
        paddle.targetY = 200 - paddle.height / 2;
        paddle.aiData.confidence = 0.5;
        paddle.aiData.spinDetected = false;
    }
}

function updateAIPaddle(paddle, difficulty, ball) {
    const settings = DIFFICULTY_SETTINGS[difficulty];
    const { paddleSpeed, canCounterSpin } = settings;
    
    // Track last position for velocity calculation
    const lastY = paddle.lastY || paddle.y;
    
    // 🎯 COUNTER-SPIN LOGIC (only impossible mode)
    if (canCounterSpin && paddle.aiData && paddle.aiData.spinDetected && ball.vx > 0) {
        // AI intenta aplicar counter-spin
        const spinType = paddle.aiData.spinType;
        const distanceToBall = paddle.x - ball.x;
        
        // Solo aplica counter-spin cuando la bola está cerca
        if (distanceToBall < 200 && distanceToBall > 0) {
            if (spinType === 'topspin') {
                // Contra topspin: mueve la pala hacia ARRIBA para generar backspin
                paddle.targetY -= 15;
            } else if (spinType === 'backspin') {
                // Contra backspin: mueve la pala hacia ABAJO para generar topspin
                paddle.targetY += 15;
            }
        }
    }
    
    // Standard movement towards target
    if (paddle.y < paddle.targetY) {
        paddle.y += Math.min(paddleSpeed, paddle.targetY - paddle.y);
    } else if (paddle.y > paddle.targetY) {
        paddle.y -= Math.min(paddleSpeed, paddle.y - paddle.targetY);
    }
    
    // Calculate velocity for spin generation
    paddle.velocity = paddle.y - lastY;
    paddle.lastY = paddle.y;
}

function startAIInterval(roomId) {
    const room = gameRooms[roomId];
    if (!room || !room.aiEnabled) return;

    const { refreshRate } = DIFFICULTY_SETTINGS[room.aiDifficulty];

    // Clear old timer if exists
    if (room.aiTimer) clearInterval(room.aiTimer);

    room.aiTimer = setInterval(() => {
        refreshAILogic(room);
    }, refreshRate);
}

// Protect socket with JWT
io.use(async (socket, next) => {
    const token = socket.handshake.auth.token;
    if (!token) return next(new Error('Auth required'));
    try {
        const decoded = await app.jwt.verify(token);
        const user = await User.findByPk(decoded.id);
        
        if (!user) {
            return next(new Error('User not found'));
        }
        if (user.activeSessionId !== decoded.sessionId) {
            return next(new Error('Session expired - another session is active'));
        }
        
        socket.user = decoded;
        next();
    } catch (error) {
        next(new Error('Invalid token'));
    }
});

// Store online users
app.decorate('onlineUsers', new Map()); // userId -> socketId

// Socket.IO connection
io.on("connection",async (socket) => {
    console.log("Player connected:", socket.user.username, socket.user.id);

    const userId = socket.user.id;

	const user = await User.findByPk(userId);
	if (!user) {
        console.error(`User ${userId} not found in database`);
        socket.disconnect();
        return;
    }
    
    const existingSocketId = user.activeSocketId;
    
    // ✅ Si hay un socket anterior, REEMPLAZARLO con el nuevo
    if (existingSocketId && existingSocketId !== socket.id) {
        console.log(`🔄 New connection for ${socket.user.username}: replacing OLD socket ${existingSocketId} with NEW socket ${socket.id}`);
        
        const oldSocket = io.sockets.sockets.get(existingSocketId);
        if (oldSocket) {
            // 🚪 PASO 1: Notificar LOGOUT a amigos con el socket VIEJO
            try {
                const friends = await Friendship.findAll({
                    where: {
                        [Op.or]: [
                            { userId: userId, status: 'accepted' },
                            { friendId: userId, status: 'accepted' }
                        ]
                    },
                    include: [
                        { model: User, as: 'User', attributes: ['id'] },
                        { model: User, as: 'Friend', attributes: ['id'] }
                    ]
                });

                if (friends && friends.length > 0) {
                    const friendsId = friends.map(f => (f.userId === userId ? f.Friend.id : f.User.id));
                    console.log(`📢 Notifying ${friendsId.length} friends that ${socket.user.username} logged out (old session)`);
                    
                    friendsId.forEach(friendId => {
                        const friendSocketId = app.onlineUsers.get(friendId);
                        if (friendSocketId) {
                            io.to(friendSocketId).emit('friendLogout', {
                                friendId: userId,
                                username: socket.user.username
                            });
                        }
                    });
                }
            } catch (error) {
                console.error('Error notifying friends on session replacement:', error);
            }
            
            // 🔴 PASO 2: Desconectar el socket VIEJO
            oldSocket.emit('sessionReplaced', { 
                message: 'Your session has been replaced by a new login from another tab or device.' 
            });
            oldSocket.disconnect(true);
            console.log(`❌ OLD socket ${existingSocketId} disconnected`);
        }
        
        // 🧹 PASO 3: Limpiar el viejo socket de onlineUsers
        app.onlineUsers.delete(userId);
    }
    
    // ✅ PASO 4: Actualizar con el NUEVO socket
    await user.update({ 
        activeSocketId: socket.id,
        isOnline: true,
        lastSeen: new Date()
    });
    app.onlineUsers.set(userId, socket.id);
    console.log(`✅ User ${socket.user.username} connected with NEW socket ${socket.id}`);
    
    // ✅ PASO 5: Notificar LOGIN a amigos con el socket NUEVO
    try {
        const friends = await Friendship.findAll({
            where: {
                [Op.or]: [
                    { userId: userId, status: 'accepted' },
                    { friendId: userId, status: 'accepted' }
                ]
            },
            include: [
                { model: User, as: 'User', attributes: ['id'] },
                { model: User, as: 'Friend', attributes: ['id'] }
            ]
        });

        if (friends && friends.length > 0) {
            const friendsId = friends.map(f => (f.userId === userId ? f.Friend.id : f.User.id));
            console.log(`📢 Notifying ${friendsId.length} friends that ${socket.user.username} logged in (new session)`);
            
            friendsId.forEach(friendId => {
                const friendSocketId = app.onlineUsers.get(friendId);
                if (friendSocketId) {
                    io.to(friendSocketId).emit('friendConnected', {
                        friendId: userId,
                        username: socket.user.username
                    });
                }
            });
        }
    } catch (error) {
        console.error('Error notifying friends on new connection:', error);
    }
	
    // Join the user's personal room (based on their ID)
    socket.join(socket.user.id);
    socket.playerRoom = new Map();

    
    // Buscar si el usuario está en algún torneo activo
    for (const [tournamentId, tournament] of Object.entries(tournaments)) {
        const isInTournament = tournament.players.some(p => p.userId === userId);
        if (isInTournament) {
            console.log(`🔄 Re-conectando ${socket.user.username} al torneo ${tournament.name}`);
            socket.join(tournamentId);
            
            // Re-enviar estado del torneo
            socket.emit("getCurrentTournament", tournament);
            
            // Si hay partida activa, reconectar a ella también
            for (const [roomId, tournamentRoom] of Object.entries(tournamentGameRooms)) {
                const isInGame = 
                    tournamentRoom.player1?.userId === userId || 
                    tournamentRoom.player2?.userId === userId;
                
                if (isInGame && tournamentRoom.tournamentId === tournamentId) {
                    console.log(`🎮 Re-conectando a partida de torneo ${roomId}`);
                    socket.join(roomId);
                    
                    // Actualizar socket ID del jugador
                    if (tournamentRoom.player1?.userId === userId) {
                        tournamentRoom.player1.id = socket.id;
                    } else {
                        tournamentRoom.player2.id = socket.id;
                    }
                    
                    // Re-enviar estado completo del juego
                    socket.emit('tournamentGameStarted', {
                        player1: tournamentRoom.player1,
                        player2: tournamentRoom.player2,
                        id: roomId,
                        tournamentGameState: tournamentRoom.tournamentGameState
                    });
                    
                    console.log(`✅ ${socket.user.username} reconectado a partida de torneo`);
                }
            }
            
            break; // Solo puede estar en un torneo
        }
    }


    //tournaments
    socket.on("createTournament",  (tournamentName, numberOfPlayers, type) => {

        //checkIf tournament with the same name exists
        let uniqueName = tournamentName;
        let count = 1;
        while (Object.values(tournaments).some(t => t.name === uniqueName)) {
            uniqueName = tournamentName + '#'.repeat(count);
            count++;
        }
        const tournamentId = Date.now().toString(); //simple unique id
        tournaments[tournamentId] = {
            id: tournamentId,
            name: uniqueName,
            numberOfPlayers: numberOfPlayers,
            type: type,
            players: [],
            matches: [],
            tournamentStarted: false,
            tournamentGameStarted: false,
            status: 'waiting', //waiting, ongoing, finished
			blockchainRecordId: null
        };
        tournaments[tournamentId].players.push({id: socket.id, userId: socket.user.id, username: socket.user.username, host: true})
        socket.join(tournamentId);
        console.log(`the ${uniqueName} TOURNAMENT has been created`)
        io.to(tournamentId).emit("getCurrentTournament", tournaments[tournamentId])
        io.emit("tournamentLobbyInfo", getTournamentLobbyInfo());
    })

    socket.on("removePlayerFromTournament", (playerId, tournamentId) => {
        const tournament = tournaments[tournamentId];
        if (!tournament) return ;
        const players = tournament.players
        if (players.length <= 0) {delete tournaments[tournamentId]; return}
        tournament.players = players.filter(p => p?.userId !== playerId);
        if (tournament.players.length <= 0) {delete tournaments[tournamentId]}

        //check if there's a host if not make a second first palyer to join to host
        const checkIFAnyHost = tournament.players?.some(p => p?.host === true);
        if (!checkIFAnyHost && tournament.players.length > 0) {
            tournament.players[0].host = true;
        }

        //remove player from the tournament room so it won't receive any data from this tournament
        socket.leave(tournamentId);
        io.emit("tournamentLobbyInfo", getTournamentLobbyInfo())
        io.to(playerId).emit("getCurrentTournament", null)
        io.to(tournamentId).emit("getCurrentTournament", tournament)
    })

    socket.emit("tournamentLobbyInfo", getTournamentLobbyInfo());


    socket.on("CheckTournamentLobbies", () => {
        //checker to see if player is in, if not then we send null so the frontend shows the tournament's lobby
        let checker = false;
        let playerId = socket.user.id;
        //reconect player on the the tournament they are in
        for (let tournamentId in tournaments) {
            const players = tournaments[tournamentId].players;
            const checkIfPlayerIsIn = players.some(p => p.userId === socket.user.id);
            if (checkIfPlayerIsIn) {
                //if player is in a tournament then send the tournament
                io.to(playerId).emit("getCurrentTournament", tournaments[tournamentId])
                checker = true;
                break ;
            }
        }
        if (!checker) {
            io.to(playerId).emit("getCurrentTournament", null)
        }
        io.emit("tournamentLobbyInfo", getTournamentLobbyInfo());
    })

    socket.on("joinTournament", async (tournamentId, tournamentName, userId) => {
        const tournament = tournaments[tournamentId];
        if (!tournament) {console.log("Returning because the tournament doesn't exits");return;}

        //check if player is already in
        const checkIfPlayerIsIn = tournament.players.some(p => p.userId === socket.user.id);
        if (checkIfPlayerIsIn) {console.log("Returning because player is in");return;}

        //check if tournament is full
        const checkIfFull = tournament.players.length >= tournament.numberOfPlayers;
        if (checkIfFull) {console.log("Returning because the tournament is full");return;}

        socket.join(tournamentId);
        tournament.players.push({id: socket.id, userId: socket.user.id, username: socket.user.username, host: false})

		if (tournament.players.length === parseInt(tournament.numberOfPlayers) && 
			blockchainReady && 
			tournament.blockchainRecordId === null) {
			
			console.log('\n📤 Registering tournament on blockchain...');
			console.log(`   Name: ${tournament.name}`);
			console.log(`   Players: ${tournament.players.map(p => p.username).join(', ')}`);
			
			try {
				const playerUsernames = tournament.players.map(p => p.username);
				const result = await blockchainService.registerTournament(
					tournament.name,
					playerUsernames
				);
				if (result && result.success) {
					tournament.blockchainRecordId = result.recordId;
					console.log(`✅ Tournament registered! Record ID: ${result.recordId}`);
					console.log(`🔗 Transaction: ${result.transactionHash}`);
					
					io.to(tournamentId).emit("tournamentRegisteredOnBlockchain", {
						recordId: result.recordId,
						transactionHash: result.transactionHash,
						blockNumber: result.blockNumber,
						tournamentName: tournament.name
					});
				} else {
					console.error(`❌ Blockchain registration failed: ${result?.message || 'Unknown error'}`);
				}
			} catch (error) {
				console.error('❌ Blockchain registration error:', error.message);
			}
		}

        //check is player is ready to start
        io.to(tournamentId).emit("getCurrentTournament", tournament)
        io.emit("tournamentLobbyInfo", getTournamentLobbyInfo());
    })

    socket.on("startTournamentNow", async (tournamentId) => {
        const tournament = tournaments[tournamentId];
        if (!tournament) return ;

        //check if match is already on... so players won't have to wait three seconds again, and they will automaticaly join their matches!!!!
        if ((tournament.tournamentStarted && tournament.tournamentGameStarted)) {
            for (let tournamentGameId in tournamentGameRooms) {
                const tournamentGame = tournamentGameRooms[tournamentGameId]
                if (tournamentGame && tournamentGame.tournamentId === tournamentId) {
                    if (tournamentGame.player1.userId === socket.user.id || tournamentGame.player2.userId === socket.user.id) {
                        socket.join(tournamentGameId);
                        //When the user reconects update the socket.id for the new one!!!
                        if (tournamentGame.player1.userId === socket.user.id ) {
                            tournamentGame.player1.id = socket.id
                        } else {
                            tournamentGame.player2.id = socket.id
                        }
                        return;
                    }
                }
            }
            return;
        }
        tournament.tournamentStarted = true;
        tournament.tournamentGameStarted = true;
        await sleep(3000);



        io.to(tournamentId).emit("tournamentJustStarted", true)
        //emit tournaments lobby so this tournament is not longer show to there because that it already started
        io.emit("tournamentLobbyInfo", getTournamentLobbyInfo())
        //create and save Matches...
        for (let i = 0; i < tournament.players.length; i += 2) {
            const p1 = tournament.players[i];
            const p2 = tournament.players[i + 1];
            if (!p1 || !p2) continue;
            const tournamentRoomId = '/' + p1.username + 'vs' + p2.username + '/';
            
            const p1Socket = io.sockets.sockets.get(p1.id);
            const p2Socket = io.sockets.sockets.get(p2.id);

            if (p1Socket) p1Socket.join(tournamentRoomId);
            if (p2Socket) p2Socket.join(tournamentRoomId);

            tournamentGameRooms[tournamentRoomId] = {
                id: tournamentRoomId,
                tournamentId: tournamentId,
                name: tournament.name,
                tournamentGameState: createTournamentGameState(),
                player1: p1,
                player2: p2,
                startTime: Date.now(),
            }
			io.to(p1.id).emit("tournamentMatchStart", { opponent: p2.username, name:tournament.name });
			io.to(p2.id).emit("tournamentMatchStart", { opponent: p1.username, name:tournament.name });

            //save Match in tournament:
            tournament.matches.push({...tournamentGameRooms[tournamentRoomId]})

			io.to(tournamentRoomId).emit('tournamentGameStarted', {
				player1: p1,
				player2: p2,
				id: tournamentRoomId,
				tournamentGameState: tournamentGameRooms[tournamentRoomId].tournamentGameState
			});
        }

    })

    socket.on("closeTournamentGame", async (tournamentGameId, winnerId) => {
        const tournamentGameInfo = {};

        console.log(`tournament Game Id: ${tournamentGameId} ---- winnerId: ${winnerId}`)

        //add a GUARD because why not? safer is better
        if (!tournamentGameRooms[tournamentGameId]) {
            return ;
        }
        const tournamentId = tournamentGameRooms[tournamentGameId].tournamentId;
        if (!tournaments[tournamentId]) return;

        //remove loser player from the tournament
        const loserPlayer = tournamentGameRooms[tournamentGameId].player1.userId !== winnerId ? tournamentGameRooms[tournamentGameId].player1 : tournamentGameRooms[tournamentGameId].player2;
        if (loserPlayer) {
            const losePlayerSocket = io.sockets.sockets.get(loserPlayer.id);
           tournaments[tournamentId].players = tournaments[tournamentId].players.filter(p => p.userId !== loserPlayer.userId)
           if (losePlayerSocket) {
                console.log(`player '${loserPlayer.username}' has been eliminated from '${tournamentGameRooms[tournamentGameId].name}' tournament`);
                losePlayerSocket.leave(tournamentId);
           }
        }

        //remove match from tournament
        tournaments[tournamentId].matches = tournaments[tournamentId].matches?.filter(match => match.id !== tournamentGameId)

        delete tournamentGameRooms[tournamentGameId];
        io.to(tournamentGameId).emit("tournamentGameFinish", tournamentGameInfo);
        io.in(tournamentGameId).socketsLeave(tournamentGameId); // Make all sockets leave the room

        //emit tournament NULL to the loser player so they can see the lobbies of the rest of tournaments
        io.to(loserPlayer.userId).emit("getCurrentTournament", null)

        if (tournaments[tournamentId].matches.length <= 0) {
            //check if players in tournament is at least 2 so a new round can start
            if (tournaments[tournamentId].players.length >= 2) {
                tournaments[tournamentId].tournamentGameStarted = false;
                io.to(tournamentId).emit("getCurrentTournament", tournaments[tournamentId])
                io.to(tournamentId).emit("tournamentJustStarted", false)
                io.to(tournamentId).emit("startTournamentNow", tournaments[tournamentId]);
            } else {
				if (tournaments[tournamentId].players.length === 1 && blockchainReady && tournaments[tournamentId].blockchainRecordId !== null) {
					const winner = tournaments[tournamentId].players[0];
					console.log('\n🏆 Finalizing tournament on blockchain...');
					console.log(`   Record ID: ${tournaments[tournamentId].blockchainRecordId}`);
					console.log(`   Winner: ${winner.username}`);
					
					try {
						const totalPlayers = parseInt(tournaments[tournamentId].numberOfPlayers);
						const scores = Array(totalPlayers).fill(0);
						scores[0] = 100;
						for (let i = 1; i < totalPlayers; i++) {
							scores[i] = Math.max(20, 100 - (i * 20));
						}
						
						const result = await blockchainService.finalizeTournament(
							tournaments[tournamentId].blockchainRecordId,
							winner.username,
							scores
						);
						
						if (result && result.success) {
							console.log('✅ Tournament finalized on blockchain!');
							console.log(`🔗 Transaction: ${result.transactionHash}`);
							io.to(tournamentId).emit("tournamentFinalizedOnBlockchain", {
								recordId: tournaments[tournamentId].blockchainRecordId,
								winner: winner.username,
								transactionHash: result.transactionHash
							});
						} else {
							console.error(`❌ Blockchain finalization failed: ${result?.message || 'Unknown error'}`);
						}
					} catch (error) {
						console.error('❌ Blockchain finalization error:', error.message);
					}
				}

				io.to(tournamentId).emit("getCurrentTournament", tournaments[tournamentId]);
			}
            return;
        }
    })

    const joinTournaments = () => {
        for (let id in tournaments) {
            const checkIfBelongsInTournament = tournaments[id].players.some(p => p.userId === socket.user.id);
            if (checkIfBelongsInTournament) {
                socket.join(id);
                //io.to(id).emit("tournamentJustStarted", true)
                break;
            }
        }
    }

    joinTournaments();







    const joinRooms = () => {
        for (let roomId in gameRooms) {
            const players = gameRooms[roomId].players;
            const player = players.find(p => p.userId === socket.user.id);
            if (player) {
				player.id = socket.id;
                socket.join(roomId);
				const isPlayer1 = player.isPlayer1;
                socket.playerRoom.set(roomId, isPlayer1);
				socket.roomId = roomId;
				
				socket.isPlayer1 = isPlayer1;
				
				roomPlayersAreIn[socket.user.id] = roomId;
				
				socket.emit("reconnectedToRoom", {
					roomId,
					isPlayer1,
					aiEnabled: gameRooms[roomId]?.aiEnabled || false,
					gameState: gameRooms[roomId]?.gameState
				});
            }
        }
    }

    joinRooms();

    // Send current lobby info
    socket.emit("lobbyUpdate", getLobbyInfo());

    socket.emit("startConnection", {
        isPlyerInRoom: gameRooms[roomPlayersAreIn[socket.user.id]]?.players.some(p => p.userId === socket.user.id),
        roomImIn: roomPlayersAreIn[socket.user.id] || null,
        aiEnabled: gameRooms[roomPlayersAreIn[socket.user.id]]?.aiEnabled || false
    })

    socket.on("createRoom", (roomNameId, {mode}) => {

        const aiEnabled = mode === 'AI';
        
        // If room already exists, append $ until we find unique name
        while (gameRooms[roomNameId]) {
            roomNameId = roomNameId + '$';
        }

        // If roomNameId is a number, add a () to not delete the sockets of the users!
        if (/^\d+$/.test(roomNameId)) {
            roomNameId = `(${roomNameId})`;
        }
    
        console.log(`🎮 Creating room '${roomNameId}' with AI=${aiEnabled}, mode='${mode}'`);
    
        gameRooms[roomNameId] = {
            players: [],
            gameState: createGameState(),
            startTime: Date.now(),
            aiEnabled,
            aiDifficulty: 'medium'
        }
        const room = gameRooms[roomNameId];
        socket.join(roomNameId);
        // 🎮 El jugador que crea la sala es siempre Player 1 (izquierda)
        socket.playerRoom.set(roomNameId, true)
        room.players.push({id: socket.id, isPlayer1: true, userId: socket.user.id, username: socket.user.username})
        io.emit("lobbyUpdate", getLobbyInfo());
        if (mode === "AI") {
            startAIInterval(roomNameId);
			io.to(roomNameId).emit("gameReady", { message: `Game ready in ${roomNameId}!` });
		}
    })

	socket.on("createRoomInvitation", (player1Username, player2Username) => {

		const roomNameId = `${player1Username} vs ${player2Username}`
		if (gameRooms[roomNameId]){
			io.in(roomNameId).socketsLeave(roomNameId);
			delete gameRooms[roomNameId]
		}
		gameRooms[roomNameId] = {
			players:[],
			gameState: createGameState(),
			startTime: Date.now(),
			aiEnabled:false,
			aiDifficulty: 'medium'
		}

		const room = gameRooms[roomNameId];
		socket.join(roomNameId);

		socket.playerRoom.set(roomNameId,true)
		room.players.push({id: socket.id, isPlayer1: true,userId: socket.user.id, username: socket.user.username})
		io.emit("lobbyUpdate", getLobbyInfo())
	})

	//Chat invitations to play a match
	socket.on("sendInvitation", ({toUserId}) => {
		io.to(toUserId).emit("receiveInvitation", {fromUserId: socket.user.id});
	})

	socket.on("sendAcceptedInvitation",(playerId,roomNameId) => {
		io.to(playerId).emit("invitationAccepted", {roomName:roomNameId});
	})

    socket.on("roomImIn", (roomId) => {
        //const room = gameRooms[roomId];
        //if (!room) return;
        //const isPlyerInRoom = room.players.some(p => p.userId === socket.user.is)
        //if (isPlyerInRoom)
        roomPlayersAreIn[socket.user.id] = roomId;
    })
    socket.on("joinRoomGame", (roomId) => {
        const room = gameRooms[roomId];
        if (!room) return;
        
        console.log(`🔍 ${socket.user.username} trying to join ${roomId}. AI=${room.aiEnabled}, players=${room.players.length}`);
        
        //check if player is in this room
        const isPlyerInRoom = room.players.some(p => p.userId === socket.user.id)
        if (isPlyerInRoom) {
            //just return because socket.emit("roomImIn", roomIamIn) is gonna let the server know which room to join
            console.log(`${socket.user.username} is re joining the room: ${roomId} like isPlayer1: ${socket.playerRoom.get(roomId)}`)
            //send User if this room is AI enabled 
            io.to(socket.user.id).emit("roomJoinedInfo", {aiEnabled: room.aiEnabled});
            console.log("reJoining game as", socket.user.username);
            return ;
        }
        //check if room is full
        if (room.players.length === 2 || room.aiEnabled) {
            console.log(`❌ ${socket.user.username} BLOCKED from ${roomId} (AI=${room.aiEnabled}, players=${room.players.length})`); 
            return;
        }

        console.log("JoinRoomGame as", socket.user.username);

        //join Room
        room.players.push({id: socket.id, isPlayer1: false, userId: socket.user.id, username: socket.user.username})
        //join socket to receive info from this roomId
        socket.join(roomId)
        //set is player is player1 in this room (in this case is false)
        socket.playerRoom.set(roomId, false)
        //send User if this room is AI enabled 
        io.to(socket.user.id).emit("roomJoinedInfo", {aiEnabled: room.aiEnabled});
        io.emit("lobbyUpdate", getLobbyInfo())
    })

    socket.on("joinRoom", (requestedRoomId, startGame, { mode }, challengeRoom) => {

		// Prevent joining multiple rooms simultaneously
		if (socket.roomId && socket.roomId !== requestedRoomId) {
			socket.emit("alreadyInRoom", {
				message: `You're already in ${socket.roomId}. Leave that room first!`,
				currentRoom: socket.roomId
			});
			return;
		}

		if (challengeRoom) {
			console.log(requestedRoomId);
			gameRooms[requestedRoomId] = {
				players: [],
				gameState: createGameState(),
				startTime: Date.now(),
				aiEnabled: false,
				aiDifficulty: "medium"
				
			}
			const room = gameRooms[requestedRoomId];
			socket.join(requestedRoomId);
			room.players.push({ id: socket.id, isPlayer1: true, userId: challengeRoom.player1 });
			socket.roomId = requestedRoomId;
			room.players.push({ id: 0, isPlayer1: false, userId: challengeRoom.player2 });

			socket.emit("gameUpdate", room.gameState);
			socket.emit("playerAssignment", {
				isPlayer1: false,
				requestedRoomId,
				playersInRoom: room.players.length,
				message: `Room ${requestedRoomId} - You are Player "2"}`,
				aiEnabled: room.aiEnabled
			});

			socket.emit("lobbyUpdate", getLobbyInfo());
			return;
		}
		if (!startGame) {
			socket.emit("chooseOpponent");
			return ;
		}
		const checkRoom = gameRooms[requestedRoomId];
		//here we can stop users from entering a room where AI mode is activated!
		if (checkRoom && (checkRoom.players.length === 2 || checkRoom.aiEnabled === true)) {
			const existingPlayer = checkRoom.players.find(p => p.userId === socket.user.id);
			if (!existingPlayer) {
				socket.emit("checkRoomStatus", {
				roomId: requestedRoomId,
				status: "roomFull",
				message: `The ${requestedRoomId} is full!`,
				isPlayer1: false,
				aiEnabled: false
				 })
				console.log("checking RoomStatus: ->roomFull");
				return ;
			}
		}
		if (checkRoom) {
			const existingPlayer = checkRoom.players.find(p => p.userId === socket.user.id);

			if (existingPlayer) {
				socket.join(requestedRoomId);
				socket.roomId = requestedRoomId;
				socket.isPlayer1 = existingPlayer.isPlayer1;
				socket.emit("checkRoomStatus",  {
					roomId: requestedRoomId,
					status: "updateRoom",
					message: `You are in the ${requestedRoomId}!`,
					isPlayer1: existingPlayer.isPlayer1,
					aiEnabled: checkRoom.aiEnabled
				});
				console.log("checking RoomStatus: ->updateRoom");
				return ;
			}
		}
		
		let roomId = requestedRoomId || createRoomId();

        // Create room if it doesn't exist
		if (mode === "AI") {
			gameRooms[roomId] = {
				players: [],
				gameState: createGameState(),
				startTime: Date.now(),
				aiEnabled: true,
				aiDifficulty: "medium"
				
			}
		}
        if (!gameRooms[roomId]) {
            gameRooms[roomId] = 
            {
                players: [],
                gameState: createGameState(),
                startTime: Date.now(),
				aiEnabled: false,
            };
            console.log(`🆕 Room created: ${roomId}`);
        }

		const room = gameRooms[roomId];

		// 👇 if not reconnecting → normal new player join logic
        //this is handle in the emit("joinRoom") in the fron-end so it can safely be remove
		//if (room.players.length >= 2) {
		//	socket.emit("roomFull", { message: `Room ${roomId} is full.` });
		//	return;
		//}

		socket.join(roomId);
		const isPlayer1 = room.players.length === 0;
		room.players.push({ id: socket.id, isPlayer1, userId: socket.user.id });
		socket.roomId = roomId;
		socket.isPlayer1 = isPlayer1;

		socket.emit("gameUpdate", room.gameState);
		socket.emit("playerAssignment", {
			isPlayer1,
			roomId,
			playersInRoom: room.players.length,
			message: `Room ${roomId} - You are Player ${isPlayer1 ? "1" : "2"}`,
			aiEnabled: room.aiEnabled
		});

		if (mode === "AI") {
            startAIInterval(roomId);
			io.to(roomId).emit("gameReady", { message: `Game ready in ${roomId}!` });
		}
		else if (room.players.length === 2) {
			io.to(roomId).emit("gameReady", { message: `Game ready in ${roomId}!` });
		}
		else {
			socket.emit("waitingForPlayer", {
                message: `Waiting for an opponent to join room ${roomId}...`
            });
		}
		io.emit("lobbyUpdate", getLobbyInfo());

	});

	socket.on('setDifficulty', (data, roomId) => {
        const room = gameRooms[roomId];
        if (room && ["easy", "medium", "hard", "impossible"].includes(data.level)) {
            room.aiDifficulty = data.level;
            console.log(`🎚️ Difficulty for ${roomId} set to ${data.level}`);
            
            // 🎮 ACTUALIZAR VELOCIDAD DE BOLA SEGÚN NUEVA DIFICULTAD
            const config = SPEED_CONFIG[data.level];
            if (config && room.gameState) {
                const currentSpeed = Math.sqrt(
                    room.gameState.ball.vx ** 2 + room.gameState.ball.vy ** 2
                );
                const speedRatio = config.initialSpeed / currentSpeed;
                room.gameState.ball.vx *= speedRatio;
                room.gameState.ball.vy *= speedRatio;
                room.gameState.ball.speed = config.initialSpeed;
                room.gameState.ball.baseSpeed = config.initialSpeed;
                room.gameState.startTime = Date.now(); // Reset timer
                room.gameState.rallyCount = 0;
            }
            
            startAIInterval(roomId); // restart with new refreshRate
        }
    });

	// Leave room
	socket.on("leaveRoom", () => {
		const roomId = socket.roomId;
		if (!roomId) return;
		
		const room = gameRooms[roomId];
		if (room) {
			room.players = room.players.filter(p => p.id !== socket.id);
			socket.leave(roomId);
			console.log(`👋 ${socket.user.username} left ${roomId}`);
			
			// Notify others
			socket.to(roomId).emit("opponentLeft", { 
				message: "Opponent left the game." 
			});
		}
		
		socket.roomId = null;
		socket.isPlayer1 = null;
		
		io.emit("lobbyUpdate", getLobbyInfo());
	});

    // Paddle movement
    socket.on("paddleMove", (data) => {
        const room = gameRooms[data.room];
        if (!room || room.gameState.gameEnded) return;

        const player = room.players.find(p => p.id === socket.id);
        if (!player) return;
        
        const isPlayer1 = player.isPlayer1;
        
        if (isPlayer1) room.gameState.player1.y = Math.max(0, Math.min(300, data.y));
        else room.gameState.player2.y = Math.max(0, Math.min(300, data.y));
    });

    socket.on("paddleTournamentGameMove", (tournamentGameRoomId, moveY, isPlayer1) => {
        const tournamentGameRoom = tournamentGameRooms[tournamentGameRoomId];
        if (!tournamentGameRoom || tournamentGameRoom.tournamentGameState.gameEnded) return;
        if (isPlayer1) tournamentGameRoom.tournamentGameState.player1.y = Math.max(0, Math.min(300, moveY));
        else tournamentGameRoom.tournamentGameState.player2.y = Math.max(0, Math.min(300, moveY));

		io.to(tournamentGameRoomId).emit("updateTournamentGame", tournamentGameRoom.tournamentGameState);
    })


    // Handle disconnect
    socket.on("disconnect", async () => {
		console.log(`🔌 User ${socket.user.username} (${userId}) disconnected`);

		const currentUser = await User.findByPk(userId);
    
		if (currentUser && currentUser.activeSocketId === socket.id) {
			console.log(`Notifying friends immediately that ${socket.user.username} disconnected`);
			
			try {
				const friends = await Friendship.findAll({
					where: {
						[Op.or]: [
							{ userId: userId, status: 'accepted' },
							{ friendId: userId, status: 'accepted' }
						]
					},
					include: [
						{ model: User, as: 'User', attributes: ['id'] },
						{ model: User, as: 'Friend', attributes: ['id'] }
					]
				});

				if (friends && friends.length > 0) {
					const friendsId = friends.map(f => (f.userId === userId ? f.Friend.id : f.User.id));
					console.log(`DISCONNECT: Notifying ${friendsId.length} friends immediately`);
					
					friendsId.forEach(friendId => {
						const friendSocketId = app.onlineUsers.get(friendId);
						if (friendSocketId) {
							console.log(`Emitting friendLogout to socket ${friendSocketId} about user ${userId}`);
							io.to(friendSocketId).emit('friendLogout', {
								friendId: userId,
								username: socket.user.username
							});
						}
					});
				}
			} catch (error) {
				console.error('Error notifying friends on disconnect:', error);
			}
		}
		setTimeout(async () => {
			const updatedUser = await User.findByPk(userId);
			if (updatedUser && updatedUser.activeSocketId === socket.id) {
				console.log(`Cleaning session for ${socket.user.username} - confirmed disconnect after 2s`);
				
				await updatedUser.update({ 
					isOnline: false,
					activeSessionId: null,
					activeSocketId: null,
					lastSeen: new Date()
				});
				
				app.onlineUsers.delete(userId);
			} else {
				console.log(`Skipping cleanup for ${socket.user.username} - socket already replaced by newer connection`);
			}
		}, 2000);
		
		const roomId = socket.roomId;
		if (!roomId || !gameRooms[roomId]) return;

		const room = gameRooms[roomId];
		const player = room.players.find(p => p.id === socket.id);

		if (player) {
			console.log(`⚠️ ${player.userId} disconnected from ${roomId}, waiting 10s...`);
			player.disconnected = true;

			socket.to(roomId).emit("opponentDisconnected", {
				message: "⚠️ Opponent disconnected. Waiting 10s for them to return..."
			});

			if (room.players.length === 0) {
				delete gameRooms[roomId];
				releaseRoomId(roomId);
				console.log(`🗑️ Room ${roomId} deleted`);
			} else {
				io.to(roomId).emit("opponentLeft", { message: "Opponent left the game." });
			}

			io.emit("lobbyUpdate", getLobbyInfo());
		}
	});


});

async function updateTournamentGame(tournamentGameState, tournamentGameRoomId) {
    if (tournamentGameState.gameEnded) return;
    
    const deltaTime = 1000 / 60;
    tournamentGameState.player1.velocity = (tournamentGameState.player1.y - tournamentGameState.player1.lastY) / deltaTime;
    tournamentGameState.player2.velocity = (tournamentGameState.player2.y - tournamentGameState.player2.lastY) / deltaTime;
    tournamentGameState.player1.lastY = tournamentGameState.player1.y;
    tournamentGameState.player2.lastY = tournamentGameState.player2.y;
    
    if (tournamentGameState.ball.spin && tournamentGameState.ball.spin.intensity > 0.1) {
        const spinEffect = tournamentGameState.ball.spin.intensity * 
            (tournamentGameState.ball.spin.type === 'topspin' ? 1 : -1);
        
        tournamentGameState.ball.vy -= spinEffect * 0.8;
        tournamentGameState.ball.spin.intensity *= 0.985;
        tournamentGameState.ball.spin.rotation += tournamentGameState.ball.spin.rotationSpeed;
        
        if (tournamentGameState.ball.spin.intensity < 0.1) {
            tournamentGameState.ball.spin = null;
        }
    }
    
    if (!tournamentGameState.ball.spin) {
        const speed = Math.sqrt(tournamentGameState.ball.vx ** 2 + tournamentGameState.ball.vy ** 2);
        tournamentGameState.ball.rotation += speed * 0.05;
    } else {
        tournamentGameState.ball.rotation = tournamentGameState.ball.spin.rotation;
    }
    
    tournamentGameState.ball.x += tournamentGameState.ball.vx;
    tournamentGameState.ball.y += tournamentGameState.ball.vy;
    
    if (tournamentGameState.ball.y <= 0 || tournamentGameState.ball.y >= 400) {
        tournamentGameState.ball.vy = -tournamentGameState.ball.vy;
        tournamentGameState.ball.y = Math.max(0, Math.min(400, tournamentGameState.ball.y));
        
        if (tournamentGameState.ball.spin) {
            if (tournamentGameState.ball.spin.type === 'topspin') {
                tournamentGameState.ball.vy *= 1.15;
                tournamentGameState.ball.vx *= 0.95;
            } else {
                tournamentGameState.ball.vy *= 0.85;
                tournamentGameState.ball.vx *= 1.05;
            }
            tournamentGameState.ball.spin.intensity *= 0.7;
        }
    }
    
    const now = Date.now();
    
    if (tournamentGameState.ball.x <= 20 && tournamentGameState.ball.x >= 10 && 
        tournamentGameState.ball.vx < 0 && 
        tournamentGameState.ball.y + 7.5 >= tournamentGameState.player1.y && 
        tournamentGameState.ball.y - 7.5 <= tournamentGameState.player1.y + 100) {
        
        tournamentGameState.ball.vx = Math.abs(tournamentGameState.ball.vx);
        tournamentGameState.ball.x = 20;
        
        const paddleVelocity = tournamentGameState.player1.velocity;
        const minVelocityForSpin = 2;
        
        if (Math.abs(paddleVelocity) > minVelocityForSpin) {
            const spinIntensity = Math.min(Math.abs(paddleVelocity) / 15, 3);
            const spinType = paddleVelocity > 0 ? 'topspin' : 'backspin';
            
            tournamentGameState.ball.spin = {
                type: spinType,
                intensity: spinIntensity,
                rotation: tournamentGameState.ball.rotation || 0,
                rotationSpeed: spinIntensity * 0.3,
                appliedBy: 'player1'
            };
        } else if (tournamentGameState.ball.spin) {
            tournamentGameState.ball.spin.intensity *= 0.6;
        }
        
        if (now - tournamentGameState.lastHitTime < 2000) {
            tournamentGameState.rallyCount++;
        } else {
            tournamentGameState.rallyCount = 1;
        }
        tournamentGameState.lastHitTime = now;
    }
    
    if (tournamentGameState.ball.x >= 780 && tournamentGameState.ball.x <= 790 && 
        tournamentGameState.ball.vx > 0 && 
        tournamentGameState.ball.y + 7.5 >= tournamentGameState.player2.y && 
        tournamentGameState.ball.y - 7.5 <= tournamentGameState.player2.y + 100) {
        
        tournamentGameState.ball.vx = -Math.abs(tournamentGameState.ball.vx);
        tournamentGameState.ball.x = 780;
        
        const paddleVelocity = tournamentGameState.player2.velocity;
        const minVelocityForSpin = 2;
        
        if (Math.abs(paddleVelocity) > minVelocityForSpin) {
            const spinIntensity = Math.min(Math.abs(paddleVelocity) / 15, 3);
            const spinType = paddleVelocity > 0 ? 'topspin' : 'backspin';
            
            tournamentGameState.ball.spin = {
                type: spinType,
                intensity: spinIntensity,
                rotation: tournamentGameState.ball.rotation || 0,
                rotationSpeed: spinIntensity * 0.3,
                appliedBy: 'player2'
            };
        } else if (tournamentGameState.ball.spin) {
            tournamentGameState.ball.spin.intensity *= 0.6;
        }
        
        if (now - tournamentGameState.lastHitTime < 2000) {
            tournamentGameState.rallyCount++;
        } else {
            tournamentGameState.rallyCount = 1;
        }
        tournamentGameState.lastHitTime = now;
    }
    
    let gameEnded = false;
    
    if (tournamentGameState.ball.x < 0) { 
        tournamentGameState.player2.score++; 
        resetTournamentBall(tournamentGameState);
        if (tournamentGameState.player2.score >= 5) gameEnded = true;
    }
    if (tournamentGameState.ball.x > 800) { 
        tournamentGameState.player1.score++; 
        resetTournamentBall(tournamentGameState);
        if (tournamentGameState.player1.score >= 5) gameEnded = true;
    }

    if (gameEnded) {
		tournamentGameState.gameEnded = true;
		console.log(`🏆 Tournament game in ${tournamentGameRoomId} ended!`);
		
		const tournamentGameRoom = tournamentGameRooms[tournamentGameRoomId];
		if (!tournamentGameRoom) return;
		
		const winner = tournamentGameState.player1.score > tournamentGameState.player2.score 
			? tournamentGameRoom.player1
			: tournamentGameRoom.player2;
		
		const loser = tournamentGameState.player1.score > tournamentGameState.player2.score
			? tournamentGameRoom.player2
			: tournamentGameRoom.player1;

		if (winner && loser) {
			await logMatchToDB(winner.userId, loser.userId, tournamentGameState.player1.score, tournamentGameState.player2.score);
		}

		// Emitir evento de fin de juego de torneo
		io.to(tournamentGameRoomId).emit("tournamentGameEnded", {
			roomId: tournamentGameRoomId,
			winner: winner?.username,
			winnerId: winner?.userId,
			loser: loser?.username,
			finalScore: {
				player1: tournamentGameState.player1.score,
				player2: tournamentGameState.player2.score
			}
		});
		
		console.log(`✅ Tournament match finished: ${winner.username} defeated ${loser.username}`);
	}
}

// Game physics
// 🎮 FUNCIÓN PRINCIPAL DEL MOTOR DE FÍSICA - FASES 1, 2 Y 3
// Actualiza la posición de la pelota, aplica spin, velocidad progresiva y detecta colisiones
async function updateGame(gameState, roomId) {
    // ⏹️ No actualizar si el juego ha terminado
    if (gameState.gameEnded) return;
    
    // ⚡ SISTEMA DE VELOCIDAD PROGRESIVA - FASE 1
    // La velocidad aumenta con el tiempo Y con los rallies según la dificultad
    const room = gameRooms[roomId];
    if (room && room.aiDifficulty) {
        const difficulty = room.aiDifficulty;
        const config = SPEED_CONFIG[difficulty] || SPEED_CONFIG.medium;
        
        // ⏱️ CÁLCULO DEL TIEMPO TRANSCURRIDO
        const gameTime = (Date.now() - gameState.startTime) / 1000;
        
        // 📊 INTERVALOS DE ACELERACIÓN COMPLETADOS
        // Cada dificultad tiene su propio intervalo (2-8 segundos)
        const timeIntervals = Math.floor(gameTime / (config.accelerationInterval / 1000));
        
        // ⚡ BONUS POR TIEMPO TRANSCURRIDO
        // Más tiempo = más velocidad según la configuración de dificultad
        const timeBonus = timeIntervals * config.accelerationRate;
        
        // 🏓 BONUS POR RALLIES LARGOS
        // Cada 5 golpes consecutivos añade velocidad bonus
        const rallyBonus = Math.floor(gameState.rallyCount / 5) * config.rallyBonus;
        
        // 🎯 VELOCIDAD OBJETIVO FINAL
        // Suma: velocidad inicial + bonus tiempo + bonus rallies (con límite máximo)
        const targetSpeed = Math.min(
            config.maxSpeed,
            config.initialSpeed + timeBonus + rallyBonus
        );
        
        // 🔄 APLICAR NUEVA VELOCIDAD MANTENIENDO DIRECCIÓN
        // Escalar el vector velocidad actual al nuevo target manteniendo la dirección
        const currentMagnitude = Math.sqrt(gameState.ball.vx ** 2 + gameState.ball.vy ** 2);
        if (currentMagnitude > 0) {
            const speedRatio = targetSpeed / currentMagnitude;
            gameState.ball.vx *= speedRatio;
            gameState.ball.vy *= speedRatio;
            gameState.ball.speed = targetSpeed;  // Guardar para el frontend
        }
    }
    
    // 🏓 TRACKING DE VELOCIDAD DE PALETAS - PREPARACIÓN PARA SPIN - FASE 2
    // Calculamos la velocidad de movimiento de cada pala para generar spin
    const deltaTime = 1000 / 60; // 16.67ms por frame a 60fps
    gameState.player1.velocity = (gameState.player1.y - gameState.player1.lastY) / deltaTime;
    gameState.player2.velocity = (gameState.player2.y - gameState.player2.lastY) / deltaTime;
    // Actualizar posiciones anteriores para próximo frame
    gameState.player1.lastY = gameState.player1.y;
    gameState.player2.lastY = gameState.player2.y;
    
    // 🌀 FÍSICA DE SPIN - FASE 2: APLICAR EFECTO DE ROTACIÓN A LA TRAYECTORIA
    // 🌀 APLICAR EFECTOS DEL SPIN SI EXISTE Y ES SIGNIFICATIVO
    if (gameState.ball.spin && gameState.ball.spin.intensity > 0.1) {
        // 📐 CALCULAR EFECTO MAGNUS
        // La intensidad del spin determina cuánto afecta a la trayectoria
        const spinEffect = gameState.ball.spin.intensity * 0.08;
        
        if (gameState.ball.spin.type === 'topspin') {
            // 🔴 TOPSPIN: Efecto Magnus hacia abajo
            // La pelota se curva hacia abajo debido a la rotación hacia adelante
            gameState.ball.vy += spinEffect;
        } else if (gameState.ball.spin.type === 'backspin') {
            // 🟢 BACKSPIN: Efecto Magnus hacia arriba
            // La pelota se curva hacia arriba debido a la rotación hacia atrás
            // (Efecto reducido al 80% para mayor realismo)
            gameState.ball.vy -= spinEffect * 0.8;
        }
        
        // ⏳ DECAIMIENTO NATURAL DEL SPIN
        // El spin se va perdiendo gradualmente por la resistencia del aire
        gameState.ball.spin.intensity *= 0.985;
        
        // 🎨 ACTUALIZAR ROTACIÓN VISUAL
        // Para animar los radios de la pelota en el frontend
        gameState.ball.spin.rotation += gameState.ball.spin.rotationSpeed;
        
        // 🗑️ ELIMINAR SPIN SI ES MUY DÉBIL
        // Evitar cálculos innecesarios cuando el efecto es negligible
        if (gameState.ball.spin.intensity < 0.1) {
            gameState.ball.spin = null;
        }
    }
    
    // 🌀 ROTACIÓN NATURAL DE LA BOLA (sin spin)
    if (!gameState.ball.spin) {
        const speed = Math.sqrt(gameState.ball.vx ** 2 + gameState.ball.vy ** 2);
        gameState.ball.rotation += speed * 0.05;
    } else {
        gameState.ball.rotation = gameState.ball.spin.rotation;
    }
    
    gameState.ball.x += gameState.ball.vx;
    gameState.ball.y += gameState.ball.vy;
    
    // 🌀 REBOTE EN PAREDES CON MODIFICACIÓN POR SPIN
    if (gameState.ball.y <= 0 || gameState.ball.y >= 400) {
        gameState.ball.vy *= -1;
        
        // Aplicar efecto del spin al rebotar
        if (gameState.ball.spin) {
            if (gameState.ball.spin.type === 'topspin') {
                // Topspin: rebote más bajo y rápido
                gameState.ball.vy *= 0.9;
                gameState.ball.vx *= 1.08;
            } else if (gameState.ball.spin.type === 'backspin') {
                // Backspin: rebote más alto y lento
                gameState.ball.vy *= 1.15;
                gameState.ball.vx *= 0.95;
            }
            
            // Reducir spin después del rebote
            gameState.ball.spin.intensity *= 0.7;
        }
    }

    // 🎮 DETECTAR COLISIONES Y ACTUALIZAR RALLY
    const now = Date.now();
    // Colisión con paddle izquierdo (Player 1)
    if (gameState.ball.x <= 20 && gameState.ball.x >= 10 && 
        gameState.ball.vx < 0 && 
        gameState.ball.y + 7.5 >= gameState.player1.y && 
        gameState.ball.y - 7.5 <= gameState.player1.y + 100) {
        gameState.ball.vx = Math.abs(gameState.ball.vx);
        gameState.ball.x = 20; // Posicionar después de la pala
        
        // 🌀 APLICAR SPIN SEGÚN VELOCIDAD DE LA PALETA
        const paddleVelocity = gameState.player1.velocity;
        const minVelocityForSpin = 2; // Velocidad mínima para generar spin
        
        if (Math.abs(paddleVelocity) > minVelocityForSpin) {
            const spinIntensity = Math.min(Math.abs(paddleVelocity) / 15, 3);
            const spinType = paddleVelocity > 0 ? 'topspin' : 'backspin';
            
            gameState.ball.spin = {
                type: spinType,
                intensity: spinIntensity,
                rotation: gameState.ball.rotation || 0,
                rotationSpeed: spinIntensity * 0.3,
                appliedBy: 'player1'
            };
        } else if (gameState.ball.spin) {
            // Reducir spin si ya tenía
            gameState.ball.spin.intensity *= 0.6;
        }
        
        // Incrementar rally si el golpe fue rápido (< 2s desde último golpe)
        if (now - gameState.lastHitTime < 2000) {
            gameState.rallyCount++;
        } else {
            gameState.rallyCount = 1;
        }
        gameState.lastHitTime = now;
    }
    // Colisión con paddle derecho (Player 2/IA)
    if (gameState.ball.x >= 780 && gameState.ball.x <= 790 && 
        gameState.ball.vx > 0 && 
        gameState.ball.y + 7.5 >= gameState.player2.y && 
        gameState.ball.y - 7.5 <= gameState.player2.y + 100) {
        gameState.ball.vx = -Math.abs(gameState.ball.vx);
        gameState.ball.x = 780; // Posicionar antes de la pala
        
        // 🌀 APLICAR SPIN SEGÚN VELOCIDAD DE LA PALETA (IA o Player 2)
        const paddleVelocity = gameState.player2.velocity;
        const minVelocityForSpin = 2;
        
        if (Math.abs(paddleVelocity) > minVelocityForSpin) {
            const spinIntensity = Math.min(Math.abs(paddleVelocity) / 15, 3);
            const spinType = paddleVelocity > 0 ? 'topspin' : 'backspin';
            
            gameState.ball.spin = {
                type: spinType,
                intensity: spinIntensity,
                rotation: gameState.ball.rotation || 0,
                rotationSpeed: spinIntensity * 0.3,
                appliedBy: 'player2'
            };
        } else if (gameState.ball.spin) {
            gameState.ball.spin.intensity *= 0.6;
        }
        
        // Incrementar rally
        if (now - gameState.lastHitTime < 2000) {
            gameState.rallyCount++;
        } else {
            gameState.rallyCount = 1;
        }
        gameState.lastHitTime = now;
    }

    let gameEnded = false;
    if (gameState.ball.x < 0) { 
        gameState.player2.score++; 
        const room = gameRooms[roomId];
        resetBall(gameState, room?.aiDifficulty || 'medium');
        if (gameState.player2.score >= 5) gameEnded = true; // 🏆 Ganar con 5 puntos
    }
    else if (gameState.ball.x > 800) { 
        gameState.player1.score++; 
        const room = gameRooms[roomId];
        resetBall(gameState, room?.aiDifficulty || 'medium');
        if (gameState.player1.score >= 5) gameEnded = true; // 🏆 Ganar con 5 puntos
    }

    // Save match when game ends
    if (gameEnded && gameRooms[roomId]) {
        gameState.gameEnded = true; // Mark game as ended to stop updates
        const room = gameRooms[roomId];
        
        // 🎯 ENVIAR ÚLTIMO GAME UPDATE CON SCORE FINAL ANTES DE TERMINAR
        room.players.forEach(p => {
            io.to(p.userId).emit('gameUpdate', {...room.gameState, players: room.players, aiDifficulty: room.aiDifficulty}, roomId);
        });
        
        // Clean up roomPlayersAreIn - remove players who were viewing this room
        for (const userId in roomPlayersAreIn) {
            if (roomPlayersAreIn[userId] === roomId) {
                delete roomPlayersAreIn[userId];
            }
        }

        if (room.players.length === 2) {
            const player1 = room.players.find(p => p.isPlayer1);
            const player2 = room.players.find(p => !p.isPlayer1);
            
            if (player1 && player2 && player1.userId && player2.userId) {
                const winnerId = gameState.player1.score > gameState.player2.score ? player1.userId : player2.userId;

                // Save match to database
                console.log(`Saving match:player1Id=${player1.userId}, player2Id=${player2.userId}, player1Score=${gameState.player1.score}, player2Score=${gameState.player2.score}, winnerId=${winnerId}`);
                await Match.create({
                    player1Id: player1.userId,
                    player2Id: player2.userId,
                    player1Score: gameState.player1.score,
                    player2Score: gameState.player2.score,
                    winnerId: winnerId,
                    duration: Math.floor((Date.now() - room.startTime) / 1000),
                    startGameTime: new Date(room.startTime).toLocaleString(),
                    gameType: '1v1'
                });

                // Update user stats
                const winnerUser = await User.findByPk(winnerId);
                const loserUser = await User.findByPk(winnerId === player1.userId ? player2.userId : player1.userId);
                
                await winnerUser.update({ wins: winnerUser.wins + 1 });
                await loserUser.update({ losses: loserUser.losses + 1 });
            }
        }
		io.to(roomId).emit("gameEnded", {roomId});
		
		// Make all sockets leave the Socket.IO room before deleting
        // with io.sockets.sockets with access to all sockets created: io -> (chosen) sockets (both fixed)
        room.players.forEach(player => {
            const playerSocket = io.sockets.sockets.get(player.id);
            if (playerSocket) {
                playerSocket.leave(roomId);
                // roomPlayersAreIn already cleaned up above (lines 607-612)
            }
        })
		
		delete gameRooms[roomId];
		//releaseRoomId(roomId);
		console.log(`🗑️ Room ${roomId} deleted`);
		io.emit("lobbyUpdate", getLobbyInfo());
    }
}

function resetBall(gameState, difficulty = 'medium') {
    // Obtener velocidad inicial según dificultad
    const config = SPEED_CONFIG[difficulty] || SPEED_CONFIG.medium;
    const initialSpeed = config.initialSpeed;
    
    gameState.ball.x = 400;
    gameState.ball.y = 200;
    gameState.ball.vx = (gameState.ball.vx > 0 ? -1 : 1) * initialSpeed;
    gameState.ball.vy = (Math.random() > 0.5 ? 1 : -1) * (initialSpeed * 0.7);
    gameState.ball.speed = initialSpeed;
    gameState.ball.baseSpeed = initialSpeed;
    
    // 🌀 Limpiar spin
    gameState.ball.spin = null;
    gameState.ball.rotation = 0;
    
    // Reset rally count y tiempo
    gameState.rallyCount = 0;
    gameState.lastHitTime = Date.now();
    // NO reseteamos startTime para mantener aceleración progresiva
}

function resetTournamentBall(tournamentGameState) {
    const initialSpeed = 5;
    
    tournamentGameState.ball.x = 400;
    tournamentGameState.ball.y = 200;
    tournamentGameState.ball.vx = (tournamentGameState.ball.vx > 0 ? -1 : 1) * initialSpeed;
    tournamentGameState.ball.vy = (Math.random() > 0.5 ? 1 : -1) * (initialSpeed * 0.7);
    tournamentGameState.ball.speed = initialSpeed;
    tournamentGameState.ball.baseSpeed = initialSpeed;
    
    tournamentGameState.ball.spin = null;
    tournamentGameState.ball.rotation = 0;
    
    tournamentGameState.rallyCount = 0;
    tournamentGameState.lastHitTime = Date.now();
}

async function initializeBlockchain() {
  try {
    blockchainService = getBlockchainService();
    blockchainReady = true;
    console.log('✅ Blockchain service ready!');
  } catch (error) {
    console.error('❌ Blockchain error:', error.message);
    blockchainReady = false;
  }
}

app.get('/api/blockchain/status', async (request, reply) => {
  try {
    if (!blockchainReady) {
      return reply.code(503).send({
        success: false,
        message: 'Blockchain service not available',
        blockchainReady: false
      });
    }

    await blockchainService.checkBalance();
    
    return reply.send({
      success: true,
      status: 'connected',
      network: 'Avalanche Fuji Testnet',
      contractAddress: blockchainService.contractAddress,
      wallet: blockchainService.wallet.address,
      snowtraceUrl: `https://testnet.snowtrace.io/address/${blockchainService.contractAddress}`,
      blockchainReady: true
    });
  } catch (error) {
    return reply.code(500).send({
      success: false,
      error: error.message
    });
  }
});

app.get('/api/blockchain/tournaments', async (request, reply) => {
  try {
    if (!blockchainReady) {
      return reply.code(503).send({
        success: false,
        message: 'Blockchain service not available',
        tournaments: []
      });
    }

    const tournaments = await blockchainService.getAllTournaments();

    return reply.send({
      success: true,
      count: tournaments.length,
      tournaments: tournaments
    });
  } catch (error) {
    return reply.code(500).send({
      success: false,
      error: error.message,
      tournaments: []
    });
  }
});

app.get('/api/blockchain/tournaments/:recordId', async (request, reply) => {
  try {
    if (!blockchainReady) {
      return reply.code(503).send({
        success: false,
        message: 'Blockchain service not available'
      });
    }

    const { recordId } = request.params;
    const tournament = await blockchainService.getTournament(parseInt(recordId));

    return reply.send({
      success: true,
      tournament: tournament
    });
  } catch (error) {
    return reply.code(500).send({
      success: false,
      error: error.message
    });
  }
});

app.get('/api/blockchain/player/:username/stats', async (request, reply) => {
  try {
    if (!blockchainReady) {
      return reply.code(503).send({
        success: false,
        message: 'Blockchain service not available'
      });
    }

    const { username } = request.params;
    const stats = await blockchainService.getPlayerStats(username);

    return reply.send({
      success: true,
      username: username,
      stats: stats
    });
  } catch (error) {
    return reply.code(500).send({
      success: false,
      error: error.message
    });
  }
});

async function cleanupOnlineUsers(){
	try{
		const result = await User.update({
				isOnline:false,
				lastSeen:new Date(),
				activeSessionId: null,
				activeSocketId:null
			},
			{
				where: {}
			}
		);
		if (app.onlineUsers){
			app.onlineUsers.clear();
		}
	}catch(error){
		console.log('Error cleaning up online users:', error);
	}
}

// Start server
const start = async () => {
    try {
        // Initialize database first
        await initializeDatabase();
        await cleanupOnlineUsers();
        await app.listen({ port: 3000, host: '0.0.0.0' });
        console.log('🚀 Pong server running on https://localhost:3000');
		await initializeBlockchain();
    } catch (err) {
        app.log.error(err);
        process.exit(1);
    }
};
start();
