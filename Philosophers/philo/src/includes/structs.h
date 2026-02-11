/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:19:06 by vampaier2         #+#    #+#             */
/*   Updated: 2026/02/11 17:33:23 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../main.h"

typedef struct s_list
{
    void            *content;
    struct s_list    *next;
    struct s_list    *prev;
}    t_list;

typedef struct s_param
{
    int					n_philos;
	long				pstart_time;
    long				time_to_die;
    long				time_to_eat;
    long				time_to_sleep;
    long				number_oftotal_meals;
}    t_param;

typedef struct s_manager    t_manager;

typedef struct s_mutex_man
{
    pthread_mutex_t		*forks;
    pthread_mutex_t		*philo_lock;
    pthread_mutex_t		print_mutex;
    pthread_mutex_t		deadflag_mutex;
	t_param				param;
	bool				dead_flag;
}				t_mutex_man;


typedef struct s_philo
{
    int					id;
    int					n_meals;
    long				last_time_eat;
    pthread_t			thread;
    t_param				param;
	t_mutex_man			*mutex_man;
    pthread_mutex_t		*r_fork; // AKA right fork
    pthread_mutex_t		*l_fork; // AKA left fork
    pthread_mutex_t		last_eat_mutex; // protects last_time_eat
}    t_philo;

typedef struct s_manager
{
    t_param				param;
    t_philo				*arr_philos;
    t_mutex_man			mutex_man;
    pthread_t			monitor_thread;
}                t_manager;

#endif