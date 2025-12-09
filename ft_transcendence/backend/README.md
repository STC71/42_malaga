# 📂 Backend - Servidor Node.js del Proyecto Transcendence

## 📋 Descripción General

Este directorio contiene el **servidor backend** completo de la aplicación Transcendence. Implementa una arquitectura basada en **Fastify** (framework HTTP rápido) + **Socket.IO** (comunicación en tiempo real) + **Sequelize ORM** (gestión de base de datos SQLite).

## 🗂️ Estructura de Archivos

```
backend/
├── pon-server.js         # Servidor principal (1071 líneas)
├── auth.js               # Autenticación y OAuth (522 líneas)
├── chat.js               # Sistema de chat y mensajería (376 líneas)
├── db.js                 # Configuración de base de datos y modelos
├── index.js              # Entry point (ejecuta pon-server.js)
├── package.json          # Dependencias y scripts
├── nodemon.json          # Configuración de auto-reload
├── Dockerfile            # Imagen Docker del backend
├── srcs/                 # Recursos adicionales
│   └── secrets/          # Archivos sensibles (.env, claves)
├── temp/                 # Archivos temporales
│   └── app/
└── tmp/                  # Directorio temporal alternativo
    └── app/
```

## 🚀 Archivo Principal: `pon-server.js`

### Descripción

**Tamaño**: 1071 líneas  
**Función**: Servidor principal que orquesta toda la lógica del juego Pong, gestión de salas, matchmaking y comunicación en tiempo real.

### Características Principales

#### 🎮 Game Server con Socket.IO

- **Rooms System**: Salas de juego para PvP, vs IA, y torneos
- **Game Loop**: Actualización de física a 60 FPS
- **Ball Physics**: Colisiones, rebotes, aceleración
- **Paddle Control**: Sincronización de movimientos de jugadores
- **AI Opponents**: 4 niveles de dificultad (Easy, Medium, Hard, Expert)
- **Replay System**: Grabación y reproducción de partidas

#### 📊 Eventos Socket.IO

```javascript
// Conexión y autenticación
socket.on('connect', () => {...})
socket.on('disconnect', () => {...})

// Gestión de salas
socket.emit('createRoom', roomName, options)
socket.emit('joinRoom', roomId)
socket.emit('leaveRoom')
socket.on('roomsList')

// Gameplay
socket.emit('paddleMove', { y: number })
socket.emit('startGame')
socket.on('gameUpdate', (gameState) => {...})
socket.on('gameOver', (result) => {...})

// Torneos
socket.emit('createTournament', players)
socket.on('tournamentUpdate', (bracket) => {...})
```

#### 🧠 Inteligencia Artificial

```javascript
// Extracto del algoritmo de IA (simplificado)
function updateAIPaddle(difficulty, ballY, paddleY) {
  const target = predictBallPosition(ball);
  const error = calculateError(difficulty);
  const speed = getAISpeed(difficulty);
  
  if (paddleY < target - error) {
    return paddleY + speed;
  } else if (paddleY > target + error) {
    return paddleY - speed;
  }
  return paddleY;
}

// Niveles de dificultad
const difficulties = {
  easy: { speed: 3, error: 50, reaction: 200 },
  medium: { speed: 5, error: 20, reaction: 100 },
  hard: { speed: 7, error: 10, reaction: 50 },
  expert: { speed: 9, error: 2, reaction: 10 }
};
```

#### 📈 Game State Structure

```javascript
const gameState = {
  roomId: string,
  players: [
    { id: string, username: string, paddle: { y: number, height: number } },
    { id: string, username: string, paddle: { y: number, height: number } }
  ],
  ball: {
    x: number,
    y: number,
    vx: number,
    vy: number,
    radius: number
  },
  score: { player1: number, player2: number },
  status: 'waiting' | 'playing' | 'paused' | 'finished',
  timestamp: number
};
```

#### 🔄 Game Loop

