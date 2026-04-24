/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:42:22 by vampaier2         #+#    #+#             */
/*   Updated: 2026/04/24 14:02:03 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

int	check_valid_arg(char *arg)
{
	if (ft_str_isdigit(arg) || !ft_atoi(arg) || ft_atoi(arg) < 0)
		return (1);
	return (0);
}

int	parcing(int ac, char **av)
{
	if (ac < 4)
		return (printf("Not enough arguments!\n"), 1);
	if (ac > 6)
		return (printf("Too many arguments!\n"), 1);
	if (check_valid_arg(av[1]) == 1)
		return (printf("Error on number of Philosofers !\n"), 1);
	if (check_valid_arg(av[2]) == 1)
		return (printf("Error on time_to_die!\n"), 1);
	if (check_valid_arg(av[3]) == 1)
		return (printf("Error on time_to_eat!\n"), 1);
	if (check_valid_arg(av[4]) == 1)
		return (printf("Error on time_to_sleep!\n"), 1);
	if (ac == 6)
		if (check_valid_arg(av[5]) == 1)
			return (printf("Error on number_oftotal_meals!\n"), 1);
	return (0);
}
