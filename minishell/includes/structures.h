/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:26:03 by sternero          #+#    #+#             */
/*   Updated: 2024/10/27 13:39:30 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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
    char        **cmd_in;
    char        **cmd_out;
}               t_cmd;

// The structure t_cmd is used to store the commands entered by the user. It has
// four members: cmd, args, in_cmd and out_cmd. The cmd member stores the name
// of the command, the args member stores the arguments of the command, the in_cmd
// member stores the input redirection command, and the out_cmd member stores the
// output redirection command.

typedef struct s_var
{
    char        *name;
    char        *value;
    struct s_var    *right;
    struct s_var    *left;
}               t_var;

// The structure t_var is used to store the variables. It has two members: name
// and value. The name member stores the name of the variable, and the value
// member stores the value of the variable.

typedef struct s_pipe_redir
{
    int         pipe;
    int         redir;
}               t_pipe_red;

// The structure t_pipe_redir is used to store the pipe and redirection flags.
// It has two members: pipe and redir. The pipe member is a flag that indicates 
// if the pipe is present, and the redir member is a flag that indicates
// if the redirection is present.

typedef struct	s_siganation
{
	int				sigint;
	int				sigquit;
	int				exit;
}				t_signation;

typedef struct s_minishell
{
    int         fd_prev;
    int         fd_in;
    int         ft_next;
    int         fd_out;
    int         exit;
    int         exec_signal;
    int         error_parse;
    int         outfile;
    int         status;
    char        *commands;
    char        *old_pwd;
    char        *parsed_prompt;
    char        *path_cmd;
    char        *prompt;
    char        **full_cmd;
    char        **env;
    char        **split_cmd;
    pid_t       pid;
    t_cmd       **cmds;
    char	    *cmd_path;
	int		    g_status;
	int		    fdin;
	int		    fdout;
	int		    fdnextin;
	char	    *oldpwd;
   	int         infile;
}               t_minishell;

// The structure t_minishell is used to store:
// - the fd_prev member stores the previous file descriptor
// - the fd_in member stores the file descriptor for input
// - the fd_next member stores the file descriptor for the next command
// - the fd_out member stores the file descriptor for output
// - the exit member is a flag that indicates if the exit command was entered
// - the exec_signal member is a flag that indicates if an execution signal was
//   received
// - the error_parse member is a flag that indicates if a parsing error occurred
// - the outfile member is a flag that indicates if the output file is present
// - the status member stores the status of the command
// - the cmds member stores the commands entered by the user
// - the old_pwd member stores the old working directory
// - the parsed_prompt member stores the parsed prompt
// - the path_cmd member stores the path of the command
// - the prompt member stores the prompt string entered by the user
// - the full_cmd member stores the full command entered by the user
// - the env member stores the environment variables entered by the user
// - the split_cmd member stores the split command entered by the user
// - the pid member stores the process ID of the command as a pid_t structure
// - the cmds member stores the commands entered by the user as a t_cmd structure

#endif
