#pragma once

#include "bag.hpp"    // Interfaz para un conjunto (bag) de enteros

class array_bag : virtual public bag {

  /*  Esta clase implementa un conjunto (bag) de enteros utilizando un arreglo.
      Hereda de la interfaz bag para proporcionar una implementación concreta
      que permite insertar, imprimir y limpiar elementos en un arreglo.	*/

protected:
  int *data;    // Puntero al arreglo que contiene los elementos
  int size;     // Tamaño actual del arreglo

public:
  array_bag();  // Constructor por defecto que inicializa el arreglo y el tamaño
  array_bag(const array_bag &);     // Constructor de copia
  array_bag &operator=(const array_bag &other);     // Operador de asignación
  ~array_bag();     // Destructor que libera la memoria del arreglo

  void insert(int);         // Inserta un elemento en el conjunto
  void insert(int *, int);  // Inserta un arreglo de elementos en el conjunto
  void print() const;       // Imprime los elementos del conjunto
  void clear();             // Limpia el conjunto
};