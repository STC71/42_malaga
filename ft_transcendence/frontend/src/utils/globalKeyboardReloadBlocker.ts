
class GlobalKeyboardReloadBlocker {
  private lastReloadAttempt: number = 0;
  private readonly BLOCK_DURATION = 1000; // 1 segundo de bloqueo
  private isBlocked: boolean = false;
  private blockTimer: ReturnType<typeof setTimeout> | null = null;
  private activeKeys: Map<string, boolean> = new Map(); // ✅ Cambio: usar Map en lugar de Set

  constructor() {
    this.init();
  }

  private init() {
    this.interceptKeyboard();
    this.handleKeyUp();
  }

  private interceptKeyboard() {
    document.addEventListener('keydown', (e: KeyboardEvent) => {
      // ✅ Detectar F5 o Ctrl+R / Cmd+R
      const isF5 = e.key === 'F5';
      const isCtrlR = (e.ctrlKey || e.metaKey) && e.key === 'r';
      
      if (!isF5 && !isCtrlR) return;

      // ✅ CLAVE 1: Si es un evento repetido (tecla sostenida), BLOQUEAR SIEMPRE
      if (e.repeat) {
        e.preventDefault();
        e.stopImmediatePropagation();
        return false;
      }

      // ✅ Crear identificador único
      const keyId = isF5 ? 'F5' : 'Ctrl+R';

      // ✅ CLAVE 2: Si ya procesamos esta combinación (backup por si repeat no funciona), BLOQUEAR
      if (this.activeKeys.has(keyId)) {
        e.preventDefault();
        e.stopImmediatePropagation();
        return false;
      }

      const now = Date.now();
      const timeSinceLastAttempt = now - this.lastReloadAttempt;

      // Si está bloqueado por tiempo, prevenir completamente
      if (this.isBlocked) {
        const remaining = Math.ceil((this.BLOCK_DURATION - timeSinceLastAttempt) / 1000);
        e.preventDefault();
        e.stopImmediatePropagation();
        return false;
      }

      // ✅ Primera presión válida: permitir reload y marcar como activa
      this.lastReloadAttempt = now;
      this.activeKeys.set(keyId, true); // ✅ Marcar como activa
      this.activateBlock();

      // NO prevenir este reload (permitir que se ejecute)

    }, { 
      capture: true,
      passive: false
    });

  }

  // ✅ Limpiar teclas cuando se sueltan
  private handleKeyUp() {
    document.addEventListener('keyup', (e: KeyboardEvent) => {
      // Limpiar F5
      if (e.key === 'F5') {
        this.activeKeys.delete('F5');
      }
      
      // Limpiar Ctrl+R cuando se suelta Ctrl, Meta o R
      if (e.key === 'Control' || e.key === 'Meta' || e.key === 'r') {
        this.activeKeys.delete('Ctrl+R');
      }
    }, { capture: true });
  }

  private activateBlock() {
    this.isBlocked = true;
    
    if (this.blockTimer) {
      clearTimeout(this.blockTimer);
    }

    this.blockTimer = setTimeout(() => {
      this.isBlocked = false;
    }, this.BLOCK_DURATION);
  }

  public reset() {
    this.isBlocked = false;
    this.lastReloadAttempt = 0;
    this.activeKeys.clear();
    if (this.blockTimer) {
      clearTimeout(this.blockTimer);
      this.blockTimer = null;
    }
  }

  public setBlockDuration(ms: number) {
    if (ms < 100 || ms > 10000) {
      console.warn('Block duration debe estar entre 100ms y 10000ms');
      return;
    }
  }
}

// Crear instancia global única
export const globalKeyboardReloadBlocker = new GlobalKeyboardReloadBlocker();
export default globalKeyboardReloadBlocker;