/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:25:50 by xalves            #+#    #+#             */
/*   Updated: 2026/02/10 15:34:46 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void accurate_sleep(t_philo *philo, long time)
{
    long	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
	{
		if (check_if_philo_died(philo) == 1)
			return ;
		usleep(500);
	}
}

void	msg(t_manager *manager, int id, char *action)
{
	long	time;

	pthread_mutex_lock(&manager->print_mutex);
	time = get_timesincestart(manager->pstart_time);
	/* if (!read_end(w))*/
	printf("%ld %d %s\n", time, id, action); 
	pthread_mutex_unlock(&manager->print_mutex);
}

int checkdead_flag(t_manager *manager)
{
    int ret;
    
    pthread_mutex_lock(&manager->deadflag_mutex);
    ret = manager->dead_flag;
    pthread_mutex_unlock(&manager->deadflag_mutex);
    return (ret);
}

//eat function
void	*eat(t_philo *philo)
{
    if (checkdead_flag(philo->manager) == 1)// if any philo dead, you stop
    {
        return (NULL);
	}
    lock_forks(philo);
    msg(philo->manager, philo->id, "is eating");
    philo->last_time_eat = ft_get_time();
    accurate_sleep(philo, philo->param.time_to_eat);
	unlock_forks(philo);

	philo->n_meals++;
	if (philo->n_meals == philo->manager->param.number_oftotal_meals)
	{//stop thread??? i don't know
		return (NULL);
	}
	return (philo);
}

int	check_if_philo_died(t_philo *philo)
{
	if (time_since_last_eat(philo) > philo->param.time_to_die)
    {
        msg(philo->manager, philo->id, "died");
        //write(2, " ----------guh-------------\n", 7);----------------debuging
        pthread_mutex_lock(&philo->manager->deadflag_mutex);
        philo->manager->dead_flag = 1;
        pthread_mutex_unlock(&philo->manager->deadflag_mutex);
        return (1);
    }
	return (0);
}

int	smartsleep(t_philo *philo)
{
    if (checkdead_flag(philo->manager) == 1)// if any philo dead, you stop    
	    return (1);
    msg(philo->manager, philo->id, "is sleeping");
    accurate_sleep(philo, philo->param.time_to_sleep);
	return (0);
}

// pthread_mutex_lock
void *routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	while (1)
	{
		if(check_if_philo_died(philo) == 1) // check if died before
			return (NULL);
		//------------------eat--------------------------
		if (eat(philo) == NULL)
			return (NULL);
		if(check_if_philo_died(philo) == 1) // check if died after
			return (NULL);
		//------------------sleeping----------------------
		if (smartsleep(philo) == 1)
			return (NULL);
		//usleep(philo->manager->time_to_sleep * 1000);
		//------------------thinking----------------------
		if (check_if_philo_died(philo) == 1)// if any philo dead, you stop
			return (NULL);
		msg(philo->manager, philo->id, "is thinking");
	}
	return (NULL);
}