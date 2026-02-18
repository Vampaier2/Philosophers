/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:25:15 by xalves            #+#    #+#             */
/*   Updated: 2026/02/18 15:55:18 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUX_H
# define AUX_H

# include "../main.h"

// aux_function.c
void	ft_usleep(t_data *data, int time);
void	msg(char *str, t_philo *philo);

int		ft_atoi(const char *nptr);

void	*ft_calloc(size_t nmemb, size_t size);

void	ft_putstr_fd(char *s, int fd);

int		odd_or_even(int id);

#endif
