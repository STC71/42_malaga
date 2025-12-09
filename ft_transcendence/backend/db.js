import { Sequelize, DataTypes } from 'sequelize';
import path from 'path';
import fs from 'fs';

// Resolve DB storage: allow override with DB_PATH env var.
// Default to `srcs/secrets/app.db` to keep compatibility with the old structure
// (the file will be created if missing). If you want a different location,
// set DB_PATH in your environment.
const secretsDir = path.resolve(process.cwd(), 'srcs', 'secrets');
if (!fs.existsSync(secretsDir)) {
  fs.mkdirSync(secretsDir, { recursive: true });
}

const defaultStorage = path.resolve(secretsDir, 'app.db');
const storage = process.env.DB_PATH || defaultStorage;

const sequelize = new Sequelize({
  	dialect: 'sqlite',
	//docker
	storage: '/app/data/database.sqlite',
	// local dev
	// storage: './tmp/app/database.sqlite',
  	logging: false
});

export const User = sequelize.define('User', {
  id: { 
    type: DataTypes.INTEGER, 
    primaryKey: true, 
    autoIncrement: true 
  },
  username: { type: DataTypes.STRING, unique: true, allowNull: false },
  password: { type: DataTypes.STRING, allowNull: true },
  displayName: { type: DataTypes.STRING, unique: true, allowNull: true },
  email: { type: DataTypes.STRING, unique: true, allowNull: true },
  avatar: { type: DataTypes.STRING, defaultValue: '' },
  wins: { type: DataTypes.INTEGER, defaultValue: 0 },
  losses: { type: DataTypes.INTEGER, defaultValue: 0 },
  isOnline: { type: DataTypes.BOOLEAN, defaultValue: false },
  lastSeen: { type: DataTypes.DATE, defaultValue: DataTypes.NOW },
  provider: {
    type: DataTypes.STRING, // e.g. "local", "google"
    allowNull: false,
    defaultValue: 'local',
  },
  providerId: {
    type: DataTypes.STRING, // Google "sub" value
    allowNull: true,
  },
  avatarUrl: {
    type: DataTypes.STRING,
    allowNull: true,
  },
  emailVerified: {
    type: DataTypes.BOOLEAN,
    defaultValue: false,
  },
  sessions: {
    type: DataTypes.INTEGER,
    defaultValue: 0,
  },
  activeSessionId: {
    type: DataTypes.STRING,
    allowNull: true,
  },
  activeSocketId: {
    type: DataTypes.STRING,
    allowNull: true,
  }
});

export const Friendship = sequelize.define('Friendship', {
	id: { 
    type: DataTypes.INTEGER, 
    primaryKey: true, 
    autoIncrement: true 
  },
  status: { 
    type: DataTypes.ENUM('pending', 'accepted', 'blocked'), 
    defaultValue: 'pending' 
  },
  challenge: {
	type: DataTypes.STRING,
	defaultValue: ""
  }
});

export const Match = sequelize.define('Match', {
	id: { 
    type: DataTypes.INTEGER, 
    primaryKey: true, 
    autoIncrement: true 
  },


  player1Id: { type: DataTypes.INTEGER, allowNull: false },
  player2Id: { type: DataTypes.INTEGER, allowNull: false },
  player1Score: { type: DataTypes.INTEGER, defaultValue: 0 },
  player2Score: { type: DataTypes.INTEGER, defaultValue: 0 },
  winnerId: { type: DataTypes.INTEGER, allowNull: true },
  duration: { type: DataTypes.INTEGER, defaultValue: 0 }, // in seconds
  startGameTime: { type: DataTypes.STRING, defaultValue: ''}, // insecond
  gameType: { type: DataTypes.STRING, defaultValue: '1v1' }
});


