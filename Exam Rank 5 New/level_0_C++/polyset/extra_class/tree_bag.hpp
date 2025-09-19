#pragma once

#include "bag.hpp"    // Incluye la definición de la clase base bag

class tree_bag : virtual public bag {

/*	Clase que representa un conjunto (bag) de enteros utilizando un árbol.
- Hereda de la clase base bag.
- Proporciona una interfaz para insertar y buscar elementos en el conjunto.	*/

protected:
	struct node {
		node *l;
		node *r;
		int value;
	};
	node *tree;		// Puntero a la raíz del árbol
	/*	Un nodo del árbol contiene un puntero al hijo izquierdo (l), un puntero al hijo derecho (r) y un valor (value).
		- l: Puntero al hijo izquierdo del nodo.
		- r: Puntero al hijo derecho del nodo.
		- value: Valor almacenado en el nodo.
		Esta estructura permite organizar los elementos en un árbol binario, facilitando la búsqueda y la inserción.	*/

public:
	tree_bag();										// Constructor por defecto
	tree_bag(const tree_bag &);	
	/*	Constructor de copia que inicializa un nuevo árbol y copia los elementos del árbol original
		- Inicializa tree con el árbol del objeto fuente.	*/
	virtual ~tree_bag();							// Destructor
	tree_bag &operator=(const tree_bag &);
	/*	Operador de asignación que copia los elementos de un árbol en otro
		- Asigna tree con el árbol del objeto fuente.	*/

	node *extract_tree();							// Extrae el árbol actual
	void set_tree(node *);							// Establece el árbol actual

	virtual void insert(int);						// Inserta un elemento en el árbol
	virtual void insert(int *array, int size);		// Inserta un arreglo de elementos en el árbol
	virtual void print() const;						// Imprime los elementos del árbol
	virtual void clear();							// Limpia el árbol
	/*	Se usa virtual para permitir la anulación en clases derivadas, o sea permite que las clases hijas
		puedan proporcionar su propia implementación de estos métodos.	*/

private:
	static void destroy_tree(node *);				// Destruye el árbol
	static void print_node(node *);					// Imprime un nodo del árbol
	static node *copy_node(node *);					// Copia un nodo del árbol
	/*	Se usa static para que estas funciones puedan ser llamadas sin necesidad de crear una instancia de la clase,
		lo que permite un acceso más fácil y directo a estas funciones utilitarias.		*/
};