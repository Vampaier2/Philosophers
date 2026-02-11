/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:06:43 by xalves            #+#    #+#             */
/*   Updated: 2026/02/11 16:07:48 by xalves           ###   ########.fr       */
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

long	get_timesincestart(long pstart_time)
{
	return (ft_get_time() - pstart_time);
}

long	time_since_last_eat(t_philo *philo)
{
	long	last;

	pthread_mutex_lock(&philo->last_eat_mutex);
	last = philo->last_time_eat;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	return (ft_get_time() - last);
}