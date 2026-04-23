/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:25:50 by xalves            #+#    #+#             */
/*   Updated: 2026/04/23 22:13:18 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	accurate_sleep(t_manager *manager, long time)
{
	long	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
	{
		if (checkis_anyone_dead(manager) == true)
			return ;
		usleep(500);
	}
}

/* void	ft_usleep(t_manager *manager, int time)
{
	long	start;
	long	elapsed;

	start = ft_get_time();
	while (1)
	{
		if (checkis_anyone_dead(manager) == true)
			return ;
		elapsed = ft_get_time() - start;
		if (elapsed >= time)
			break ;
		usleep(1000);
	}
} */

void	msg(t_manager *manager, int id, char *action)
{
	long	time;

	if (checkis_anyone_dead(manager) == true)
	{
		return ;
	}
	pthread_mutex_lock(&manager->print_mutex);
	time = get_timesincestart(manager->pstart_time);
	printf("%ld %d %s\n", time, id, action);
	pthread_mutex_unlock(&manager->print_mutex);
}

//eat function
void	eat(t_philo *philo)
{

	lock_forks(philo);
	msg(philo->manager, philo->id, "is eating");
	pthread_mutex_lock(&philo->manager->eating_mutex);
	philo->last_time_eat = ft_get_time();
	philo->n_meals++;
	if (philo->n_meals == philo->manager->param.number_oftotal_meals)
	{
		philo->manager->n_philo_finished_eating++;
	}
	pthread_mutex_unlock(&philo->manager->eating_mutex);
	accurate_sleep(philo->manager, philo->param.time_to_eat);
	unlock_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	msg(philo->manager, philo->id, "is sleeping");
	accurate_sleep(philo->manager, philo->param.time_to_sleep);
}

bool	checkis_anyone_dead(t_manager *manager)
{
	bool	ret;

	pthread_mutex_lock(&manager->checkdead_mutex);
	ret = manager->is_anyone_dead;
	pthread_mutex_unlock(&manager->checkdead_mutex);
	return (ret);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		accurate_sleep(philo->manager, 10);
	while (!checkis_anyone_dead(philo->manager))
	{
		eat(philo);
		if (checkis_anyone_dead(philo->manager) == true)
		{
			break ;
		}
		philo_sleep(philo);
		if (checkis_anyone_dead(philo->manager) == true)
		{
			break ;
		}
		msg(philo->manager, philo->id, "is thinking");//philo think
	}
	return (NULL);
}
