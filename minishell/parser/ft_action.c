/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-16 15:22:38 by sternero          #+#    #+#             */
/*   Updated: 2024-10-16 15:22:38 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_action_structures(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	shell->cmds = NULL;
	shell->cmd_path = NULL;
	shell->exec_signal = 0;
	shell->exit = 0;
	shell->full_cmd = NULL;
	shell->g_status = 0;
	shell->oldpwd = NULL;
	shell->parsed_prompt = NULL;
	shell->prompt = NULL;
	while (envp[i] != NULL)
		i++; // lleva i hasta la última linea de las envp
	shell->env = ft_calloc(i + 1, sizeof(char *));  // crea una matrix de tamaño i + 1
	i = 0;
	while (envp[i] != NULL)
	{
		shell->env[i] = ft_strdup(envp[i]); // copia las variables de entorno a la matrix env
		i++;
	}
	reset_fds(shell);
	save_fds(shell);
	update_shlvl(shell);
}

/*Iniciamos la estructura con la copia de keys y vals de las
variables de entorno, para usarlas en el parseo.*/
t_var	**ft_action_envp(char **envp)
{
	int		i;
	int		j;
	t_var	**var;

	i = 0;
	j = ft_string_len(envp);
	var = ft_calloc(sizeof(t_var *), j + 1);
	if (!var)
		return (NULL);
	while (i < j)
	{
		var[i] = ft_calloc(sizeof(t_var), 1);
		var[i]->key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		var[i]->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		i++;
	}
	var[i] = NULL;
	return (var);
}

/* Iniciamos el prompt:
	- Parseamos los arg (analizar gramaticalmente).
	- ft_shell_split.
	- Expansion de las variables de entorno. */
void	ft_action_prompt(t_shell *shell, char *line)
{
	shell->prompt = line;
	shell->parse_error = 0;
	ft_remove_spcs(shell->prompt);
		// borramos los espacios q pueda haber al final del prompt.
	if (!ft_check_cmd(shell))
	{
		printf(RED"parse error\n"RESET);
		shell->parse_error = 1;
		shell->prompt = NULL;
		return ;
	}
	ft_action_prompt_2(shell);
	shell->split_cmd = ft_matrixdup(shell->full_cmd);
	ft_parse_split(shell);
	ft_free_array(shell->full_cmd);
	ft_free_array(shell->split_cmd);
}

/* Segunda parte de ft_action_prompt.*/
void	ft_action_prompt_2(t_shell *shell)
{
	shell->full_cmd = ft_shell_split(shell->prompt);
	if (shell->prompt[ft_strlen(shell->prompt) - 1] == ' ')
		shell->full_cmd = ft_string_del_last(shell->full_cmd);
	ft_expand_envp(shell, shell->env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	if (argc != 1 || argv[1] != NULL)
		return (ft_putstr_fd(RED "Invalid arguments\n" NC, STDERR_FILENO), EXIT_FAILURE);
	ft_action_structures(&shell, envp);	
	while (shell.exit == 0)
	{
		if_signal();
		line = readline("minishell ~ % ");
			//muestra un prompt ("Minishell$~ ") y espera a que el usuario escriba una línea de texto y presione Enter.
			//Este prompt indica al usuario que el shell está listo para recibir comandos
			//devuelve un puntero a una cadena que contiene la línea de texto ingresada por el usuario
		if (line == NULL)
			break ;
		else if (ft_check_line(line) == 0) // comprueba q no hay espacios ni tabuladores
		{
			add_history(line);
				// agregar el comando más recientemente ingresado a la lista de historial.
				// sirve para q al presionar la flecha arriba para recuperar el comando 
				// ls -l del historial y pueda ejecutarlo nuevamente o modificarlo.
			ft_action_prompt(&shell, line);
			if (shell.parse_error == 0)
				execute(shell.cmds, &shell);
		}
		if (line) // liberamos la memoria de la linea
			free(line);
	}
	ft_free_structures(&shell);
	return (ft_free_array(shell.env), 0);
}
