/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-25 07:27:59 by sternero          #+#    #+#             */
/*   Updated: 2024-08-25 07:27:59 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

typedef struct s_list
{
    void            *data;
    struct s_list   *next;
} t_list;

#endif

// The ft_list.h file contains the definition of the t_list structure, which 
// is used to represent a linked list node. The structure contains a pointer
// to void that points to the data stored in the node and a pointer to the
// next node in the list.

/*
typedef se utiliza para definir un nuevo tipo de datos en C. En este caso, se
define un nuevo tipo de datos llamado t_list que representa un nodo de una lista
enlazada. La estructura t_list contiene dos miembros: un puntero a void llamado
data que apunta a los datos almacenados en el nodo y un puntero a la estructura
t_list llamado next que apunta al siguiente nodo en la lista.

void *data se utiliza para almacenar un puntero a cualquier tipo de datos en C.
Esto permite que la estructura t_list almacene datos de cualquier tipo sin
necesidad de especificar el tipo de datos concreto en la definición de la
estructura.

struct s_list *next se utiliza para almacenar un puntero al siguiente nodo en
la lista enlazada. Esto permite que la estructura t_list se utilice para
representar una lista enlazada donde cada nodo contiene un puntero al siguiente
nodo en la lista.
*/