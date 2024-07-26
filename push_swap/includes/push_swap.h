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
	int				value;
	int				index;
	int				cost;
	int				pos;
	int				target;
	int				a_cost;
	int				b_cost;
	struct s_stack	*next;
	struct s_stack	*prev;
	struct s_stack	*target_node;
	bool			above;
	bool			best;
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

//push_push.c functions:

void		pa(t_stack **stack_a, t_stack **stack_b, int print);
//This funtion push the first element of the stack b to the stack a.

void		pb(t_stack **stack_a, t_stack **stack_b, int print);
//This funtion push the first element of the stack a to the stack b.

//ft_rotate_down.c functions:

void		rra(t_stack **stack_a, int print);
//This funtion is used to rate the stack a down. If print is 1, the funtion
//print the move.

void		rrb(t_stack **stack_b, int print);
//This funtion is used to rate the stack b down. If print is 1, the funtion
//print the move.

void		rrr(t_stack **stack_a, t_stack **stack_b, int print);
//This funtion is used to rate the stack a and the stack b down. 
//If print is 1, the funtion print the move. Only one move is printed.

void		rrr_rot(t_stack **s_a, t_stack **s_b, int *a_cost, int *b_cost);
//This funtion is used to rate the stack a and the stack b down. The funtion
//print the moves of the stack a and the stack b. Only one move is printed.

void		b_rot(t_stack **stack_b, int *cost);
//This funtion is used to rate the stack b down. The funtion print the moves
//of the stack b. Only one move is printed.

//ft_rotate_up.c functions:

void		ra(t_stack **stack, int print);
//This funtion is used to rate the stack a up. 
//If print is 1, the funtion print

void		rb(t_stack **stack, int print);
//This funtion is used to rate the stack b up. 
//If print is 1, the funtion print

void		rr(t_stack **stack_a, t_stack **stack_b, int print);
//This funtion is used to rate the stack a and the stack b up.
//If print is 1, the funtion print. Only one move is printed.

void		rr_rot(t_stack **s_a, t_stack **s_b, int *a_cost, int *b_cost);
//This funtion is used to rate the stack a and the stack b up. The funtion
//print the moves of the stack a and the stack b. Only one move is printed.

void		a_rot(t_stack **stack_a, int *cost);
//This funtion is used to rate the stack a up. The funtion print the moves
//of the stack a.

//ft_swap.c functions:

void		sa(t_stack **stack, int print);
//This funtion is used to swap the first two elements of the stack a.

void		sb(t_stack **stack, int print);
//This funtion is used to swap the first two elements of the stack b.

void		ss(t_stack **stack_a, t_stack **stack_b, int print);
//This funtion is used to swap the first two elements of the stack a and the
//stack b. Only one move is printed.

//ft_tfind_index.c functions:

int			ft_find_index_up(t_stack **stack_a, int min, int max);
//This funtion is used to find the index of the first element of the stack 
//that is between the min and max values.

int			ft_find_index_down(t_stack **stack_a, int min, int max);
//This funtion is used to find the index of the last element of the stack.

