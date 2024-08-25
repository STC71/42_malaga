/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-25 08:33:11 by sternero          #+#    #+#             */
/*   Updated: 2024-08-25 08:33:11 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

// Passed Moulinette 2019.09.01

#include <stdlib.h>
#include "ft_list.h"

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	if (begin_list == NULL || *begin_list == NULL)
		return;
	t_list *tmp = *begin_list;
	if (cmp(tmp->data, data_ref) == 0)
	{
		*begin_list = tmp->next;
		free(tmp);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
	{
		tmp = *begin_list;
		ft_list_remove_if(&tmp->next, data_ref, cmp);
	}
}

/*
The ft_list_remove_if function removes nodes from a linked list that contain
a given reference value. It takes three arguments: a pointer to the pointer
of the first node of the list (begin_list), a pointer to the reference value
(data_ref, the one to be removed), and a pointer to a comparison function (cmp)
that compares the reference value with the value of a node in the list. We
understand that if the comparison function returns 0, the node should be removed,
as the value matches the reference value.

int (*cmp)() is a function pointer that takes no arguments and returns an int.
It is used to point to the comparison function that compares the value of a node
with the reference value. If returns 0, means that the node is equal to the
reference value and should be removed.

Function Body:

The function starts with a series of base case checks. If the pointer to the
pointer of the first node of the list is NULL or the pointer to the first node
of the list is NULL, the function exits without doing anything.

Then, a variable tmp is declared that points to the first node of the list.
It checks if the value of the first node matches the reference value using the
comparison function cmp. If the value matches, the node is removed by making
the pointer to the first node point to the next node and freeing the memory of
the removed node. Then, the function is called recursively with the pointer to
the pointer of the new first node of the list (begin_list), the reference value
(data_ref), and the comparison function (cmp).

Alternatively (else), if the value of the first node does not match the reference
value, tmp is assigned the pointer to the first node of the list and the function
is called recursively with the pointer to the pointer of the next node of the list
(tmp->next), the reference value (data_ref), and the comparison function (cmp).

& means that the memory address of the pointer to the next node is passed, the
difference with * is that * accesses the value of the memory address, the value
contained in the memory address, while & accesses the memory address itself.

The function will continue to be called recursively until all nodes in the list
that contain the reference value are removed.

Example Usage:

Suppose we have a linked list of integers and we want to remove all nodes that
contain the value 42. We can define a comparison function that compares the value
of a node with the reference value and then use the ft_list_remove_if function to
remove the nodes that contain the value 42 from the list.

Here is an example of how the ft_list_remove_if function could be used to remove
nodes that contain the value 42 from a linked list:

int cmp(void *data, void *data_ref)
{
    return (*(int *)data == *(int *)data_ref);
}

int main(void)
{
    t_list *list = NULL;

    // Add elements to the list (not shown here)

    int data_ref = 42;

    // Call the ft_list_remove_if function to remove nodes that contain 
    // the value 42
    
    ft_list_remove_if(&list, &data_ref, &cmp);

    return 0;
}

In this example, the cmp function compares the value of a node with the reference
value. Then, in the main function, a linked list (list) is created and the
ft_list_remove_if function is called to remove nodes that contain the value 42
from the list using the comparison function cmp. Each time the ft_list_remove_if
function is called, nodes that contain the value 42 are removed from the list,
leaving only nodes that do NOT contain the reference value.
*/


/*
La función ft_list_remove_if elimina los nodos de una lista enlazada que 
contienen un valor de referencia dado. Toma tres argumentos: un puntero al
puntero del primer nodo de la lista (begin_list), un puntero al valor de
referencia (data_ref, la que se va a eliminar) y un puntero a una función
de comparación (cmp) que compara el valor de referencia con el valor de un
nodo de la lista. Entendemos que si la función de comparación devuelve 0,
el nodo debe ser eliminado, ya que el valor coincide con el valor de
referencia.

int (*cmp)() es un puntero a función que no toma argumentos y devuelve un int.
Se utiliza para apuntar a la función de comparación que compara el valor de
un nodo con el valor de referencia. Si devuelve 0, significa que el nodo es
igual al valor de referencia y debe ser eliminado.

Cuerpo de la función:

La función comienza con una serie de comprobaciones de casos base. Si el
puntero al puntero del primer nodo de la lista es NULL o el puntero al
primer nodo de la lista es NULL, la función termina sin hacer nada.

Luego, se declara una variable tmp que apunta al primer nodo de la lista.
Se comprueba si el valor del primer nodo coincide con el valor de referencia
utilizando la función de comparación cmp. Si el valor coincide, se elimina
el nodo haciendo que el puntero al primer nodo apunte al siguiente nodo y
liberando la memoria del nodo eliminado. Luego, se llama a la función
recursivamente con el puntero al puntero del nuevo primer nodo de la lista
(begin_list), el valor de referencia (data_ref) y la función de comparación
(cmp).

Por el contrario (else), si el valor del primer nodo no coincide con el valor
de referencia, se asigna a tmp el puntero al primer nodo de la lista y se
llama a la función de forma recursiva con el puntero al puntero del siguiente
nodo de la lista (tmp->next), el valor de referencia (data_ref) y la función
de comparación (cmp).

& significa que se pasa la dirección de memoria del puntero al siguiente nodo,
la diferencia con * es que * accede al valor de la dirección de memoria, el 
valor que contiene la dirección de memoria, mientras que & accede a la dirección
de memoria en sí.

La función seguirá llamanándose recursivamente hasta que se eliminen todos
los nodos de la lista que contienen el valor de referencia.

Ejemplo de uso:

Supongamos que tenemos una lista enlazada de números enteros y queremos eliminar
todos los nodos que contienen el valor 42. Podemos definir una función de
comparación que compare el valor de un nodo con el valor de referencia y luego
usar la función ft_list_remove_if para eliminar los nodos que contienen el valor
42 de la lista.

Aquí hay un ejemplo de cómo se podría usar la función ft_list_remove_if para
eliminar los nodos que contienen el valor 42 de una lista enlazada:

int cmp(void *data, void *data_ref)
{
    return (*(int *)data == *(int *)data_ref);
}

int main(void)
{
    t_list *list = NULL;

    // Añadir elementos a la lista (no se muestra aquí)

    int data_ref = 42;

    // Llamar a la función ft_list_remove_if para eliminar los nodos que 
    // contienen el valor 42
    
    ft_list_remove_if(&list, &data_ref, &cmp);

    return 0;
}

En este ejemplo, la función cmp compara el valor de un nodo con el valor de
referencia. Luego, en la función main, se crea una lista enlazada (list) y se
llama a la función ft_list_remove_if para eliminar los nodos que contienen el
valor 42 de la lista utilizando la función de comparación cmp. Cada vez que se
llama a la función ft_list_remove_if, se eliminan los nodos que contienen el
valor 42 de la lista, dejando solo los nodos que NO contienen el valor de
referencia.
*/