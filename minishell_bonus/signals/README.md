# 🚨 Módulo: signals — Documentación técnica

Documento conciso que describe la carpeta `signals/` del proyecto Minishell: gestión de señales, responsabilidades, estrategias para master/child, ejemplos de pruebas y recomendaciones para debugging.

---

## 📌 Visión general

El módulo `signals` centraliza el manejo de señales relevantes para una shell: principalmente `SIGINT` (Ctrl-C) y `SIGQUIT` (Ctrl-\). Su objetivo es garantizar un comportamiento coherente entre el proceso principal (master) y los procesos hijos, evitando interrumpir la shell principal indebidamente y permitiendo que los hijos manejen señales según convenga.

---

## 🗂️ Contenido y responsabilidad (por fichero)

- `ft_signals.c` — Implementación de los handlers y utilidades para registrar/restaurar manejadores, separar comportamiento en proceso maestro y procesos hijos, y lógica especial para heredocs y ejecución de binarios.

El módulo debe exponer funciones para:

- Inicializar los handlers en el proceso principal.
- Restaurar la configuración por defecto en procesos hijos antes de `execve`.
- Gestión específica para heredoc (capturar interrupciones y limpiar temporales).

---

## 🧭 Principios de diseño y buenas prácticas

- **Separar responsabilidades:** el proceso master instala handlers que controlan la shell interactiva; los procesos hijos deben restaurar handlers por defecto o instalar handlers específicos según necesidad.
- **No imprimir desde handlers si puede evitarse:** los handlers deben ser seguros para ejecuciones asíncronas; si se necesita I/O, delegar a variables `volatile sig_atomic_t` y procesarlas en el loop principal.
- **Limpieza consistente:** en caso de señales durante `heredoc`, asegurarse de eliminar temporales y restablecer el estado.
- **Documentar efectos en las funciones públicas:** indicar qué hace cada inicializador y cuándo debería llamarse `restore_default_signals()` en el flujo de ejecución.

---

## 🔗 Comportamiento esperado (master vs children)

- Master (shell interactiva):
  - `SIGINT` debe interrumpir la entrada actual y devolver un prompt limpio (no finalizar la shell).
  - `SIGQUIT` suele ser ignorado o producir una salida manejada (según especificación del proyecto).

- Children (procesos fork + execve):
  - Restaurar acciones por defecto para `SIGINT`/`SIGQUIT` antes de `execve` para que programas externos reciban señales normalmente.

---

## 🔎 Pruebas manuales y automatizadas recomendadas

- Test manuales desde la shell:

```sh
# Ejecuta un binario largo y pulsa Ctrl-C
./minishell
sleep 30  # en otra sesión, enviar SIGINT con kill -INT <pid>

# Probar heredoc: pulsa Ctrl-C durante la entrada
./minishell
cat <<EOF
hola
^C (Ctrl-C enviado)
EOF
```

- Simular señales desde otra terminal:

```bash
kill -INT <pid>   # SIGINT
kill -QUIT <pid>  # SIGQUIT
```

- Pruebas manuales con Ctrl-C/Ctrl-\ durante ejecución interactiva para validar comportamiento.

---

## ⚙️ Cómo compilar y ejecutar pruebas

```bash
make fclean && make
./test_auto.sh
```

Para debug, habilita prints controlados (temporalmente) o registra el estado en variables atómicas para evitar operaciones inseguras dentro de handlers.

---

## 🧪 Casos de prueba importantes

- Ctrl-C durante lectura de línea (prompt) — la shell debe mostrar un prompt limpio y no terminar.
- Ctrl-C dentro de `heredoc` — cancelar heredoc, borrar temporales y volver al prompt.
- Ctrl-\ (SIGQUIT) en procesos hijos — debe comportarse según la especificación (habitualmente terminar con core dump en shells estándar; en este proyecto puede optarse por ignorarlo o mostrar mensaje).

---

## 🖼️ Diagrama sencillo (ASCII)

```
    +--------+
    | master |
    | shell  |
    +--------+
       |  ^
       |  | install handlers
       v  |
    [signal handler]
       |  |
       |  v
    fork() -> child (restore defaults) -> execve

Leyenda: master instala handlers; antes de execve, children restauran acciones por defecto.
```

---

## ✨ Cierre

El manejo de señales es crítico para una experiencia de shell robusta. 