```javascript
// Actualización cada 16ms (60 FPS)
function gameLoop(roomId) {
  const room = rooms.get(roomId);
  
  // 1. Actualizar posición de la bola
  room.ball.x += room.ball.vx;
  room.ball.y += room.ball.vy;
  
  // 2. Colisiones con paredes
  if (room.ball.y <= 0 || room.ball.y >= CANVAS_HEIGHT) {
    room.ball.vy *= -1;
  }
  
  // 3. Colisiones con palas
  if (checkPaddleCollision(room.ball, room.players[0].paddle)) {
    room.ball.vx *= -1.05;  // Aceleración gradual
    room.ball.vy += calculateSpin(room.players[0].paddle);
  }
  
  // 4. Detectar puntos
  if (room.ball.x <= 0) {
    room.score.player2++;
    resetBall(room);
  } else if (room.ball.x >= CANVAS_WIDTH) {
    room.score.player1++;
    resetBall(room);
  }
  
  // 5. Enviar actualización a clientes
  io.to(roomId).emit('gameUpdate', room);
  
  // 6. Verificar fin de juego
  if (room.score.player1 >= 5 || room.score.player2 >= 5) {
    endGame(room);
  } else {
    setTimeout(() => gameLoop(roomId), 16);
  }
}
```

---

## 🔐 Módulo de Autenticación: `auth.js`

### Descripción

**Tamaño**: 522 líneas  
**Función**: Gestión completa de autenticación con JWT, OAuth 2.0, y bcrypt para passwords.

### Endpoints REST

```javascript
// Registro de usuarios
POST /api/auth/register
Body: { username, email, password }
Response: { message: "Usuario creado", userId }

// Login estándar
POST /api/auth/login
Body: { username, password }
Response: { token, refreshToken, user }

// Login con OAuth (Google, 42)
GET /api/auth/oauth/:provider
Redirect: OAuth provider authorization page
Callback: /api/auth/oauth/:provider/callback

// Verificar token
GET /api/auth/verify
Headers: { Authorization: "Bearer <token>" }
Response: { valid: boolean, user }

// Refresh token
POST /api/auth/refresh
Body: { refreshToken }
Response: { token }

// Logout
POST /api/auth/logout
Headers: { Authorization: "Bearer <token>" }
Response: { message: "Logged out" }
```

### Flujo de Autenticación

```
┌─────────────┐
│   Cliente   │
└──────┬──────┘
       │ POST /api/auth/login
       │ { username, password }
       ↓
┌─────────────────┐
│   auth.js       │
│  1. Buscar user │
│  2. bcrypt.compare(password, hash)
│  3. Generar JWT token
│  4. Generar refresh token
└──────┬──────────┘
       │ { token, user }
       ↓
┌─────────────┐
│   Cliente   │
│ Guarda token│
│ en localStorage
└─────────────┘
```

### Seguridad

```javascript
// Hashing de passwords con bcrypt
const bcrypt = require('bcrypt');
const saltRounds = 10;

// Al registrar
const hashedPassword = await bcrypt.hash(password, saltRounds);
await User.create({ username, email, password: hashedPassword });

// Al hacer login
const user = await User.findOne({ where: { username } });
const isValid = await bcrypt.compare(password, user.password);

if (!isValid) {
  return reply.code(401).send({ error: 'Credenciales inválidas' });
}
```

### JWT Tokens

```javascript
const jwt = require('jsonwebtoken');

// Generar token
const token = jwt.sign(
  { userId: user.id, username: user.username },
  process.env.JWT_SECRET,
  { expiresIn: '1h' }
);

// Refresh token (más duradero)
const refreshToken = jwt.sign(
  { userId: user.id },
  process.env.JWT_REFRESH_SECRET,
  { expiresIn: '7d' }
);

// Middleware de autenticación
fastify.decorate('authenticate', async (request, reply) => {
  try {
    const token = request.headers.authorization?.split(' ')[1];
    const decoded = jwt.verify(token, process.env.JWT_SECRET);
    request.user = await User.findByPk(decoded.userId);
  } catch (error) {
    reply.code(401).send({ error: 'Token inválido' });
  }
});
```

---

## 💬 Módulo de Chat: `chat.js`

### Descripción

**Tamaño**: 376 líneas  
**Función**: Sistema completo de mensajería instantánea con soporte para conversaciones privadas, grupos, bloqueo de usuarios.

### Endpoints REST

```javascript
// Conversaciones
GET    /api/conversations              // Listar conversaciones del usuario
POST   /api/conversations              // Crear nueva conversación
GET    /api/conversations/:id/messages // Obtener mensajes de una conversación
DELETE /api/conversations/:id          // Eliminar conversación

// Mensajes
POST   /api/messages                   // Enviar mensaje
PUT    /api/messages/:id               // Editar mensaje
DELETE /api/messages/:id               // Eliminar mensaje

// Usuarios bloqueados
GET    /api/blocked-users              // Listar usuarios bloqueados
POST   /api/blocked-users/:userId      // Bloquear usuario
DELETE /api/blocked-users/:userId      // Desbloquear usuario
```

