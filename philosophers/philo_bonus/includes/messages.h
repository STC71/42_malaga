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

# define INPUT_ERROR 1
# define MALLOC_ERROR 2

// ------- Messages ------------------------------------------------------------

# define EAT "is eating 🤤"
# define DIED "is died 💀"
# define SLEEP "is sleeping 😴"
# define TAKE_FORKS "has taken a fork 🍴"
# define THINK "is thinking 🤯"

// ------- Return Codes --------------------------------------------------------

# define FAILURE 1
# define SUCCESS 0

#endif