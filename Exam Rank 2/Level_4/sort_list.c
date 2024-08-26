/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-26 16:18:12 by sternero          #+#    #+#             */
/*   Updated: 2024-08-26 16:18:12 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
    int tmp;                                  // to store the data of the nodes
    t_list *begin = lst;                  // to store the beginning of the list

    while (lst && lst->next)                // while there are nodes to compare
    {
        if ((*cmp)(lst->data, lst->next->data) == 0) 
                                                 // if the data is not in order
        {
            tmp = lst->data;                // store the data of the first node
            lst->data = lst->next->data;   // store the data of the second node
            lst->next->data = tmp;          // store the data of the first node
            lst = begin;                      // start again from the beginning
        }
        else
            lst = lst->next;  // if the data is in order, move to the next node
    }
    return (begin);                         // return the beginning of the list
}

/*
The sort_list function sorts a linked list in ascending order.
The function takes two arguments: a pointer to the first node of the list (lst)
and a pointer to a function that compares two integers (cmp).
The function iterates through the list comparing each node with the next node.
If the data of the current node is greater than the data of the next node, the
two nodes are swapped. The function continues to iterate through the list until
no more swaps are needed.
*/

/*
La función sort_list ordena una lista enlazada en orden ascendente.
La función toma dos argumentos: un puntero al primer nodo de la lista (lst) y
un puntero a una función que compara dos enteros (cmp).
La función itera a través de la lista comparando cada nodo con el siguiente nodo.
Si los datos del nodo actual son mayores que los datos del siguiente nodo, los
dos nodos se intercambian. La función continúa iterando a través de la lista
hasta que no se necesiten más intercambios.
*/
