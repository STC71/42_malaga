/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 10:26:03 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 10:26:03 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"
# include <fcntl.h>

// ------- Structures ------------------------------------------------------- //

typedef struct  s_env
{
    char        *name;
    char        *value;
    struct s_env *next;
}               t_env;

// The structure t_env is used to store the environment variables. It has three
// members: name, value and next. The name member stores the name of the 
// environment variable, the value member stores the value of the environment
// variable, and the next member is a pointer to the next element of the list.

typedef struct  s_cmd
{
    char        *cmd;
    char        **args;
    char        **incmd;
    char        **outcmd;
}               t_cmd;

// The structure t_cmd is used to store the commands entered by the user. It has
// four members: cmd, args, incmd and outcmd. The cmd member stores the name
// of the command, the args member stores the arguments of the command, the in_cmd
// member stores the input redirection command, and the out_cmd member stores the
// output redirection command.

typedef struct s_var
{
    char        *key;
    char        *value;
}               t_var;

// The structure t_var is used to store the variables. It has two members: key
// and value. The key member stores the name of the variable, and the value
// member stores the value of the variable.

typedef struct s_pipe_redirection
{
    int         pipe;
    int         red;
}               t_pipe_red;

// The structure t_pipe_redirection is used to store the pipe and redirection
// flags. It has two members: pipe and redir. The pipe member is a flag that
// indicates if the pipe is present, and the redir member is a flag that indicates
// if the redirection is present.

typedef struct s_shell
{
	int		exec_signal;
	int		exit;
	int		fdin;
	int		fdnextin;
	int		fdout;
	int		g_status;
	int		infile;
	int		outfile;
	int		parse_error;
	int		prev_fd;
	pid_t	pid;
	char	*oldpwd;
	char	*parsed_prompt;
	char	*prompt;
	char	*cmd_path;
	char	**env;
	char	**full_cmd;
	char	**split_cmd;
	t_cmd	**cmds;
}			t_shell;

/*	The structure t_shell is used to store the shell variables. 
	It has 20 members:
	* oldpwd: stores the previous working directory
	* parsed_prompt: stores the parsed prompt. The prompt with the variables.
	* prompt: stores the prompt.
	* cmd_path: stores the path of the command.
	* env: stores the environment variables.
	* full_cmd: stores the full command.
	* split_cmd: stores the split command.
	* exec_signal: stores the execution signal.
	* exit: stores the exit flag.
	* fdin: stores the file descriptor for input.
	* fdnextin: stores the file descriptor for the next input.
	* fdout: stores the file descriptor for output.
	* g_status: stores the global status.
	* infile: stores the input file.
	* outfile: stores the output file.
	* parse_error: stores the parse error.
	* prev_fd: stores the previous file descriptor.
	* pid: stores the process id.
	* cmds: stores the commands.	*/

#endif