# 📦 bigint

Una clase C++ para enteros de precisión arbitraria

---

## 🚀 ¿Qué es `bigint`?
`bigint` es una clase en C++ que permite trabajar con números enteros no negativos tan grandes como necesites, sin perder precisión. Es ideal para cálculos matemáticos, criptografía, o cualquier situación donde los tipos estándar (`int`, `unsigned long`, etc.) no son suficientes.

---

## ✨ Características principales
- **Precisión ilimitada:** Trabaja con números tan grandes como permita la memoria de tu equipo.
- **Operaciones soportadas:**
  - Suma (`+`, `+=`)
  - Comparaciones (`<`, `>`, `<=`, `>=`, `==`, `!=`)
  - Desplazamiento de dígitos ("digitshift") a la izquierda y derecha (`<<`, `>>`, `<<=`, `>>=`), equivalente a multiplicar o dividir por potencias de 10.
- **Impresión directa:** Compatible con `std::cout` sin ceros a la izquierda.

---

## 🛠️ Archivos del proyecto
- `bigint.hpp` — Declaración e implementación de la clase.
- `bigint_comentado.hpp` — Igual que el anterior pero con el código comentado.
- `bigint.cpp` — Archivo fuente (puede estar vacío si todo está en el header).
- `main.cpp` — Ejemplo de uso y pruebas.

---

## 📝 Ejemplo de uso
```cpp
#include "bigint.hpp"
#include <iostream>

int main() {
    bigint a(42), b(21), c, d(1337), e(d);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "(c += a) = " << (c += a) << std::endl;
    std::cout << "++b = " << ++b << std::endl;
    std::cout << "b++ = " << b++ << std::endl;
    std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
    std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;
    std::cout << "(d < a) = " << (d < a) << std::endl;
    std::cout << "(d == a) = " << (d == a) << std::endl;
}
```

---

## ⚙️ Compilación y ejecución
1. Compila los archivos (recomendado usar flags -Wall -Werror -Wextra):
   ```sh
   g++ main.cpp bigint.cpp -o bigint_test -Wall -Werror -Wextra
   ```

   > **¿Por qué estas flags?**
   > - `-Wall` activa la mayoría de advertencias del compilador.
   > - `-Wextra` activa advertencias adicionales.
   > - `-Werror` convierte todas las advertencias en errores, obligándote a escribir código más seguro y limpio.

   Usar estas opciones ayuda a detectar posibles errores y a mantener un código de mayor calidad.
2. Ejecuta el programa:
   ```sh
   ./bigint_test
   ```

---

## 💡 Notas
- Puedes modificar `main.cpp` para hacer tus propias pruebas.
- El archivo `bigint.cpp` puede estar vacío si toda la implementación está en el header.
- El código es didáctico y fácil de entender.

---


---

## 🎯 Consejos para aprender y dominar este proyecto

Si quieres prepararte para un examen o entrevista técnica, aquí tienes algunos consejos para comprender y asimilar el contenido de este proyecto de forma eficiente:

- **Lee primero el código comentado:** Empieza por `bigint_comentado.hpp` para entender la lógica y el propósito de cada parte del código.
- **Haz pruebas propias:** Modifica y amplía `main.cpp` con tus propios casos de prueba. Experimenta con números grandes y observa los resultados.
- **Dibuja el flujo de operaciones:** Haz esquemas o diagramas de cómo se realiza la suma, el "digitshift" y las comparaciones internamente.
- **Implementa desde cero:** Intenta reescribir la clase `bigint` en un archivo aparte, sin mirar el original, para afianzar los conceptos.
- **Explica el código en voz alta:** Enseñar o explicar el funcionamiento a otra persona (o a ti mismo) ayuda a detectar lagunas de comprensión.
- **Comprende la utilidad de cada operador:** Asegúrate de saber cuándo y por qué usar cada operador sobrecargado (`+`, `<<`, `>>`, etc.).
- **Consulta documentación estándar:** Familiarízate con métodos de `std::string` y buenas prácticas de C++.
- **Simula preguntas de entrevista:** Piensa en posibles preguntas que te harían sobre la implementación, eficiencia, o posibles mejoras.

Estos pasos te ayudarán a interiorizar el funcionamiento de la clase y a estar preparado para explicarla o implementarla en cualquier contexto técnico.

---

## 🧑‍💻 Autoría
Proyecto realizado como ejercicio de programación avanzada en C++. sternero (2025).
