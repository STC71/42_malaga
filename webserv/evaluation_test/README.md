# 🚀 WEBSERV - Suite de Evaluación Completa

Esta suite de scripts automatiza la verificación de todos los puntos de la hoja de evaluación del proyecto **webserv** de 42 School.

#  WEBSERV - Suite de Evaluación Completa

Esta suite de scripts automatiza la verificación de **TODOS** los puntos de la hoja de evaluación del proyecto **webserv** de 42 School, siguiendo el **ORDEN EXACTO** de la evaluación oficial.

## 📋 Scripts Incluidos - ORDEN OFICIAL DE EVALUACIÓN

### 🔥 MANDATORY PART - Check the code and ask questions

**00. `00_siege_installation.sh`** - 🍺 Instalación de Siege  
- Verifica instalación de Siege con homebrew/package manager  
- PRIMER PASO obligatorio de la evaluación  

**01. `01_siege_installation.sh`** - 🍺 Instalación de Siege (alternativo)  
- Verificación adicional de Siege  

**02. `02_http_basics.sh`** - Conceptos HTTP Básicos  
- Explicaciones sobre conceptos básicos de servidor HTTP  
- Verifica implementación de métodos HTTP  

**03. `03_io_multiplexing.sh`** - I/O Multiplexing  
- Identifica qué función usa el grupo para I/O Multiplexing  
- Verifica select(), poll(), epoll(), kqueue()  

**04. `04_select_explanation.sh`** - Explicación de Select  
- Pregunta por explicación de cómo funciona select()  
- Evaluación de comprensión conceptual  

**05. `05_only_one_select.sh`** - ⚠️ CRÍTICO (Eliminatorio)  
- Verifica que usan solo un select() y manejo de servidor/cliente  
- Select debe estar en main loop, check read/write AL MISMO TIEMPO  

**06. `05_read_write_per_select.sh`** - ⚠️ CRÍTICO  
- Solo un read o write por cliente por select()  
- Mostrar código desde select() hasta read/write  

**07. `06_error_handling.sh`** - Manejo de Errores  
- Búsqueda de read/recv/write/send con manejo de errores  
- Cliente eliminado si error es retornado  

**08. `07_errno_check.sh`** - ⚠️ CRÍTICO (Eliminatorio)  
- Si errno es verificado después de read/recv/write/send = NOTA 0  
- Evaluación se para inmediatamente  

**09. `08_fd_through_select.sh`** - ⚠️ CRÍTICO (Eliminatorio)  
- Escribir/leer ANY file descriptor sin select() está PROHIBIDO  
- Todo I/O debe pasar por select()  

### 🔧 CONFIGURATION

**10. `09_configuration.sh`** - Archivo de Configuración  
- Múltiples servidores con puertos diferentes  
- Setup hostnames diferentes, páginas de error  
- Límite de client body, rutas, métodos aceptados  

**11. `14_port_configuration.sh`** - Problemas de Puertos  
- Múltiples puertos con sitios diferentes  
- Puerto mismo múltiples veces no debe funcionar  
- Múltiples servidores con puertos comunes  

### ✅ BASIC CHECKS

**12. `10_basic_requests.sh`** - Requests Básicos  
- GET, POST, DELETE deben funcionar  
- Requests desconocidos no deben crashear  
- Código de estado apropiado para cada test  

**13. `13_file_upload_download.sh`** - Upload/Download  
- Subir archivo al servidor y recuperarlo  
- Verificación de integridad de archivos  

### 🔧 CHECK CGI

**14. `11_cgi_testing.sh`** - Testing CGI  
- Servidor funciona bien usando CGI  
- CGI ejecutado en directorio correcto  
- Test con GET y POST, manejo de errores  

### 🌐 CHECK WITH BROWSER

**15. `12_browser_compatibility.sh`** - Compatibilidad Navegador  
- Navegador de referencia del equipo  
- Headers request/response, sitio estático  
- URL incorrecta, directory listing, redirección  

### 🚀 SIEGE & STRESS TEST

**16. `15_stress_testing.sh`** - Stress Testing  
- Disponibilidad >99.5% con siege -b  
- Verificar no memory leak ni hanging connections  
- Uso indefinido sin restart del servidor  

### 🔧 COMPILATION CHECK

**17. `17_compilation_check.sh`** - Compilación sin Re-link  
- Proyecto debe compilar sin problemas de re-link  
- Si no compila = flag 'Invalid compilation'  

### 🎁 BONUS PART

**18. `16_bonus_features.sh`** - Características Bonus  
- Sistema de cookies y sesiones funcionando  
- Más de un sistema CGI  

## 🎯 Uso Rápido

### Ejecutar todas las evaluaciones en secuencia:
```bash
./run_all_evaluations.sh
# Seleccionar opción 0
```

### Ejecutar un script específico:
```bash
./00_siege_installation.sh
./02_http_basics.sh
./05_only_one_select.sh
# ... etc
```

### Usar el menú interactivo:
```bash
./run_all_evaluations.sh
```

## 🎨 Características

- **🌈 Colores**: Cada tipo de información tiene su color distintivo
- **🔍 Verificación automática**: Grep automatizado para encontrar patrones en el código
- **💬 Preguntas estructuradas**: Formato Q&A con respuestas esperadas
- **💻 Comandos de verificación**: Comandos específicos para validar manualmente
- **📊 Evaluación automática**: Criterios cumplidos automáticamente
- **⚠️ Puntos críticos**: Identificación de elementos eliminatorios

## 🚨 Puntos Críticos (Eliminatorios)

