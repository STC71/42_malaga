/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tfind_index.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-12 17:36:48 by sternero          #+#    #+#             */
/*   Updated: 2024-07-12 17:36:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int ft_find_index_up(t_stack **stack_a, int min, int max)
{
    t_stack *tmp;
    
    tmp = *stack_a;
    int index = 1;

    while (tmp)
    {
        if (tmp->index >= min && tmp->index <= max)
            return index;
        tmp = tmp->next;
        index++;
    }
    return -1;
}

int ft_find_index_down(t_stack **stack_a, int min, int max)
{
    t_stack *tmp;
    int reverse; // Índice desde el final de la lista
    
    reverse = 0;
    if (!stack_a || !*stack_a) // Verificación de punteros nulos
        return -1;
    tmp = *stack_a;
    while (tmp != NULL) // Recorre toda la lista
    {
        if (tmp->index >= min && tmp->index <= max)
            return reverse; // Retorna el índice desde el final
        tmp = tmp->next;
        reverse++;
    }
    return -1; // No se encontró un elemento en el rango
}

/*
int ft_find_index_down(t_stack **stack_a, int min, int max)
{
    t_stack *tmp;
    int higuest = max; // Inicializa como -1 para indicar que aún no se ha encontrado ningún índice válido

    if (!stack_a || !*stack_a)
        return (-1);

    tmp = *stack_a;
    while (tmp != NULL)
    {
        // Verifica si el índice del elemento actual está dentro del rango [min, max]
        if (tmp->index >= min && tmp->index <= max)
        {
            // Actualiza higuest si el índice actual es mayor que el almacenado
            if (higuest < tmp->index)
                higuest = tmp->index;
        }
        tmp = tmp->next; // Avanza al siguiente elemento
    }
    return (higuest);
}

int     ft_find_index_down(t_stack **stack_a, int min, int max)
{
    t_stack *tmp;
    int     down;
    int     end;

    if (!stack_a || !*stack_a)
        return (-1);

    tmp = *stack_a;
    down = 0;
    end = max;
    while (down == 0 && tmp != NULL)
    {
        while (min < end && tmp->next != NULL)
            tmp = tmp->next;
        if (tmp->index >= min && tmp->index <= max)
            down++;
        else
        {
            end--;
            tmp = *stack_a;
            if (end < min)
                break;
        }
    }
    return (end);
}
*/

// ft_find_index_up() function finds the index of the element in the stack that 
// is between min and max.
