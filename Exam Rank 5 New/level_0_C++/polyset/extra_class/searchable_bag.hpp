#pragma once

#include "bag.hpp"			// Incluye la definición de la clase base bag

class searchable_bag : virtual public bag {

/*	Clase que representa un conjunto (bag) de enteros con capacidad de búsqueda.
	- Hereda de la clase base bag.
	- Proporciona una interfaz para buscar elementos en el conjunto.	*/

public:
	virtual bool has(int) const = 0;	// Método virtual puro para buscar un elemento en el conjunto
};