/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:19:06 by vampaier2         #+#    #+#             */
/*   Updated: 2026/04/23 22:30:10 by xalves           ###   ########.fr       */
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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_oftotal_meals;
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
	t_param			param;
}	t_philo;

typedef struct s_manager
{
	t_param			param;
	long			pstart_time;
	bool			is_anyone_dead;//was dead_flag
	int				id_of_dead;
	int				n_philo_finished_eating;
	t_philo			*arr_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	checkdead_mutex;//checkdead_mutex
	pthread_mutex_t	eating_mutex;
	pthread_t		monitor;
}				t_manager;

#endif
