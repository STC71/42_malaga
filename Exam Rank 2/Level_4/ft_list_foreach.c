/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-25 07:29:31 by sternero          #+#    #+#             */
/*   Updated: 2024-08-25 07:29:31 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
    while (begin_list)
    {
        (*f)(begin_list->data);
        begin_list = begin_list->next;
    }
}


/*
The ft_list_foreach function traverses a linked list and applies a given function to each
element of the list. It takes two arguments: a pointer to the first element (first node) 
of the list; and a pointer to a function that takes a pointer to void as an argument and
returns nothing. This function is applied to each element of the list.

Function Body:

The function starts with a while loop that traverses the linked list. In each iteration
of the loop, the function f is applied to the data stored in the current node of the list.
The function f is called using function pointer notation (*f) and the pointer to void
pointing to the data stored in the node (begin_list->data) is passed as an argument.

After applying the function to the current node, the pointer will move to the next node
in the list (begin_list = begin_list->next) to continue traversing the list. The loop
will continue until the end of the list is reached, i.e., until begin_list is NULL.

Example Usage:

Suppose we want to print the data (char *) stored in each node of a linked list. We can
define a function that prints a char * data and then use the ft_list_foreach function to
apply this function to each element of the list.

Here is an example of how the ft_list_foreach function could be used to print the data
from a linked list:

void print_data(void *data)
{
    printf("%s\n", (char *)data);
}

int main(void)
{
    t_list *list = NULL;

    // Add elements to the list (not shown here)

    // Call the ft_list_foreach function to print the data from the list
    ft_list_foreach(list, &print_data);

    return 0;
}

In this example, the print_data function prints a char * data. Then, in the main function,
a linked list (list) is created and the ft_list_foreach function is called to print the
data from the list using the print_data function. Each time the ft_list_foreach function
is called, the print_data function is applied to each element of the list, printing the
data stored in each node.

In summary, the ft_list_foreach function is useful for applying a function to each element
of a linked list, allowing operations to be performed on the data stored in the list
efficiently.
*/

/*
La función ft_list_foreach recorre una lista enlazada y aplica una función dada
a cada elemento de la lista. Toma dos argumentos: un puntero al primer elemento
(primer nodo) de la lista; y un puntero a una función que toma un puntero a void 
como argumento y no devuelve nada. Esta función se aplica a cada elemento de la 
lista.

Cuerpo de la función:

La función comienza con un bucle while que recorre la lista enlazada. En cada
iteración del bucle, se aplica la función f al dato almacenado en el nodo actual
de la lista. La función f se llama utilizando la notación de puntero a función
(*f) y se pasa el puntero a void que apunta a los datos almacenados en el nodo
(begin_list->data) como argumento.

Después de aplicar la función al nodo actual, el puntero avanzará al siguiente
nodo en la lista (begin_list = begin_list->next) para continuar el recorrido de
la lista. El bucle continuará hasta que se alcance el final de la lista, es decir,
hasta que begin_list sea NULL.

Ejemplo de uso:

Supongamos que queremos imprimir los datos (char *) almacenados en cada nodo de
una lista enlazada. Podemos definir una función que imprima un dato de tipo 
char * y luego usar la función ft_list_foreach para aplicar esta función a cada
elemento de la lista.

Aquí hay un ejemplo de cómo se podría usar la función ft_list_foreach para imprimir
los datos de una lista enlazada:

void print_data(void *data)
{
    printf("%s\n", (char *)data);
}

int main(void)
{
    t_list *list = NULL;

    // Añadir elementos a la lista (no se muestra aquí)

    // Llamar a la función ft_list_foreach para imprimir los datos de la lista
    ft_list_foreach(list, &print_data);

    return 0;
}

En este ejemplo, la función print_data imprime un dato de tipo char *. Luego, en la
función main, se crea una lista enlazada (list) y se llama a la función ft_list_foreach
para imprimir los datos de la lista utilizando la función print_data. Cada vez que se
llama a la función ft_list_foreach, se aplica la función print_data a cada elemento de
la lista, imprimiendo los datos almacenados en cada nodo.

En resumen, la función ft_list_foreach es útil para aplicar una función a cada elemento
de una lista enlazada, lo que permite realizar operaciones en los datos almacenados en
la lista de forma eficiente.
*/
