/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-16 13:21:31 by sternero          #+#    #+#             */
/*   Updated: 2024-06-16 13:21:31 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

/*
This is the header file for the checker program. It contains the librraries 
needed for the program to run, and the prototypes of the functions used in the 
program.
*/

# include <unistd.h>
// This library is used to include, for example, the write function.
# include <stdio.h>
// This library is used to include, for example, the printf function.
# include <limits.h>
// This library is used to include the INT_MAX and INT_MIN values.
# include "./push_swap.h"
// This library is used to include the prototypes of the functions used in the
// push_swap program.
# include "../libft/libft.h"
// This library is used to include the libft library.
# include "../ft_printf/ft_printf.h"
// This library is used to include the ft_printf library.

void	ft_be_nbr(char *str);
// This function is used to check if the string is a number.

void	ft_be_duplicated(t_stack *stack_a);
// This function is used to check if there are any duplicated numbers in the
// stack.

void	ft_be_sorted(t_stack *stack_a, t_stack *stack_b);
// This function is used to check if the stack is sorted.

void	ft_include(t_stack **stack_a, int argc, char **argv);
// This function is used to include the numbers in the stack.

int		ft_operations(t_stack **stack_a, t_stack **stack_b, char *operation);
// This function is used to execute the operations on the stacks.

t_stack	*ft_checker_stacknew(int value);
// This function is used to create a new stack.

//int     main(int argc, char **argv);
// This function is the main function of the checker program.

#endif

// This is the end of the header guard for the checker.h file.