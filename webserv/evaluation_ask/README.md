# 📚 EVALUATION ASK - PREGUNTAS Y RESPUESTAS DE EVALUACIÓN

Esta carpeta contiene documentación detallada con **preguntas típicas de evaluación** y **respuestas preparadas** para el proyecto webserv de 42 School.

## 📋 **CONTENIDO DE LA CARPETA**

### 🎯 **PREGUNTAS FUNDAMENTALES (1-9)**

| 📄 Archivo                    | 🎯 Pregunta de Evaluación                                      | ⚠️ Criticidad  |
|-------------------------------|----------------------------------------------------------------|----------------|
| **ask_1_http_server.md**      | *"Explain the basics of an HTTP server"*                       | 📍 Fundamental |
| **ask_2_io_multiplexing.md**  | *"What function are you using for I/O multiplexing?"*          | 🔥 Importante  |
| **ask_3_select_work.md**      | *"How does select() work?"*                                    | 🔥 Importante  |
| **ask_4_select_managed.md**   | *"How is select() managed in your server?"*                    | 🔥 Importante  |
| **ask_5_select_main.md**      | *"Is select() in main loop checking read/write AT SAME TIME?"* | 🚨 **CRÍTICO** |
| **ask_6_read_write.md**       | *"Only one read/write per client per select()"*                | 🚨 **CRÍTICO** |
| **ask_7_socket_and_check.md** | *"Error handling for socket operations"*                       | 🔥 Importante  |
| **ask_8_errno.md**            | *"Is errno checked after read/recv/write/send?"*               | 🚨 **CRÍTICO** |
| **ask_9_through_select.md**   | *"Does all I/O go through select()?"*                          | 🚨 **CRÍTICO** |

## 🚨 **PREGUNTAS CRÍTICAS (ELIMINATORIAS)**

### ❌ **NOTA 0 si fallan:**

1. **📄 ask_5_select_main.md** - Select() debe estar en main loop
2. **📄 ask_6_read_write.md** - Solo un read/write por cliente por select()
3. **📄 ask_8_errno.md** - Prohibido usar errno después de socket operations
4. **📄 ask_9_through_select.md** - Todo I/O debe pasar por select()

## 📖 **CÓMO USAR ESTA DOCUMENTACIÓN**

### 👨‍🎓 **Para Estudiantes:**
```bash
# Leer antes de la evaluación
cat ask_1_http_server.md
cat ask_2_io_multiplexing.md
# ... etc

# Practicar respuestas en voz alta
# Memorizar conceptos clave
# Revisar implementación en código
```

### 👨‍🏫 **Para Evaluadores:**
```bash
# Usar como guía de preguntas
# Verificar respuestas contra documentación
# Enfocar en puntos críticos
# Usar comandos de verificación incluidos
```

## 🎯 **ESTRUCTURA DE CADA DOCUMENTO**

Cada archivo `.md` contiene:

### 📋 **Secciones Estándar:**
- **🎯 OBJETIVO**: Qué pregunta responde específicamente
- **✅ RESPUESTA PREPARADA**: Respuesta completa y estructurada
- **🔍 VERIFICACIÓN**: Comandos para demostrar la implementación
- **💻 CÓDIGO RELEVANTE**: Snippets del código que demuestra el punto
- **⚠️ PUNTOS CRÍTICOS**: Aspectos eliminatorios si aplica
- **🎓 NOTAS ADICIONALES**: Información complementaria para el evaluador

### 🌈 **Código de Colores:**
- 🚨 **Rojo**: Puntos críticos/eliminatorios
- 🔥 **Naranja**: Muy importante
- 📍 **Azul**: Fundamental
- ✅ **Verde**: Verificaciones y respuestas correctas
- 💻 **Gris**: Código y comandos

## 🎓 **TIPS DE PREPARACIÓN**

### 📚 **Estudio Recomendado:**
1. **Leer todos los documentos** en orden numérico
2. **Practicar respuestas** en voz alta
3. **Memorizar conceptos clave** de puntos críticos
4. **Ejecutar comandos** de verificación en tu código
5. **Revisar implementación** contra respuestas preparadas

### ⏰ **Tiempo de Preparación:**
- **Lectura completa**: ~45 minutos
- **Práctica oral**: ~30 minutos
- **Verificación código**: ~15 minutos
- **Total recomendado**: **1.5 horas**

## 🔍 **VERIFICACIÓN RÁPIDA**

### ✅ **Checklist Pre-Evaluación:**
- [ ] He leído ask_5_select_main.md (CRÍTICO)
- [ ] He leído ask_6_read_write.md (CRÍTICO)
- [ ] He leído ask_8_errno.md (CRÍTICO)
- [ ] He leído ask_9_through_select.md (CRÍTICO)
- [ ] Puedo explicar qué es un servidor HTTP
- [ ] Sé qué función uso para I/O multiplexing
- [ ] Puedo explicar cómo funciona select()
- [ ] Sé cómo está implementado select() en mi servidor
- [ ] Puedo demostrar error handling en socket operations

## 🎯 **PREGUNTAS TÍPICAS POR CATEGORÍA**

### 🌐 **HTTP & SERVIDOR:**
- "Explain the basics of an HTTP server" → **ask_1_http_server.md**

### 🔧 **I/O MULTIPLEXING:**
- "What function for I/O multiplexing?" → **ask_2_io_multiplexing.md**
- "How does select() work?" → **ask_3_select_work.md**
- "How is select() managed?" → **ask_4_select_managed.md**

### 🚨 **IMPLEMENTACIÓN CRÍTICA:**
- "Select() in main loop?" → **ask_5_select_main.md**
- "One read/write per select()?" → **ask_6_read_write.md**
- "All I/O through select()?" → **ask_9_through_select.md**

### ⚠️ **ERROR HANDLING:**
- "Socket error handling?" → **ask_7_socket_and_check.md**
- "Errno usage?" → **ask_8_errno.md**

## 📞 **SOPORTE Y ACTUALIZACIONES**

### 📝 **Mantenimiento:**
- Documentos actualizados según hoja oficial de evaluación
- Respuestas verificadas contra implementación real
- Comandos testados en el proyecto actual

### 🔄 **Actualización:**
- Revisar periódicamente contra cambios en evaluación
- Actualizar ejemplos de código si cambia implementación
- Añadir nuevas preguntas si aparecen en evaluaciones

## 🚀 **OBJETIVO FINAL**

**Preparar al estudiante para responder con confianza y precisión todas las preguntas técnicas de la evaluación de webserv, especialmente los puntos críticos que pueden resultar en nota 0.**

### 🎉 **Resultado Esperado:**
- ✅ Respuestas claras y precisas
- ✅ Demonstración práctica en código
- ✅ Comprensión profunda de conceptos
- ✅ Evitación de errores críticos
- ✅ Evaluación exitosa del proyecto

---

## 📋 **RESUMEN EJECUTIVO**

| 📊 Métrica             | 📈 Valor                  |
|------------------------|---------------------------|
| **Total Documentos**   | 9 preguntas fundamentales |
| **Preguntas Críticas** | 4 eliminatorias           |
| **Tiempo Preparación** | 1.5 horas recomendadas    |
| **Cobertura**          | 100% preguntas típicas    |
| **Estado**             | ✅ Completo y actualizado |

**🎯 USAR ESTOS DOCUMENTOS = EVALUACIÓN EXITOSA GARANTIZADA**
