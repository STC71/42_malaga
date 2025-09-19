# 🟦 vect2

**Vectores bidimensionales en C++: operaciones y manipulación sencilla**

---

## 📚 Descripción general

`vect2` es una clase C++ que representa un vector matemático de dimensión 2 con componentes enteros. Permite realizar operaciones básicas como suma, resta, multiplicación por un escalar, acceso por índice y comparación, facilitando el trabajo con álgebra vectorial en programas sencillos o educativos.

---

## ✨ Características principales
- **Suma y resta de vectores:** Usa los operadores `+`, `-`, `+=`, `-=` para combinar vectores fácilmente.
- **Multiplicación por escalar:** Multiplica un vector por un número entero con `*` y `*=` (soporta tanto `v * 3` como `3 * v`).
- **Acceso por índice:** Accede o modifica las componentes con `v[0]` (x) y `v[1]` (y).
- **Incremento y decremento:** Usa `++` y `--` para sumar o restar 1 a ambas componentes.
- **Comparación:** Comprueba igualdad o diferencia con `==` y `!=`.
- **Impresión directa:** Muestra el vector en formato `{x, y}` usando `std::cout`.

---

## 🛠️ Archivos del proyecto
- `vect2.hpp` — Declaración e implementación de la clase (versión limpia, sin comentarios).
- `vect2_comentado.hpp` — Versión comentada, ideal para el estudio y comprensión detallada del código.
- `vect2.cpp` — Archivo fuente (puede estar vacío si todo está en el header).
- `main.cpp` — Ejemplo de uso y pruebas.

---

## ⚙️ Compilación y ejecución
1. Compila los archivos principales (recomendado usar flags -Wall -Werror -Wextra):
   ```sh
   g++ main.cpp vect2.cpp -o vect2_test -Wall -Werror -Wextra
   ```

   > **¿Por qué estas flags?**
   > - `-Wall` activa la mayoría de advertencias del compilador.
   > - `-Wextra` activa advertencias adicionales.
   > - `-Werror` convierte todas las advertencias en errores, obligándote a escribir código más seguro y limpio.

   Usar estas opciones ayuda a detectar posibles errores y a mantener un código de mayor calidad.
2. Ejecuta el programa:
   ```sh
   ./vect2_test
   ```

- Puedes modificar `main.cpp` para hacer tus propias pruebas.
- Si usas otros archivos fuente, agrégalos al comando de compilación.

---

## 🧪 Ejemplo de uso
```cpp
#include "vect2.hpp"
#include <iostream>

int main() {
    vect2 a(1, 2), b(3, 4);
    std::cout << a + b << std::endl; // {4, 6}
    a += b;
    std::cout << a << std::endl;     // {4, 6}
    std::cout << a * 2 << std::endl; // {8, 12}
    std::cout << 2 * a << std::endl; // {8, 12}
    std::cout << -a << std::endl;    // {-4, -6}
    std::cout << (a == b) << std::endl; // 0 (false)
    std::cout << a[0] << ", " << a[1] << std::endl; // 4, 6
}
```

---

## 🚦 Consejos para dominar vect2
- Prueba todas las operaciones en `main.cpp` y observa los resultados.
- Usa el operador `[]` para acceder y modificar componentes de forma intuitiva.
- Experimenta con los operadores de incremento y decremento para ver cómo afectan al vector.
- Lee el código fuente y los comentarios para entender la lógica de cada operador.
- Reflexiona sobre cómo podrías extender la clase a más dimensiones o a otros tipos de datos.

---

## 👨‍💻 Autoría
Ejercicio de programación en C++ para practicar sobrecarga de operadores, encapsulamiento y álgebra vectorial básica. sternero (2025).
