# 📚 Módulo: includes — Documentación técnica

Documento conciso que describe la carpeta `includes/` del proyecto Minishell: responsabilidades de las cabeceras, tipos y estructuras compartidas, macros y funciones auxiliares, ejemplos de uso, y cómo validar su correcto funcionamiento.

---

## 📌 Visión general

La carpeta `includes/` agrupa las cabeceras públicas y privadas que exponen las APIs internas del proyecto: definiciones de estructuras, macros de configuración, prototipos de funciones y mensajes comunes. Es el contrato entre módulos (parser, executor, builtins, etc.) y actúa como la fuente única de verdad para tipos y constantes compartidas.

Mantener `includes/` clara y estable facilita la lectura del código y reduce errores por duplicación o desincronización entre módulos.

---

## 🗂️ Contenido y responsabilidad (por fichero)

- `minishell.h` — Cabecera principal del proyecto: incluye las estructuras globales, prototipos generales y dependencias comunes. Punto de entrada para la mayoría de los módulos.
- `structures.h` — Definición de las estructuras de datos usadas a lo largo del proyecto (nodos del parser, representaciones de comandos, listas, entorno, etc.).
- `functions.h` — Prototipos de funciones compartidas entre módulos (helpers de ejecución, utilidades de entorno, manejo de listas, etc.).
- `define.h` — Macros de configuración, constantes y valores por defecto (p. ej. BUFFERS, flags de compilación dependientes del proyecto).
- `messages.h` — Formatos y constantes de mensajes de error/advertencia que deben reutilizarse para homogeneidad en la salida del programa.
- `colors.h` — Macros y secuencias ANSI para coloreado en salida (si se utiliza); centraliza definiciones para evitar duplicidad.

> Nota: la lista anterior refleja la estructura actual del repositorio. Mantener estas cabeceras bien documentadas evita que otros módulos dependan de definiciones internas no expuestas.

---

## 🔗 Cómo se usan estas cabeceras

1. Las cabeceras de `includes/` se incluyen en los `.c` y otros `.h` según necesidad, preferiblemente usando `#include "includes/minishell.h"` (rutas relativas desde la raíz del proyecto según las reglas del Makefile).
2. `minishell.h` debe incluir (o declarar) lo mínimo necesario para no provocar dependencias circulares; en su lugar, usar forward declarations cuando sea posible.
3. `structures.h` agrupa los tipos que definen el AST y las entidades compartidas entre `parser/`, `executor/` y `builtins/`.

---

## 🧭 Principios de diseño y buenas prácticas

- **Única fuente de verdad:** evitar duplicar definiciones entre módulos; si algo se comparte, colócalo en `includes/`.
- **Simplicidad en las cabeceras:** limitar dependencias y evitar incluir implementaciones en `.h` (solo prototipos y macros pequeños).
- **Documentar cada símbolo público:** añadir comentarios breves sobre invariantes, ownership de memoria y contratos (por ejemplo quién libera qué).
- **Macros con cuidado:** preferir `static inline` o funciones cuando la semántica lo requiere; usar macros solo para constantes y wrappers triviales.
- **Evitar efectos colaterales:** no ejecutar código en cabeceras (p. ej. asignaciones globales no controladas).

---

## ⚙️ Cómo compilar y validar localmente

Desde la raíz del proyecto:

```bash
make fclean && make
./test_auto.sh
```

- Comprobar estilo con Norminette (si aplica a tu flujo):

```bash
norminette includes/*.h
```

- Revisar que no hay símbolos públicos sin documentar y que las cabeceras se incluyen con guardas (`#ifndef` / `#define` / `#endif`).

---

## 🔎 Ejemplos rápidos y recomendaciones de uso

- Para declarar una nueva estructura que será visible en todo el proyecto, añadir su typedef en `structures.h` y documentar la responsabilidad de cada campo.
- Si una función es utilizada por varios módulos, añadir su prototipo a `functions.h` y documentar ownership y expectativas de parámetros (por ejemplo: "la función no libera la cadena pasada").

---

## 🧪 Pruebas, análisis estático y dinámico

- `test_auto.sh` — la suite automatizada cubre comportamiento funcional; corrige errores en implementaciones antes de cambiar cabeceras públicas.
- Valgrind: ejecutar módulos críticos bajo `valgrind` tras cambios en estructuras o ownership para detectar leaks y accesos inválidos.
- Revisión: cada cambio en `includes/` debe revisarse con especial cuidado en PRs, porque puede impactar múltiples módulos.

---

## 🖼️ Diagrama sencillo (ASCII)

```
         +----------------+
         |   includes/    |
         |  (headers API) |
         +----------------+
           /     |      \
          /      |       \
         v       v        v
    parser/  executor/  builtins/
      |         |          |
      +---------+----------+
                |
             libft/ (helpers)

Leyenda: `includes/` define los tipos, macros y prototipos que conectan los módulos.
```

---

## ✨ Cierre

`includes/` es el contrato entre módulos: claridad, documentación y cuidado en los cambios aquí reducen errores a lo largo del proyecto. 
