import {User, Conversation, BlockedUsers, Message} from "./db.js"

import {Op} from 'sequelize'

export async function createConversation(req, reply){
	try{
		const currentUserId = req.user.id;
		const {otherUserId} = req.body;

		if (!otherUserId){
			return reply.code(400).send({error: 'otherUserId is required'})
		}

		if (currentUserId === parseInt(otherUserId)){
			return reply.code(400).send({error: 'Cannot create a conversation with yourself'})
		}

		const otherUser = await User.findByPk(otherUserId)

		if (!otherUser){
			return reply.code(400).send({error: 'User not found'})
		}

		const isBlocked = await BlockedUsers.findOne({
			where: {
				[Op.or]: [
					{userId: currentUserId, blockedUserId: otherUserId},
					{userId: otherUserId, blockedUserId: currentUserId}
				]
			}
		})

		if (isBlocked){
			return reply.code(403).send({error: 'Cannot create conversation: user blocked'})
		}

		const [user1Id, user2Id] = currentUserId < otherUserId ? [currentUserId,otherUserId] : [otherUserId, currentUserId];

		let conversation = await Conversation.findOne({
			where: {user1Id, user2Id},
			include: [
				{model: User, as: 'User1', attributes: ['id', 'username', 'displayName', 'avatar']},
				{model: User, as: 'User2', attributes: ['id', 'username', 'displayName', 'avatar']}
			]
		});

		if (!conversation){
			conversation = await Conversation.create({user1Id, user2Id});

			conversation = await Conversation.findByPk(conversation.id, {
                include: [
                    { model: User, as: 'User1', attributes: ['id', 'username', 'displayName', 'avatar'] },
                    { model: User, as: 'User2', attributes: ['id', 'username', 'displayName', 'avatar'] }
                ]
            });
			const io = req.server.io;
            io.to(user1Id).emit('chatNewConversation', { conversation });
            io.to(user2Id).emit('chatNewConversation', { conversation });
		}
		return reply.send({ 
            success: true, 
            conversation,
            message: 'Conversation ready'
        });

	}catch(error){
		return reply.code(500).send({error: 'Sever error: Could not create a conversation'})
	}
}

export async function getConversations(req, reply){
	try{
		const currentUserId = req.user.id;

		const conversations = await Conversation.findAll({
			where: {
				[Op.or]: [
					{user1Id: currentUserId},
					{user2Id: currentUserId}
				]
			},
			include: [
				{ model: User, as: 'User1', attributes: ['id', 'username', 'displayName','avatar','email','losses','wins'] },
				{ model: User, as: 'User2', attributes: ['id', 'username', 'displayName','avatar','email','losses','wins'] }
			],
			order: [['lastMessageAt', 'DESC']]
		})
		return reply.send({
			success: true,
			conversations
		})
	}catch(error){
		return reply.code(500).send({error: 'Failed to get conversations'})
	}
}

export async function getConversationById(req, reply) {
    try {
        const { id } = req.params;
        const currentUserId = req.user.id;
        const conversation = await Conversation.findOne({
            where: {
                id,
                [Op.or]: [
                    { user1Id: currentUserId },
                    { user2Id: currentUserId }
                ]
            },
            include: [
                { model: User, as: 'User1', attributes: ['id', 'username', 'displayName', 'avatar','email','losses','wins'] },
                { model: User, as: 'User2', attributes: ['id', 'username', 'displayName', 'avatar','email','losses','wins'] }
            ]
        });
        if (!conversation) {
            return reply.code(404).send({ error: 'Conversation not found' });
        }
        return reply.send({
			success:true,
			conversation });
    } catch (error) {
        return reply.code(500).send({ error: 'Failed to get conversation' });
    }
}

export async function deleteConversation(req, reply){
	try{
		const currentUserId = req.user.id;
		const {id} = req.params;

		const conversation = await Conversation.findOne({
			where: {
				id,
				[Op.or]:[
					{user1Id: currentUserId},
					{user2Id: currentUserId},
				]
			}
		})
		if (!conversation){
			return reply.code(404).send({error:'Conversation not found'})
		}
		const user1Id = conversation.user1Id;
        const user2Id = conversation.user2Id;

		const sequelize = Conversation.sequelize;
		await sequelize.transaction(async (t) => {
			await Message.destroy({where: {conversationId:id},transaction: t});
			await conversation.destroy({transaction: t});
		})

		const io = req.server.io;
        io.to(user1Id).emit('chatConversationDeleted', { conversationId: Number(id) });
        io.to(user2Id).emit('chatConversationDeleted', { conversationId: Number(id) });

		return reply.send({success:true, message: 'Conversation deleted'})
	}catch(error){
		return reply.code(500).send({error: error.message || String(error)})
	}
}

