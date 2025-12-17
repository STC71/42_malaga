# Minishell — Proyecto

**Autores:** druiz-ca & sternero
**Versión:** 2.0 (con características bonus integradas)

## 📋 Descripción

Minishell es una implementación de una shell mínima en C (parsing, execution, builtins) diseñada para replicar comportamientos POSIX básicos y varias funcionalidades bonus. Este `README` actúa como índice y guía rápida; la documentación por módulo se encuentra en `*/README.md` dentro de cada carpeta.

---

## 📁 Estructura del repositorio (resumen)

- `includes/` — Tipos, macros y cabeceras compartidas. Ver `includes/README.md`.
- `libft/` — Librería utilitaria local (`ft_*`). Ver `libft/README.md`.
- `parser/` — Tokenización y construcción de estructuras (AST/nodos). Ver `parser/README.md`.
- `executor/` — Lógica de ejecución, redirecciones y pipelines. Ver `executor/README.md`.
- `builtins/` — Implementación de comandos internos (`cd`, `echo`, `pwd`, `export`, etc.). Ver `builtins/README.md`.
- `signals/` — Manejo centralizado de señales (SIGINT, SIGQUIT). Ver `signals/README.md`.
- `test_auto.sh` — Suite automatizada de tests (115 pruebas comprehensivas).
- `test.sh` — Suite interactiva según hoja de evaluación oficial de 42.

---

## 🚀 Quick start

```bash
# Limpiar y compilar
make fclean && make

# Ejecutar la shell
./minishell
```

---

## 🧪 Pruebas y QA

### Suites de tests disponibles

El proyecto incluye dos suites de tests complementarias:

**1. test_auto.sh** — Suite automatizada comprehensiva (recomendado para CI/desarrollo)

```bash
# Ejecución completa (genera reporte detallado)
./test_auto.sh

# Ejecución rápida (omite stress tests)
./test_auto.sh --fast
```

- 115 tests automatizados que cubren todos los aspectos del minishell
- Genera automáticamente `test_auto_result.md` con reporte detallado
- Ideal para validación rápida durante desarrollo

**2. test.sh** — Suite interactiva según hoja de evaluación oficial

```bash
# Ejecución interactiva completa
./test.sh

# Modo rápido (sin confirmaciones manuales)
./test.sh --quick
```

- Sigue exactamente la hoja de evaluación oficial de 42 School
- Permite validación manual de comportamiento interactivo
- Genera `test_result.md` con resultados de evaluación
- Ideal para preparación de evaluación peer-to-peer

### Análisis de memoria (Valgrind)

Usa Valgrind para analizar casos específicos:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

Nota: `readline` puede generar informes que suelen ser aceptables en este contexto; usa supresiones si es necesario.

### Norminette (estilo)

Ejecuta la comprobación de estilo en los módulos modificados:

```bash
norminette includes/*.h libft/*.c parser/*.c builtins/*.c executor/*.c
```

---

## 🛠️ Flujo recomendado de QA antes de PR

1. Compilar: `make fclean && make`.
2. Ejecutar: `./test_auto.sh` y revisar fallos.
3. Si hay fallos de memoria, ejecutar Valgrind en los binarios afectados.
4. Corregir código y ejecutar `norminette` sobre los archivos modificados.
5. Añadir/actualizar pruebas en `test_auto.sh` que cubran el caso.

---


