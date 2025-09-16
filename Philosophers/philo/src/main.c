/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:46:54 by xalves            #+#    #+#             */
/*   Updated: 2025/09/16 16:56:42 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	mutex;
int	mails = 0;

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

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * res);
}

void	*routine()
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	pthread_t	*philos;
	int			n_philos;
	int	i;
	if (argc < 4)
		return(printf("Not enough arguments!\n"), 1);
	n_philos = ft_atoi(argv[1]);
	if (n_philos <= 0)
	{
		return(printf("Not enough Philosofers!\n"), 1);
	}

	philos = ft_calloc(n_philos, sizeof(pthread_t));

	i = 0;
	while (i < n_philos)
	{
		if (pthread_create(&philos[i], NULL, &routine, NULL) != 0)
			return (printf("Error while creating philosofer\n"), 1);
		if (pthread_join(philos[i], NULL) != 0)
			return (1);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}
