# 🔧 Módulo: builtins  — Documentación técnica

Esta documentación explica qué contiene la carpeta `builtins/`, cómo se integra con el resto del proyecto Minishell y cómo validar su correcto funcionamiento.

---

## 📌 Visión general

Los *builtins* son comandos implementados dentro del proceso de la shell (no son ejecutables externos). Permiten modificar el estado de la shell (variables de entorno, directorio actual, estado de salida) sin crear procesos adicionales, lo que es esencial para operaciones como `cd`, `export` o `unset`.

Esta carpeta agrupa implementaciones, validaciones y utilidades relacionadas con los comandos internos de la shell.

---

## 🗂️ Contenido y responsabilidad (resumen)

- `cd.c` — Cambio de directorio, actualización de `PWD` y `OLDPWD`, gestión de errores relacionados con `chdir`.
- `cd_errors.c` — Mensajería y formatos comunes para errores en `cd`.
- `cd_utils.c` — Helpers para normalizar rutas, resolver atajos (`~`, `-`) y actualización de variables de entorno PWD/OLDPWD.
- `echo.c` — Implementación de `echo` con soporte de `-n` y manejo de espacios.
- `exit.c` — Cierre controlado de la shell, interpretación de argumentos numéricos y código de salida.
- `print_env.c` — Listado de variables de entorno actuales (equivalente a `env`).
- `pwd.c` — Ruta de trabajo actual con manejo de errores y compatibilidad POSIX.
- `delete_env.c` — Implementación de `unset` y eliminación segura de entradas de entorno.
- `update_env_export.c` & `update_env2.c` — Lógica de `export` (inserción/actualización) y helpers auxiliares.
- `update_env_errors.c` & `some_errors.c` — Validaciones y utilidades comunes para mensajes de error.

Cada fichero tiene una responsabilidad clara y busca la simplicidad, testabilidad y cumplimiento de normas de estilo.

---

## 🔗 Flujo de ejecución y relación con el proyecto

1. `parser/` tokeniza y genera la representación de la instrucción (nodos, redirecciones, tokens).
2. `executor/` determina si el comando es un builtin:
   - Si es builtin: invoca la función correspondiente desde `builtins/` dentro del proceso actual.
   - Si no: realiza `fork` + `execve` para ejecutar el binario externo.
3. Los builtins que modifican el entorno actúan sobre la estructura compartida (gestión centralizada del `env`), garantizando consistencia para llamadas posteriores.

Dependencias clave:
- `includes/` — cabeceras y estructuras compartidas (`minishell.h`, `functions.h`).
- `libft/` — utilidades comunes (strings, listas, memoria) para evitar duplicación.

---

## 🧩 Principios de diseño y calidad

- Responsabilidad única: cada archivo implementa una función clara y bien acotada.
- Claridad y legibilidad: funciones cortas, nombres explícitos y control de errores uniforme.
- Testabilidad: código diseñado para ser validado por `test_auto.sh` y pruebas TTY adicionales.
- Estándares: seguir las reglas de estilo (Norminette) y ejecutar análisis dinámicos (Valgrind) durante QA.
- Robustez: validaciones defensivas en entradas y manejo consistente de códigos de retorno.

---

## ⚙️ Cómo compilar y ejecutar pruebas

Comandos rápidos (desde la raíz del proyecto):

```bash
make fclean && make
./test_auto.sh
```

- Ver estilo con Norminette: `norminette builtins/*.c includes/*.h`.
- Análisis de memoria (Valgrind): `valgrind --leak-check=full ./minishell` sobre casos concretos.

---

## 🔎 Ejemplos de comportamiento (esperado)

- `cd /ruta` → cambia `PWD`, actualiza `OLDPWD` y devuelve `0` en caso de éxito.
- `echo -n hola` → imprime `hola` sin salto final.
- `export VAR=valor` → añade o actualiza `VAR` en la estructura de entorno.
- `unset VAR` → elimina `VAR` si existe; no imprime en stdout.

Los ejemplos se reflejan y validan en la suite automatizada de pruebas.

---

## 🧪 Pruebas y aseguramiento

- `test_auto.sh` — suite automatizada con 115 pruebas comprehensivas.
- Norminette y Valgrind forman parte del flujo de QA recomendado.

---

## 🖼️ Diagrama arquitectural (ASCII)

El diagrama siguiente está en formato ASCII para asegurar compatibilidad y lectura inmediata en cualquier visor.

```
                   +-----------+
                   |  parser/  |
                   +-----------+
                     |
                     v
                   +-----------+
                   | executor/ |
                   +-----------+
                    /    |    \
                   /     |     \
                  v      v      v
               +---------+ +---------+ +--------+
               | builtins| | includes| | tests  |
               |  / env  | |  (API)  | |(auto)  |
               +---------+ +---------+ +--------+
                  |            ^
                  |            |
                  v            |
               +-----------+   |
               | env store |---+
               +-----------+

Leyenda:
- `parser/`    : tokeniza y produce nodos/AST
- `executor/`  : decide builtin vs binario externo y despacha
- `builtins/`  : implementaciones internas que pueden modificar `env`
- `includes/`  : cabeceras y estructuras compartidas
- `tests`      : `test_auto.sh` (suite automatizada con 115 tests)
```

---

## ✨ Notas finales

Documento técnico y visual pensado para facilitar la comprensión del módulo `builtins/`. Está diseñado para ser directo, atractivo y útil tanto para revisión técnica como para evaluación de calidad.
