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

// ------- ft_check.c ------------------------------------------------------- //

int		ft_check_args(int c, char **v);
int		ft_error_argv(int argc, char **argv);
int		ft_argv_num(int argc, char **argv);
t_state	ft_how_are_you(t_philo *philo);
void	*ft_are_you_dead(void *data);

// ------- ft_controller.c -------------------------------------------------- //

bool	ft_keep_or_not(t_data *data);
bool	ft_has_eaten(t_data *value, t_philo *philo);
bool	ft_rip(t_philo *philo);
bool	ft_num_meals(t_data *value);

// ------- ft_eat_n_think.c ------------------------------------------------- //

int		ft_times_eating(t_philo *philo);
int		ft_eating(t_philo *philo);
int		ft_thinking(t_philo *philo);

// ------- ft_forks.c ------------------------------------------------------- //

void	ft_drop_fork(t_philo *philo);
void	ft_drop_fork_l(t_philo *philo);
void	ft_drop_fork_r(t_philo *philo);

// ------- ft_free_tools.c ------------------------------------------------- //

void	leaks(void);
void	ft_free_all(t_data *data);
int		ft_malloc(t_data *data);

// ------- ft_gettering_a.c ------------------------------------------------- //

void	ft_get_last_meal(t_philo *philo);
void	ft_get_num_meals(t_philo *philo);
uint64_t	ft_get_die(t_data *data);
uint64_t	ft_get_eat(t_data *data);
uint64_t	ft_get_last_eat(t_philo *philo);

// ------- ft_gettering_b.c ------------------------------------------------- //

int		ft_get_fork_l(t_philo *philo);
int		ft_get_fork_r(t_philo *philo);
int		get_forks(t_philo *philo);

// ------- ft_gettering_c.c ------------------------------------------------- //

uint64_t	ft_get_start(t_data *data);
uint64_t	ft_get_sleep(t_data *data);

// ------- ft_init.c -------------------------------------------------------- //

int		ft_init_values(t_data *data, int argc, char **argv);
int		ft_init_threads(t_data *data);
int		ft_init_philos(int argc, char **argv);
int		ft_init_philos_data(t_data *data);
int		ft_init_forks(t_data *data);

// ------- ft_philo_bonus.c ------------------------------------------------- //

// int		main(int argc, char **argv);
// main function is the entry point of the program. It checks the number of
// arguments and the values of the arguments passed to the program. If the
// arguments are not valid, it calls ft_check_args() with the corresponding
// error number. 

void	*ft_the_core(void *philo);
int		ft_only_one(t_philo *philo);
void	*ft_the_watchdog(void *value);
int		ft_sincro(t_data *data);

// ------- ft_printing.c ---------------------------------------------------- //

void	ft_writing(t_data *data, int id, char *src);
void	ft_instruction(void);

// ------- ft_sleep.c ------------------------------------------------------- //

int		ft_sleeping(t_philo *philo);
void	ft_sleep_for_eating(t_philo *philo);

// ------- ft_tools_1.c ----------------------------------------------------- //

void	ft_delay(uint64_t pause);
uint64_t	ft_my_watch(void);
int		ft_atoi(char *str);

// ------- ft_tools_2.c ----------------------------------------------------- //

int		ft_num_philos(t_data *data);
void	ft_game_over(t_data *value);
void	ft_keep_flag(t_data *value, bool now);
void	ft_status(t_philo *philo, t_state status);

#endif