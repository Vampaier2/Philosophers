/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:13:04 by xalves            #+#    #+#             */
/*   Updated: 2026/02/10 12:05:22 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	lock_forks(t_philo *philo)
{
	if (odd_or_even(philo->id) == 2)//par - right->left
	{
		pthread_mutex_lock(philo->r_fork);
		msg(philo->manager, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		msg(philo->manager, philo->id, "has taken a fork");
	}
	else//impar- left->right
	{
		pthread_mutex_lock(philo->l_fork);
		msg(philo->manager, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		msg(philo->manager, philo->id, "has taken a fork");
	}
}

void unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	init_arrforks(t_manager	*manager)
{
	int	i;

	i = 0;

	manager->forks = ft_calloc(sizeof(pthread_mutex_t), manager->param.n_philos);
	if (manager->forks == NULL)
		return (1);
	while (i < manager->param.n_philos)
	{
		if (pthread_mutex_init(&manager->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}