/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-03 11:27:51 by sternero          #+#    #+#             */
/*   Updated: 2024-08-03 11:27:51 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
    struct s_list   *next;
    void            *data;
}   t_list;

#endif

/*
First we define FT_LIST_H to avoid multiple inclusions. 
Then we include the necessary libraries: 
    To use lists, we need to include the stdlib.h and unistd.h libraries.
We define a structure called s_list that contains a pointer
to the next element of the list and a pointer to the data of the element.
Finally, we define a type called t_list that is a pointer to the structure 
s_list.

Primero definimos FT_LIST_H para evitar inclusiones múltiples.
Luego incluimos las librerías necesarias:
    Para usar listas, necesitamos incluir las librerías stdlib.h y unistd.h.
Definimos una estructura llamada s_list que contiene un puntero al siguiente
elemento de la lista y un puntero a los datos del elemento.
Finalmente, definimos un tipo llamado t_list que es un puntero a la estructura
s_list.
*/