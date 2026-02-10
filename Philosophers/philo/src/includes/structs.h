/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:19:06 by vampaier2         #+#    #+#             */
/*   Updated: 2026/02/10 15:32:38 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../main.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_param
{
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_oftotal_meals;
}	t_param;

typedef struct s_manager	t_manager;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_manager		*manager; // manager
	int				n_meals;
	long			last_time_eat;
	pthread_mutex_t	*r_fork; // AKA right fork
	pthread_mutex_t	*l_fork; // AKA left fork
	long			pstart_time;
	t_param			param;
}	t_philo;



typedef struct s_manager
{
	t_param			param;
	long			pstart_time;
	int				dead_flag;
	t_philo			*arr_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	deadflag_mutex;
/* 	pthread_t		monitor_thread;
	int             meals_done;     
    pthread_mutex_t mealsdone_mutex; */
}				t_manager;

#endif
