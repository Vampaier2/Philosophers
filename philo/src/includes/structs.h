/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:26:08 by xalves            #+#    #+#             */
/*   Updated: 2026/02/18 15:52:51 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../main.h"

typedef struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;//write_flag
	pthread_mutex_t	deadflag_mutex;//dead_flag
	pthread_mutex_t	meal_flag;
	int				init_write_flag;
	int				init_dead_flag;
	int				init_meal_flag;
}				t_mutex;

typedef struct s_args
{
	int				count_eat;
	int				n_philos;//count_philo
	int				time_to_die;//time_die
	int				time_to_eat;//time_eat
	int				time_to_sleep;//time_sleep
}				t_args;

typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	long			last_eat_time;
	int				id;
	int				count_eat;
	int				limit_eat;
}				t_philo;

typedef struct s_data
{
	pthread_t		monitor;
	t_args			args;
	t_philo			*philos;
	t_mutex			mutex;
	long			pstart_time;//start_time;
	int				id_dead;
	int				dead_flag;
	int				philo_check;
}				t_data;

#endif