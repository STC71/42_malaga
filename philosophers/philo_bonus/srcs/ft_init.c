/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 12:40:50 by sternero          #+#    #+#             */
/*   Updated: 2024-10-31 12:40:50 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_init_all(t_data *data)
{
	pid_t	p_id;
	int		i;

	i = 0;
	data->start_time = ft_my_watch();
	while (i++ < data->philos_num)
	{
		p_id = fork();
		if (p_id == 0)
		{
			ft_run_all(data, i);
		}
		else if (p_id == -1)
			return (ERROR_FORK);
	}
	p_id = waitpid(0, NULL, 0);
	while (p_id != -1)
		p_id = waitpid(0, NULL, 0);
	return (SUCCESS);
}

int	ft_init_philo(int argc, char **argv)
{
	t_data	data;

	if (ft_init_values(&data, argc, argv) != 0)
		return (ERROR_INPUT);
	ft_init_all(&data);
	ft_free_sem(&data);
	return (0);
}

char	*ft_init_sem_name(int id)
{
	return (ft_strjoin("/philo_", ft_itoa(id)));
}

int	ft_init_sem(t_data *data)
{
	sem_unlink("/death");
	sem_unlink("/forks");
	sem_unlink("/print");
	data->forks_sem = sem_open("/forks", O_CREAT, 0644, data->philos_num);
	data->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	if (data->forks_sem == SEM_FAILED)
	{
		printf("SEM FAILED\n");
		return (ERROR_SEM);
	}
	if (data->print_sem == SEM_FAILED)
	{
		printf("SEM FAILED\n");
		return (ERROR_SEM);
	}
	sem_unlink("/forks");
	sem_unlink("/print");
	return (0);
}

int	ft_init_values(t_data *data, int argc, char **argv)
{
	data->philos_num = ft_atoi(argv[1]);
	data->die_time = (uint64_t) ft_atoi(argv[2]);
	data->eat_time = (uint64_t) ft_atoi(argv[3]);
	data->sleep_time = (uint64_t) ft_atoi(argv[4]);
	data->meals_num = -1;
	if (argc == 6)
		data->meals_num = ft_atoi(argv[5]);
	data->philo.data = data;
	data->philo.meals = 0;
	data->philo.state = OFF;
	return (ft_init_sem(data));
}
