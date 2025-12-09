import bcrypt from 'bcrypt';
import { User, Friendship, Match } from './db.js';
import { Op } from 'sequelize';
import crypto from 'crypto'

export async function getCsrfToken(req, reply) {
  try {
    const csrfToken = crypto.randomBytes(32).toString('hex');
    
    // Guardar en cookie (accesible desde JS porque httpOnly: false)
    reply.setCookie('csrf-token', csrfToken, {
      httpOnly: false,  // Debe ser false para que JS pueda leerlo
      secure: true,
      sameSite: 'none',
      path: '/',
      maxAge: 3600  // 1 hora
    });
    
    return reply.send({ 
      success: true,
      csrfToken 
    });
  } catch (error) {
    console.error('getCsrfToken error:', error);
    return reply.code(500).send({ 
      success: false,
      error: 'Failed to generate CSRF token' 
    });
  }
}

export async function register(req, reply) {
  const { username, password, emailOptional, displayNameOptional } = req.body;

  if (username === "" || password === "") return reply.code(400).send({ error: 'Username and password are required' });
  const email = (emailOptional && emailOptional !== "") ? emailOptional : null;
  const displayName = (displayNameOptional && displayNameOptional !== "") ? displayNameOptional : username;


  try {
	const hashed = await bcrypt.hash(password, 10);
    const user = await User.create({ 
      username, 
      password: hashed, 
      email, 
      displayName
    });
    reply.send({ message: 'User created successfully', userId: user.id });
  } catch (error) {
    if (error.name === 'SequelizeUniqueConstraintError') {
      reply.code(400).send({ error: 'Username or display name already exists' });
    } else {
      reply.code(500).send({ error: 'Registration failed', details: error.message });
    }
  }
}

// Google handler
export async function authGoogleCallback(req, reply) {
  
  const cookieHeader = req.headers.cookie || '';
  const cookies = cookieHeader.split(';').map(c => c.trim());
  
  // Buscar TODAS las cookies oauth2-redirect-state
  const stateCookies = cookies
    .filter(c => c.startsWith('oauth2-redirect-state='))
    .map(c => c.split('=')[1]);
  
  // Usar la ÚLTIMA cookie (la más reciente)
  const correctStateCookie = stateCookies[stateCookies.length - 1];
  
  if (correctStateCookie !== req.query.state) {
    return reply.redirect(`https://localhost:8443/?error=oauth_state_mismatch`);
  }
  try {
    req.cookies = req.cookies || {};
    req.cookies['oauth2-redirect-state'] = correctStateCookie;
    
    // 1. Consigue el access token de Google
    const tokenResponse = await req.server.googleOAuth2.getAccessTokenFromAuthorizationCodeFlow(req);
    const accessToken = tokenResponse.token.access_token;

    // 2. Obtén el perfil del usuario de Google
    const response = await fetch('https://openidconnect.googleapis.com/v1/userinfo', {
      headers: { Authorization: `Bearer ${accessToken}` },
    });
    const profile = await response.json();
    // 3. Busca o crea el usuario en tu base de datos
    let user = await User.findOne({ where: { provider: 'google', providerId: profile.sub } });
    if (!user) {
      console.log('🆕 Creating new user from Google OAuth');
      user = await User.create({
        username: profile.name || profile.email.split('@')[0],
        email: profile.email,
        displayName: profile.name,
        provider: 'google',
        providerId: profile.sub,
        avatar: profile.picture,
        avatarUrl: profile.picture,
        emailVerified: profile.email_verified ?? true,
        password: '',
      });
    } else {
      await user.update({});
    }
	if (user.isOnline) {
      return reply.redirect(`https://localhost:8443/login?error=already_logged_in&message=${encodeURIComponent('This account is already active in another session')}`);
    }

	const sessionId = crypto.randomBytes(32).toString('hex');
    await user.update({
      isOnline: true,
      lastSeen: new Date(),
      sessions: (user.sessions || 0) + 1,
	  activeSessionId: sessionId
    });

    // Notificar amigos
    try {
      const friends = await Friendship.findAll({
        where: {
          [Op.or]: [
            { userId: user.id, status: 'accepted' },
            { friendId: user.id, status: 'accepted' }
          ]
        },
        include: [
          { model: User, as: 'User', attributes: ['id'] },
          { model: User, as: 'Friend', attributes: ['id'] }
        ]
      });

      if (friends && friends.length > 0) {
        const friendsId = friends.map(f => (f.userId === user.id ? f.Friend.id : f.User.id));

        friendsId.forEach(friendId => {
          const friendSocketId = req.server.onlineUsers.get(friendId);
          if (friendSocketId) {
            req.server.io.to(friendSocketId).emit('friendConnected', { 
              username: user.username, 
              friendId: user.id, 
              avatar: user.avatar || user.avatarUrl || null 
            });
          }
        });
      }
    } catch (err) {
      console.error('Error notifying friends on Google OAuth login:', err);
    }

    // 4. Genera JWT
    const myJwt = req.server.jwt.sign(
      { id: user.id, username: user.username, displayName: user.displayName,sessionId },
      { expiresIn: '7d' }
    );
    
    const csrfToken = crypto.randomBytes(32).toString('hex');
    reply.clearCookie('oauth2-redirect-state', { path: '/', domain: 'localhost' });
    
    reply.setCookie('csrf-token', csrfToken, {
      httpOnly: false,
      secure: true,
      sameSite: 'none',
      path: '/',
      maxAge: 7 * 24 * 60 * 60
    });

    // 5. Redirige al frontend
    const frontendUrl = 'https://localhost:8443/login';
    return reply.redirect(`${frontendUrl}#token=${myJwt}&csrfToken=${csrfToken}&sessionId=${sessionId}&viaGoogle=true`);
    
  } catch (error) {
    
    return reply.redirect(`https://localhost:8443/?error=oauth_failed&reason=${encodeURIComponent(error.message)}`);
  }
}

