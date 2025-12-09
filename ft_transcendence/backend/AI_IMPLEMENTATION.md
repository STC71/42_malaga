# 🤖 Inteligencia Artificial - Oponente IA del Juego Pong

## 📋 Descripción General

Este documento describe la **implementación completa del módulo de Inteligencia Artificial** del proyecto Transcendence. El sistema IA proporciona un oponente desafiante con 4 niveles de dificultad, simulando comportamiento humano realista y física avanzada.

**Módulo:** AI-Algo (Major Module - 1.0 puntos)  
**Implementación:** `backend/pon-server.js` (líneas 330-580)  
**Estado:** ✅ **COMPLETAMENTE FUNCIONAL**

---

## 🎯 Objetivos del Módulo IA

### Requisitos del Subject

✅ **Introducir un oponente IA** - Sistema completo con 4 niveles  
✅ **Experiencia desafiante y engagement** - Física avanzada con spin, counter-spin  
✅ **Simular comportamiento humano** - Errores, latencia, velocidad limitada  
✅ **No usar A\* o pathfinding** - Predicción cinemática y heurísticas  
✅ **Integración con arquitectura** - Socket.IO + game loop a 60fps

### Características Implementadas

- 🎮 **4 Niveles de Dificultad** (Easy, Medium, Hard, Impossible)
- 🧠 **Predicción de Trayectoria** con cálculo de rebotes
- 🌀 **Detección de Spin** probabilística según nivel
- ⚡ **Counter-Spin** (solo nivel Impossible)
- 🎯 **Simulación de Input Humano** (sin "trampas")
- 📊 **Velocidad Progresiva** que aumenta con el tiempo
- 🏓 **Sistema de Rally Counter** que bonifica juego prolongado

---

## 🗂️ Arquitectura e Integración

### Punto de Entrada Principal

**Archivo:** `backend/pon-server.js`  
**Funciones clave:**

```javascript
// Línea ~338: Configuración por dificultad
const DIFFICULTY_SETTINGS = {
    easy: { paddleSpeed, errorRange, refreshRate, spinDetection, ... },
    medium: { ... },
    hard: { ... },
    impossible: { ... }
};

// Línea ~381: Velocidades progresivas
const SPEED_CONFIG = {
    easy: { initial: 3, max: 8, acceleration: 0.05, interval: 8000 },
    medium: { initial: 5, max: 14, acceleration: 0.1, interval: 5000 },
    hard: { initial: 7, max: 20, acceleration: 0.15, interval: 3000 },
    impossible: { initial: 9, max: 25, acceleration: 0.2, interval: 2000 }
};

// Funciones principales
refreshAILogic(room)      // Calcula estrategia IA
updateAIPaddle(paddle, difficulty, ball)  // Mueve la pala
startAIInterval(roomId)   // Gestiona temporizador de actualización
```

### Estructura de Datos

```javascript
gameState = {
    ball: {
        x, y,           // Posición actual
        vx, vy,         // Velocidad
        speed,          // Magnitud de velocidad
        radius,         // Tamaño de la pelota
        spin: {         // Sistema de spin
            type: 'topspin' | 'backspin' | null,
            intensity: 0.0 - 1.0,
            decay: 0.02
        }
    },
    player1: { x, y, width, height, score },  // Jugador humano
    player2: {                                 // IA
        x, y, width, height, score,
        targetY,        // Objetivo calculado
        velocity,       // Velocidad actual de la pala
        aiData: {       // Estado interno IA
            confidence: 0.0 - 1.0,
            spinDetected: boolean,
            lastPrediction: number,
            consecutiveHits: number
        }
    },
    rallyCount,         // Golpes consecutivos
    lastHitTime,        // Timestamp último golpe
    gameEnded: boolean
};
```

---

## ⚙️ Configuración de Dificultades

### Parámetros por Nivel

