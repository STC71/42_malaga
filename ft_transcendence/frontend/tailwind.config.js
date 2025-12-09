/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,jsx,ts,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        'pong-green': '#00ff00',
        'pong-dark': '#0a0a0a',
        'pong-gray': '#1a1a1a',
      },
      keyframes: {
        glow: {
          '0%, 100%': {
            color: '#ff9800',
            'text-shadow': '0 0 8px #ff9800, 0 0 16px #ff9800',
          },
          '50%': {
            color: '#ff1744',
            'text-shadow': '0 0 8px #ff1744, 0 0 16px #ff1744',
          },
        },
      },
      animation: {
        glow: 'glow 1.5s infinite alternate',
      },
    },
  },
  plugins: [],
}
