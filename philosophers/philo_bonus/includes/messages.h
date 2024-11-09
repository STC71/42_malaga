/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-23 11:36:35 by sternero          #+#    #+#             */
/*   Updated: 2024-09-23 11:36:35 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

// ------- Error Messages ------------------------------------------------------

# define ERROR_ARGS_1 "Error: Wrong number of arguments\n"
# define ERROR_ARGS_2 "Error: Number of philosophers must be at least 2\n"
# define ERROR_ARGS_3 "Error: Time to die must be at least 60 ms\n"
# define ERROR_ARGS_4 "Error: Time to eat must be at least 60 ms\n"
# define ERROR_ARGS_5 "Error: Time to sleep must be at least 60 ms\n"
# define ERROR_ARGS_6 "Error: Number of meals must be at least 1\n"

// ------- Error Codes ---------------------------------------------------------

# define ERROR_THREAD 5		// The thread is not available
# define ERROR_SEM 4		// The semaphore is not available
# define ERROR_FORK 3		// The fork is not available
# define ERROR_MALLOC 2		// The memory allocation failed
# define ERROR_INPUT 1		// The input is not valid

// ------- Messages ------------------------------------------------------------

# define EAT "is eating 🤤"
# define DIED "is died 💀"
# define SLEEP "is sleeping 😴"
# define TAKE_FORKS "has taken a fork 🍴"
# define THINK "is thinking 🤯"

// ------- Return Codes --------------------------------------------------------

# define FAILURE 1			// The program failed
# define SUCCESS 0			// The program succeeded

#endif