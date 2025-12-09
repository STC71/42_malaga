import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import checker from 'vite-plugin-checker'
import 'dotenv/config'


const host = '0.0.0.0'
// https://vite.dev/config/
export default defineConfig({
  plugins: [
		react(),
		checker({
      typescript: true,
    })
	],

  server: {
    // run Vite on the same port the backend expects for Socket.IO origin
    host,
    port: 2323,
    proxy: {
      // forward API requests to the backend
      '/api': {
        target: `http://${host}:3000`,
        changeOrigin: true,
        secure: false,
      },
      // sometimes auth endpoints are under /auth
      '/auth': {
        target: `http://${host}:3000`,
        changeOrigin: true,
        secure: false,
      }
    }
  }
})
