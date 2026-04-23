/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:20:17 by xalves            #+#    #+#             */
/*   Updated: 2026/04/23 22:33:11 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// -------------- struct funcs -----------------------
/// @brief creates new struct
/// @param content content to be given new struct
/// @return returns the created struct
int	ft_createphilo(t_philo *philo, int i, t_manager *manager)
{
	philo->id = i + 1;
	philo->manager = manager;
	philo->n_meals = 0;
	philo->last_time_eat = manager->pstart_time;
	philo->param = manager->param;
	//---------FORKS---------
	//Left
	if (i == 0)//if first philo
		philo->l_fork = &manager->forks[philo->param.n_philos - 1];
	else
		philo->l_fork = &manager->forks[i - 1];
	//Right
	philo->r_fork = &manager->forks[i];
	if (pthread_create(&philo->thread, NULL, &routine, philo) != 0)
		return (1);
	return (0);
}

void	ft_free_philo(t_manager *manager)
{
	int		i;

	i = 0;
	while (i < manager->param.n_philos)
	{
		pthread_mutex_destroy(&manager->forks[i]);
		i++;
	}
	free(manager->arr_philos);
}