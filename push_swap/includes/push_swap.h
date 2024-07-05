/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-16 13:14:47 by sternero          #+#    #+#             */
/*   Updated: 2024-06-16 13:14:47 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/*
This is the header file for the push_swap project. It includes the 
necessary libraries, definitions and structures to run the program, and the
prototypes of the functions defined in the project.
*/

# include <stdbool.h>
//This library is used to define the boolean type.
# include <limits.h>
//This library is used to define the INT_MAX and INT_MIN constants.
# include <stdlib.h>
//This library is used to include the malloc and free functions.
# include <unistd.h>
//This library is used to include the write function.
# include <stdio.h>
//This library is used to include the printf function.
# include <stddef.h>
//This library is used to include the size_t type, the null pointer constant
//and the offsetof macro.

# include "../libft/libft.h"
//This library is used to include my prototypes of the libft functions.
# include "../ft_printf/ft_printf.h"
//This library is used to include my prototype of the printf function.

typedef struct s_stack
{
	int		value;
	int		index;
	int		cost;
	int		target;
	int		a_cost;
	int		b_cost;
	struct s_stack	*next;
	struct s_stack	*prev;
	struct s_stack	*target_node;
	bool	above;
	bool	best;
}	t_stack;

/*
This is the structure that contains the information of the stack. With typedef,
the structure is defined as t_stack. It is used to store the information of the
stack.

The structure t_stack is defined with the following members:
- value: is an integer. It is used to store the value of the stack.
- t_stack *next: is a pointer to a structure. It is used to point to the next
element of the stack.

t_stack is a structure that contains the information of the stack. It is used
to store the information of the stack.
*/

//Funtions prototypes for the push_swap project.

//push_swap.c functions:

void	ft_error(int i);
//ft_error is a static function that returns void. It takes an integer as a
//parameter. It is used to print an error message and exit the program.

void	be_nbr(char *str);
//be_nbr is a function that returns void. It takes a string as a parameter. It
//is used to check if the string is a number.

void	ft_be_duplicated(t_stack *stack_a);
//be_duplicated is a function that returns void. It takes a string and an integer
//as parameters. It is used to check if there are duplicated numbers.

int		be_sorted(t_stack *stack_a);
//be_sorted is a function that returns an integer. It takes a pointer to a stack
//as a parameter. It is used to check if the stack is sorted.

t_stack		*ft_stacknew(int value);
//ft_stacknew is a function that returns a pointer to a stack. It takes an integer
//as a parameter. It is used to create a new element of the stack.

//ft_sort.c functions:

int		ft_stack_len(t_stack *stack);
//ft_stack_len is a function that returns an integer. It takes a pointer to a stack
//as a parameter. It is used to get the length of the stack.

void	ft_sort(t_stack **stack_a, t_stack **stack_b);
//ft_sort is a function that returns void. It takes two pointers to stacks as
//parameters. It is used to sort the stack.

void	ft_sort_three(t_stack **stack);
//ft_sort_three is a function that returns void. It takes a pointer to a stack as
//a parameter. It is used to sort a stack with three elements.

void	ft_sort_five(t_stack **stack_a, t_stack **stack_b);
//ft_sort_five is a function that returns void. It takes two pointers to stacks
//and an integer as parameters. It is used to sort a stack with four or five
//elements.

//ft_find.c functions:

int		ft_find_min(t_stack **stack);
//ft_find_min is a function that returns void. It takes a pointer to a stack as a
//parameter. It is used to find the minimum value of the stack.

int		ft_find_max(t_stack **stack);
//ft_find_max is a function that returns void. It takes a pointer to a stack as a
//parameter. It is used to find the maximum value of the stack.

int		ft_find_pos_min(t_stack **stack, int min);
//ft_find_pos_min is a function that returns an integer. It takes a pointer to a
//stack and an integer as parameters. It is used to find the position of the
//minimum value of the stack.

int		ft_find_pos_max(t_stack **stack, int max);
//ft_find_pos_max is a function that returns an integer. It takes a pointer to a
//stack and an integer as parameters. It is used to find the position of the
//maximum value of the stack.

//Other functions:

void	sa(t_stack **stack, int print);
//sa is a function that returns void. It takes a pointer to a stack and an integer
//as parameters. It is used to swap the first two elements of the stack.

void	sb(t_stack **stack, int print);
//sb is a function that returns void. It takes a pointer to a stack and an integer
//as parameters. It is used to swap the first two elements of the stack.

void	ss(t_stack **stack_a, t_stack **stack_b, int print);
//ss is a function that returns void. It takes two pointers to stacks and an
//integer as parameters. It is used to swap the first two elements of the two
//stacks.

void	pa(t_stack **stack_a, t_stack **stack_b, int print);
//pa is a function that returns void. It takes two pointers to stacks and an
//integer as parameters. It is used to push the first element of the second stack
//to the first stack.

void	pb(t_stack **stack_a, t_stack **stack_b, int print);
//pb is a function that returns void. It takes two pointers to stacks and an
//integer as parameters. It is used to push the first element of the first stack
//to the second stack.

void	ra(t_stack **stack, int print);
//ra is a function that returns void. It takes a pointer to a stack and an integer
//as parameters. It is used to rotate the stack.

void	rb(t_stack **stack, int print);
//rb is a function that returns void. It takes a pointer to a stack and an integer
//as parameters. It is used to rotate the stack.

void	rr(t_stack **stack_a, t_stack **stack_b, int print);
//rr is a function that returns void. It takes two pointers to stacks and an
//integer as parameters. It is used to rotate the two stacks.

void	rra(t_stack **stack, int print);
//rra is a function that returns void. It takes a pointer to a stack and an integer
//as parameters. It is used to reverse rotate the stack.

void	rrb(t_stack **stack, int print);
//rrb is a function that returns void. It takes a pointer to a stack and an integer
//as parameters. It is used to reverse rotate the stack.

void	rrr(t_stack **stack_a, t_stack **stack_b, int print);
//rrr is a function that returns void. It takes two pointers to stacks and an
//integer as parameters. It is used to reverse rotate the two stacks.

#endif

//This is the end of the header guard for the PUSH_SWAP_H macro.
