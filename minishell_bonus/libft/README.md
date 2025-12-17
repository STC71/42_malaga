# 🧰 Módulo: libft — Documentación técnica

Documento profesional y conciso que describe la carpeta `libft/` del proyecto Minishell: propósito de la librería, lista de funciones y ficheros, contratos de API, pruebas y pautas de mantenimiento.

---

## 📌 Visión general

`libft` contiene un conjunto de utilidades y reimplementaciones de funciones básicas de C (strings, memoria, listas, I/O helpers y manejo de cadenas) usadas por el resto del proyecto. Su objetivo es proporcionar implementaciones fiables y bien testeadas para evitar duplicación de código y centralizar comportamiento común.

La calidad de `libft` impacta en todo el proyecto: por eso debe ser estable, documentada y su API clara.

---

## 🗂️ Contenido y responsabilidad (por fichero)

Esta es la lista de ficheros actuales en `libft/` y una breve descripción de su responsabilidad:

- `ft_atoi.c` — conversión segura de cadena a entero.
- `ft_bzero.c` — escribir ceros en un bloque de memoria.
- `ft_calloc.c` — asignación y cero-inicialización segura.
- `ft_isalnum.c`, `ft_isalpha.c`, `ft_isascii.c`, `ft_isdigit.c`, `ft_isdigit_str.c`, `ft_isprint.c` — funciones de clasificación de caracteres y validaciones.
- `ft_itoa.c` — conversión de entero a cadena.
- `ft_lst*.c` — operaciones sobre listas enlazadas (`new`, `add_front`, `add_back`, `size`, `last`, `iter`, `map`, `clear`, `delone`).
- `ft_matrixdup.c` — duplicado seguro de matrices de cadenas.
- `ft_mem*.c` — `memcpy`, `memmove`, `memset`, `memchr`, `memcmp` y utilidades relacionadas.
- `ft_putchar_fd.c`, `ft_putendl_fd.c`, `ft_putnbr_fd.c`, `ft_putstr_fd.c` — salidas a descriptor de archivo.
- `ft_split.c`, `ft_str*.c`, `ft_substr.c`, `ft_strtrim.c`, `ft_strjoin.c`, `ft_strlcpy.c`, `ft_strlcat.c`, `ft_strdup.c` — manipulación y creación de cadenas.
- `ft_string_*.c` — una pequeña API de buffer/string dinámico usada internamente en el proyecto (`ft_string_new`, `ft_string_add`, `ft_string_del_last`, `ft_string_free`, `ft_string_len`).
- `get_next_line.c` y `get_next_line_utils.c` — lector por línea, importante para entradas/lectura controlada.
- `libft.h` — cabecera pública que declara todas las funciones y tipos expuestos por `libft`.
- `Makefile` — reglas de compilación para construir la librería localmente (si aplica).

Mantén cada función con una responsabilidad única y con comportamiento documentado (ownership de memoria, return values y errores esperados).

---

## 🔗 Contratos y expectations (API)

- Todas las funciones que devuelven punteros documentan si el caller es responsable de liberar la memoria.
- Las funciones que modifican buffers reciben un tamaño/longitud cuando procede; evite comportamiento indefinido con `NULL` salvo que se documente explícitamente.
- Las funciones de listas deben documentar si actúan por referencia y cómo se deben liberar los nodos.

---

## 🧭 Buenas prácticas y estilo

- Mantener funciones pequeñas y bien probadas.
- Evitar efectos laterales inesperados en helpers (p. ej. no modificar entradas sin documentarlo).
- Seguir Norminette/estándares de estilo del proyecto: nombres, indentación, y longitud de líneas.
- Documentar invariantes de memoria: quién libera qué.

---

## ⚙️ Cómo compilar y validar localmente

Desde la raíz del proyecto, una compilación completa del proyecto asegura que `libft` esté siendo vinculada y usada correctamente:

```bash
make fclean && make
```

- Para compilar solo la librería (si `libft/Makefile` existe):

```bash
cd libft && make
```

- Ver estilo con Norminette (si se aplica):

```bash
norminette libft/*.c libft/libft.h
```

- Ejecutar pruebas funcionales y dinámicas con `test_auto.sh` o pruebas específicas de `libft` cuando existan.

---

## 🔎 Pruebas y análisis dinámico

- Valgrind: probar funciones que manejan memoria directamente con `valgrind --leak-check=full`.
- Casos de prueba: cubrir bordes (NULL, cadenas vacías, enteros límites) y comportamiento en listas con nodos nulos.
- Añadir tests unitarios si se dispone de un runner o harness para `libft`.

---

## 🧪 Ejemplos de uso

- Uso de `ft_strdup`:

```c
char *s = ft_strdup("hola");
if (!s) return (1);
/* usar s */
free(s);
```

- Uso de listas:

```c
t_list *n = ft_lstnew(ft_strdup("valor"));
ft_lstadd_back(&lst, n);
/* al finalizar */
ft_lstclear(&lst, free);
```

---

## 🖼️ Diagrama sencillo (ASCII)

```
   +-------+
   | libft |
   +-------+
       ^
       |  (usado por)
  +--------+--------+---------+
  |        |        |         |
 parser executor builtins includes

Leyenda: `libft` ofrece utilidades básicas consumidas por parsers, executor y builtins.
```

---

## ✨ Cierre

`libft` es una pieza crítica: su estabilidad y claridad facilitan el trabajo en todo el proyecto.
