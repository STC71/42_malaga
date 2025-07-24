# � MAPEO DE EVALUACIÓN - WEBSERV PROJECT

## 🎯 **GUÍA DE CORRESPONDENCIA: EVALUACIÓN OFICIAL ↔ SCRIPTS AUTOMATIZADOS**

### 🚨 **MANDATORY PART - Check the code and ask questions**

| Punto Oficial                                                              | Script de Evaluación             |
|----------------------------------------------------------------------------|----------------------------------|
| 1. "Launch the installation of siege with homebrew"                        | `01_siege_installation.sh`       |
| 2. "Ask explanations about the basics of an HTTP server"                   | `02_http_basics.sh`              |
| 3. "Ask what function the group used for I/O Multiplexing"                 | `03_io_multiplexing.sh`          |
| 4. "Ask for an explanation of how does select() work"                      | `04_select_explanation.sh`       |
| 5. "Ask if they use only one select()"                                     | `05_only_one_select.sh`          |
| 6. "select() should be in main loop and check read/write AT THE SAME TIME" | `05_only_one_select.sh`          |
| 7. "only one read or write per client per select()"                        | `06_error_handling.sh`           |
| 8. "Search for all read/recv/write/send errors"                            | `06_error_handling.sh`           |
| 9. "check returned value correctly (not just -1 or 0)"                     | `06_error_handling.sh`           |
| 10. "If errno is checked after read/recv/write/send, grade is 0"           | `07_errno_check.sh`              |
| 11. "Writing/reading ANY file descriptor without select() FORBIDDEN"       | `08_fd_through_select.sh`        |
| 12. "Project must compile without re-link issue"                           | `17_compilation_check.sh`        |
| 13. "If any point unclear or incorrect, evaluation stops"                  | *Integrado en todos los scripts* |

### 🚨 **CONFIGURATION**

| Punto Oficial                                               | Script de Evaluación         |
|-------------------------------------------------------------|------------------------------|
| 1. "Search for HTTP response status codes on internet"      | `02_http_basics.sh`          |
| 2. "Setup multiple servers with different ports"            | `09_configuration.sh`        |
| 3. "Setup multiple servers with different hostnames"        | `14_port_configuration.sh`   |
| 4. "Setup default error page (try to change error 404)"     | `09_configuration.sh`        |
| 5. "Limit client body (test with curl)"                     | `09_configuration.sh`        |
| 6. "Setup routes in server to different directories"        | `09_configuration.sh`        |
| 7. "Setup default file for directory"                       | `09_configuration.sh`        |
| 8. "Setup list of methods accepted for route"               | `09_configuration.sh`        |

### 🚨 **BASIC CHECKS**

| Punto Oficial                                       | Script de Evaluación         |
|-----------------------------------------------------|------------------------------|
| 1. "GET, POST and DELETE requests should work"      | `10_basic_requests.sh`       |
| 2. "UNKNOWN requests should not crash"              | `10_basic_requests.sh`       |
| 3. "receive appropriate status code for every test" | `10_basic_requests.sh`       |
| 4. "Upload file to server and get it back"          | `13_file_upload_download.sh` |

### 🚨 **CHECK CGI**

| Punto Oficial                                               | Script de Evaluación         |
|-------------------------------------------------------------|------------------------------|
| 1. "Server working fine using CGI"                          | `11_cgi_testing.sh`          |
| 2. "CGI run in correct directory for relative path access"  | `11_cgi_testing.sh`          |
| 3. "Test CGI with GET and POST methods"                     | `11_cgi_testing.sh`          |
| 4. "Test files containing errors"                           | `11_cgi_testing.sh`          |
| 5. "Server never crash, error visible"                      | `11_cgi_testing.sh`          |

### 🚨 **CHECK WITH BROWSER**

