/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-03 11:28:15 by sternero          #+#    #+#             */
/*   Updated: 2024-08-03 11:28:15 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

int ft_list_size(t_list *list)
{
    if (list == 0)
        return (0);
    else
        return (1 + ft_list_size(list->next));
        // It return 1 plus the result of calling itself with the pointer to 
        // the next element of the list. For example, if the list has 3 elements,
        // the function will return 1 + 1 + 1 + 0 = 3. '0' because the last 
        // element of the list is NULL.
}

/*
The funtion ft_list_size receives a pointer to the first element of a list.
If the pointer is NULL, the function returns 0.
Otherwise, the function returns 1 plus the result of calling itself with the
pointer to the next element of the list.
The function finishes when the pointer is NULL.

La función ft_list_size recibe un puntero al primer elemento de una lista.
Si el puntero es NULL, la función devuelve 0.
De lo contrario, la función devuelve 1 más el resultado de llamarse a sí 
misma con el puntero al siguiente elemento de la lista.
La función termina cuando el puntero es NULL.
*/