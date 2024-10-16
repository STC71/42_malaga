/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-16 09:15:48 by sternero          #+#    #+#             */
/*   Updated: 2024-10-16 09:15:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_struct_start(t_pipe_red *pipe_red)
{
    pipe_red->pipe = 0;
    pipe_red->redir = 0;
}

/* ft_struct_start function initializes the pipe and redirection flags. It takes
    one argument: a pointer to a t_pipe_red structure. It initializes the pipe
    and redirection flags to 0. This is necessary to avoid undefined behavior
    when the flags are used in the program. */