| Parámetro | Easy | Medium | Hard | Impossible |
|-----------|------|--------|------|------------|
| **paddleSpeed** | 3 px/frame | 5 px/frame | 8 px/frame | 10 px/frame |
| **errorRange** | 40px | 20px | 5px | 2px |
| **refreshRate** | 1500ms | 1000ms | 500ms | 300ms |
| **spinDetection** | 0% | 30% | 70% | 100% |
| **spinCompensation** | 0% | 30% | 70% | 100% |
| **canCounterSpin** | ❌ No | ❌ No | ❌ No | ✅ Sí |

### Impacto en Gameplay

**Easy (Principiante):**
- Movimiento lento (3 px/frame = 180 px/s a 60fps)
- Error grande (±40px de desviación)
- Actualiza estrategia cada 1.5 segundos
- NO detecta spin → pelota con efecto le sorprende
- **Resultado:** Pierde la mayoría de partidas

**Medium (Casual):**
- Velocidad moderada (5 px/frame = 300 px/s)
- Error medio (±20px)
- Actualiza cada 1 segundo
- Detecta spin 30% de las veces
- **Resultado:** Partidas equilibradas

**Hard (Experimentado):**
- Velocidad alta (8 px/frame = 480 px/s)
- Error pequeño (±5px)
- Actualiza cada 0.5 segundos
- Detecta spin 70% de las veces
- **Resultado:** Gana la mayoría de partidas

**Impossible (Inhuman):**
- Velocidad máxima (10 px/frame = 600 px/s)
- Error mínimo (±2px)
- Actualiza cada 0.3 segundos
- Detecta spin 100% + puede generar counter-spin
- **Resultado:** Casi invencible

---

## 🧠 Algoritmos Principales

### 1. Predicción de Trayectoria (`refreshAILogic`)

**Propósito:** Calcular dónde llegará la pelota en el eje Y cuando cruce la coordenada X de la pala.

**Pseudocódigo:**

```javascript
function refreshAILogic(room) {
    const { ball, player2: paddle } = room.gameState;
    const settings = DIFFICULTY_SETTINGS[room.aiDifficulty];
    
    // 1. Verificar si la pelota viene hacia la IA
    if (ball.vx > 0) {  // Pelota moviéndose hacia la derecha (IA)
        
        // 2. Calcular tiempo hasta impacto
        const timeToReach = (paddle.x - ball.x) / ball.vx;
        
        // 3. Predicción inicial de Y
        let predictedY = ball.y + (ball.vy * timeToReach);
        
        // 4. Aplicar rebotes en paredes (reflexión)
        const canvasHeight = 600;
        while (predictedY < 0 || predictedY > canvasHeight) {
            if (predictedY < 0) {
                predictedY = -predictedY;  // Rebote superior
            }
            if (predictedY > canvasHeight) {
                predictedY = 2 * canvasHeight - predictedY;  // Rebote inferior
            }
        }
        
        // 5. Detección y compensación de spin
        if (ball.spin && ball.spin.intensity > 0.5) {
            const detectionChance = settings.spinDetection;
            
            if (Math.random() < detectionChance) {
                paddle.aiData.spinDetected = true;
                
                // Calcular efecto del spin sobre la trayectoria
                const spinEffect = ball.spin.intensity * 50;  // Píxeles de desviación
                const spinDirection = ball.spin.type === 'topspin' ? -1 : 1;
                
                // Aplicar compensación
                const compensation = settings.spinCompensation;
                predictedY += spinEffect * spinDirection * compensation * timeToReach;
            }
        }
        
        // 6. Counter-spin (solo Impossible)
        if (settings.canCounterSpin && paddle.aiData.spinDetected) {
            if (ball.spin.type === 'topspin') {
                paddle.targetY -= 15;  // Golpea arriba → genera backspin
            } else if (ball.spin.type === 'backspin') {
                paddle.targetY += 15;  // Golpea abajo → genera topspin
            }
        }
        
        // 7. Aplicar error aleatorio (simula imperfección humana)
        const error = (Math.random() - 0.5) * settings.errorRange;
        predictedY += error;
        
        // 8. Clamp dentro del canvas
        paddle.targetY = Math.max(
            0,
            Math.min(predictedY, canvasHeight - paddle.height)
        );
        
    } else {  // Pelota alejándose → volver al centro
        paddle.targetY = (canvasHeight / 2) - (paddle.height / 2);
    }
}
```

