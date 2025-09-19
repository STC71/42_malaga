#include "array_bag.hpp"	// Implementación de un conjunto (bag) de enteros utilizando un arreglo
#include <iostream>			// Para la impresión de elementos

array_bag::array_bag() {
  size = 0;
  data = nullptr;
}
/*	Constructor por defecto que inicializa el arreglo y el tamaño.
	- Inicializa size a 0 y data a nullptr, indicando que el arreglo está vacío.
	- No se reserva memoria para data en este constructor, ya que el arreglo estará vacío inicialmente.	*/

array_bag::array_bag(const array_bag &src) {
  size = src.size;
  data = new int[size];
  for (int i = 0; i < size; i++) {
	data[i] = src.data[i];
  }
}
/*	Constructor de copia que inicializa un nuevo arreglo y copia los elementos del arreglo original.
	- Inicializa size con el tamaño del arreglo original.
	- Reserva memoria para el nuevo arreglo y copia los elementos del arreglo original. */

array_bag &array_bag::operator=(const array_bag &src) {
	if (this != &src) {
		if (data != nullptr) {
			delete[] data;		// Libera la memoria del arreglo actual si no es nullptr
			data = nullptr;		// Establece el puntero a nullptr para evitar punteros colgantes
		}
		size = src.size;		// Copia el tamaño del arreglo fuente
		data = new int[size];	// Reserva memoria para el nuevo arreglo
		for (int i = 0; i < size; i++) {
			data[i] = src.data[i];		// Copia los elementos del arreglo fuente
		}
	}
	return *this;
}
/*	Operador de asignación que asigna el contenido de otro array_bag al actual.
	- Comprueba si no es la misma instancia (self-assignment check).
	- Libera la memoria del arreglo actual si no es nullptr.
	- Copia el tamaño y los elementos del arreglo del objeto fuente.
	- Devuelve una referencia al objeto actual para permitir encadenamiento de asignaciones. */

array_bag::~array_bag() {
	if (data != nullptr) {
		delete[] data;		// Libera la memoria del arreglo
		data = nullptr;		// Establece el puntero a nullptr para evitar punteros colgantes
	}
}
/*	Destructor que libera la memoria del arreglo.	*/

void array_bag::insert(int item) {
	int *new_data = new int[size + 1];		// Crea un nuevo arreglo de tamaño incrementado
	for (int i = 0; i < size; i++) {
		new_data[i] = data[i];				// Copia los elementos existentes al nuevo arreglo
	}
	new_data[size] = item;					// Agrega el nuevo elemento al final
	if (data != nullptr) {
		delete[] data;						// Libera la memoria del arreglo antiguo
	}
	data = new_data;						// Actualiza el puntero al nuevo arreglo
	size++;									// Incrementa el tamaño para reflejar la adición
}
/*	Inserta un nuevo elemento en el arreglo.
	- Crea un nuevo arreglo de tamaño incrementado.
	- Copia los elementos existentes al nuevo arreglo.
	- Agrega el nuevo elemento al final.
	- Libera la memoria del arreglo antiguo y actualiza el puntero.	*/

void array_bag::insert(int *items, int count) {
	int *new_data = new int[size + count];	// Crea un nuevo arreglo de tamaño incrementado por la cantidad de elementos a insertar
	for (int i = 0; i < size; i++) {
		new_data[i] = data[i];				// Copia los elementos existentes al nuevo arreglo
	}
	for (int i = 0; i < count; i++) {
		new_data[size + i] = items[i];		// Agrega los nuevos elementos al final del nuevo arreglo
	}
	if (data != nullptr) {
		delete[] data;						// Libera la memoria del arreglo antiguo
	}
	data = new_data;						// Actualiza el puntero al nuevo arreglo
	size += count;							// Incrementa el tamaño para reflejar la adición
}
/*	Inserta un arreglo de elementos en el conjunto.
	- Crea un nuevo arreglo de tamaño incrementado por la cantidad de elementos a insertar.
	- Copia los elementos existentes al nuevo arreglo.
	- Agrega los nuevos elementos al final del nuevo arreglo.
	- Libera la memoria del arreglo antiguo y actualiza el puntero.	*/

void array_bag::print() const {
	for (int i = 0; i < size; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}
/*	Imprime los elementos del conjunto.
	- Recorre el arreglo y muestra cada elemento en la consola, seguido de un espacio.
	- Al final, imprime un salto de línea para mejorar la legibilidad.	*/

void array_bag::clear() {
	if (data != nullptr) {
		delete[] data;		// Libera la memoria del arreglo si no es nullptr
		data = nullptr;		// Establece el puntero a nullptr para evitar punteros colgantes
	}
	size = 0;				// Establece el tamaño a 0, indicando que el conjunto está vacío	
}
/*	Limpia el conjunto.
	- Libera la memoria del arreglo si no es nullptr.
	- Establece el puntero a nullptr y el tamaño a 0, indicando que el conjunto está vacío.	*/