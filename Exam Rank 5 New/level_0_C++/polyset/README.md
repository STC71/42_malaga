# 🧩 Polyset

**Colecciones, Bags y Sets en C++: estructuras flexibles y eficientes**

---

## 📚 Descripción general

Polyset es un proyecto educativo en C++ que explora la implementación de colecciones de enteros bajo dos paradigmas clásicos: las "bags" (bolsas, permiten repetidos) y los "sets" (conjuntos, solo elementos únicos). El proyecto muestra cómo diseñar jerarquías de clases, herencia múltiple y uso de estructuras de datos como arrays y árboles binarios de búsqueda.

---


## 🏗️ Estructura y clases principales

- **bag**: Interfaz abstracta para una colección de enteros.
- **searchable_bag**: Interfaz abstracta que añade búsqueda a una bag.
- **array_bag**: Implementación de bag usando un array dinámico.
- **tree_bag**: Implementación de bag usando un árbol binario de búsqueda.
- **searchable_array_bag**: Bag basada en array con búsqueda eficiente.
- **searchable_tree_bag**: Bag basada en árbol con búsqueda eficiente.
- **set**: Envuelve una searchable_bag y garantiza unicidad de elementos (comportamiento de conjunto matemático).


### 📝 Sobre los headers comentados y limpios

> **Nota sobre los includes y la estructura de directorios:**
> Los archivos de cabecera comentados y sin comentar usan rutas de include diferentes únicamente para adaptarse a la estructura de carpetas del proyecto (por ejemplo, `extra_class/`).
> En un proyecto típico, todos los headers estarían en el mismo nivel y los includes serían directos, sin necesidad de redireccionar a subcarpetas. Puedes reorganizar los archivos si lo prefieres y ajustar los includes en consecuencia.

Para facilitar el estudio y el desarrollo, cada clase principal tiene dos versiones de su archivo header:

- Archivos **_comentado.hpp**: Incluyen explicaciones detalladas y comentarios para facilitar el aprendizaje.
- Archivos **.hpp** (sin _comentado): Son versiones limpias, sin comentarios, recomendadas para uso en compilación, entrega o integración en otros proyectos.

Ambas versiones contienen exactamente el mismo código funcional.

---

## ⚡ ¿Qué puedes aprender con este proyecto?
- Diferencias entre bags y sets.
- Implementación de colecciones con arrays y árboles.
- Herencia múltiple y uso de clases abstractas en C++.
- Práctica de la forma canónica ortodoxa (constructores, destructores, copia, asignación).
- Cómo envolver y extender funcionalidades usando composición y herencia.

---

## 🧪 Ejemplo de uso
```cpp
#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"

int main(int argc, char **argv) {
    searchable_bag *t = new searchable_tree_bag;
    searchable_bag *a = new searchable_array_bag;
    t->insert(1); t->insert(2); t->insert(2);
    a->insert(3); a->insert(3); a->insert(4);
    t->print();
    a->print();
    set s(*a);
    s.insert(4); s.insert(5);
    s.print();
    return 0;
}
```

---

## ⚙️ Compilación y ejecución
1. Compila los archivos principales (recomendado usar flags -Wall -Werror -Wextra):
   ```sh
   g++ main.cpp set.cpp searchable_array_bag.cpp searchable_tree_bag.cpp extra_class/array_bag.cpp extra_class/tree_bag.cpp -o polyset_test -Wall -Werror -Wextra
   ```

   > **¿Por qué estas flags?**
   > - `-Wall` activa la mayoría de advertencias del compilador.
   > - `-Wextra` activa advertencias adicionales.
   > - `-Werror` convierte todas las advertencias en errores, obligándote a escribir código más seguro y limpio.

   Usar estas opciones ayuda a detectar posibles errores y a mantener un código de mayor calidad.

2. Ejecuta el programa:
   ```sh
   ./polyset_test
   ```

---

### Ejemplos de pruebas recomendadas

Puedes ejecutar el programa con diferentes argumentos para comprobar su funcionamiento. Aquí tienes algunos ejemplos útiles:

| Comando | Descripción |
|---------|-------------|
| `./polyset_test 5 10 15` | Inserta varios valores y comprueba inserción, búsqueda e impresión básica. |
| `./polyset_test 1 1 1 1` | Prueba la gestión de valores repetidos (duplicados). |
| `./polyset_test 10 9 8 7 6` | Inserta valores en orden descendente para comprobar el manejo de secuencias inversas. |
| `./polyset_test 0 -1 -5 3` | Inserta y busca valores negativos y cero. |
| `./polyset_test 1000000 2 999999 -1000000` | Prueba el manejo de valores extremos y mezcla de grandes y pequeños. |
| `./polyset_test 2147483647 -2147483648` | Inserta los valores extremos del tipo int de 32 bits. |
| `./polyset_test $(seq 1 1000)` | Inserta una gran cantidad de valores para comprobar el rendimiento y la robustez. |
| `./polyset_test 1 2 1 2 1 2` | Prueba la gestión de duplicados alternados. |
| `./polyset_test -1 -1 -1` | Prueba la gestión de valores negativos repetidos. |

Estas pruebas cubren casos típicos, límites y situaciones de estrés para asegurar la robustez del código.

- Puedes modificar `main.cpp` para hacer tus propias pruebas.
- Si usas otros archivos fuente, agrégalos al comando de compilación.

---


## 🛠️ Archivos principales
- `searchable_array_bag.cpp/hpp` y `searchable_array_bag_comentado.hpp`
- `searchable_tree_bag.cpp/hpp` y `searchable_tree_bag_comentado.hpp`
- `set.cpp/hpp` y `set_comentado.hpp`
- `main.cpp` (ejemplo y pruebas)
- Carpeta `extra_class/` (clases base y utilidades)

> **Recomendación:** Lee primero los headers comentados para entender la lógica y usa los headers limpios para compilar y entregar tu proyecto.

---

## 🚦 Consejos para dominar Polyset
- Lee primero los headers comentados para entender la jerarquía y relaciones.
- Dibuja diagramas de herencia y composición.
- Prueba a implementar una clase desde cero sin mirar el código.
- Modifica el `main.cpp` para experimentar con diferentes entradas y observa el comportamiento.
- Reflexiona sobre las ventajas y desventajas de cada estructura (array vs árbol).
- Prepárate para explicar la diferencia entre bag y set en una entrevista.

---

## 👨‍💻 Autoría
Ejercicio de programación avanzada en C++ para practicar estructuras de datos, herencia y diseño orientado a objetos. sternero (2025).
