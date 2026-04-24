/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:47:11 by xalves            #+#    #+#             */
/*   Updated: 2026/04/24 15:36:24 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_time_to_die(t_manager *manager)
{
	int		id;
	long	time;
	long	last_eat;

	id = 0;
	while (id < manager->param.n_philos)
	{
		pthread_mutex_lock(&manager->eating_mutex);
		last_eat = manager->arr_philos[id].last_time_eat;
		pthread_mutex_unlock(&manager->eating_mutex);
		if ((ft_get_time() - last_eat) > manager->param.time_to_die)
		{
			pthread_mutex_lock(&manager->checkdead_mutex);
			manager->is_anyone_dead = true;
			manager->id_of_dead = id + 1;
			pthread_mutex_unlock(&manager->checkdead_mutex);
			pthread_mutex_lock(&manager->print_mutex);
			time = get_timesincestart(manager->pstart_time);
			printf("%ld %d died\n", time, id + 1);
			pthread_mutex_unlock(&manager->print_mutex);
			return (1);
		}
		id++;
	}
	return (0);
}

int	check_philo_limit_eat(t_manager *manager)
{
	pthread_mutex_lock(&manager->checkdead_mutex);
	pthread_mutex_lock(&manager->eating_mutex);
	if (manager->n_philo_finished_eating == manager->param.n_philos)
	{
		manager->is_anyone_dead = true;
		pthread_mutex_unlock(&manager->eating_mutex);
		pthread_mutex_unlock(&manager->checkdead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&manager->eating_mutex);
	pthread_mutex_unlock(&manager->checkdead_mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_manager	*manager;

	manager = (t_manager *)arg;
	while (1)
	{
		if (manager->param.number_oftotal_meals != -1)
		{
			if (check_philo_limit_eat(manager))
				return (NULL);
		}
		if (check_time_to_die(manager))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
