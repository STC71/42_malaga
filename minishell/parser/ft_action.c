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
		i++;
	shell->env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i] != NULL)
	{
		shell->env[i] = ft_strdup(envp[i]);
		i++;
	}
	reset_fds(shell);
	save_fds(shell);
	update_shlvl(shell);
}

/* 	ft_action_structures() function is used to initialize the structure with the 
	environment variables. It allocates memory for the structure and copies the 
	environment variables to the structure. */

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

/* 	ft_action_envp() function is used to initialize the structure with the copy 
	of keys and vals of the environment variables, to use them in the parsing.*/

void	ft_action_prompt(t_shell *shell, char *line)
{
	shell->prompt = line;
	shell->parse_error = 0;
	ft_remove_spcs(shell->prompt);
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

/* 	ft_action_prompt() function is used to initialize the prompt. It removes the 
	spaces at the end of the prompt and checks if the command is valid. If the 
	command is not valid, it will print an error message.
	We begin by parsing the arguments (grammatically analyzing).
	- ft_shell_split, to split the prompt into words.
	- Expansion of environment variables. Is the process of replacing the 
		variables in the prompt with their values. */

/* Segunda parte de ft_action_prompt.*/
void	ft_action_prompt_2(t_shell *shell)
{
	shell->full_cmd = ft_shell_split(shell->prompt);
	if (shell->prompt[ft_strlen(shell->prompt) - 1] == ' ')
		shell->full_cmd = ft_string_del_last(shell->full_cmd);
	ft_expand_envp(shell, shell->env);
}

/*	ft_action_prompt_2() function is the second part of the ft_action_prompt() 
	function. It splits the prompt into words and expands the environment 
	variables.
	- shell->full_cmd is the prompt split into words and recieves the expanded 
		environment variables.
	- if shell->prompt ends with a space, it will delete the last word.
	- ft_expand_envp() function is used to expand the environment variables. */

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

/*	The main function is the entry point of the program. It initializes the 
	structure with the environment variables and the prompt. It reads the line 
	entered by the user and checks if the line is valid. If the line is not
	valid, it will print an error message. It will add the line to the history
	if it is valid and execute the command. 
	- ft_action_structures() function is used to initialize the structure with 
		the environment variables.
	- if_signal() function is used to check if the signal is received, for 
		example if the user presses Ctrl + C to exit the program or Ctrl + D 
		to exit the shell or Ctrl + \ to exit the shell and print the core dump.
	- readline() function is used to read the line entered by the user.
	- add_history() function is used to add the line to the history.
	- ft_action_prompt() function is used to initialize the prompt (the prompot 
		is the line entered by the user), and check if the command is valid.
	- execute() function is used to execute the command. */
