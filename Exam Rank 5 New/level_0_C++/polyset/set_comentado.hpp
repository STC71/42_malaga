#pragma once
#include "searchable_bag.hpp"		// Incluye la definición de la clase searchable_bag

class set {

	/*	Esta clase representa un conjunto (set) de enteros utilizando una instancia de searchable_bag.
		- Permite insertar elementos en el conjunto, asegurando que no se repitan.
		- Utiliza la clase searchable_bag para gestionar los elementos.		*/

	private:
		searchable_bag &bag;
		/*	Referencia a la instancia de searchable_bag para gestionar los elementos del conjunto	*/
	public:
		set(searchable_bag &bg) : bag(bg) {}		// Constructor que inicializa la referencia a searchable_bag
		~set() {}									// Destructor
		void insert(int item) {
			if (!bag.has(item))						// Verifica si el elemento item no está en el conjunto bag
				bag.insert(item);					// Si no está, lo inserta en el conjunto
		}
		/*	Inserta un solo elemento en el conjunto.	*/
		void insert(int *items, int count) {
			for (int i = 0; i < count; i++)
				insert(items[i]);
		}
		/*	Inserta un arreglo de elementos en el conjunto.	*/
		bool has(int item) const {
			return bag.has(item);					// Retorna true si el elemento item está en el conjunto bag
		}
		/*	Comprueba si un elemento está en el conjunto.	*/
		void print() {
			bag.print();
		}
		/*	Imprime los elementos del conjunto.		*/
		void clear() {
			bag.clear();
		}
		/*	Destruye el conjunto.	*/
		searchable_bag &get_bag() {
			return bag;
		}
		/*	Devuelve la referencia a la instancia de searchable_bag. Útil para acceder a las operaciones de la
			bolsa subyacente, como la búsqueda y eliminación de elementos.	*/

};