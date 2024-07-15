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
	int		pos;
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

void	ft_sort_four(t_stack **stack_a, t_stack **stack_b);
//ft_sort_four is a function that returns void. It takes two pointers to stacks as
//parameters. It is used to sort a stack with four elements.

void	ft_sort_five(t_stack **stack_a, t_stack **stack_b);
//ft_sort_five is a function that returns void. It takes two pointers to stacks
//and an integer as parameters. It is used to sort a stack with four or five
//elements.

//ft_sort_big.c functions:

int		ft_pos_min(t_stack **stack_a, int pos);
//ft_pos_min is a function that returns an integer. It takes a pointer to a stack
//and an integer as parameters. It is used to find the position of the minimum
//value of the stack.

void	ft_sort_min(t_stack **stack_a, t_stack **stack_b);
//ft_sort_min to order the stack with more of five elements and less or equal to
//one hundred elements.

void	ft_sort_max(t_stack **stack_a, t_stack **stack_b);
//ft_sort_max to orden the stack with more of one hundred elements and less or 
//equal to two five hundred elements.

void	ft_sort_big(t_stack **stack_a, t_stack **stack_b);
//ft_sort_big is a function that returns void. It takes two pointers to stacks as
//parameters. It is used to sort a stack of any size.

//ft_sort_c.c functions (100 elements):

void	ft_sort_c(t_stack **stack_a, t_stack **stack_b);
//ft_sort_c is a function that returns void. It takes two pointers to stacks as
//parameters. It is used to sort the stack.

void	ft_b_to_a(t_stack **stack_a, t_stack **stack_b);
//ft_a_to_b is a function that returns void. It takes two pointers to stacks as
//parameters. It is used to move the elements of the stack from stack a to stack b.

void	ft_sort_a(t_stack **stack_a);
//ft_sort_a is a function that returns void. It takes a pointer to a stack as a
//parameter. It is used to sort the stack.

//ft_tcheap_cost.c functions:

void	ft_cheap_sort(t_stack **stack_a, t_stack **stack_b);
//ft_cheap_sort is a function that returns void. It takes two pointers to stacks
//as parameters. It is used to sort the stack in the cheapest way possible.

void	ft_get_cost(t_stack **stack_a, t_stack **stack_b);
//ft_get_cost is a function that returns void. It takes two pointers to stacks as
//parameters. It is used to get the cost of the moves for each element of the stack.

void	ft_moves(t_stack **a, t_stack **b, int a_cost, int b_cost);
//ft_moves is a function that returns void. It takes two pointers to stacks and
//two integers as parameters. It is used to move the elements of the stack to the
//appropriate position.

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

int		ft_find_last(t_stack *stack);
//ft_find_last is a function that returns an integer. It takes a pointer to a stack
//as a parameter. It is used to find the index of the last element of the stack.

//ft_find_index.c functions:

int		ft_find_index_up(t_stack **stack_a, int min, int max);
//ft_find_index_up is a function that returns an integer. It takes a pointer to a
//stack and two integers as parameters. It is used to find the index of the
//elements of the stack that are between the minimum and maximum values in the
//up direction.

int		ft_find_index_down(t_stack **stack_a, int min, int max);
//ft_find_index_down is a function that returns an integer. It takes a pointer to
//a stack and two integers as parameters. It is used to find the index of the
//elements of the stack that are between the minimum and maximum values in the
//down direction.

//ft_free.c functions:

void    ft_free(t_stack **stack);
//ft_free is a function that returns void. It takes a pointer to a stack as a
//parameter. It is used to free the memory of the stack.

void    ft_free_all(t_stack **stack_a, t_stack **stack_b);
//ft_free_all is a function that returns void. It takes two pointers to stacks as
//parameters. It is used to free the memory of the two stacks.

//ft_tindex.c functions:

t_stack	*copy_stack(t_stack *stack);
//copy_stack is a function that returns a pointer to a stack. It takes a pointer
//to a stack as a parameter. It is used to copy the stack.

void	sort_list(t_stack **list);
//sort_list is a function that returns void. It takes a pointer to a stack as a
//parameter. It is used to sort the stack.

int		find_index(t_stack *sorted_list, int value);
//find_index is a function that returns an integer. It takes a pointer to a stack
//and an integer as parameters. It is used to find the index of a value in the
//stack.

void	ft_get_index(t_stack **stack_a);
//ft_get_index is a function that returns void. It takes a pointer to a stack as a
//parameter. It is used to assign an index to each element of the stack.

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

void	rrr_rev(t_stack **stack_a, t_stack **stack_b, int *a_cost, int *b_cost);
//rrr_rev is a function that returns void. It takes two pointers to stacks and two
//integers as parameters. It is used to reverse rotate the two stacks.
//And control the cost of the rotations.

void	rr_rot(t_stack **stack_a, t_stack **stack_b, int *a_cost, int *b_cost);
//rr_rot is a function that returns void. It takes two pointers to stacks and two
//integers as parameters. It is used to rotate the two stacks.
//And control the cost of the rotations.

void	a_rot(t_stack **stack_a, int *cost);
//a_rot is a function that returns void. It takes a pointer to a stack and an
//integer as parameters. It is used to rotate the stack.
//And control the cost of the rotations.

void	b_rot(t_stack **stack_b, int *cost);
//b_rot is a function that returns void. It takes a pointer to a stack and an
//integer as parameters. It is used to rotate the stack.
//And control the cost of the rotations.

//ft_tools.c functions:

t_stack    *ft_new_stack(int value);
//ft_new_stack is a function that returns a pointer to a stack. It takes an integer
//as a parameter. It is used to create a new element of the stack.

int   ft_count_neg(t_stack **stack_a);
//ft_count_neg is a function that returns an integer. It takes a pointer to a stack
//as a parameter. It is used to count the number of negative numbers in the stack.

void    ft_get_index(t_stack **stack_a);
//ft_get_index is a function that returns void. It takes a pointer to a stack as a
//parameter. It is used to assign an index to each element of the stack.

void	ft_position(t_stack **stack);
//ft_position is a function that returns void. It takes a pointer to a stack as a
//parameter. It is used to assign a position to each element of the stack.

void	ft_end_pos(t_stack **stack_a, t_stack **stack_b);
//ft_end_pos is a function that returns void. It takes two pointers to stacks as
//parameters. It is used to assign a target position to each element of the stack.

//ft_tpos.c functions:

void    ft_add_pos(t_stack **stack_a, t_stack **stack_b);
//ft_add_pos is a function that returns void. It takes two pointers to stacks as
//parameters. It is used to assign a position to each element of the stacks.

void    ft_be_good(t_stack **stack_a, t_stack **stack_b);
//ft_be_good is a function that returns void. It takes two pointers to stacks as
//parameters. It is used to print the values, indexes and positions of the stacks.

#endif

//This is the end of the header guard for the PUSH_SWAP_H macro.
