/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:25:08 by xalves            #+#    #+#             */
/*   Updated: 2026/02/18 16:00:39 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aux.h"

void	ft_usleep(t_data *data, int time)
{
	long	start;
	long	elapsed;

	start = ft_get_time();
	while (1)
	{
		if (checkdead_flag(data))
			return ;
		elapsed = ft_get_time() - start;
		if (elapsed >= time)
			break ;
		usleep(1000);
	}
}

void	msg(char *str, t_philo *philo)
{
	long	time;

	if (checkdead_flag(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->mutex.print_mutex);
	time = ft_get_time() - philo->data->pstart_time;
	printf("%ld %i %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->mutex.print_mutex);
}