void		ft_cheap_sort(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to sort the stack a and the stack b with the cheapest
//way. The funtion is used to sort a stack of any size.

void		ft_get_cost(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to get the cost of the stack a and the stack b.

//ft_tfind.c functions:

int			ft_find_min(t_stack **stack);
//This funtion is used to find the minimum value of the stack.

int			ft_find_max(t_stack **stack);
//This funtion is used to find the maximum value of the stack.

int			ft_find_pos_min(t_stack **stack, int min);
//This funtion is used to find the position of the minimum value of the stack.

int			ft_find_pos_max(t_stack **stack, int max);
//This funtion is used to find the position of the maximum value of the stack.

int			ft_find_last(t_stack **stack);
//This funtion is used to find the last element of the stack.

//ft_tfree.c functions:

void		ft_free(t_stack **stack);
//This funtion is used to free the memory of the stack.

void		ft_free_all(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to free the memory of the stack a and the stack b.

//ft_tindex.c functions:

t_stack		*copy_stack(t_stack *original);
//This funtion is used to copy the stack. It is used to copy the stack a to a
//temporary stack to define de index of the stack.

void		sort_list(t_stack **list);
//This funtion is used to sort the list, and so the index of the stack is
//defined.

int			find_index(t_stack *sorted_list, int value);
//This funtion is used to find the index of the value in the sorted list. It
//is used to define the index of the stack.

void		ft_get_index(t_stack **stack_a);
//This funtion is used to get the index of the stack a.

//ft_tmoves.c functions:

void		ft_move_a(t_stack **stack_a, t_stack **stack_b, int pos, int i);
//This funtion is used to move the stack a to the stack b. The funtion is used
//to sort the stack with the push_swap algorithm.

void		ft_select_a(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to select the stack a to move the stack a to the stack b.
//The funtion is used to sort the stack with the push_swap algorithm.

//ft_tools.c functions:

t_stack		*ft_new_stack(int value);
//This funtion is used to create a new element of the stack.

int			ft_count_neg(t_stack **stack_a);
//This funtion is used to count the number of negative values of the stack.

void		ft_b_to_a(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to push all the elements of the stack b to the stack a.

int			ft_abs(int a);
//This funtion is used to return the absolute value of the integer. If the 
//integer is negative, the funtion returns the positive value.

//ft_tpos.c functions:

void		ft_add_pos(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to add the position of the elements of the stack a and
//the stack b. The position is the number of elements that are above the
//element. The position is used to calculate the cost of the element. 

void		ft_find_pos_target(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to find the position and the target of the stack a and
//the stack b. The position is the number of elements that are above the
//element. The target is the element that is closest to the element.

int			ft_target(t_stack **stack_a, int index, int target, int pos);
//This funtion is used to find the target of the element, to calculate the
//cost of the element.

void		ft_pos_target(t_stack **stack);
//This funtion is used to find the position and the target of the element.

//ft_tsort_big.c functions:

int			ft_pos_min(t_stack **stack_a, int pos);
//This funtion is used to find the position of the minimum value of the stack.

void		ft_sort_max(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to sort the stack a and the stack b, with the maximum
//value of the stack.

void		ft_sort_end(t_stack **stack_a, t_stack **stack_b);
//This funtion is the last of the sort functions.

void		ft_moves(t_stack **s_a, t_stack **s_b, int a_cost, int b_cost);
//This funtion is used to move the elements of the stack a and the stack b.
//a_cost and b_cost are used to calculate the cost of the element.

void		ft_sort_big(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to sort the stack a and the stack b, with the push_swap
//algorithm. It is used to sort a stack of any size. In this case, the stack
//is sorted by pushing the smallest number to stack b and then sorting stack a
//recursively. The funtion is used to sort more of 500 elements.

//ft_tsortc.c functions:

void		ft_sort_min(t_stack **stack);
//This funtion is used to sort the stack with the minimum value of the stack.

void		shifte_change(t_stack **stack_a);
//This funtion is used to shift the stack a to the minimum value of the stack.

int			ft_low_index(t_stack **stack);
//This funtion is used to find the index of the minimum value of the stack.

int			ft_hi_index(t_stack *stack);
//This funtion is used to find the index of the maximum value of the stack.

//ft_tsort.c functions:

int			ft_stack_len(t_stack *stack);
//This funtion is used to calculate the length of the stack whit a while loop.

void		ft_sort(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to sort the stack a and the stack b.

void		ft_sort_three(t_stack **stack);
//This funtion is used to sort the stack with three elements.

void		ft_sort_four(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to sort the stack with four elements.

void		ft_sort_five(t_stack **stack_a, t_stack **stack_b);
//This funtion is used to sort the stack with five elements.

//push_swap.c functions:

void		ft_error(int i);
//The funtion takes an integer as a parameter. It is used to print a error 
//message and exit the program.

void		be_nbr(char *str);
//The funtion takes a string as a parameter. It is used to check if the string
//is a number, positive or negative. If the string is not a number or the value
//is greater than INT_MAX or less than INT_MIN, the funtion calls the ft_error.

void		ft_be_duplicated(t_stack *stack_a);
//The funtion is used to check if the stack has duplicated values. 
//If the stack has duplicated values, the funtion calls the ft_error.

int			be_sorted(t_stack *stack_a);
//The funtion is used to check if the stack is sorted. If the stack is sorted,
//the funtion returns 1. If the stack is not sorted, the funtion returns 0.

t_stack		*ft_stacknew(int value);
//The funtion is used to create a new element of the stack.

//int main (int argc, char *argv[]);
//The funtion is used to check the arguments, create the list and sort it.

#endif

//This is the end of the header guard for the PUSH_SWAP_H macro.
