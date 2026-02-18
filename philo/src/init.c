/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vampaier2 <vampaier2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:26:44 by xalves            #+#    #+#             */
/*   Updated: 2026/02/18 16:39:07 by vampaier2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_args(t_args *args, char **av)
{
	if (av[5])
		args->count_eat = ft_atoi(av[5]);
	else
		args->count_eat = -1;
	args->n_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
}

int	init_mutex2(t_mutex *mutex)
{
	mutex->init_write_flag = 0;
	mutex->init_dead_flag = 0;
	mutex->init_meal_flag = 0;
	if (pthread_mutex_init(&mutex->print_mutex, NULL) != 0)
		return (1);
	else
		mutex->init_write_flag = 1;
	if (pthread_mutex_init(&mutex->deadflag_mutex, NULL) != 0)
		return (1);
	else
		mutex->init_dead_flag = 1;
	if (pthread_mutex_init(&mutex->meal_flag, NULL) != 0)
		return (1);
	else
		mutex->init_meal_flag = 0;
	return (0);
}

int	init_mutex(t_data *data, t_mutex *mutex)
{
	int		fork;

	mutex->forks = malloc(sizeof(pthread_mutex_t) * data->args.n_philos);
	if (!mutex->forks)
		return (1);
	fork = 0;
	while (fork < data->args.n_philos)
	{
		if (pthread_mutex_init(&mutex->forks[fork], NULL) != 0)
		{
			while (--fork >= 0)
				pthread_mutex_destroy(&mutex->forks[fork]);
			return (1);
		}
		fork++;
	}
	if (init_mutex2(mutex))
		return (1);
	return (0);
}

void	init_philo(t_philo *philo, int id, t_data *data)
{
	philo->data = data;
	philo->last_eat_time = ft_get_time();
	philo->id = id + 1;
	philo->count_eat = 0;
	philo->limit_eat = 0;
	philo->l_fork = &data->mutex.forks[id];
	philo->r_fork = &data->mutex.forks[(id + 1) % data->args.n_philos];
}

//create_table
t_philo	*create_philos(t_data *data)
{
	int		philo;
	t_philo	*table;

	table = ft_calloc(data->args.n_philos, sizeof(t_philo));
	if (!table)
		return (NULL);
	philo = 0;
	while (philo < data->args.n_philos)
	{
		init_philo(&table[philo], philo, data);
		philo++;
	}
	if (philo == data->args.n_philos)
		data->philo_check = 1;
	return (table);
}
