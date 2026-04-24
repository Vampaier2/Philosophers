/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:44:14 by vampaier2         #+#    #+#             */
/*   Updated: 2026/04/24 13:56:17 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aux.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			m;
	size_t			i;
	unsigned char	*ptr_aux;

	m = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (m / size))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	ptr_aux = (unsigned char *)ptr;
	while (i < m)
	{
		ptr_aux[i] = 0;
		i++;
	}
	return (ptr_aux);
}