// 42 handler
export async function auth42Callback(req, reply) {
  const cookieHeader = req.headers.cookie || '';
  const cookies = cookieHeader.split(';').map(c => c.trim());
  
  // Buscar TODAS las cookies oauth2-redirect-state
  const stateCookies = cookies
    .filter(c => c.startsWith('oauth2-redirect-state='))
    .map(c => c.split('=')[1]);
  // Usar la ÚLTIMA cookie (la más reciente)
  const correctStateCookie = stateCookies[stateCookies.length - 1];
  
  if (correctStateCookie !== req.query.state) {
    return reply.redirect(`https://localhost:8443/?error=oauth_state_mismatch`);
  }

  try {
    req.cookies = req.cookies || {};
    req.cookies['oauth2-redirect-state'] = correctStateCookie;
    
    // 1. Consigue el access token de 42
    const tokenResponse = await req.server.fortyTwoOauth2.getAccessTokenFromAuthorizationCodeFlow(req);
    const accessToken = tokenResponse.token.access_token;

    // 2. Obtén el perfil del usuario de la API de 42
    const response = await fetch('https://api.intra.42.fr/v2/me', {
      headers: { Authorization: `Bearer ${accessToken}` },
    });
    const profile = await response.json();

    // 3. Busca o crea el usuario en tu base de datos
    let user = await User.findOne({ where: { provider: '42', providerId: profile.id } });
    if (!user) {
      user = await User.create({
        username: profile.login,
        email: profile.email,
        displayName: profile.displayname,
        provider: '42',
        providerId: profile.id,
        avatar: profile.image?.link,
        avatarUrl: profile.image?.link,
        emailVerified: true,
        password: '',
      });
    } else {
      await user.update({});
    }
	if (user.isOnline) {
      return reply.redirect(`https://localhost:8443/login?error=already_logged_in&message=${encodeURIComponent('This account is already active in another session')}`);
    }

	const sessionId = crypto.randomBytes(32).toString('hex');

    await user.update({
      isOnline: true,
      lastSeen: new Date(),
      sessions: (user.sessions || 0) + 1,
	  activeSessionId: sessionId
    });

    // Notificar amigos
    try {
      const friends = await Friendship.findAll({
        where: {
          [Op.or]: [
            { userId: user.id, status: 'accepted' },
            { friendId: user.id, status: 'accepted' }
          ]
        },
        include: [
          { model: User, as: 'User', attributes: ['id'] },
          { model: User, as: 'Friend', attributes: ['id'] }
        ]
      });

      if (friends && friends.length > 0) {
        const friendsId = friends.map(f => (f.userId === user.id ? f.Friend.id : f.User.id));

        friendsId.forEach(friendId => {
          const friendSocketId = req.server.onlineUsers.get(friendId);
          if (friendSocketId) {
            req.server.io.to(friendSocketId).emit('friendConnected', { 
              username: user.username, 
              friendId: user.id, 
              avatar: user.avatar || user.avatarUrl || null 
            });
          }
        });
      }
    } catch (err) {
      console.error('Error notifying friends on 42 OAuth login:', err);
    }

    // 4. Genera JWT
    const myJwt = req.server.jwt.sign(
      { id: user.id, username: user.username, displayName: user.displayName,sessionId },
      { expiresIn: '7d' }
    );
    
    const csrfToken = crypto.randomBytes(32).toString('hex');
    
    // ✅ LIMPIAR cookies viejas antes de crear nuevas
    reply.clearCookie('oauth2-redirect-state', { path: '/', domain: 'localhost' });
    
    reply.setCookie('csrf-token', csrfToken, {
      httpOnly: false,
      secure: true,
      sameSite: 'none',
      path: '/',
      maxAge: 7 * 24 * 60 * 60
    });

    // 5. Redirige al frontend
    const frontendUrl = 'https://localhost:8443/login';
    return reply.redirect(`${frontendUrl}#token=${myJwt}&csrfToken=${csrfToken}&sessionId=${sessionId}&via42=true`);
    
  } catch (error) {
    return reply.redirect(`https://localhost:8443/?error=oauth_failed&reason=${encodeURIComponent(error.message)}`);
  }
}

