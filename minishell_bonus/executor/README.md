# 🚦 Módulo: executor — Documentación técnica

Documento conciso que describe la carpeta `executor/` del proyecto Minishell: responsabilidad, ficheros, flujo de ejecución, ejemplos de uso, y cómo validar su correcto funcionamiento.

---

## 📌 Visión general

El módulo `executor` es el corazón de la fase de ejecución: recibe la representación sintáctica generada por el `parser` y decide cómo ejecutar cada comando (builtin vs binario externo), gestiona tuberías, redirecciones, heredocs y el ciclo de vida de los procesos hijos. Su objetivo es realizar ejecuciones correctas, seguras y con un comportamiento POSIX-compatible dentro de las restricciones del proyecto.

---

## 🗂️ Contenido y responsabilidades (por fichero)

- `check_and_exec_builtins.c` — Determina si un comando es builtin y, si aplica, lo ejecuta en el contexto adecuado (p.ej. sin fork cuando corresponde).
- `clean.c` — Funciones de limpieza de estructuras, descriptors y memoria tras la ejecución.
- `execute_bin.c` — Lógica para ejecutar binarios externos (`fork` + `execve`), configuración de entorno y manejo de señales en hijos.
- `execute_bin2.c` — Helpers y casos auxiliares para la ejecución de binarios (reenvío de pipes, reapertura de fds, fallos controlados).
- `execute_builtins.c` — Implementaciones que encapsulan la llamada a los builtins desde el executor (gestión de return codes y efectos en el entorno).
- `heredoc.c` — Implementación segura de heredocs: creación de temporales, lectura de contenido, e integración con el flujo de redirecciones.
- `redirections.c` — Apertura, duplicación y restauración de `stdin`/`stdout`/`stderr` para soportar `>`, `>>`, `<`, `<<`.

Cada fichero intenta mantener responsabilidades bien acotadas, con helpers en `execute_bin2.c` y limpieza centralizada en `clean.c`.

---

## 🔗 Flujo de ejecución (alto nivel)

1. `parser` produce un nodo/estructura para cada instrucción.
2. `executor` recibe el nodo y: 
   - Resuelve redirecciones y heredocs (abre ficheros/crea temporales).
   - Si la instrucción es una tubería, crea los pipes necesarios y enlaza procesos.
   - Para cada comando en la pipeline: decide builtin vs binario externo.
     - Builtin que debe afectar al proceso principal: se ejecuta en el proceso actual.
     - Otros builtins / binarios: se ejecutan en procesos hijos (`fork`).
   - Gestiona señales, códigos de salida y limpieza de descriptors.

---

## 🧭 Interacción con otras capas

- `parser/` → entrada: AST/nodos de comando.
- `builtins/` → funciones de alto nivel que pueden ser invocadas por el `executor`.
- `includes/` & `libft/` → utilidades y estructuras compartidas (strings, listas, GNL, etc.).
- `signals/` → manejo global y políticas de señales (SIGINT/SIGQUIT) en master/children.

---

## 🧾 Principios de diseño y buenas prácticas

- Minimizar fugas: garantizar `close()` de fds y liberar memoria en `clean.c`.
- Separación de responsabilidades: decisión (check) vs ejecución (execute).
- Robustez en redirecciones: restaurar fds al valor previo tras la ejecución.
- Manejo claro de errores y códigos de salida: devolver códigos POSIX donde proceda.

---

## ⚙️ Cómo compilar y validar localmente

Desde la raíz del proyecto:

```bash
make fclean && make
./test_auto.sh
```

- Ejecuta pruebas unitarias/integradas relevantes usando la suite existente (`test_auto.sh`).
- Para depuración, ejecutar ejemplos concretos en una terminal y observar la salida y códigos de salida.

---

## 🔎 Casos de ejemplo y expectativas

- Pipeline simple:

```sh
ls -l | grep minishell | wc -l
```

Expectativa: `executor` crea 3 procesos conectados por pipes, redirige correctamente `stdout`/`stdin` entre ellos y devuelve el código de salida del último proceso.

- Redirección y builtin:

```sh
echo "hola" > archivo.txt
```

Expectativa: `echo` ejecutado (builtin) con `stdout` redirigido a `archivo.txt`; `executor` asegura que el descriptor esté abierto y cerrado correctamente.

- Heredoc:

```sh
cat <<EOF
línea1
línea2
EOF
```

Expectativa: `heredoc.c` crea contenido temporal y lo asocia a `stdin` del proceso, sin dejar temporales abiertos ni fugas.

---

## 🧪 Pruebas y análisis dinámico

- `test_auto.sh` — suite general; incluye trazas y comparaciones.
- Valgrind: ejecutar casos puntuales con `valgrind --leak-check=full ./minishell` para detectar fugas introducidas por el executor.
- Logs/prints: para debugging local, añadir prints controlados (evitar dejar prints en el código de producción).

---

## 🖼️ Diagrama sencillo (ASCII)

```
 [User input] --> parser ---> [ AST / commands ]
                                  |
                                  v
                               executor
                +-----------------+----------------+
                |                 |                |
             redirs           pipelines         heredoc
                |                 |                |
       +--------v---------+  +----v------+   +-----v------+
       | open/dup fds     |  | fork/exec |   | create tmp |
       | restore on exit  |  |   pipes   |   | feed stdin |
       +------------------+  +-----------+   +------------+

```

---

## ✨ Cierre

El `executor` coordina la ejecución real de comandos en la shell: su claridad y robustez determinan la corrección del comportamiento observable por el usuario. Este README resume responsabilidades, flujo y puntos clave para entender y validar el módulo.
