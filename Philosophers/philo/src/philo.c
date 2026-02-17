/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vampaier2 <vampaier2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:20:17 by xalves            #+#    #+#             */
/*   Updated: 2026/02/16 14:05:12 by vampaier2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	create_mutex(t_manager *manager)
{
	manager->mutex_man.param = manager->param;
	manager->mutex_man.forks = ft_calloc(sizeof(pthread_mutex_t), manager->param.n_philos);
	if (!manager->mutex_man.forks)
		return (1);
	manager->mutex_man.philo_lock = ft_calloc(sizeof(pthread_mutex_t), manager->param.n_philos);
	if (!manager->mutex_man.philo_lock)
		return (1);
	return (0);
}

// -------------- struct funcs -----------------------
/// @brief creates new struct
/// @param content content to be given new struct
/// @return returns the created struct
int	ft_createphilo(t_philo *philo, int i, t_manager *manager)
{
	philo->id = i + 1;
	philo->mutex_man = &manager->mutex_man;
	philo->n_meals = 0;
	philo->last_time_eat = ft_get_time();
	philo->param = manager->param;
	//---------FORKS---------
	//Left
	if (i == 0)//if first philo
		philo->l_fork = &manager->mutex_man.forks[philo->param.n_philos - 1];
	else
		philo->l_fork = &manager->mutex_man.forks[i - 1];
	//Right
	philo->r_fork = &manager->mutex_man.forks[i];
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
		//printf("Philosopher %d was freed\n", manager->arr_philos[i].id);
		pthread_mutex_destroy(&manager->mutex_man.forks[i]);
		pthread_mutex_destroy(&manager->arr_philos[i].last_eat_mutex);
		i++;
	}
	//free(&manager->mutex_man.forks);
	free(manager->arr_philos);
}