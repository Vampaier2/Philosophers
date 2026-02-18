/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:51:58 by xalves            #+#    #+#             */
/*   Updated: 2026/02/18 15:52:02 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/// @brief routine for the monitor. Check (n meals) + if philo died
/// @param arg 
/// @return 
void	*monitor_routine(void *arg)
{
	t_philo		*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (check_limite_eat(philos))
			return (NULL);
		if (check_time_to_die(philos))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

/// @brief routine for every philo
/// @param arg 
/// @return 
void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_usleep(data, 10);
	while (!checkdead_flag(data))
	{
		philo_eat(philo);
		if (checkdead_flag(data))
			break ;
		philo_sleep(philo);
		if (checkdead_flag(data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

/// @brief 
/// @param philos 
void	start_routines(t_philo *philos)
{
	int		id;
	int		num;

	id = 0;
	while (id < philos->data->args.n_philos)
	{
		pthread_create(&philos[id].philo, NULL, &routine, &philos[id]);
		id++;
	}
	pthread_create(&philos->data->monitor, NULL, &monitor_routine, philos);
	pthread_join(philos->data->monitor, NULL);
	num = philos->data->id_dead;
	if (num > 0)
	{
		pthread_mutex_lock(&philos->data->mutex.print_mutex);
		printf("%ld %i died\n", get_timesincestart(philos[num - 1]), num);
		pthread_mutex_unlock(&philos->data->mutex.print_mutex);
	}
	id = 0;
	while (id < philos->data->args.n_philos)
	{
		pthread_join(philos[id].philo, NULL);
		id++;
	}
}
