# 💬 Chat - Componentes de Interfaz de Mensajería

## 📋 Descripción General

Este directorio contiene los componentes React especializados que conforman el sistema completo de chat en tiempo real de la aplicación. Implementa una interfaz de mensajería instantánea moderna con soporte para conversaciones privadas, bloqueo de usuarios y gestión de contactos.

## 🗂️ Estructura de Componentes

### Componentes Principales

#### `ChatMain.tsx`
**Propósito**: Componente contenedor principal que orquesta toda la interfaz de chat.

**Responsabilidades**:
- Gestiona el layout de dos paneles (sidebar + área de mensajes)
- Coordina la comunicación entre subcomponentes
- Mantiene el estado global del chat activo
- Maneja la selección de conversaciones

**Relación con el proyecto**: Punto de entrada principal invocado desde `Chat.tsx` del directorio padre.

---

#### `ChatSideBar.tsx`
**Propósito**: Panel lateral izquierdo con lista de conversaciones activas.

**Funcionalidades**:
- Muestra todas las conversaciones del usuario
- Indica mensajes no leídos con badges
- Permite búsqueda/filtrado de conversaciones
- Botón para iniciar nuevas conversaciones

**Comunicación**: Se conecta con el backend mediante Socket.IO para actualizaciones en tiempo real.

---

#### `ConversationList.tsx`
**Propósito**: Renderiza la lista scrollable de conversaciones en el sidebar.

**Características**:
- Muestra avatar, nombre y último mensaje de cada conversación
- Resalta la conversación actualmente seleccionada
- Formato de timestamps relativos ("hace 5 min", "ayer")
- Indicadores de estado online/offline

**Datos**: Consume el array de conversaciones del contexto `ComponentsContext`.

---

### Componentes de Mensajería

#### `MessagesList.tsx`
**Propósito**: Área principal que muestra el historial de mensajes de la conversación seleccionada.

**Implementación**:
- Auto-scroll al recibir mensajes nuevos
- Diseño tipo "burbuja" con alineación por emisor (izq/der)
- Lazy loading de mensajes antiguos al hacer scroll arriba
- Timestamps y confirmaciones de lectura

**Optimización**: Virtualización de lista para manejo eficiente de miles de mensajes.

---

#### `MessageInput.tsx`
**Propósito**: Campo de entrada para componer y enviar mensajes.

**Características**:
- Textarea con auto-expansión al escribir
- Botón de envío y soporte para Enter (Shift+Enter para salto de línea)
- Indicador "escribiendo..." que se emite a otros usuarios
- Preview de archivos adjuntos (si implementado)

**Validación**: Previene envío de mensajes vacíos o demasiado largos.

---

### Componentes de Gestión

#### `ChatHeader.tsx`
**Propósito**: Barra superior de la conversación activa.

**Muestra**:
- Avatar y nombre del usuario con quien se chatea
- Estado de conexión (online/offline/escribiendo)
- Botones de acción: perfil, bloquear, opciones

**Navegación**: Permite acceder al perfil del otro usuario mediante `ShowProfile.tsx`.

---

#### `NewChat.tsx`
**Propósito**: Modal/Panel para iniciar una nueva conversación.

**Proceso**:
1. Muestra lista de usuarios disponibles (amigos, conocidos)
2. Campo de búsqueda por nombre de usuario
3. Al seleccionar, crea conversación y redirige a ella

**API**: Llama a `POST /api/conversations/create` con el `otherUserId`.

---

#### `ShowProfile.tsx`
**Propósito**: Modal que muestra el perfil resumido del usuario con quien se chatea.

**Información Visible**:
- Avatar, nombre de usuario, displayName
- Estadísticas de juego (victorias, derrotas)
- Botón para ver perfil completo
- Opción para bloquear/desbloquear

**Integración**: Comparte lógica con `Profile.tsx` del directorio padre.

---

### Componentes de Seguridad

#### `BlockUser.tsx`
**Propósito**: Interface para bloquear a un usuario específico.