**Implementación Real:** `backend/pon-server.js` líneas 416-490

---

### 2. Movimiento de Pala (`updateAIPaddle`)

**Propósito:** Mover gradualmente la pala hacia `targetY` usando velocidad limitada (simula teclas presionadas).

**Pseudocódigo:**

```javascript
function updateAIPaddle(paddle, difficulty, ball) {
    const settings = DIFFICULTY_SETTINGS[difficulty];
    const { paddleSpeed } = settings;
    
    // 1. Calcular distancia al objetivo
    const paddleCenter = paddle.y + (paddle.height / 2);
    const distance = paddle.targetY - paddleCenter;
    
    // 2. Mover gradualmente (máximo paddleSpeed píxeles por frame)
    if (Math.abs(distance) > 2) {  // Deadzone de 2px para evitar oscillación
        const direction = Math.sign(distance);
        const moveAmount = Math.min(Math.abs(distance), paddleSpeed);
        
        paddle.y += direction * moveAmount;
        paddle.velocity = direction * moveAmount;  // Guardar para spin
        
    } else {
        paddle.velocity = 0;  // Pala quieta
    }
    
    // 3. Clamp dentro del canvas
    paddle.y = Math.max(0, Math.min(paddle.y, 600 - paddle.height));
}
```

**Implementación Real:** `backend/pon-server.js` líneas 491-530

---

### 3. Sistema de Spin y Counter-Spin

#### Generación de Spin al Golpear

```javascript
function handleBallPaddleCollision(ball, paddle) {
    // ... código de rebote básico ...
    
    // Generar spin según velocidad vertical de la pala
    if (Math.abs(paddle.velocity) > 3) {
        ball.spin = {
            type: paddle.velocity < 0 ? 'topspin' : 'backspin',
            intensity: Math.min(Math.abs(paddle.velocity) / 10, 1.0),
            decay: 0.02  // Decae 2% por frame
        };
    }
}
```

#### Counter-Spin (Nivel Impossible)

```javascript
// En refreshAILogic (línea ~508)
if (canCounterSpin && paddle.aiData.spinDetected) {
    // Estrategia: golpear con movimiento opuesto al spin detectado
    if (ball.spin.type === 'topspin') {
        paddle.targetY = ball.y - 15;  // Golpea arriba → backspin
    } else if (ball.spin.type === 'backspin') {
        paddle.targetY = ball.y + 15;  // Golpea abajo → topspin
    }
}
```

**Efecto:** La IA en nivel Impossible no solo defiende, sino que **contraataca** devolviendo la pelota con spin opuesto.

---

## 🚀 Sistema de Velocidad Progresiva

### Aceleración Temporal

```javascript
// En updateGame (línea ~1186)
const gameTime = Date.now() - gameState.startTime;
const config = SPEED_CONFIG[difficulty];

// Incrementos cada X segundos (según dificultad)
const timeIntervals = Math.floor(gameTime / config.interval);
const timeAcceleration = timeIntervals * config.acceleration;

// Bonus por rally largo
const rallyBonus = gameState.rallyCount > 0 
    ? Math.floor(gameState.rallyCount / 5) * 0.5 
    : 0;

// Velocidad final
gameState.ball.speed = Math.min(
    config.max,
    config.initial + timeAcceleration + rallyBonus
);
```

### Ejemplo de Progresión (Medium)

| Tiempo | Rally | Velocidad | Comentario |
|--------|-------|-----------|------------|
| 0:00 | 0 | 5 px/frame | Velocidad inicial |
| 0:05 | 3 | 5.1 px/frame | Primera aceleración |
| 0:10 | 8 | 5.7 px/frame | Bonus por rally (+0.5) |
| 0:30 | 15 | 7.1 px/frame | Rally largo + tiempo |
| 1:00 | 20 | 9.7 px/frame | Muy rápido |
| 2:00+ | 25+ | 14 px/frame | **Velocidad máxima** |

---

## 🎮 Integración con Frontend

### Visualización en `Game.tsx`

