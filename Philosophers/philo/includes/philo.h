/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:32:16 by xalves            #+#    #+#             */
/*   Updated: 2025/09/23 17:00:58 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <string.h>     // memset
#include <stdio.h>      // printf
#include <stdlib.h>     // malloc, free
#include <unistd.h>     // write, usleep
#include <sys/time.h>   // gettimeofday
#include <pthread.h>    // pthread_create, pthread_detach, pthread_join, pthread_mutex_*

typedef struct	s_manager
{
	int	n_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_oftotal_meals;
}				t_manager;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_manager		manager; // manager
	int				n_meals;
	//pthread_mutex_t	r_fork; // AKA right fork
	//pthread_mutex_t	l_fork; // AKA left fork


}	t_philo;
#endif
