<div align="center">

# 🖨️ FT_PRINTF

### *Porque `ft_putnbr()` y `ft_putstr()` no son suficientes...*

[![42 School](https://img.shields.io/badge/42-Málaga-000000?style=for-the-badge&logo=42&logoColor=white)](https://www.42malaga.com/)
[![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge&logo=42&logoColor=white)](https://github.com/42School/norminette)
[![Calificación](https://img.shields.io/badge/Calificación-125%2F100-success?style=for-the-badge)](.)
[![Lenguaje](https://img.shields.io/badge/Lenguaje-C-blue?style=for-the-badge&logo=c)](.)

<img src="https://raw.githubusercontent.com/byaliego/42-project-badges/main/badges/ft_printfe.png" alt="ft_printf badge" width="150"/>

*Reimplementación completa de la función `printf()` de la biblioteca estándar de C*

[Instalación](#-instalación) • [Uso](#-uso) • [Testing](#-testing) • [Documentación](TECHNICAL.md)

</div>

---

## 🎯 Descripción

**ft_printf** es una reimplementación de `printf()` desarrollada para el currículo de **42 School**, demostrando dominio de funciones variádicas, parseo de cadenas, operaciones I/O de bajo nivel y arquitectura modular.

**🏆 Calificación: 125/100** *(Obligatorio + Todos los Bonus)*

### ✨ Características

**Conversiones soportadas:**
```c
%c  %s  %p  %d  %i  %u  %x  %X  %%
```

**Bonus flags:**
```c
-    // Justificación izquierda
0    // Relleno con ceros
.    // Precisión
#    // Forma alternativa (0x/0X)
+    // Mostrar siempre el signo
' '  // Espacio antes de positivos
```

**Ancho y precisión:**
- Ancho mínimo de campo
- Precisión numérica y de strings
- Valores dinámicos con `*`

---

## 🚀 Instalación

```bash
# Clonar o descargar el proyecto
cd ft_printf_bonus

# Compilar (con bonus)
make bonus

# Usar en tu programa
cc tu_programa.c -L. -lftprintf -o programa
./programa
```

**Comandos make:**
```bash
make          # Compilar parte obligatoria
make bonus    # Compilar con bonus
make test     # Ejecutar 54 tests
make clean    # Limpiar objetos
make fclean   # Limpiar todo
```

---

## 💡 Ejemplos de Uso

### Básico
```c
#include "ft_printf.h"

ft_printf("Hola, %s!\n", "Mundo");           // Hola, Mundo!
ft_printf("Número: %d\n", 42);               // Número: 42
ft_printf("Hex: %x\n", 255);                 // Hex: ff
ft_printf("Dirección: %p\n", &var);          // Dirección: 0x7ffd...
```

### Con Bonus
```c
ft_printf("|%10d|\n", 42);                   // |        42|
ft_printf("|%-10d|\n", 42);                  // |42        |
ft_printf("|%010d|\n", 42);                  // |0000000042|
ft_printf("%.5d\n", 42);                     // 00042
ft_printf("%#x\n", 255);                     // 0xff
ft_printf("%+d\n", 42);                      // +42
ft_printf("%*.*d\n", 10, 5, 42);             //      00042
```

---

## 🧪 Testing

```bash
# Ejecutar suite completa (54 tests)
make test
```

**Resultados:**
- ✅ **54/54 tests** aprobados
- ✅ **0 fugas** de memoria (valgrind)
- ✅ **100% Norminette** (14 archivos)

<details>
<summary><b>Ver categorías de tests</b></summary>

- ✅ Conversiones obligatorias (17 tests)
- ✅ Flags bonus (20 tests)
- ✅ Combinaciones de flags (10 tests)
- ✅ Casos límite (7 tests)

</details>

---

## 📁 Estructura

```
ft_printf_bonus/
├── ft_printf.h              # Header obligatorio
├── ft_printf.c              # Implementación básica
├── ft_printf_bonus.h        # Header con bonus
├── ft_printf_bonus.c        # Parser completo
├── ft_parse_bonus.c         # Utilidades de parsing
├── ft_dispatch_bonus.c      # Router de conversiones
├── ft_utils_bonus.c         # Utilidades
├── ft_numlen_bonus.c        # Cálculo de longitudes
├── ft_putnbr_bonus.c        # Enteros con flags
├── ft_putunsigned_bonus.c   # Sin signo/hex
├── ft_putptr_bonus.c        # Punteros
├── Makefile                 # Sistema de build
└── libftprintf.a            # Biblioteca compilada
```

---

## 📚 Documentación

- **[TECHNICAL.md](TECHNICAL.md)** - Arquitectura, funciones y rendimiento

### Especificaciones Técnicas

- ✅ Norminette 42 v3.x compliant
- ✅ Máx. 25 líneas por función
- ✅ Sin fugas de memoria
- ✅ Funciones variádicas ISO C99
- ✅ Solo syscall `write()`

---

## 🎓 Aprendizajes

Este proyecto demuestra dominio de:

- **Funciones variádicas** (`va_start`, `va_arg`, `va_end`)
- **Parseo complejo** de cadenas de formato
- **I/O de bajo nivel** con `write()`
- **Gestión de memoria** sin fugas
- **Arquitectura modular** y código limpio
- **Testing exhaustivo** de casos límite

---

## 👨‍💻 Autor

**sternero** - 42 Málaga | Noviembre 2024

[![42 Profile](https://img.shields.io/badge/42-Perfil-000000?style=flat-square&logo=42)](https://profile.intra.42.fr/)
[![GitHub](https://img.shields.io/badge/GitHub-STC71-181717?style=flat-square&logo=github)](https://github.com/STC71)

---

## ⚠️ Nota Académica

Este proyecto es parte del currículo de **42 School**:

- ✅ Libre para **aprendizaje** y **referencia**
- 🚫 **NO copiar** para entregas (viola política académica)
- ✅ Úsalo para **entender conceptos**
- ✅ Escribe tu **propia implementación**

---

<div align="center">

**¡Feliz Coding! 🚀**

*Construido con ❤️ en 42 Málaga*

</div>
