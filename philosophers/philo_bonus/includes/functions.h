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

// ------- ft_check_arg.c --------------------------------------------------- //

int			ft_argv_num(int argc, char **argv);
int			ft_check_args(int c, char **v);

// ------- ft_check.c ------------------------------------------------------- //

int			ft_error_argv(int argc, char **argv);
t_state		ft_how_are_you(t_data *data);
bool		ft_everyone_ok(void);
void		ft_philo_dep(void);
bool		ft_rip(t_data *data);

// ------- ft_controller.c -------------------------------------------------- //

void		*ft_cerberus(void *data_p);

// ------- ft_eat_n_think.c ------------------------------------------------- //

bool		ft_num_meals(t_data *data);
bool		ft_has_eaten(t_data *data);
int			ft_eating(t_data *data);
int			ft_thinking(t_data *data);
uint64_t	ft_get_last_eat(t_data *data);

// ------- ft_forks.c ------------------------------------------------------- //

int			ft_drop_forks(t_data *data);
int			ft_get_forks(t_data *data);

// ------- ft_free_tools.c -------------------------------------------------- //

void		ft_free_sem(t_data *data);

// ------- ft_gettering_a.c ------------------------------------------------- //

uint64_t	ft_get_start(t_data *data);
void		ft_get_last_meal(t_data *data);

// ------- ft_init.c -------------------------------------------------------- //

int			ft_init_all(t_data *data);
int			ft_init_philo(int argc, char **argv);
char		*ft_init_sem_name(int id);
int			ft_init_sem(t_data *data);
int			ft_init_values(t_data *data, int argc, char **argv);

// ------- ft_philo_bonus.c ------------------------------------------------- //

int			ft_run_all(t_data *data, int id);
int			ft_philo_struct(t_data *data, int id);

// ------- ft_printing.c ---------------------------------------------------- //

int			ft_writing(t_data *data, char *msg);
void		ft_instruction(void);

// ------- ft_sleep.c ------------------------------------------------------- //

void		ft_sleeping_for_eating(t_data *data);
int			ft_sleeping(t_data *data);

// ------- ft_tools_1.c ----------------------------------------------------- //

int			ft_strlen(char *str);
int			ft_num_digits(long n);
char		*ft_itoa(int n);
int			ft_atoi(char *str);
char		*ft_strjoin(char *s1, char *s2);

// ------- ft_tools_2.c ----------------------------------------------------- //

void		ft_delay_even(t_data *data);
bool		ft_suspend(t_state state);
void		ft_status(t_data *data, t_state state);
void		ft_delay(uint64_t sleep_time);
uint64_t	ft_my_watch(void);

#endif