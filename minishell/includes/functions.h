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

// ------- Execution Functions ---------------------------------------------- //



// ------- Parser Functions ------------------------------------------------- //

// ------- ft_checkers.c

int     ft_check_cmd(t_minishell *minishell);
// The ft_check_cmd() function checks if a command is valid. It takes a pointer
// to a t_minishell structure as an argument. It returns 1 if the command is
// valid, and 0 if the command is not valid.

int     ft_chek_first_pipe(char *str);
// The ft_chek_first_pipe() function checks if a string contains pipe character
// at the beginning. It takes one argument: a string. It returns 1 if the string
// contains a pipe character at the beginning, and 0 if the string does not
// contain a pipe character at the beginning.

int     ft_check_last_pipe(char *str);
// The ft_check_last_pipe() function checks if a string contains a pipe character
// at the end. It takes one argument: a string. It returns 1 if the string
// contains a pipe character at the end, and 0 if the string does not contain a
// pipe character at the end.

int     ft_check_mixes(char *str, int i);
// The ft_chek_mixes() function checks if a string contains a mix of pipe and
// redirection characters. It takes two arguments: a string and an index. It
// returns 1 if the string contains a mix of pipe and redirection characters, and
// 0 if the string does not contain a mix of pipe and redirection characters.

int     ft_validating_pipes(char *str);
// The ft_validating_pipes() function checks if a string contains valid pipe
// characters. It takes one argument: a string. It returns 1 if the string
// contains valid pipe characters, and 0 if the string does not contain valid
// pipe characters.

// ------- ft_elements.c

int     ft_check_quotes(char *str, int i);
// The ft_check_quotes() function checks if a character is a quote. It takes two
// arguments: a string and an index. It returns DQ_OPEN if the character is a
// double quote, SQ_OPEN if the character is a single quote, and NO_QUOTE if
// the character is not a quote.

int     ft_chck_pipe(char *str);
// The ft_chck_pipe() function checks if a string contains a pipe character. It
// takes one argument: a string. It returns 1 if the string contains a pipe
// character, and 0 if the string does not contain a pipe character.

int     ft_check_redirection(char *str, int i);
// The ft_check_redirection() function checks if a character is a redirection
// character. It takes two arguments: a string and an index. It returns 1 if
// the character is a '>', 2 if the character is a '<', and 0 if the character
// is not a redirection character.

// ------- ft_env_tools.c

char    *ft_find_var(char *str, int i);
// The ft_find_var() function finds the variable in the command. It takes two
// arguments: a string and an index. It returns a pointer to the variable.

char    *ft_get_var(t_var **list_var, char *str);
// The ft_get_var() function gets the value of the variable. It takes two
// arguments: a pointer to a t_var structure and a pointer to a string. It
// returns a pointer to the value of the variable.

char    *ft_insert_str(char *str, char *ins, size_t pos);
// The ft_insert_str() function inserts a string into another string. It takes
// three arguments: two strings and a position. It returns a pointer to the new
// string.

// ------- ft_environment.c

static void	ft_replace_vars(char **str, int *i, char *status, t_var **list_var);
// The ft_replace_vars() function replaces the environment variables in the 
// command with their values. It takes three arguments: a pointer to a char
// array, a pointer to an index, a pointer to a char array, and a pointer to a
// t_var structure.

static void	ft_do_cmd(char **str, t_var **list_var, char *status);
// The ft_do_cmd() function processes the command. It takes three arguments: a
// pointer to a char array, a pointer to a t_var structure, and a pointer to a
// char array.

void	ft_restore_dolar(char **dolar);
// The ft_restore_dolar() function restores the dollar signs in the command. It
// takes a pointer to a char array as an argument.

// ------- ft_handling.c 

int     ft_end_word(char *str, int i);
// The ft_end_word() function calculates the end of a word in a string. It takes
// two arguments: a string and an index. It returns the index of the next space
// or redirection character in the string.

int     ft_len_word(char *str, int i);
// The ft_len_word() function calculates the length of a word in a string. It
// takes two arguments: a string and an index. It returns the length of the word
// in the string.

char    *ft_process_word(char *str, int *i);
// The ft_process_char() function extracts a word from a string. It takes two
// arguments: a string and a pointer to an index. It returns a pointer to the
// word extracted from the string.

// ------- ft_remove.c

void    ft_remove_quotes(char *str);
// The ft_remove_quotes() function removes the single and double quotes from a
// string. It takes one argument: a string and returns void.

char    *ft_delete_str(char *str, size_t init, size_t end);
// The ft_delete_str() function deletes a substring from a string. It takes 
// three arguments: a string, an initial position, and an end position. It
// returns a pointer to the modified string.

// ------- ft_struct_len.c

int     ft_len_double(char *str, int i);
// The ft_len_double() function calculates the length of a word in a string. It
// takes two arguments: a string and an index. It returns the length of the word
// in the string. The " character is used to calculate the length of the word.

int     ft_len_single(char *str, int i);
// The ft_len_single() function calculates the length of a word in a string. It
// takes two arguments: a string and an index. It returns the length of the word
// in the string. The ' character is used to calculate the length of the word.

int     ft_len_pipe(char *str, int i);
// The ft_len_pipe() function calculates the length of a word in a string. It
// takes two arguments: a string and an index. It returns the length of the word
// in the string. The | character is used to calculate the length of the word.

int     ft_len_redirection_1(char *str, int i);
// The ft_len_redirection_1() function calculates the length of a word in a
// string. It takes two arguments: a string and an index. It returns the length
// of the word in the string. The > character is used to calculate the length of
// the word.

int     ft_len_redirection_2(char *str, int i);
// The ft_len_redirection_2() function calculates the length of a word in a
// string. It takes two arguments: a string and an index. It returns the length
// of the word in the string. The < character is used to calculate the length of
// the word.

// ------- ft_struct_parse.c

void    ft_parse_input(t_minishell *minishell);
// The ft_parse_input() function reads the input from the user, parses it into
// tokens, and prints the tokens to the screen. It takes a pointer to a
// t_minishell structure as an argument.

// ------- ft_struct_process.c

char    *ft_process_double(char *str, int *i);
// The ft_process_word() function extracts a word from a string. It takes two
// arguments: a string and a pointer to an index. It returns a pointer to the
// word extracted from the string. The " character is used to extract the word.

char    *ft_process_singel(char *str, int *i);
// The ft_process_word_next() function extracts a word from a string. It takes
// two arguments: a string and a pointer to an index. It returns a pointer to
// the word extracted from the string. The ' character is used to extract the   
// word.

char    *ft_process_pipe(char *str, int *i);
// The ft_process_pipe() function extracts a word from a string. It takes two
// arguments: a string and a pointer to an index. It returns a pointer to the
// word extracted from the string. The | character is used to extract the word.

char    *ft_process_redirection_1(char *str, int *i);
// The ft_process_redirection_1() function extracts a word from a string. It
// takes two arguments: a string and a pointer to an index. It returns a pointer
// to the word extracted from the string. The > character is used to extract the
// word.

char    *ft_process_redirection_2(char *str, int *i);
// The ft_process_redirection_2() function extracts a word from a string. It
// takes two arguments: a string and a pointer to an index. It returns a pointer
// to the word extracted from the string. The < character is used to extract the
// word.

// ------- ft_token.c

char    **ft_top_split(char *str);
// The ft_top_split() function splits a string into an array of strings. It 
// takes one argument: a string. It returns an array of strings.

char    *proess_tokens(char *str, int *i);
// The process_tokens() function extracts a word from a string. It takes two
// arguments: a string and a pointer to an index. It returns a pointer to the
// word extracted from the string.

#endif