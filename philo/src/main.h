/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:32:16 by xalves            #+#    #+#             */
/*   Updated: 2026/04/23 22:31:37 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "includes/include.h"
# include "includes/structs.h"
# include "aux/aux.h"
# include "parcing/parcing.h"

// time funcs
long	ft_get_time(void);
long	get_timesincestart(long pstart_time);
long	time_since_last_eat(t_philo *philo);

// forks funcs
void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
int		init_arrforks(t_manager	*manager);

// philo funcs
int		ft_createphilo(t_philo *philo, int i, t_manager *manager);
void	ft_free_philo(t_manager *manager);

// routine funcs
void	*routine(void *arg);
void	eat(t_philo *philo);
bool	checkis_anyone_dead(t_manager *manager);
int		smartsleep(t_philo *philo);

void	msg(t_manager *manager, int id, char *action);

//	monitor.c
void	*monitor_routine(void *arg);

#endif