### Eventos Socket.IO

```javascript
// Unirse a sala de chat
socket.emit('join-chat', conversationId)

// Enviar mensaje
socket.emit('send-message', {
  conversationId,
  text,
  attachments
})

// Recibir mensaje en tiempo real
socket.on('new-message', (message) => {
  // Actualizar UI con nuevo mensaje
})

// Typing indicator
socket.emit('typing', { conversationId })
socket.on('user-typing', ({ userId, username }) => {
  // Mostrar "Usuario está escribiendo..."
})

// Mensaje leído
socket.emit('message-read', { messageId })
socket.on('message-read-receipt', ({ messageId, readBy }) => {
  // Marcar mensaje como leído con doble check
})
```

### Modelos de Base de Datos

```javascript
// Conversation Model
const Conversation = sequelize.define('Conversation', {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  name: DataTypes.STRING,  // Nombre del grupo (null para privados)
  isGroup: { type: DataTypes.BOOLEAN, defaultValue: false },
  createdAt: DataTypes.DATE
});

// Message Model
const Message = sequelize.define('Message', {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  conversationId: DataTypes.INTEGER,
  senderId: DataTypes.INTEGER,
  text: DataTypes.TEXT,
  attachments: DataTypes.JSON,  // URLs de archivos adjuntos
  isEdited: { type: DataTypes.BOOLEAN, defaultValue: false },
  createdAt: DataTypes.DATE
});

// BlockedUser Model
const BlockedUser = sequelize.define('BlockedUser', {
  blockerId: DataTypes.INTEGER,  // Quien bloquea
  blockedId: DataTypes.INTEGER   // Quien es bloqueado
});

// Relaciones
Conversation.hasMany(Message, { foreignKey: 'conversationId' });
Message.belongsTo(User, { foreignKey: 'senderId' });
User.hasMany(BlockedUser, { foreignKey: 'blockerId' });
```

### Lógica de Bloqueo

```javascript
// Verificar si un usuario está bloqueado
async function isBlocked(userId, targetUserId) {
  const block = await BlockedUser.findOne({
    where: {
      [Op.or]: [
        { blockerId: userId, blockedId: targetUserId },
        { blockerId: targetUserId, blockedId: userId }
      ]
    }
  });
  return !!block;
}

// Filtrar mensajes de usuarios bloqueados
app.get('/api/conversations/:id/messages', async (req, reply) => {
  const messages = await Message.findAll({
    where: { conversationId: req.params.id },
    include: [{ model: User, as: 'sender' }]
  });

  // Filtrar bloqueados
  const blockedUsers = await BlockedUser.findAll({
    where: { blockerId: req.user.id }
  });
  const blockedIds = blockedUsers.map(b => b.blockedId);

  const filteredMessages = messages.filter(
    m => !blockedIds.includes(m.senderId)
  );

  return filteredMessages;
});
```

---

## 🗄️ Base de Datos: `db.js`

### Descripción

**Función**: Configuración de Sequelize ORM, definición de modelos y relaciones.

### Configuración

```javascript
const { Sequelize, DataTypes } = require('sequelize');

// SQLite para desarrollo
const sequelize = new Sequelize({
  dialect: 'sqlite',
  storage: './srcs/secrets/app.db',
  logging: false  // Desactivar logs SQL en producción
});

// Probar conexión
sequelize.authenticate()
  .then(() => console.log('Database connected'))
  .catch(err => console.error('Database connection error:', err));
```

### Modelos Principales

