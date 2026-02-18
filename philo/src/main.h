/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:18:06 by xalves            #+#    #+#             */
/*   Updated: 2026/02/18 16:09:16 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "includes/include.h"
# include "includes/structs.h"
# include "aux/aux.h"
# include "parcing/parcing.h"

// init.c
void	init_args(t_args *args, char **av);//initialize_args
int		init_mutex2(t_mutex *mutex);//initialize_mutex2
int		init_mutex(t_data *data, t_mutex *mutex);//initialize_mutex
void	init_philo(t_philo *philo, int id, t_data *data);//initialize_philo
t_philo	*create_philos(t_data *data);

// philo.c
int		init_all(t_data *data, char **argv);//initialize_all
void	clear_all(t_philo *philos, t_mutex *mutex);

// routine.c
void	take_forks(t_philo *philo, int id);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);//philo_dream
void	philo_think(t_philo *philo);

// start_routines.c
void	*monitor_routine(void *arg);
void	*routine(void *arg);
void	start_routines(t_philo *philos);

// time.c
long	ft_get_time(void);
long	get_timesincestart(t_philo philo);

// utils_threads.c
int		checkdead_flag(t_data *data);
int		check_limite_eat(t_philo *philos);
int		check_time_to_die(t_philo *philos);

#endif