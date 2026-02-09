/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vampaier2 <vampaier2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:19:06 by vampaier2         #+#    #+#             */
/*   Updated: 2026/02/04 11:48:16 by vampaier2        ###   ########.fr       */
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
}	t_philo;

typedef struct s_manager
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_oftotal_meals;
	long			pstart_time;
	t_philo			*arr_philos;
	pthread_mutex_t	*forks;
}				t_manager;

#endif
