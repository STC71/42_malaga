# 🧪 Guía de Testing de Transcendence

Esta guía explica cómo usar los scripts de validación automática del proyecto.

---

## 📋 Scripts Disponibles

### 1. `test_auto.sh` - Validación de Módulos del Subject

Valida los **26 módulos** especificados en `en.subject.pdf`:
- Major modules (1.0 punto cada uno)
- Minor modules (0.5 puntos cada uno)
- Mínimo para aprobar: 7.0 puntos
- Nivel bonus: 9.5+ puntos

**Genera:** `test_result.md`

### 2. `test_evaluation.sh` - Validación de Criterios de Evaluación

Verifica los **61 criterios** del PDF oficial de evaluación:
- Preliminary Setup (6 checks)
- Project Overview (6 checks)
- User Management (8 checks)
- Gameplay (7 checks)
- Chat System (5 checks)
- AI Opponent (4 checks)
- Security (7 checks)
- Blockchain (5 checks)
- DevOps (5 checks)
- Bonus Features (8 checks)

**Genera:** `test_evaluation_result.md`

---

## 🚀 Uso Básico

### Preparación (IMPORTANTE)

**Antes de ejecutar los scripts, levanta los contenedores:**

```bash
make up

# Espera 10-15 segundos para que todo inicie
sleep 15
```

### Ejecutar Validaciones

```bash
# Opción 1: Validación de módulos del subject
make test

# Opción 2: Validación de criterios de evaluación
make evaluation

# Opción 3: Ambas validaciones completas
make test-all
```

### Ejecución Directa

```bash
# Scripts directamente (también funcionan)
./test_auto.sh
./test_evaluation.sh
```

---

## 🔍 Pre-Flight Checks

Ambos scripts incluyen **verificaciones previas automáticas**:

### ✅ Checks Realizados

1. **Docker daemon activo**
   - Verifica que Docker está corriendo
   
2. **Contenedores de Transcendence**
   - Detecta si los contenedores están levantados
   - Cuenta cuántos contenedores están corriendo
   
3. **Archivos críticos**
   - `docker-compose.yml`
   - `Makefile`
   - Directorios `backend/` y `frontend/`
   
4. **Backend API** (puerto 3000)
   - Verifica conectividad con el backend
   
5. **Frontend** (puerto 2323)
   - Verifica que el frontend responde

### ⚠️ Comportamiento con Advertencias

Si se detectan problemas, el script:

1. **Muestra las advertencias detectadas**
2. **Proporciona recomendaciones** (ej: ejecuta `make up`)
3. **Pregunta si continuar:** `¿Continuar de todas formas? (y/N)`

**Opciones:**
- **N (o Enter):** Cancela la ejecución → Debes resolver el problema
- **Y:** Continúa con advertencias → Algunos tests fallarán

---

## 📊 Interpretación de Resultados

### test_auto.sh → test_result.md

```markdown
## 📊 PUNTUACIÓN FINAL

| Categoría | Módulos | Puntos Obtenidos |
|-----------|---------|------------------|
| Major Modules | 9 / 15 | 9.0 pts |
| Minor Modules | 6 / 11 | 3.0 pts |
| TOTAL | 15 / 26 | 12.0 / 21.0 pts |
```

**Interpretación:**
- ✅ **>= 9.5 pts:** APROBADO CON BONUS ⭐⭐⭐
- ✅ **>= 7.0 pts:** APROBADO ✅
- ⚠️  **5.0-6.9 pts:** CASI (implementar más módulos)
- ❌ **< 5.0 pts:** INSUFICIENTE

### test_evaluation.sh → test_evaluation_result.md

```markdown
## 📊 RESUMEN EJECUTIVO

| Métrica | Valor |
|---------|-------|
| Criterios evaluados | 61 |
| Criterios aprobados | ✅ 55 |
| Criterios no cumplidos | ❌ 6 |
| Porcentaje de aprobación | 90.2% |
```

**Interpretación:**
- ✅ **>= 80%:** EXCELENTE ⭐⭐⭐
- ✅ **>= 60%:** APROBADO ✅
- ❌ **< 60%:** REQUIERE TRABAJO

---

## 🛠️ Troubleshooting

### Problema: "Contenedores NO están corriendo"

**Solución:**
```bash
make up
sleep 15
./test_evaluation.sh
```

### Problema: "Backend/Frontend no responden"

**Verificar que estén levantados:**
```bash
docker ps | grep transcendence

# Deberías ver al menos:
# - transcendence-backend
# - transcendence-frontend
```

**Si no están, reiniciar:**
```bash
make down
make up
```

### Problema: "Docker daemon no está corriendo"

**Linux:**
```bash
sudo systemctl start docker
```

**macOS:**
```bash
open -a Docker
```

### Problema: Tests fallan pero contenedores están corriendo

**Verificar conectividad manual:**
```bash
# Backend
curl http://localhost:3000

# Frontend
curl http://localhost:2323

# Si fallan, revisar logs
make logs
```

---

## 📝 Flujo Recomendado para Evaluación

### Antes de la Defensa

1. **Levantar servicios**
   ```bash
   make up
   sleep 15
   ```

2. **Ejecutar ambas validaciones**
   ```bash
   make test-all
   ```

3. **Revisar reportes**
   ```bash
   cat test_result.md
   cat test_evaluation_result.md
   ```

4. **Verificar puntuación**
   - Subject modules: >= 7.0 puntos ✅
   - Evaluation criteria: >= 80% ✅

5. **Identificar criterios faltantes**
   - Buscar líneas con ❌ en los reportes
   - Implementar funcionalidades críticas si faltan

### Durante la Evaluación

**Mostrar al evaluador:**
```bash
# 1. Ejecutar validaciones en vivo
make evaluation

# 2. Mostrar reporte generado
cat test_evaluation_result.md

# 3. Demos interactivas (según checklist del reporte)
```

---

## 🎓 Criterios Más Comunes que Fallan

### Sin Contenedores Corriendo

- ❌ Backend está corriendo y responde
- ❌ Frontend está corriendo y responde
- ❌ Múltiples servicios en docker-compose

**Fix:** `make up`

### Archivos Faltantes

- ❌ AppRole Vault (srcs/secrets/api-approle/)
- ❌ Certificados SSL

**Fix:** Ejecutar scripts de inicialización:
```bash
./srcs/scripts/00.gen_selfsigned_cert.sh
./srcs/scripts/01.init_waf_and_vault.sh
```

### Features No Implementadas

- ❌ 2FA/TOTP
- ❌ Responsive design
- ❌ SSR (Server-Side Rendering)

**Acción:** Estos son bonus opcionales, no bloquean aprobación

---

## 📚 Archivos Relacionados

- `test_auto.sh` - Script de validación de módulos
- `test_evaluation.sh` - Script de validación de evaluación
- `test_result.md` - Reporte de módulos (generado)
- `test_evaluation_result.md` - Reporte de evaluación (generado)
- `Makefile` - Comandos make para ejecutar tests
- `README.md` - Documentación principal del proyecto

---

## 🤝 Soporte

Si encuentras problemas con los scripts:

1. Verifica que Docker está corriendo
2. Ejecuta `make up` antes de los tests
3. Revisa logs: `make logs`
4. Consulta esta guía completa

**Equipo:** davigome, jesopan-, nporras-, rdel-olm & sternero  
**Fecha:** Diciembre 2025  
**Proyecto:** ft_transcendence - 42 School
