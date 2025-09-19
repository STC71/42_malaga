#pragma once
#include "searchable_bag.hpp"	// Clase base que proporciona funcionalidad de búsqueda
#include "array_bag.hpp"		// Clase base que proporciona funcionalidad de arreglo

class searchable_array_bag : public searchable_bag, public array_bag {

	/*	Esta clase combina las funcionalidades de un conjunto (bag) y un arreglo (array).
		Hereda de searchable_bag y array_bag para proporcionar una implementación
		que permite buscar elementos en un arreglo.	*/
	public:
	searchable_array_bag() : array_bag() {}
	/*	Constructor por defecto que inicializa el arreglo y el tamaño.
		- El array se inicializa con un tamaño predeterminado y se establece en vacío.	*/
	searchable_array_bag(const searchable_array_bag &other) : array_bag(other) {}
	/*	Constructor de copia que inicializa el arreglo y el tamaño a partir de otro objeto.
		- Llama al constructor de copia de array_bag para copiar el contenido del arreglo.	*/
	searchable_array_bag &operator=(const searchable_array_bag &other) {
		if (this != &other)
			array_bag::operator=(other);	// Asigna el contenido del otro objeto al actual
		return *this;
	}
	/*	Con esto se asegura que el operador de asignación funcione correctamente
		y se copie el contenido del arreglo.	*/
	~searchable_array_bag() {}
	/*	Destructor que libera los recursos del arreglo.	*/

	bool has(int item) const
	{
		for (int i = 0; i < size; i++)	// size se hereda de array_bag en el constructor
			if (data[i] == item)		// data se hereda de array_bag en el constructor
				return true;
		return false;
	}
	/*	Implementa la búsqueda de un elemento en el arreglo.
		- Recorre el arreglo y devuelve true si encuentra el elemento, false en caso contrario.	*/
};
