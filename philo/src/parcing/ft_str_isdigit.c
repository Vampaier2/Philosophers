/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vampaier2 <vampaier2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:33:36 by vampaier2         #+#    #+#             */
/*   Updated: 2026/01/26 12:35:49 by vampaier2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

/// @brief checks if the string there are only digits(and +-)
/// @param str string to check
/// @return 0 if error, 1 of not
int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