export async function changePassword(req, reply) {
	const {oldPassword, newPassword} = req.body;
  console.log("changing password updating!")

	try {
		const user = await User.findByPk(req.user.id);
		if (!user || !(await bcrypt.compare(oldPassword, user.password))) {
			return reply.code(401).send({ error: 'Invalid Password' });
		}
		const passwordHash = await bcrypt.hash(newPassword, 10);
		await user.update({
			password: passwordHash
		})
    console.log("chPassword has been update!!!!!")
		reply.send({message: 'Password has been change correctly!', id: user.id, username: user.username})
	}
	catch (e) {
		 reply.code(500).send({ error: 'Password update failed' });
	}
}

export async function login(req, reply) {
  const { username, password } = req.body;
  const user = await User.findOne({ where: { username } });

  if (!user || !(await bcrypt.compare(password, user.password))) {
    return reply.code(401).send({ error: 'Invalid credentials' });
  }

  if (user.isOnline) {
    return reply.code(409).send({ 
      error: 'User already logged in',
      message: 'This account is already active in another session. Please logout first or close that session.'
    });
  }
  const sessionId = crypto.randomBytes(32).toString('hex');

  // Update online status
  await user.update({ isOnline: true, lastSeen: new Date(), sessions: (user.sessions || 0) + 1, activeSessionId: sessionId });

  const token = req.server.jwt.sign({ 
    id: user.id, 
    username: user.username, 
    displayName: user.displayName,
	sessionId
  }, { expiresIn: '7d' });

  const csrfToken = crypto.randomBytes(32).toString('hex');

  reply.setCookie('csrf-token', csrfToken, {
    httpOnly: false,  // Accesible desde JS
    secure: true,
    sameSite: 'none',
    path: '/',
    maxAge: 7 * 24 * 60 * 60  // 7 días (igual que JWT)
  });

  const friends = await Friendship.findAll({
    where: {
      [Op.or]: [
        {userId: user.id, status: 'accepted'},
        {friendId: user.id, status: 'accepted'}
      ]
    },
    include: [
      {
        model: User,
        as: 'User',
        attributes: ["id"]
      },
      {
        model: User,
        as: 'Friend',
        attributes: ["id"]
      }
    ]
  })

  if (friends) {
    const friendId = friends.map(friend => friend.userId === user.id ? friend.Friend.id : friend.User.id);
    friendId.forEach(friendId => {
      console.log(`Sending im loggins to friend with the id :${friendId}`);
      const friendSocketId = req.server.onlineUsers.get(friendId);
      if (friendSocketId) {
        req.server.io.to(friendSocketId).emit("friendConnected", {username: user.username, friendId: user.id});
      }
    });
  }
  else
      console.log(`CURRENTLY NO FRIENDS FOR:${user.username}`)
  reply.send({ token,csrfToken,sessionId, user: { id: user.id, username: user.username, displayName: user.displayName } });
}

