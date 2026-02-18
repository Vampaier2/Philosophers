/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:27:31 by xalves            #+#    #+#             */
/*   Updated: 2026/02/18 15:48:42 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

//philos[num - 1].data->pstart_time
long	get_timesincestart(t_philo philo)
{
	return (ft_get_time() - philo.data->pstart_time);
}

/* long	time_since_last_eat(t_philo *philo)
{
	long	last;

	pthread_mutex_lock(&philo->last_eat_mutex);
	last = philo->last_time_eat;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	return (ft_get_time() - last);
} */