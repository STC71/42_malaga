#include "tree_bag.hpp"			// Incluye la definición de la clase tree_bag
#include <iostream>				// Incluye la biblioteca iostream para operaciones de entrada/salida

tree_bag::tree_bag() {
	tree = nullptr;
}
/*	Constructor por defecto que inicializa el árbol como vacío (nullptr).	*/

tree_bag::tree_bag(const tree_bag &src) {
	tree = copy_node(src.tree);
}
/*	Constructor de copia que inicializa un nuevo árbol y copia los elementos del árbol original.
	- Utiliza la función copy_node para crear una copia profunda del árbol del objeto fuente.	*/

tree_bag::~tree_bag() {
	destroy_tree(tree);
}
/*	Destructor que destruye el árbol llamando a destroy_tree.	*/

tree_bag &tree_bag::operator=(const tree_bag &src) {
	if (this != &src) {
		destroy_tree(tree);				// Destruye el árbol actual
		tree = copy_node(src.tree);		// Crea una copia del árbol fuente
	}
	/*	Comprueba si el árbol fuente es diferente del árbol actual
		para evitar autoasignación.	*/
	return *this;						// Devuelve la referencia al objeto actual
}
/*	Operador de asignación que copia los elementos de un árbol en otro
	- Asigna tree con el árbol del objeto fuente.	*/

tree_bag::node *tree_bag::extract_tree() {
	node *temp = tree;					// Guarda el árbol actual
	tree = nullptr;						// Establece el árbol actual como vacío
	return temp;						//
}
/*	Extrae el árbol actual y lo establece como vacío.	*/

void tree_bag::set_tree(node *new_tree) {
	destroy_tree(tree);
	tree = new_tree;
}
/*	Establece el árbol actual a un nuevo árbol.
	- Destruye el árbol actual antes de asignar el nuevo árbol.	*/

void tree_bag::insert(int item) {
	node *new_node = new node;
	std::cout << "create node: " << item << std::endl;
	new_node->value = item;
	new_node->l = nullptr;
	new_node->r = nullptr;

	if (tree == nullptr) {
		tree = new_node;
	} else {
		node *current = tree;
		while (true) {
			if (item < current->value) {
				if (current->l == nullptr) {
					current->l = new_node;
					break;
				} else {
					current = current->l;
				}
			} else if (item > current->value) {
				if (current->r == nullptr) {
					current->r = new_node;
					break;
				} else {
					current = current->r;
				}
			} else {
				std::cout << "duplicate value: delete node" << std::endl;
				delete new_node;
				break;
			}
		}
	}
}
/*	Inserta un solo elemento en el árbol.	*/

void tree_bag::insert(int *items, int count) {
	for (int i = 0; i < count; i++) {
		insert(items[i]);
	}
}
/*	Inserta un arreglo de elementos en el árbol.
	- Recorre el arreglo y llama a insert para cada elemento.	*/

void tree_bag::print() const {
	print_node(tree);
	std::cout << std::endl;
}
/*	Imprime los elementos del árbol en orden.	*/

void tree_bag::clear() {
	destroy_tree(tree);
	tree = nullptr;
}
/*	Destruye el árbol actual y lo establece como vacío.	*/

void tree_bag::destroy_tree(node *current) {
	if (current != nullptr) {
		std::cout << "destroying value: " << current->value << std::endl;
		destroy_tree(current->l);
		destroy_tree(current->r);
		delete current;
	}
}
/*	Destruye el árbol actual y lo establece como vacío.	La diferencia con el anterior es que este método
	se llama recursivamente para eliminar todos los nodos del árbol, mientras que el anterior solo eliminaba el nodo raíz.	*/

void tree_bag::print_node(node *current) {
	if (current != nullptr) {
		print_node(current->l);
		if (current->value != 0)
			std::cout << current->value << " ";
		print_node(current->r);
	}
}
/*	Imprime los elementos del árbol en orden.	*/

tree_bag::node *tree_bag::copy_node(node *current) {
	if (current == nullptr) {
		return nullptr;
	} else {
		node *new_node = new node;					// Crea un nuevo nodo// defined as static functions in the class
		new_node->value = current->value;			// Copia el valor del nodo actual
		new_node->l = copy_node(current->l);		// Copia el subárbol izquierdo
		new_node->r = copy_node(current->r);		// Copia el subárbol derecho
		return new_node;							// Devuelve el nuevo nodo copiado
	}
}
/*	Copia un nodo del árbol.	*/