export async function authenticate(req, reply) {
  try {
    await req.jwtVerify();
    const user = await User.findByPk(req.user.id);
    
    if (!user) {
      return reply.code(401).send({ error: 'User not found' });
    }
    if (user.activeSessionId !== req.user.sessionId) {
      return reply.code(401).send({ 
        error: 'Session expired',
        reason: 'Another session is active'
      });
    }
    
  } catch (error) {
    reply.code(401).send({ error: 'Unauthorized' });
  }
}

export async function logout(req, reply) {
  console.log(`🚪 Starting logout process for user: ${req.user.username} (ID: ${req.user.id})`);
  
  const user = await User.findByPk(req.user.id);
  if (user) {
    // CAMBIO: Siempre marcar como offline en logout, ignorar sistema de sesiones por ahora
    console.log(`� Forcing user ${user.username} offline`);
    
    await user.update({ 
      isOnline: false,  // FORZAR offline siempre
      lastSeen: new Date(),
	  activeSessionId: null,
	  activeSocketId:null,
    });
    
    // Forzar eliminación de onlineUsers
    const wasInOnlineUsers = req.server.onlineUsers.has(user.id);
    console.log(`� User ${user.username} was in onlineUsers: ${wasInOnlineUsers}`);
    
    if (wasInOnlineUsers) {
      req.server.onlineUsers.delete(user.id);
      console.log(`✅ User ${user.username} forcefully removed from onlineUsers`);
    }
    
    // Obtener amigos y notificarles del logout
    const friends = await Friendship.findAll({
      where: {
        [Op.and]: [
          { status: 'accepted' },
          {
            [Op.or]: [
              { userId: req.user.id },
              { friendId: req.user.id }
            ]
          }
        ]
      },
      include: [
        {
          model: User,
          as: 'User',
          attributes: ["id"]
        },
        {
          model: User,
          as: 'Friend',
          attributes: ["id"]
        }
      ]
    });
    
    if (friends && friends.length > 0) {
      const friendsId = friends.map(friend => (friend.userId === req.user.id ? friend.Friend.id : friend.User.id));
      console.log(`📢 Notifying ${friendsId.length} friends that ${user.username} logged out`);

      friendsId.forEach(friendId => {
        const friendSocketId = req.server.onlineUsers.get(friendId);
        console.log(`📬 Friend ${friendId} socketId: ${friendSocketId}`);
        
        if (friendSocketId) {
          console.log(`✅ HTTP LOGOUT: Emitting friendLogout to socketId: ${friendSocketId} for user: ${user.username}`);
          req.server.io.to(friendSocketId).emit("friendLogout", {username: user.username, friendId: user.id});
        } else {
          console.log(`❌ Friend ${friendId} is not online, cannot emit event`);
        }
      });
      req.server.io.emit("friendLogout", {username: user.username, id: user.id});
    } else {
      console.log(`📭 User ${user.username} has no friends to notify`);
    }
  }
  reply.clearCookie('csrf-token');
  reply.send({ message: 'Logged out successfully' });
}

export async function me(req, reply) {
  const user = await User.findByPk(req.user.id, {
    attributes: { exclude: ['password'] }
  });
  reply.send({ user });
}

