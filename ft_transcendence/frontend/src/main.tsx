import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.css'
import App from './App' // Mantenemos .jsx hasta que migremos App
import './utils/globalKeyboardReloadBlocker';
const rootElement = document.getElementById('root')

if (!rootElement) {
  throw new Error('Root element not found. Make sure there is an element with id="root" in your HTML.')
}

createRoot(rootElement).render(
  <StrictMode>
    <App />
  </StrictMode>
)