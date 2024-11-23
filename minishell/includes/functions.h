/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-23 11:47:37 by sternero          #+#    #+#             */
/*   Updated: 2024-09-23 11:47:37 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

// ------- Builtins Functions ----------------------------------------------- //

// ------- cd_errors.c

void	write_cd_err(t_shell *shell);
void	write_backpwd_err(char *back_path, t_shell *shell);
void	write_cdhome_error(char *home_path, t_shell *shell);
void	write_too_many_args(t_shell *shell);
void	write_oldpwd_error(t_shell *shell);

// ------- cd.c

void	renew_path(t_shell *shell);
void	exec_back_pwd(t_shell *shell);
char	*ft_get_environment(char *str_pwd, char **env_paths);
void	exec_cd_home(t_shell *shell);
void	ft_cd(char **full_command, t_shell *shell);

// ------- delete_env.c

void	ft_delete_env_unset(char **name_var, t_shell *shell);

// ------- echo.c

void	ft_echo(char **args, t_shell *shell);

// ------- exit.c

void	ft_exit(char **command, t_shell *shell);

// ------- print_env.c

int		ft_print_env_err(t_shell *shell, char *path);
int		ft_check_path(t_shell *shell, char **paths);
void	ft_print_env(t_shell *shell, char **paths);

// ------- pwd.c

void	ft_pwd(t_shell *shell);

// ------- some_errors.c

void	write_exit_toomany_err(t_shell *shell);
void	write_numeric_err(t_shell *shell, char **command);
void	write_pwd_err(t_shell *shell);

// ------- update_env_errors.c

void	env_err0(char *command, int i);
void	env_err1(char *command, int i);
void	env_err2(char *command, int i);
void	env_err3(void);

// ------- update_env_export.c

void	ft_print_env_err2(t_shell *shell, int env_err, char *command);
int		check_env(char *env);
void	ft_print_env2(t_shell *shell);
void	ft_update_env_export(t_shell *shell, char **commands);

// ------- update_env2.c

void	ft_free_env(char **env);
char	*ft_new_env(char *name, char *value);
void	ft_create_env(char *name, char *value, t_shell *shell);
int		ft_check_update_env(char *name, char *value, t_shell *shell);
void	ft_update_env(char *command, t_shell *shell);

// ------- Executor Functions ----------------------------------------------- //

// ------- executor_and_exec_builtins.c

void	choose_builtin(t_shell *shell, t_cmd **commands, int i);
int		check_if_is_builtin(char *command);

// ------- clean.c

void	reset_std(t_shell *shell);
void	close_fds(t_shell *shell);
void	reset_fds(t_shell *shell);
void	ft_close_resets(t_shell *shell);

// ------- execute_bin.c

void	ft_str_free(char **str);
char	*join_binpath_and_cmd(char *cmd, char *bin_path);
int		write_bin_error(char *cmd, t_shell *shell);
char	**get_bin_paths(t_shell *shell);
void	execute_bin_cmd_main(t_cmd **commands, t_shell *shell, int i);

// ------- execute_bin2.c

void	execute_child_proces(char *path, char **exc, t_shell *shell);
char	**create_matrix_cmd_and_args(t_cmd **commands, int i);
void	execute_bin_cmd(char *cmd_path, t_cmd **commands, t_shell *shell, int i);

// ------- execute_builtins.c

void	reset_oldpwd(t_shell *shell, int i);
void	reset_old_pwd_and_lastcmd(t_shell *shell, t_cmd **commands);
void	check_if_builtin(t_cmd **commands, t_shell *shell, int i);
void	config_pipe(t_shell *shell);
void	execute(t_cmd **commands, t_shell *shell);

// ------- heredoc.c

void	error_pipe(t_shell *shell);
void	apply_heredoc(char *delimiter, t_shell *shell);
void	update_shlvl(t_shell *shell);

// ------- redirections.c

void	reset_redirections(t_shell *shell);
void	redir_infile(char **cmd, t_shell *shell, int i);
void	redir_outfile(char **cmd, t_shell *shell, int i);
void	save_fds(t_shell *shell);
void	choose_redirections(char **cmd, t_shell *shell);

// ------- Parser Functions ------------------------------------------------- //

// ------- ft_action.c

void	ft_action_structures(t_shell *shell, char **envp);
t_var	**ft_action_envp(char **envp);
void	ft_action_prompt(t_shell *shell, char *line);
void	ft_action_prompt_2(t_shell *shell);
// int	main(int argc, char **argv, char **envp);

// ------- ft_checkers_1.c

int		ft_check_pipe_n_red_mixes(char *prompt, int *pos);
int		ft_check_last(char *prompt);
int		ft_check_red_and_pipe(char *prompt);
int		ft_check_pipe_in(char *prompt);
void	ft_check_red_or_pipe(t_pipe_red *val, int i);

// ------- ft_checkers_2.c

void	ft_check_env(char *str);
void	ft_check_args(int argc, char *argv);
int		ft_check_line(char *line);
int		ft_check_cmd(t_shell *shell);

// ------- ft_elements.c

int		ft_pipe_redir(char c, t_pipe_red *val, char *prompt, int *in);
int		ft_len_word(char *prompt, int i);
void	ft_no_spc_entry(char **new, char *old);
void	ft_action_pipe_redir(t_pipe_red *val);
char	**ft_shell_split(char *prompt);

// ------- ft_envp_tools.c

char	*ft_get_value_envp(t_var **list_var, char *key);
char	*ft_find_envp(char *str, int pos);
void	ft_add_dollar(char **dollar);
void	ft_expand_envp(t_shell *shell, char **envp);

// ------- ft_free_utils.c

void	ft_free_array(char **array);
void	ft_free_commands(t_cmd *commands);
void	ft_free_env_vars(t_var **vars);
void	ft_free_structures(t_shell *shell);
void	ft_free_vars(t_var *vars);

// ------- ft_handling_1.c

char	*ft_token_director(char *prompt, int *i);
char	*ft_handles_pipe(char *prompt, int *i);
char	*ft_handles_redir_in(char *prompt, int *i);
char	*ft_handles_redir_out(char *prompt, int *i);
char	*ft_handles_characters(char *prompt, int *i);

// ------- ft_handling_2.c

int		ft_pipes_nbr(char **str);
void	ft_handles_in_redir(char **split, int *i, t_cmd *cmd, int *cont);
void	ft_handles_out_redir(char **split, int *i, t_cmd *cmd, int *cont);

// ------- ft_mem_tools.c

void	ft_mem_args(t_cmd *cmds, char **split);
void	ft_mem_in(t_cmd *cmds, char **split);
void	ft_mem_out(t_cmd *cmds, char **split);
void	ft_mem_cmds(t_cmd **cmds, char **split);

// ------- ft_quotes_handling.c

char	*ft_handles_double_quotes(char *prompt, int *i);
char	*ft_handles_single_quotes(char *prompt, int *i);

// ------- ft_quotes.c

int		ft_check_double_quotes(int val);
int		ft_check_single_quotes(int val);
int		ft_check_quotes(char quotes, int old);
int		ft_quotes_state(char c, int state);
void	ft_del_quotes(char *str);

// ------- ft_remove.c

void	ft_remove_spcs(char *str);

// ------- ft_struct_parse.c

void	ft_parse_cmd(char **split_cmd, int *i, t_cmd *cmd_struct);
void	ft_parse_split(t_shell *shell);

// ------- ft_tools.c

char	*ft_delete_str(char *old, size_t start, size_t finish);
char	*ft_insert_str(char *old, char *part, size_t pos);
void	ft_replace_envp(char **cmd, int *j, char *status, t_var **list);
void	ft_replace_status(char **cmd, t_var **list, char *status);

// ------- Signal Functions ------------------------------------------------- //

// ------- ft_signals.c

void	handler(int sig);
void	if_signal(void);

#endif