export async function updateProfile(req, reply) {
  
  let displayName, email, avatar;
  
  try {
    const contentType = req.headers['content-type'] || '';
    
    if (contentType.includes('multipart/form-data')) {
      const parts = req.parts();
      
      for await (const part of parts) {
        if (part.type === 'file') {
          const validMimeTypes = [
            'image/jpeg',
            'image/jpg', 
            'image/png', 
            'image/gif', 
            'image/webp',
            'image/bmp'
          ];
          
          if (!validMimeTypes.includes(part.mimetype)) {
            return reply.code(400).send({ 
              error: 'Invalid file type',
              message: 'Only image files are allowed (JPEG, PNG, GIF, WebP, BMP)',
              receivedType: part.mimetype
            });
          }
          const buffer = await part.toBuffer();
          const MAX_SIZE_MB = 20;
          const MAX_SIZE_BYTES = MAX_SIZE_MB * 1024 * 1024;
          
          if (buffer.length > MAX_SIZE_BYTES) {
            return reply.code(413).send({ 
              error: 'File is too large',
              maxSizeMB: MAX_SIZE_MB,
              actualSizeMB: (buffer.length / 1024 / 1024).toFixed(2),
              message: `Avatar must be smaller than ${MAX_SIZE_MB}MB. Current size: ${(buffer.length / 1024 / 1024).toFixed(2)}MB`
            });
          }
          avatar = `data:${part.mimetype};base64,${buffer.toString('base64')}`;
          console.log(`💾 Base64 string length: ${avatar.length} chars`);
          
        } else {
          
          if (part.fieldname === 'displayName') {
            displayName = part.value;
          } else if (part.fieldname === 'email') {
            email = part.value;
          }
        }
      }
      
    } else if (contentType.includes('application/json')) {
      const body = req.body;
      displayName = body.displayName;
      email = body.email;
      avatar = body.avatar; // Por si acaso envían Base64 manualmente
      
    } else {
      return reply.code(415).send({ 
        error: 'Unsupported Content-Type',
        message: 'Content-Type must be multipart/form-data or application/json',
        received: contentType
      });
    }
    
    // ✅ PASO 4: Actualizar usuario en DB
    const user = await User.findByPk(req.user.id);
    
    if (!user) {
      return reply.code(404).send({ error: 'User not found' });
    }
    
    // Preparar datos para actualizar
    const updateData = {};
    
    if (displayName !== undefined && displayName !== user.displayName) {
      updateData.displayName = displayName;
    }
    
    if (email !== undefined && email !== user.email) {
      updateData.email = email;
    }
    
    if (avatar !== undefined) {
      updateData.avatar = avatar;
    }
    
    // Solo actualizar si hay cambios
    if (Object.keys(updateData).length > 0) {
      await user.update(updateData);
    } else {
    }
    return reply.send({ 
      message: 'Profile updated successfully', 
      user: {
        id: user.id,
        username: user.username,
        displayName: user.displayName,
        email: user.email,
        avatar: user.avatar
      }
    });
    
  } catch (error) {
    if (error.code === 'FST_REQ_FILE_TOO_LARGE') {
      return reply.code(413).send({ 
        error: 'File is too large',
        message: 'Avatar file exceeds the maximum allowed size of 20MB'
      });
    }
    
    if (error.code === 'FST_PARTS_LIMIT') {
      return reply.code(400).send({ 
        error: 'Too many files',
        message: 'Only one file can be uploaded at a time'
      });
    }
    
    if (error.name === 'SequelizeUniqueConstraintError') {
      return reply.code(400).send({ 
        error: 'Display name or email already exists',
        message: 'The display name or email you entered is already in use by another user'
      });
    }
    
    return reply.code(500).send({ 
      error: 'Profile update failed',
      message: 'An error occurred while updating your profile. Please try again.',
      details: error.message
    });
  }
}

export async function getUserProfile(req, reply) {
  const { userId } = req.params;
  try {
    const user = await User.findByPk(userId, {
      attributes: { exclude: ['password'] }
    });
    
    if (!user) return reply.code(404).send({ error: 'User not found' });
    
    // Get recent matches separately to avoid complex joins
    const recentMatches = await Match.findAll({
      where: {
        [Op.or]: [
          { player1Id: userId },
          { player2Id: userId }
        ]
      },
      limit: 10,
      order: [['createdAt', 'DESC']],
      include: [
        { model: User, as: 'Player1', attributes: ['username', 'displayName'] },
        { model: User, as: 'Player2', attributes: ['username', 'displayName'] },
        { model: User, as: 'Winner', attributes: ['username', 'displayName'] }
      ]
    });
    
    reply.send({ user: { ...user.toJSON(), recentMatches } });
  } catch (error) {
    console.error('Get user profile error:', error);
    reply.code(500).send({ error: 'Failed to fetch user profile' });
  }
}