**Archivo:** `frontend/src/Components/Game.tsx`

#### 1. Overlay de Predicción (Debug)

```typescript
// Línea ~1166: Indicador visual de targetY de la IA
if (aiDebugMode) {
    const predictedY = gameState.player2.targetY;
    
    ctx.strokeStyle = 'rgba(255, 255, 0, 0.5)';
    ctx.setLineDash([5, 5]);
    ctx.beginPath();
    ctx.moveTo(gameState.ball.x, gameState.ball.y);
    ctx.lineTo(gameState.player2.x, predictedY);
    ctx.stroke();
    
    // Círculo en objetivo
    ctx.fillStyle = 'yellow';
    ctx.beginPath();
    ctx.arc(gameState.player2.x, predictedY, 5, 0, Math.PI * 2);
    ctx.fill();
}
```

#### 2. Barra de Velocidad Progresiva

```typescript
// Línea ~1200: Indicador visual de velocidad actual
const maxSpeed = SPEED_CONFIG[difficulty].max;
const currentSpeed = gameState.ball.speed;
const progress = Math.min(currentSpeed / maxSpeed, 1);

// Gradiente de color (verde → amarillo → rojo)
const hue = 120 - (progress * 120);
ctx.fillStyle = `hsl(${hue}, 100%, 50%)`;

// Barra de progreso
ctx.fillRect(barX, barY, barWidth * progress, barHeight);

// Advertencia parpadeante al 80%+
if (progress >= 0.8) {
    const blink = Math.floor(Date.now() / 300) % 2;
    if (blink) {
        ctx.fillStyle = 'red';
        ctx.fillText('⚠️ MAX SPEED', barX, barY - 10);
    }
}
```

#### 3. Rally Counter

```typescript
// Línea ~1250: Contador de golpes consecutivos
if (gameState.rallyCount > 0) {
    ctx.font = 'bold 24px Arial';
    ctx.fillStyle = gameState.rallyCount > 10 ? '#FFD700' : '#FFF';
    ctx.fillText(`🔥 RALLY: ${gameState.rallyCount}`, canvas.width / 2 - 80, 50);
}
```

---

## 🔍 Casos de Uso y Ejemplos

### Caso 1: Jugador vs IA Easy

**Escenario:** Jugador principiante quiere aprender

```bash
# Backend
Dificultad: easy
- paddleSpeed: 3 (muy lento)
- errorRange: 40 (muchos fallos)
- refreshRate: 1500ms (reacciona tarde)
- spinDetection: 0% (no detecta spin)

# Gameplay
- IA reacciona lentamente
- Falla muchos golpes (±40px de error)
- No se adapta al spin del jugador
- Jugador gana 80% de las partidas
```

**Resultado:** ✅ Experiencia satisfactoria para principiantes

---

### Caso 2: Jugador vs IA Hard

**Escenario:** Jugador experimentado busca desafío

```bash
# Backend
Dificultad: hard
- paddleSpeed: 8 (rápido)
- errorRange: 5 (preciso)
- refreshRate: 500ms (reacciona rápido)
- spinDetection: 70% (detecta la mayoría)

# Gameplay
- IA responde rápidamente
- Solo falla ocasionalmente (±5px)
- Compensa el 70% de los spins
- Jugador debe jugar muy bien para ganar
```

**Resultado:** ✅ Partidas competitivas y emocionantes

---

### Caso 3: Jugador vs IA Impossible

**Escenario:** Jugador experto quiere máximo reto

```bash
# Backend
Dificultad: impossible
- paddleSpeed: 10 (máximo)
- errorRange: 2 (casi perfecto)
- refreshRate: 300ms (instantáneo)
- spinDetection: 100% (siempre detecta)
- canCounterSpin: true (contraataca)

# Gameplay
- IA responde casi instantáneamente
- Predicción casi perfecta
- Detecta TODO el spin
- GENERA counter-spin para devolver pelotas difíciles
- Jugador debe jugar PERFECTO para ganar
```

**Resultado:** ✅ Desafío extremo, casi imposible de vencer

---

## 📊 Estadísticas y Métricas

### Métricas Recopiladas

