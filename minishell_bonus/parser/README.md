# 🧭 Módulo: parser — Documentación técnica

Este documento describe la carpeta `parser/` del proyecto Minishell: responsabilidades del parser, lista de ficheros, flujo de parseo/tokenización, manejo de comillas y here-docs, ejemplos de uso y cómo validar su correcto funcionamiento.

---

## 📌 Visión general

El `parser` transforma la entrada del usuario (línea de comando cruda) en una representación estructurada (tokens, nodos, AST o estructuras de comandos) que el `executor` puede consumir. Se encarga de:

- Tokenizar respetando separadores y operadores (`|`, `<`, `>`, `>>`, `<<`).
- Manejar comillas simples y dobles, escapes y expansiones donde corresponda.
- Construir la estructura que representa pipelines, redirecciones y comandos con sus argumentos.
- Validar sintaxis básica y reportar errores comprensibles.

Un parser claro y robusto reduce la complejidad del `executor` y evita comportamientos inesperados en la shell.

---

## 🗂️ Contenido y responsabilidad (por fichero)

Lista actual de ficheros en `parser/` y su responsabilidad esperada:

- `ft_action.c` — Aplicación de acciones sobre tokens/nodos durante el parseo (callbacks, transformaciones).
- `ft_checkers_1.c`, `ft_checkers_2.c` — Validaciones sintácticas y semánticas (operadores mal situados, tokens inesperados).
- `ft_elements.c` — Creación y manejo de elementos básicos (tokens, nodos de comando, argumentos).
- `ft_envp_tools.c` — Helpers para manejar expansiones relacionadas con `envp` (reemplazo de `$VAR`).
- `ft_free_utils.c` — Liberaciones centralizadas de estructuras temporales del parser.
- `ft_handling_1.c`, `ft_handling_2.c` — Lógica de alto nivel para ensamblar pipelines, redirecciones y comandos.
- `ft_mem_tools.c` — Utilidades de memoria específicas del parser (duplicados, concatenaciones seguras).
- `ft_quotes_handling.c`, `ft_quotes.c` — Módulo dedicado a parsing y normalización de comillas (simple/doble), escapes, y su impacto en expansions.
- `ft_remove.c` — Eliminación y limpieza de tokens inválidos o espacios innecesarios.
- `ft_struct_parse.c` — Construcción final de las estructuras que consumirá el `executor`.
- `ft_tools.c` — Helpers varios usados por el parser (split seguro, iteradores, etc.).

Mantener responsabilidades separadas facilita pruebas unitarias y revisiones.

---

## 🔗 Flujo de parseo (alto nivel)

1. Recepción de la línea de comando por `main`/input-reader.
2. Tokenización: dividir la línea en tokens teniendo en cuenta comillas y escapes.
3. Preprocesado: eliminar tokens vacíos, normalizar espacios y separar operadores.
4. Validación sintáctica: detectar errores como `| |`, redirecciones sin objetivo, o EOF inesperado tras `<<`.
5. Construcción de estructuras: crear nodos/AST que representen comandos, pipelines y redirecciones.
6. Retorno al `executor` con estructuras listas para ejecutar.

Errores detectados en la fase de parseo deben producir mensajes claros y códigos de fallo previsibles.

---

## 🧭 Manejo de comillas, escapes y expansiones

- Comillas simples (`'`): texto literal; no se expanden variables ni escapes (excepto cierre de comilla).
- Comillas dobles (`"`): permiten expansión de variables (`$VAR`) y escapes específicos (`\`, `"`, etc.) según la implementación.
- Escapes (`\`) fuera de comillas: permiten incluir caracteres especiales como literales.
- Here-documents (`<<`): lectura hasta el delimitador; si el delimitador está sin comillas, realizar expansiones; si está entre comillas, tratar como literal.

El conjunto de reglas debe estar documentado y las funciones en `ft_quotes*.c` centralizan esta lógica.

---

## 🔎 Mensajes de error y validaciones comunes

- Redirección sin destino: `syntax error near unexpected token`.
- Pipe final sin comando: `syntax error near unexpected token '|'`.
- EOF en here-doc: mostrar mensaje apropiado y limpiar temporales.

La biblioteca de mensajes debería reutilizar `includes/messages.h` para mantener consistencia.

---

## ⚙️ Cómo compilar y validar localmente

Desde la raíz del proyecto:

```bash
make fclean && make
./test_auto.sh
```

- Revisar logs del parser (si existen prints de debug) y verificar los resultados detallados en `test_auto_result.md`.

---

## 🧪 Casos de prueba recomendados

- Combinaciones de comillas: `echo "hola 'mundo'"` y `echo 'hola "mundo"'`.
- Redirecciones complejas: `cmd > out 2>&1` y `cmd >> out`.
- Pipelines anidados: `cat file | grep x | sort | uniq`.
- Here-doc con/ sin expansión:

```sh
cat <<EOF
$HOME
EOF

cat <<'EOF'
$HOME
EOF
```

Comparar comportamiento con una shell estándar para establecer expectativas.

---

## 🖼️ Diagrama sencillo (ASCII)

```
 [User input] -> tokenizer -> token stream
                             |
                             v
                       syntax checker
                             |
                             v
                   struct builder (AST/nodos)
                             |
                             v
                         executor

```

---

## ✨ Cierre

El `parser` es la puerta de entrada del comportamiento visible de la shell: documentación clara, validaciones y pruebas exhaustivas en esta carpeta reducen errores en toda la aplicación.