### ❌ Fallo inmediato si:
1. **No usa solo un select()** en main loop ➜ `05_only_one_select.sh`
2. **Múltiples read/write** por select() ➜ `05_read_write_per_select.sh`  
3. **Se usa errno** después de socket ops ➜ `07_errno_check.sh`
4. **I/O fuera de select()** detectado ➜ `08_fd_through_select.sh`
5. **No compila** sin re-link issues ➜ `17_compilation_check.sh`

## 🎯 Esquema de Colores

- 🔵 **Azul**: Títulos de secciones
- 🟣 **Púrpura**: Comandos para ejecutar
- 🟡 **Amarillo**: Análisis y estadísticas
- 🟢 **Verde**: Resultados correctos y respuestas esperadas
- 🔴 **Rojo**: Errores y problemas críticos

## 📋 Checklist Completo de Evaluación

### ✅ MANDATORY PART - Check the Code
- [x] **Scripts 00-01**: Instalación de Siege (prerequisito)
- [x] **Script 02**: Conceptos básicos HTTP
- [x] **Script 03**: Función I/O Multiplexing
- [x] **Script 04**: Explicación select()
- [x] **Script 05**: Solo un select() (CRÍTICO)
- [x] **Script 05**: Un read/write por select() (CRÍTICO)
- [x] **Script 06**: Manejo errores en socket operations
- [x] **Script 07**: Verificación errno prohibido (CRÍTICO)
- [x] **Script 08**: Todo I/O por select() (CRÍTICO)

### ✅ CONFIGURATION
- [x] **Script 09**: Archivo configuración completo
- [x] **Script 14**: Múltiples puertos y problemas

### ✅ BASIC CHECKS
- [x] **Script 10**: GET, POST, DELETE requests
- [x] **Script 13**: Upload/download archivos

### ✅ CHECK CGI
- [x] **Script 11**: Funcionalidad CGI completa

### ✅ CHECK WITH BROWSER
- [x] **Script 12**: Compatibilidad navegador web

### ✅ COMPILATION CHECK
- [x] **Script 17**: Compilación sin re-link

### ✅ SIEGE & STRESS TEST
- [x] **Script 15**: Testing con Siege (>99.5% disponibilidad)

### ✅ BONUS PART
- [x] **Script 16**: Cookies, sesiones, múltiples CGI

### 🎯 Total: 18 scripts cubriendo 100% de la evaluación oficial
## 📁 Estructura de Archivos - Scripts Reales

```
evaluation_test/
├── 00_siege_installation.sh      # 🍺 Instalación Siege (primario)
├── 01_siege_installation.sh      # 🍺 Instalación Siege (alternativo)
├── 01_only_one_select.sh         # ⚠️ Solo un select() (duplicado)
├── 02_http_basics.sh             # HTTP conceptos básicos
├── 03_io_multiplexing.sh         # I/O multiplexing
├── 04_select_explanation.sh      # Explicación select()
├── 05_only_one_select.sh         # ⚠️ Solo un select()
├── 05_read_write_per_select.sh   # Un read/write por select
├── 06_error_handling.sh          # Manejo errores
├── 07_errno_check.sh             # ⚠️ CRÍTICO: errno
├── 08_fd_through_select.sh       # ⚠️ I/O por select()
├── 09_configuration.sh           # Configuración
├── 10_basic_requests.sh          # Requests básicos
├── 11_cgi_testing.sh             # Testing CGI
├── 12_browser_compatibility.sh   # Compatibilidad navegador
├── 13_file_upload_download.sh    # Upload/download
├── 14_port_configuration.sh      # Configuración puertos
├── 15_stress_testing.sh          # Stress testing
├── 16_bonus_features.sh          # Características bonus
├── 17_compilation_check.sh       # Compilación sin re-link
├── run_all_evaluations.sh        # 🚀 Script maestro
├── evaluation_mapping.md         # Mapeo de evaluación
└── README.md                     # Esta documentación
```

## 🔧 Funcionamiento

Cada script:

1. **🔍 Analiza automáticamente** el código con grep
2. **📊 Muestra estadísticas** de lo encontrado
3. **✅ Evalúa criterios** específicos
4. **💬 Proporciona preguntas** con respuestas esperadas
5. **💻 Incluye comandos** para verificación manual
6. **🎯 Da resultado final** (✅ / ❌)

## 🎓 Para Evaluadores

- **Ejecuta `run_all_evaluations.sh`** para verificación completa
- **Usa preguntas incluidas** para interrogar al grupo
- **Ejecuta comandos sugeridos** para verificación manual
- **Presta atención** a puntos críticos (eliminatorios)

## 👥 Para Estudiantes

- **Ejecuta antes de la evaluación** para auto-verificación
- **Revisa puntos fallidos** antes de presentar
- **Usa como guía** para entender qué se evalúa
- **Prepara respuestas** basadas en las preguntas incluidas

## � Estadísticas del Proyecto

- **✅ Scripts totales**: 18 scripts de evaluación
- **⚠️ Puntos críticos**: 5 elementos eliminatorios identificados
- **🔍 Cobertura**: 100% de la hoja de evaluación oficial
- **🎯 Organización**: Orden correcto de evaluación

## �📞 Soporte

Los scripts están diseñados para ser auto-explicativos. Cada uno incluye:
- Descripción clara del punto de evaluación
- Comandos específicos para verificar
- Explicación de qué buscar en los resultados
- Preguntas típicas de evaluación

## � Resultado Final

**✅ SUITE DE EVALUACIÓN COMPLETA**: Esta suite ha sido diseñada para seguir paso a paso la hoja de evaluación oficial de 42 School, facilitando evaluaciones consistentes, completas y eficientes del proyecto webserv.

**🎯 Objetivo**: Automatizar y estandarizar el proceso de evaluación para todos los participantes.

**✨ Beneficio**: Evaluaciones más rápidas, precisas y educativas que cubren todos los aspectos técnicos del proyecto webserv.