**Flujo**:
1. Confirmación mediante modal/diálogo
2. Llamada a API `POST /api/block`
3. Actualización inmediata del estado local
4. Oculta la conversación del sidebar

**Efecto**: El usuario bloqueado no puede enviar mensajes ni ver perfil.

---

#### `BlockedUsersList.tsx`
**Propósito**: Panel de gestión de usuarios bloqueados.

**Funcionalidades**:
- Lista completa de usuarios bloqueados
- Botón "Desbloquear" por cada entrada
- Búsqueda/filtrado de la lista
- Acceso desde Settings o desde el chat

**API**: Consume `GET /api/blocked-users` y `DELETE /api/blocked-users/:id`.

---

## 🔄 Flujo de Datos

```
Backend (chat.js)
    ↕️ Socket.IO (eventos: message, typing, read)
ComponentsContext.tsx (estado global)
    ↕️
ChatMain.tsx (orquestador)
    ├─→ ChatSideBar.tsx
    │       ├─→ ConversationList.tsx
    │       └─→ NewChat.tsx
    ├─→ ChatHeader.tsx
    │       └─→ ShowProfile.tsx
    ├─→ MessagesList.tsx
    └─→ MessageInput.tsx
```

## 🎨 Tecnologías y Patrones

- **React Hooks**: `useState`, `useEffect`, `useContext`, `useRef`
- **Context API**: Consume `AuthContext` y `ComponentsContext`
- **Socket.IO Client**: Para mensajería en tiempo real
- **TailwindCSS**: Estilizado mediante clases utility-first
- **TypeScript**: Tipado estricto mediante interfaces de `types.tsx`

## 🔗 Integración con el Backend

### Endpoints REST Utilizados

```typescript
POST   /api/conversations/create     // Crear conversación
GET    /api/conversations            // Listar conversaciones
GET    /api/messages/:conversationId // Obtener mensajes
POST   /api/messages                 // Enviar mensaje (REST fallback)
POST   /api/block                    // Bloquear usuario
GET    /api/blocked-users            // Listar bloqueados
DELETE /api/blocked-users/:userId    // Desbloquear
```

### Eventos Socket.IO

```typescript
// Emitidos por cliente
socket.emit('join-chat', conversationId)
socket.emit('send-message', { conversationId, text })
socket.emit('typing', { conversationId, isTyping })
socket.emit('read-messages', conversationId)

// Escuchados por cliente
socket.on('new-message', (message) => {...})
socket.on('user-typing', ({ userId, isTyping }) => {...})
socket.on('messages-read', ({ conversationId, readBy }) => {...})
```

## 📦 Dependencias Externas

- `socket.io-client`: Conexión WebSocket bidireccional
- `react-icons`: Iconografía (mensajes, notificaciones)
- `date-fns` o `dayjs`: Formateo de timestamps (si usado)

## 🧪 Testing y Validación

Para probar estos componentes:

```bash
# 1. Asegurar backend corriendo
cd backend && npm start

# 2. Login con dos usuarios diferentes en navegadores distintos
# 3. Usuario A inicia conversación con Usuario B
# 4. Enviar mensajes bilateralmente
# 5. Probar bloqueo y verificar que se deshabilita el chat
# 6. Desbloquear y verificar restauración
```

## 🛡️ Seguridad

- **Validación de entrada**: Sanitización de texto para prevenir XSS
- **Autenticación requerida**: Todos los endpoints verifican JWT token
- **Bloqueo bidireccional**: Usuario bloqueado no puede interactuar
- **Rate limiting**: Backend previene spam de mensajes

## 🚀 Mejoras Futuras

- [ ] Soporte para mensajes multimedia (imágenes, GIFs)
- [ ] Reacciones a mensajes (emojis)
- [ ] Mensajes de audio/video llamadas
- [ ] Cifrado end-to-end
- [ ] Salas de chat grupales
- [ ] Respuesta a mensajes específicos (threading)

---

**Ubicación**: `/frontend/src/Components/Chat/`  
**Documentación relacionada**: Ver `Chat.tsx` (padre), `chat.js` (backend), `ComponentsContext.tsx`
