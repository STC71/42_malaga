import Fastify from 'fastify';
import dotenv from 'dotenv';
import path from 'path';
import { initializeDatabase, User } from './db.js';

// Load env from secrets/.env in project root (robust when running from repo root)

dotenv.config({ path: path.resolve(process.cwd(), 'srcs', 'secrets', '.env') });


const fastify = Fastify();

fastify.get('/healthz', async () => 'ok');

// Endpoint to anonymize a user (for demo, by id param)
fastify.post('/api/user/:id/anonymize', async (request, reply) => {
  const { id } = request.params;
  const user = await User.findByPk(id);
  if (!user) return reply.code(404).send({ error: 'User not found' });

  user.username = `anon${id}`;
  user.email = `anon${id}@example.com`;
  user.displayName = 'Anonymous';
  user.avatar = '';
  user.providerId = null;

  await user.save();

  return { message: 'User data anonymized' };
});

// Minimal endpoint to create a user (for testing)
fastify.post('/api/user', async (request, reply) => {
  const { username, email, displayName } = request.body;
  const created = await User.create({ username, email, displayName });
  return { id: created.id };
});

const PORT = process.env.PORT || 3000;

// Ensure DB is initialized before listening
initializeDatabase({ force: false, alter: true })
  .then(() => {
    fastify.listen({ port: PORT, host: '0.0.0.0' }, err => {
      if (err) throw err;
      console.log(`Fastify backend listening on port ${PORT}`);
    });
  })
  .catch(err => {
    console.error('Failed to initialize database', err);
    process.exit(1);
  });