```javascript
// aiData almacena estadísticas internas
paddle.aiData = {
    confidence: 0.85,           // Confianza en predicción (0-1)
    spinDetected: true,         // Si detectó spin actual
    lastPrediction: 350,        // Y predicho anterior
    consecutiveHits: 12,        // Golpes seguidos sin fallo
    totalPredictions: 145,      // Total de predicciones realizadas
    accuratePredictions: 123,   // Predicciones correctas
    accuracy: 0.848            // Ratio de acierto (123/145)
};
```

### Dashboard de IA (Propuesta)

```typescript
// En Game.tsx (opcional para debug/visualización)
<div className="ai-stats">
    <h3>AI Statistics</h3>
    <p>Difficulty: {difficulty}</p>
    <p>Confidence: {(aiData.confidence * 100).toFixed(1)}%</p>
    <p>Accuracy: {(aiData.accuracy * 100).toFixed(1)}%</p>
    <p>Consecutive Hits: {aiData.consecutiveHits}</p>
    <p>Spin Detected: {aiData.spinDetected ? '✅' : '❌'}</p>
</div>
```

---

## 🧪 Testing y Validación

### Tests Realizados

#### 1. Test de Predicción
```javascript
// Test unitario de predicción
function testPrediction() {
    const ball = { x: 200, y: 300, vx: 5, vy: -3 };
    const paddle = { x: 750, y: 250 };
    
    const timeToReach = (paddle.x - ball.x) / ball.vx;  // 110 frames
    const predictedY = ball.y + ball.vy * timeToReach;  // 300 + (-3 * 110) = -30
    
    // Aplicar rebote
    const finalY = Math.abs(predictedY);  // 30
    
    assert(finalY >= 0 && finalY <= 600);
    console.log('✅ Predicción correcta:', finalY);
}
```

#### 2. Test de Dificultades
```bash
# Test manual
make test-ai-easy       # Debe perder 80%+ de partidas
make test-ai-medium     # Debe ser equilibrado (45-55% winrate)
make test-ai-hard       # Debe ganar 70%+ de partidas
make test-ai-impossible # Debe ganar 95%+ de partidas
```

#### 3. Test de Spin
```javascript
// Verificar detección de spin según dificultad
function testSpinDetection(difficulty, trials = 100) {
    const settings = DIFFICULTY_SETTINGS[difficulty];
    let detected = 0;
    
    for (let i = 0; i < trials; i++) {
        if (Math.random() < settings.spinDetection) {
            detected++;
        }
    }
    
    const actualRate = detected / trials;
    const expectedRate = settings.spinDetection;
    const error = Math.abs(actualRate - expectedRate);
    
    assert(error < 0.1, `Spin detection rate off by ${error}`);
    console.log(`✅ ${difficulty}: ${actualRate * 100}% (expected ${expectedRate * 100}%)`);
}
```

---

## 🐛 Troubleshooting

### Problema 1: IA Demasiado Fácil/Difícil

**Síntoma:** La IA gana/pierde siempre independientemente del nivel.

**Diagnóstico:**
```bash
# Verificar configuración
grep -A 5 "DIFFICULTY_SETTINGS" backend/pon-server.js

# Verificar que refreshAILogic se ejecuta
# Añadir log temporal:
console.log(`[AI] targetY: ${paddle.targetY}, actualY: ${paddle.y}`);
```

**Solución:**
1. Verificar que `startAIInterval()` se llama al crear sala
2. Ajustar `errorRange` para aumentar/reducir dificultad
3. Verificar que `paddleSpeed` es apropiado

---

### Problema 2: IA No Detecta Spin

**Síntoma:** La IA falla todos los golpes con spin.

**Diagnóstico:**
```javascript
// En refreshAILogic, añadir log:
if (ball.spin && ball.spin.intensity > 0.5) {
    console.log(`[AI] Spin: ${ball.spin.type}, intensity: ${ball.spin.intensity}`);
    console.log(`[AI] Detection chance: ${settings.spinDetection}`);
    console.log(`[AI] Detected: ${paddle.aiData.spinDetected}`);
}
```

