/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:46:06 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/09 11:35:42 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void   error_pipe(t_shell *shell)
{
    write(STDERR_FILENO, "heredoc: error creating pipe\n", 27);
    shell->exec_signal = 1;
    shell->g_status = 1;
}

/* Funcion que permite escribir varias lineas de texto y espera a
que se escriba el "delimitador: letra o frase especificada al principio
despu'es de poner el <" y guarda ese contenido escrito en un archivo
temportal, a no ser que se redireccione a otro archivo con > */
void apply_heredoc(char *delimiter, t_shell *shell)
{
    int fdpipe[2];
    char *line;

    if(pipe(fdpipe) == -1)
        return (error_pipe(shell));
    while (1)
    {
        write(1,"Minishell> ", 11);
        line = get_next_line(STDIN_FILENO);
        if (!line || ft_strcmp(line, delimiter) == 0)
            break ;
        line[ft_strlen(line) - 1] = '\0';
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break ;
        }
        line[ft_strlen(line)] = '\n';
        write(fdpipe[1], line, ft_strlen(line));
        free(line);
    }
    close(fdpipe[1]);
    shell->fdin = fdpipe[0];
    dup2(shell->fdin, STDIN_FILENO);
}

void	update_shlvl(t_shell *shell)
{
	char	*shlvl;
	int		i;
	int		level;

	i = 0;
	while (shell->env[i] != NULL)
	{	
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			shlvl = ft_strdup(shell->env[i] + 6);
			level = ft_atoi(shlvl);
			free(shlvl);
			level++;
			shlvl = ft_itoa(level);
			free(shell->env[i]); 
			shell->env[i] = ft_strjoin("SHLVL=", shlvl);
			free(shlvl);
			return ;
		}
		i++;
	}
}