/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:27:23 by xalves            #+#    #+#             */
/*   Updated: 2026/02/18 15:50:52 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	checkdead_flag(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->mutex.deadflag_mutex);
	ret = data->dead_flag;
	pthread_mutex_unlock(&data->mutex.deadflag_mutex);
	return (ret);
}

int	check_limite_eat(t_philo *philos)
{
	int		id;
	t_data	*data;

	id = 0;
	data = philos->data;
	if (data->args.count_eat == -1)
		return (0);
	pthread_mutex_lock(&data->mutex.meal_flag);
	while (id < data->args.n_philos)
	{
		if (philos[id].limit_eat == 0)
			break ;
		id++;
	}
	if (id == data->args.n_philos)
	{
		pthread_mutex_lock(&data->mutex.deadflag_mutex);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->mutex.deadflag_mutex);
		pthread_mutex_unlock(&data->mutex.meal_flag);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex.meal_flag);
	return (0);
}

int	check_time_to_die(t_philo *philos)
{
	int		id;
	t_data	*data;

	data = philos->data;
	id = 0;
	while (id < data->args.n_philos)
	{
		pthread_mutex_lock(&data->mutex.meal_flag);
		if (ft_get_time() - philos[id].last_eat_time > data->args.time_to_die)
		{
			pthread_mutex_lock(&data->mutex.deadflag_mutex);
			data->dead_flag = 1;
			data->id_dead = id + 1;
			pthread_mutex_unlock(&data->mutex.deadflag_mutex);
			pthread_mutex_unlock(&data->mutex.meal_flag);
			return (1);
		}
		pthread_mutex_unlock(&data->mutex.meal_flag);
		id++;
	}
	return (0);
}