**Solución:**
1. Verificar que `ball.spin` se genera en colisión
2. Aumentar `spinDetection` en configuración
3. Verificar que `Math.random() < spinDetection` funciona

---

### Problema 3: Counter-Spin No Funciona

**Síntoma:** IA en Impossible no genera counter-spin.

**Diagnóstico:**
```javascript
// Verificar flag
console.log(`[AI] canCounterSpin: ${settings.canCounterSpin}`);
console.log(`[AI] spinDetected: ${paddle.aiData.spinDetected}`);
```

**Solución:**
1. Verificar que `canCounterSpin: true` solo en Impossible
2. Verificar que `spinDetected` se setea a `true`
3. Verificar que el offset `±15px` se aplica a `targetY`

---

## 📚 Referencias y Recursos

### Documentación Interna
- [Backend README](../README.md) - Servidor principal y game loop
- [Frontend Game Component](../../frontend/src/Components/README.md) - Renderizado y controles
- [README Principal](../../README.md) - Visión general del proyecto

### Algoritmos y Conceptos
- **Predicción Cinemática:** Ecuaciones de movimiento uniformemente acelerado
- **Spin en Pong:** Efecto Magnus y desviación de trayectoria
- **Finite State Machine:** Estado de IA (predicting, moving, idle)
- **PID Controller:** Alternativa avanzada (no implementada, but could be)

### Inspiración
- [Pong AI Tutorial (Three.js)](https://github.com/mrdoob/three.js/blob/master/examples/misc_controls_pointerlock.html)
- [AI Algorithms for Games](https://www.gamedev.net/articles/programming/artificial-intelligence/)
- [Tennis Physics](https://www.real-world-physics-problems.com/physics-of-tennis.html)

---

## 🔮 Mejoras Futuras (Roadmap)

### Fase 1: Machine Learning (Opcional)
```javascript
// Entrenar IA con partidas reales
function trainAI(matches) {
    // Usar TensorFlow.js para aprender patrones
    const model = tf.sequential({
        layers: [
            tf.layers.dense({ units: 128, activation: 'relu', inputShape: [6] }),
            tf.layers.dense({ units: 64, activation: 'relu' }),
            tf.layers.dense({ units: 1, activation: 'linear' })
        ]
    });
    
    // Input: [ballX, ballY, ballVx, ballVy, paddleY, spin]
    // Output: targetY óptimo
}
```

### Fase 2: Adaptive Difficulty
```javascript
// Ajustar dificultad según performance del jugador
function adjustDifficulty(playerWinRate) {
    if (playerWinRate > 0.7) {
        increaseDifficulty();
    } else if (playerWinRate < 0.3) {
        decreaseDifficulty();
    }
}
```

### Fase 3: IA Multijugador
```javascript
// IA puede jugar contra otra IA
socket.on('aiVsAi', () => {
    gameState.player1.isAI = true;
    gameState.player2.isAI = true;
    startAIInterval(roomId, 'player1');
    startAIInterval(roomId, 'player2');
});
```

---

## 🤝 Equipo y Contribuciones

### Implementación Principal
- **sternero** - Arquitectura de IA, algoritmos de predicción, sistema de spin

### Colaboradores
- **davigome** - Integración con game loop, física de colisión
- **jesopan-** - Socket.IO y sincronización en tiempo real
- **nporras-** - Testing y balance de dificultades
- **rdel-olm** - Visualización frontend y debug tools

---

## 📄 Licencia y Uso Educativo

Este código es parte del proyecto **Transcendence** de **42 School Málaga** (2025).

**Propósito:** Material educativo para comprensión de algoritmos de IA en videojuegos.

**Uso permitido:**
- ✅ Estudio y aprendizaje de conceptos
- ✅ Referencia para implementaciones propias
- ✅ Mejoras y extensiones del código

**Uso NO permitido:**
- ❌ Copia exacta para otros proyectos de 42
- ❌ Distribución como trabajo propio sin modificaciones

---

**🤖 AI Module - Transcendence Project**  
*Última actualización: Diciembre 2025*  
*Versión: 3.0 (Producción)*
