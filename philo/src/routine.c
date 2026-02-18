/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:27:11 by xalves            #+#    #+#             */
/*   Updated: 2026/02/18 15:48:07 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	take_forks(t_philo *philo, int id)
{
	if (id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		msg("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		msg("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		msg("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		msg("has taken a fork", philo);
	}
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo, philo->id);
	pthread_mutex_lock(&philo->data->mutex.meal_flag);
	msg("is eating", philo);
	philo->last_eat_time = ft_get_time();
	philo->count_eat++;
	if (philo->count_eat == philo->data->args.count_eat)
		philo->limit_eat = 1;
	pthread_mutex_unlock(&philo->data->mutex.meal_flag);
	ft_usleep(philo->data, philo->data->args.time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	msg("is sleeping", philo);
	ft_usleep(philo->data, philo->data->args.time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	msg("is thinking", philo);
	if (philo->data->args.n_philos % 2 != 0)
		if (philo->data->args.time_to_eat >= philo->data->args.time_to_sleep)
			ft_usleep(philo->data, (philo->data->args.time_to_eat * 2)
				- philo->data->args.time_to_sleep);
}