export async function sendFriendRequest(req, reply) {
  const { friendUsername } = req.body;
  console.log(`BACK-END     friend request sent to ${friendUsername}!`)
  try {
    const friend = await User.findOne({ where: { username: friendUsername } });
    if (!friend) return reply.type('application/json').code(404).send({ error: 'User not found' });
    if (friend.id === req.user.id) return reply.code(400).send({ error: 'Cannot add yourself as friend' });

    // Check if friendship already exists
    const existingFriendship = await Friendship.findOne({
      where: {
        [Op.or]: [
          { userId: req.user.id, friendId: friend.id },
          { userId: friend.id, friendId: req.user.id }
        ]
      }
    });

    if (existingFriendship) {
      console.log('Friendship already exists:', existingFriendship);
      return reply.code(400).send({ error: 'Friendship request already exists' });
    }

    await Friendship.create({
      userId: req.user.id,
      friendId: friend.id,
      status: 'pending'
    });
    
    // check if friend is online
    const friendSocketId = req.server.onlineUsers.get(friend.id);
  if (friendSocketId) {
    req.server.io.to(friendSocketId).emit("sendFriendRequest", {
      from: req.user.username,
      to: friend.username
    });
  }
    reply.send({ message: 'Friend request sent successfully' });
  } catch (error) {
    console.error("❌ sendFriendRequest error:", error);
    reply.code(500).send({ error: 'Failed to send friend request' });
  }
}

export async function respondToFriendRequest(req, reply) {
  const { requestId, action } = req.body; // action: 'accept' or 'reject'
  try {
    const friendship = await Friendship.findOne({
      where: { id: requestId, friendId: req.user.id, status: 'pending' }
    });

    if (!friendship) return reply.code(404).send({ error: 'Friend request not found' });

    if (action === 'accept') {
      await friendship.update({ status: 'accepted' });
      reply.send({ message: 'Friend request accepted' });

      const me = await User.findByPk(req.user.id, {
        attributes: ['username', 'displayName']
      });
      
      if (me) {
        // Emitir al usuario que envió la solicitud (friendship.userId), no al requestId
        const requesterSocketId = req.server.onlineUsers.get(friendship.userId);
        if (requesterSocketId) {
          req.server.io.to(requesterSocketId).emit("acceptedFriendRequest", {
            friendUsername: me.username, 
            friendDisplayName: me.displayName
          });
        }
      }
    } else {
      await friendship.destroy();
      reply.send({ message: 'Friend request rejected' });
    }
  } catch (error) {
    reply.code(500).send({ error: 'Failed to respond to friend request' });
  }
}

export async function getFriendRequests(req, reply) {
  try {
    const friendRequest = await Friendship.findAll({
      where: {
        [Op.or]: [
          { friendId: req.user.id, status: 'pending' }
        ]
      },
      include: [
        {
          model: User,
          as: 'User',
          attributes: ['id', 'username', 'displayName', 'avatar', 'isOnline', 'lastSeen', 'email']
        }
      ],
      order: [['createdAt', 'DESC']],
      limit: 20
    });
    
    reply.send({friendRequest});
  }
  catch (error) {
    console.error('getFriendRequests error:', error);
    reply.code(500).send({ error: 'Failed to get friend-Requests' });
  }
}

export async function getFriends(req, reply) {
  console.log(`👥 Getting friends for user: ${req.user.username} (ID: ${req.user.id})`);
  try {
    const friendships = await Friendship.findAll({
      where: {
        [Op.or]: [
          { userId: req.user.id, status: 'accepted' },
          { friendId: req.user.id, status: 'accepted' }
        ]
      },
      include: [
        {
          model: User,
          as: 'User',
          attributes: ['id', 'username', 'displayName', 'avatar', 'isOnline', 'lastSeen']
        },
        {
          model: User,
          as: 'Friend',
          attributes: ['id', 'username', 'displayName', 'avatar', 'isOnline', 'lastSeen']
        }
      ]
    });

    const friends = friendships.map(friendship => {
      const friend = friendship.userId === req.user.id ? friendship.Friend : friendship.User;
      console.log(`👤 Friend: ${friend.username} (ID: ${friend.id}) - isOnline: ${friend.isOnline}`);
      return {...friend.toJSON(), challenge: friendship.challenge};
    });

    console.log(`📋 Returning ${friends.length} friends for ${req.user.username}`);
    reply.send( {friends} );
  } catch (error) {
    console.error('getFriends error:', error);
    reply.code(500).send({ error: 'Failed to fetch friends' });
  }
}