//Chat
export const Conversation = sequelize.define('Conversation', {
	id: {
		type: DataTypes.INTEGER,
		primaryKey: true,
		autoIncrement: true,
	},
	user1Id: {
		type: DataTypes.INTEGER,
		allowNull: false,
		references: {model: User, key: 'id'},
	},
	user2Id: {
		type: DataTypes.INTEGER,
		allowNull: false,
		references: {model: User, key: 'id'},
	},
	lastMessageAt: {
		type: DataTypes.DATE, defaultValue: DataTypes.NOW,
	},
	createdAt: {
		type: DataTypes.DATE,
		defaultValue: DataTypes.NOW
	}}, {
		indexes: [
			{unique: true, fields: ['user1Id', 'user2Id']}
		]
});

export const Message = sequelize.define('Message',{
	id: {
		type: DataTypes.INTEGER,
		primaryKey: true,
		autoIncrement: true,
	},
	senderId: {
		type: DataTypes.INTEGER,
		allowNull: false,
		references: {model: User, key: 'id'}
	},
	conversationId: {
		type: DataTypes.INTEGER,
		allowNull: false,
		references: {model: Conversation, key: 'id'}
	},
	message: {
		type:DataTypes.TEXT,
		allowNull: false
	},
	createdAt: {
		type: DataTypes.DATE,
		defaultValue: DataTypes.NOW
	}
},{
	indexes: [
		{fields: ['conversationId']},
		{fields: ['createdAt']}
	]
});

export const BlockedUsers = sequelize.define('BlockedUsers',{
	id: {
		type: DataTypes.INTEGER,
		primaryKey: true,
		autoIncrement: true,
	},
	userId: {
		type: DataTypes.INTEGER,
		allowNull: false,
		references: {model: User, key: 'id'}
	},
	blockedUserId: {
		type: DataTypes.INTEGER,
		allowNull: false,
		references: {model: User, key: 'id'}
	}
},{
	indexes: [
		{fields: ['userId']},
		{fields: ['blockedUserId']},
		{unique: true, fields: ['userId', 'blockedUserId']}
	]
});

//Associartions of chat implementation
Conversation.belongsTo(User, {
	as: 'User1',
	foreignKey: 'user1Id'
});

Conversation.belongsTo(User, {
	as:'User2',
	foreignKey: 'user2Id'
});

Conversation.hasMany(Message, {
	foreignKey: 'conversationId'
});

Message.belongsTo(User, {
	as: 'Sender',
	foreignKey: 'senderId'
});

Message.belongsTo(Conversation, {
	foreignKey: 'conversationId'
});

BlockedUsers.belongsTo(User, {
	as: 'User',
	foreignKey: 'userId'
});

BlockedUsers.belongsTo(User,{
	as: 'Blocked',
	foreignKey: 'blockedUserId'
});

// Define associations
User.belongsToMany(User, { 
  through: Friendship, 
  as: 'Friends',
  foreignKey: 'userId',
  otherKey: 'friendId'
});

// The .belongsTo association is necessary to link User information by ID.
// It enables us to easily get full User details from a related model using only the user's ID.

// Add direct associations for Friendship model
Friendship.belongsTo(User, { as: 'User', foreignKey: 'userId' });
Friendship.belongsTo(User, { as: 'Friend', foreignKey: 'friendId' });

Match.belongsTo(User, { as: 'Player1', foreignKey: 'player1Id' });
Match.belongsTo(User, { as: 'Player2', foreignKey: 'player2Id' });
Match.belongsTo(User, { as: 'Winner', foreignKey: 'winnerId' });

// Associate User with Match as both Player1 and Player2.
// These models allow us to get all matches where the user participated, either as player1 or player2.
User.hasMany(Match, { as: 'Player1Matches', foreignKey: 'player1Id' });
User.hasMany(Match, { as: 'Player2Matches', foreignKey: 'player2Id' });

// Initialize database
export async function initializeDatabase({ force = false, alter = false } = {}) {
  // By default avoid dropping tables. Use force=true in dev/test when needed.
  await sequelize.sync({ force, alter });
  console.log('✅ Database synced', { force, alter, storage });
}

// Backwards-compatible default export for code that expects `import db from './db'`.
export default {
  sequelize,
  User,
  Friendship,
  Match,
  initializeDatabase,
  Conversation,
  Message,
  BlockedUsers,
};
