/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:23:54 by xalves            #+#    #+#             */
/*   Updated: 2026/02/18 16:09:10 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	init_all(t_data *data, char **argv)
{
	data->philo_check = 0;
	data->dead_flag = 0;
	data->id_dead = 0;
	data->pstart_time = ft_get_time();
	init_args(&data->args, argv);
	if (init_mutex(data, &data->mutex))
		return (1);
	data->philos = create_philos(data);
	if (!data->philos)
		return (1);
	return (0);
}

void	clear_all(t_philo *philos, t_mutex *mutex)
{
	int		id;

	id = 0;
	if (mutex)
	{
		if (mutex->forks)
		{
			while (id < philos->data->args.n_philos)
			{
				pthread_mutex_destroy(&mutex->forks[id]);
				id++;
			}
		}
		free(mutex->forks);
		if (mutex->init_dead_flag)
			pthread_mutex_destroy(&mutex->deadflag_mutex);
		if (mutex->init_write_flag)
			pthread_mutex_destroy(&mutex->print_mutex);
		if (mutex->init_meal_flag)
			pthread_mutex_destroy(&mutex->meal_flag);
	}
	if (philos)
		free(philos);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (parcing(argc, argv) == 1)
		return (1);
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi(argv[2]) * 1000);
		printf("%i 1 died\n", ft_atoi(argv[2]));
		return (0);
	}
	if (init_all(&data, argv))
	{
		ft_putstr_fd("Error: initialization failed!!!", 2);
		clear_all(data.philos, &data.mutex);
		return (1);
	}
	if (data.philo_check == 1)
		start_routines(data.philos);
	clear_all(data.philos, &data.mutex);
}