export async function getMatchHistory(req, reply) {
  try {
    const matches = await Match.findAll({
      where: {
        [Op.or]: [
          { player1Id: req.user.id },
          { player2Id: req.user.id }
        ]
      },
      include: [
        { model: User, as: 'Player1', attributes: ['username', 'displayName'] },
        { model: User, as: 'Player2', attributes: ['username', 'displayName'] },
        { model: User, as: 'Winner', attributes: ['username', 'displayName'] }
      ],
      order: [['createdAt', 'DESC']],
      limit: 50
    });
    console.log(`getting matchHistory!!!!matches = ${matches.map(m => `${m.Player1.username} vs ${m.Player2.username}`).join(', ')}`);
    reply.send({ matches });
  } catch (error) {
    reply.code(500).send({ error: 'Failed to fetch match history' });
  }
}

export async function challenge(req, reply) {
	const { friendUsername } = req.body;

	if (!friendUsername) reply.code(404).send({ error: 'User not found' });

	try {
		const friend = await User.findOne({ where: { username: friendUsername } });
		if (!friend) throw 1;
		const friendshipRow = await Friendship.findOne({
			where: {
				[Op.or]: [
					{ userId: req.user.id, friendId: friend.id },
					{ userId: friend.id, friendId: req.user.id }
				]
			}
		});
		if (!friendshipRow) return reply.code(404).send({ error: 'Friendship not found' });
		await friendshipRow.update({challenge: friend.username});
		reply.send({ message: 'Challenge Friend request sent successfully' });

	}
	catch {
		reply.code(500).send({ error: 'Failed to sent challenge to a friend' });
	}
}

export async function respondChallenge(req, reply) {
	const { friendUsername } = req.body;
	console.log(friendUsername, "88888888888888888888888888888888888888888888888888888")

	try {
		const friend = await User.findOne({where: {username: friendUsername}});
		const me = await User.findByPk(req.user.id)
		if (!me) reply.code(404).send({ error: 'User not found' });
		if (!friend) reply.code(404).send({ error: 'User not found' });
		const friendshipRow = await Friendship.findOne({
			where: {
				[Op.or]: [
					{ userId: req.user.id, friendId: friend.id },
					{ userId: friend.id, friendId: req.user.id }
				]
			}
		});
		if (!friendshipRow) return reply.code(404).send({ error: 'Friendship not found' });
		await friendshipRow.update({challenge: ""});
		const myUsername = me.username;
		console.log(friendUsername, "respondChallenge AFTEER UPDATING!!!1111111111111111111111111111111111111111111111111111111111111")
		reply.send({ ...friend.toJSON(), userId: req.user.id, myUsername});
	}
	catch {
		reply.code(500).send({ error: 'Failed to sent challenge to a friend' });

	}
}


export async function logMatchToDB(player1Id, player2Id, player1Score, player2Score) {
  try {
    const winnerId = player1Score > player2Score ? player1Id : player2Id;
    const loserId = player1Score > player2Score ? player2Id : player1Id;

    // Crear registro del partido
    const match = await Match.create({
      player1Id,
      player2Id,
      player1Score,
      player2Score,
      winnerId,
      gameType: 'tournament'
    });

    // Actualizar estadísticas de ganador
    const winner = await User.findByPk(winnerId);
    if (winner) {
      await winner.update({ wins: winner.wins + 1 });
    }

    // Actualizar estadísticas de perdedor
    const loser = await User.findByPk(loserId);
    if (loser) {
      await loser.update({ losses: loser.losses + 1 });
    }

    console.log(`✅ Match saved to DB: Player ${winnerId} defeated Player ${loserId} (${player1Score}-${player2Score})`);
    return match;
  } catch (error) {
    console.error('❌ Error saving match to DB:', error);
    throw error;
  }
}