```javascript
// User Model
const User = sequelize.define('User', {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  username: { type: DataTypes.STRING, unique: true, allowNull: false },
  email: { type: DataTypes.STRING, unique: true, allowNull: false },
  password: DataTypes.STRING,  // Hash bcrypt
  displayName: DataTypes.STRING,
  avatar: DataTypes.STRING,    // URL de avatar
  bio: DataTypes.TEXT,
  oauthProvider: DataTypes.STRING,  // 'google', '42', null
  oauthId: DataTypes.STRING,
  wins: { type: DataTypes.INTEGER, defaultValue: 0 },
  losses: { type: DataTypes.INTEGER, defaultValue: 0 },
  elo: { type: DataTypes.INTEGER, defaultValue: 1000 },
  createdAt: DataTypes.DATE
});

// Match Model
const Match = sequelize.define('Match', {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  player1Id: DataTypes.INTEGER,
  player2Id: DataTypes.INTEGER,
  winnerId: DataTypes.INTEGER,
  scorePlayer1: DataTypes.INTEGER,
  scorePlayer2: DataTypes.INTEGER,
  duration: DataTypes.INTEGER,  // En segundos
  mode: DataTypes.STRING,       // 'PvP', 'AI', 'Tournament'
  replayData: DataTypes.JSON,   // Datos para replay
  createdAt: DataTypes.DATE
});

// FriendRequest Model
const FriendRequest = sequelize.define('FriendRequest', {
  senderId: DataTypes.INTEGER,
  receiverId: DataTypes.INTEGER,
  status: {
    type: DataTypes.ENUM('pending', 'accepted', 'rejected'),
    defaultValue: 'pending'
  },
  createdAt: DataTypes.DATE
});

// Friendship Model (auto-generada al aceptar FriendRequest)
const Friendship = sequelize.define('Friendship', {
  user1Id: DataTypes.INTEGER,
  user2Id: DataTypes.INTEGER,
  createdAt: DataTypes.DATE
});
```

### Relaciones

```javascript
// Usuario → Partidas
User.hasMany(Match, { as: 'matchesAsPlayer1', foreignKey: 'player1Id' });
User.hasMany(Match, { as: 'matchesAsPlayer2', foreignKey: 'player2Id' });
Match.belongsTo(User, { as: 'player1', foreignKey: 'player1Id' });
Match.belongsTo(User, { as: 'player2', foreignKey: 'player2Id' });

// Usuario → Solicitudes de amistad
User.hasMany(FriendRequest, { as: 'sentRequests', foreignKey: 'senderId' });
User.hasMany(FriendRequest, { as: 'receivedRequests', foreignKey: 'receiverId' });

// Amistad (many-to-many)
User.belongsToMany(User, { as: 'friends', through: Friendship, foreignKey: 'user1Id' });
```

### Sincronización

```javascript
// Crear tablas si no existen
sequelize.sync({ force: false })  // force: true → DROP + CREATE
  .then(() => console.log('Database tables created'))
  .catch(err => console.error('Sync error:', err));
```

---

## 📦 Dependencias (`package.json`)

```json
{
  "name": "transcendence-backend",
  "version": "1.0.0",
  "scripts": {
    "start": "node index.js",
    "dev": "nodemon index.js",
    "test": "jest",
    "migrate": "sequelize-cli db:migrate"
  },
  "dependencies": {
    "fastify": "^4.25.0",
    "socket.io": "^4.7.0",
    "sequelize": "^6.32.0",
    "sqlite3": "^5.1.6",
    "bcrypt": "^5.1.1",
    "jsonwebtoken": "^9.0.2",
    "dotenv": "^16.3.1",
    "cors": "^2.8.5"
  },
  "devDependencies": {
    "nodemon": "^3.0.1",
    "jest": "^29.6.0"
  }
}
```

## 🐳 Dockerfile

```dockerfile
FROM node:20-alpine

WORKDIR /app

# Copiar package files
COPY package*.json ./

# Instalar dependencias
RUN npm ci --only=production

# Copiar código fuente
COPY . .

# Exponer puerto
EXPOSE 3000

# Comando de inicio
CMD ["node", "index.js"]
```

## 🔗 Integración con Frontend

```typescript
// Frontend → Backend (REST)
const response = await fetch('http://localhost:3000/api/users/me', {
  headers: { Authorization: `Bearer ${token}` }
});

// Frontend → Backend (Socket.IO)
import { io } from 'socket.io-client';

const socket = io('http://localhost:3000', {
  auth: { token: localStorage.getItem('auth_token') }
});

socket.on('connect', () => {
  console.log('Connected to game server');
});

socket.emit('createRoom', 'My Room', { mode: 'AI', difficulty: 'hard' });
```

## 🚀 Ejecución

```bash
# Desarrollo con auto-reload
npm run dev

# Producción
npm start

# Docker
docker build -t transcendence-backend .
docker run -p 3000:3000 transcendence-backend
```

---

**Ubicación**: `/backend/`  
**Tecnologías**: Node.js 20, Fastify 4, Socket.IO 4, Sequelize 6, SQLite 3, bcrypt, JWT  
**Documentación relacionada**: 
- `/frontend/` - Cliente React que consume este backend
- `/AI.md` - Detalles de la implementación de IA
- `/docker-compose.yml` - Orquestación de servicios
