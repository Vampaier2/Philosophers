/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:25:50 by xalves            #+#    #+#             */
/*   Updated: 2026/02/11 18:04:22 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"



void accurate_sleep(t_philo *philo, long time)
{
    long	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
	{
		if (checkdead_flag(philo->mutex_man) == 1)
			return ;
		usleep(500);
	}
}

void	msg(t_mutex_man *mutex_man, int id, char *action) // was manager
{
	long	time;

	pthread_mutex_lock(&mutex_man->print_mutex);
	if (checkdead_flag(mutex_man) == 0)
	{
		time = get_timesincestart(mutex_man->param.pstart_time);//dupe pstart_time
		printf("%ld %d %s\n", time, id, action);
	}
	pthread_mutex_unlock(&mutex_man->print_mutex);
}

bool checkdead_flag(t_mutex_man *mutex_man) // was manager
{
    bool ret;
    
    pthread_mutex_lock(&mutex_man->deadflag_mutex);
    ret = &mutex_man->dead_flag;
	pthread_mutex_unlock(&mutex_man->deadflag_mutex);
    return (ret);
}

//eat function
void	*eat(t_philo *philo)
{
/*     if (check_if_philo_died(philo) == 1)// if any philo dead, you stop
    {
        return (NULL);
	}
	else
	{ */
	lock_forks(philo);
	pthread_mutex_lock(&philo->mutex_man->philo_lock[philo->id - 1]);
	philo->last_time_eat = ft_get_time();
	accurate_sleep(philo, philo->param.time_to_eat);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->mutex_man->philo_lock[philo->id - 1]);
	unlock_forks(philo);
	msg(philo, philo->id, "is eating");
	if (philo->n_meals == philo->param.number_oftotal_meals)
	{//stop thread??? i don't know
		return (NULL);
	}
//	}
	return (philo);
}

int	smartsleep(t_philo *philo)
{
    if (checkdead_flag(philo) == 1)// if any philo dead, you stop    
	    return (1);
    msg(philo, philo->id, "is sleeping");
    accurate_sleep(philo, philo->param.time_to_sleep);
	return (0);
}

// pthread_mutex_lock
void *routine(void *arg)
{
	t_philo	*philo = arg;

	if ((philo->id % 2) == 0)
		accurate_sleep(philo, 10);
	while (1)
	{
		//------------------eat--------------------------
		if (eat(philo) == NULL)
			return (NULL);
		//------------------sleeping----------------------
		if (smartsleep(philo) == 1)
			return (NULL);
		//------------------thinking----------------------
		msg(philo->mutex_man, philo->id, "is thinking");
		//usleep(500);
	}
	return (NULL);
}