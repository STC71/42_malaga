#pragma once
#include "tree_bag.hpp"				// Clase base que proporciona funcionalidad de árbol
#include "searchable_bag.hpp"		// Clase base que proporciona funcionalidad de búsqueda

class searchable_tree_bag : public tree_bag, public searchable_bag {

	/*	Esta clase combina las funcionalidades de un conjunto (bag) y un árbol (tree).
		Hereda de tree_bag y searchable_bag para proporcionar una implementación
		que permite buscar elementos en un árbol. En este contexto, un árbol
		es una estructura de datos jerárquica que permite una búsqueda eficiente, en el que
		los elementos están organizados en nodos. Cada nodo tiene un valor y referencias
		a sus hijos izquierdo y derecho, lo que permite realizar búsquedas de manera
		más rápida que en un arreglo desordenado.	*/

	public:
	searchable_tree_bag() : tree_bag() {}
	/*	Constructor por defecto que inicializa el árbol y el tamaño.
		- El árbol se inicializa como vacío.	*/
	searchable_tree_bag( const searchable_tree_bag &other) : tree_bag(other) {}
	/*	Constructor de copia que inicializa el árbol y el tamaño a partir de otro objeto.
		- Llama al constructor de copia de tree_bag para copiar el contenido del árbol.	*/
	searchable_tree_bag& operator=(const searchable_tree_bag &other) {
		if (this != &other)
			tree_bag::operator=(other);		// Asigna el contenido del otro objeto al actual
		return *this;
	}
	/*	Con esto se asegura que el operador de asignación funcione correctamente
		y se copie el contenido del árbol.	*/
	~searchable_tree_bag() {}
	/*	Destructor que libera los recursos del árbol.	*/

	bool has(int item) const
	{
		node *current = tree;					// Apunta a la raíz del árbol
		while (current)
		{
			if (item == current->value)			// Compara el valor del nodo actual con el elemento buscado
				return true;
			else if (item > current->value)		// Si el elemento es mayor, se mueve a la derecha
				current = current->r;
			else
				current = current->l;			// Si el elemento es menor, se mueve a la izquierda
		}
		return false;
	}
	/*	Implementa la búsqueda de un elemento en el árbol.
		- Utiliza un recorrido en profundidad (DFS) para buscar el elemento.
		- Devuelve true si encuentra el elemento, false en caso contrario.
		Ejemplo: has(5) buscará el elemento 5 en el árbol.	*/
};