export async function sendMessage(req, reply){

	try{
		const currentId = req.user.id;
		const {conversationId} = req.params;
		const {message} = req.body;

		if (!message || message.trim() === '') {
            return reply.code(400).send({error: 'Message cannot be empty'});
        }

		const conversation = await Conversation.findOne({
			where:{
				id: conversationId, 
				[Op.or]: [
					{user1Id: currentId},
					{user2Id: currentId}
				]}
		})

		if (!conversation)
		{
			return reply.code(403).send({error: 'The user does not participate in this conversation'})
		}
		const newMessage = await Message.create({
			conversationId,
			senderId: currentId,
			message: message.trim()
		})
		await conversation.update({lastMessageAt: new Date()});

		const fullMessage = await Message.findByPk(newMessage.id, {
			include: { model: User, as: 'Sender', attributes: ['username', 'displayName'] }
		});
		const io = req.server.io;
        io.to(conversation.user1Id).emit('chatMessage', { conversationId, message: fullMessage });
        io.to(conversation.user2Id).emit('chatMessage', { conversationId, message: fullMessage });

		return reply.send({
			success:true,
			message: fullMessage
		})
	}catch(error){
		return reply.code(500).send({error: 'Failed to send message'});
	}
}

export async function getMessages(req, reply){
	try{
		const currentUserId = req.user.id;
		const {conversationId} = req.params;

		const {page = 1, limit = 20} = req.query;

		const pageNum = parseInt(page);
		const limitNum = parseInt(limit);

		if (pageNum < 1 || limitNum < 1 || limitNum > 100){
			return reply.code(400).send({
				error: 'Invalid page or limit. Page must be >= 1, limit must be 1-100'
			})
		}

		const offset = (pageNum - 1) * limitNum;

		const conversation = await Conversation.findOne({
			where: {
				id: conversationId,
				[Op.or]: [
					{user1Id: currentUserId},
					{user2Id: currentUserId}
				]
			}
		});
		if (!conversation){
			return reply.code(403).send({
				error: 'Not authorized for this conversation '
			})
		}

		const messages = await Message.findAll({
			where: {conversationId},
			include: {
				model:User,
				as: 'Sender',
				attributes: ['username', 'displayName']
			},
			order: [['createdAt', 'ASC']],
			limit: limitNum,
			offset: offset
		});

		const hasMore = messages.length === limitNum;
		return reply.send({
			success:true,
			messages: messages,
			pagination: {
				page: pageNum,
				limit: limitNum,
				hasMore: hasMore,
			}
		})

	}catch(error){
		return reply.code(500).send({error: 'Failed to get messages'})
	}
}; 

export async function blockUser(req, reply){
	try{
		const currentUserId = req.user.id;
		const {userId} = req.body;

		if (!userId){
			return reply.code(400).send({error: 'userId is required'})
		}
		if (userId === currentUserId)
		{
			return reply.code(400).send({error: 'You cannot block yourself'})
		}

		const userToBlock = await User.findOne({
			where:{
				id: userId
			}
		})

		if (!userToBlock)
		{
			return reply.code(400).send({error: 'The user to block does not exist'})
		}

		const checkBlocked = await BlockedUsers.findOne({
			where:{
				userId: currentUserId,
				blockedUserId: userId,
			}
		})

		if (checkBlocked){
			return reply.code(400).send({error: 'Cannot block a blocked user'})
		}

		await BlockedUsers.create({
			userId: currentUserId,
			blockedUserId: userId
		})

		const io = req.server.io;
        io.to(currentUserId).emit('chatBlocked', { blockedUserId: userId });
        io.to(userId).emit('chatBlocked', { blockedById: currentUserId });

		return reply.send({
			success: true,
			message: 'User blocked successfully'
		});
	}catch(error){
		return reply.code(500).send({error: 'Failed to block user'})
	}
};

export async function getBlockedUsers(req, reply){
    try{
        const currentUserId = req.user.id;
        const userId = req.query.userId ? parseInt(req.query.userId) : currentUserId;
        const blockedUsers = await BlockedUsers.findAll({
            where:{
                userId: userId
            },
            include: {
                model: User,
                as: 'Blocked',
                attributes: ['id', 'username','displayName']
            }
        })

        return reply.send({
            success: true,
            blockedUsers
        })
    }catch(error){
        return reply.code(500).send({error: 'Failed to get blocked users'})
    }
}

export async function getBlockedByUsers(req, reply) {
    try {
        const currentUserId = req.user.id;
        const blockedBy = await BlockedUsers.findAll({
            where: { blockedUserId: currentUserId },
            include: {
                model: User,
                as: 'User',
                attributes: ['id', 'username', 'displayName']
            }
        });
        return reply.send({
            success: true,
            blockedByUsers: blockedBy.map(b => b.userId)
        });
    } catch (error) {
        return reply.code(500).send({ error: 'Failed to get blocked-by users' });
    }
}

export async function unblockUser(req, reply) {
    try {
        const currentUserId = req.user.id;
        const { userId } = req.body;

        if (!userId) {
            return reply.code(400).send({ error: 'userId is required' });
        }

        const blocked = await BlockedUsers.findOne({
            where: {
                userId: currentUserId,
                blockedUserId: userId
            }
        });

        if (!blocked) {
            return reply.code(404).send({ error: 'User is not blocked' });
        }

        await blocked.destroy();

		const io = req.server.io;
        io.to(currentUserId).emit('chatUnblocked', { unblockedUserId: userId });
        io.to(userId).emit('chatUnblocked', { unblockedById: currentUserId });
		
        return reply.send({ success: true, message: 'User unblocked successfully' });
    } catch (error) {
        return reply.code(500).send({ error: error.message || 'Failed to unblock user' });
    }
}