| Punto Oficial                                       | Script de Evaluación          |
|-----------------------------------------------------|-------------------------------|
| 1. "Use reference browser of team"                  | `12_browser_compatibility.sh` |
| 2. "Look at request/response headers"               | `12_browser_compatibility.sh` |
| 3. "Compatible to serve fully static website"       | `12_browser_compatibility.sh` |
| 4. "Try wrong URL"                                  | `12_browser_compatibility.sh` |
| 5. "Try to list directory"                          | `12_browser_compatibility.sh` |
| 6. "Try redirected URL"                             | `12_browser_compatibility.sh` |

### 🚨 **PORT ISSUES**

| Punto Oficial                                       | Script de Evaluación         |
|-----------------------------------------------------|------------------------------|
| 1. "Multiple ports with different websites"         | `14_port_configuration.sh`   |
| 2. "Same port multiple times should not work"       | `14_port_configuration.sh`   |
| 3. "Multiple servers with common ports"             | `14_port_configuration.sh`   |

### 🚨 **SIEGE & STRESS TEST**

| Punto Oficial                                               | Script de Evaluación         |
|-------------------------------------------------------------|------------------------------|
| 1. "Use Siege to run stress tests"                          | `15_stress_testing.sh`       |
| 2. "Availability >99.5% for simple GET with siege -b"       | `15_stress_testing.sh`       |
| 3. "Verify no memory leak"                                  | `15_stress_testing.sh`       |
| 4. "Check no hanging connection"                            | `15_stress_testing.sh`       |
| 5. "Use siege indefinitely without restart"                 | `15_stress_testing.sh`       |

### 🚨 **BONUS PART**

| Punto Oficial                                       | Script de Evaluación         |
|-----------------------------------------------------|------------------------------|
| 1. "Working session and cookies system"             | `16_bonus_features.sh`       |
| 2. "More than one CGI system"                       | `16_bonus_features.sh`       |

---

## 📊 **RESUMEN DEL SUITE DE EVALUACIÓN**

### ✅ **SUITE COMPLETO Y FUNCIONAL**

- **17 Scripts de evaluación** - Todos funcionales y ejecutables
- **Mapeo 1:1** - Cada punto oficial tiene su script correspondiente
- **Cobertura total** - Todos los puntos obligatorios y bonus cubiertos
- **Automatización completa** - Tests, verificaciones y Q&A integrados
- **Documentación completa** - README y guías actualizadas

### 🎯 **SCRIPTS ORDENADOS CORRECTAMENTE**

```
01_siege_installation.sh      - Instalación de Siege
02_http_basics.sh            - Conceptos básicos HTTP
03_io_multiplexing.sh        - I/O Multiplexing
04_select_explanation.sh     - Explicación de select()
05_only_one_select.sh        - Verificación de un solo select()
06_error_handling.sh         - Manejo de errores read/write
07_errno_check.sh            - Verificación de errno
08_fd_through_select.sh      - FD a través de select()
09_configuration.sh          - Configuración del servidor
10_basic_requests.sh         - Requests básicos
11_cgi_testing.sh           - Tests de CGI
12_browser_compatibility.sh  - Compatibilidad con navegador
13_file_upload_download.sh   - Upload/Download de archivos
14_port_configuration.sh     - Configuración de puertos
15_stress_testing.sh         - Tests de estrés con Siege
16_bonus_features.sh         - Características bonus
17_compilation_check.sh      - Verificación de compilación
```

### 🔧 **HERRAMIENTAS DE GESTIÓN**

- **`run_all_evaluations.sh`** - Script maestro con menú interactivo
- **`chmods.sh`** - Gestión de permisos del proyecto
- **`README.md`** - Documentación completa de uso
- **`evaluation_mapping.md`** - Esta guía de correspondencia

### 🎉 **ESTADO: MAPEO COMPLETO Y LISTO PARA USO**

Este mapeo proporciona la correspondencia exacta entre cada punto de la hoja de evaluación oficial del proyecto webserv de 42 y su script automatizado correspondiente.

