/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:46:54 by xalves            #+#    #+#             */
/*   Updated: 2025/09/23 17:45:49 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	mutex;
int				mails = 0;

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

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	/* int		i;

	i = 0;
	while (i < 1000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	} */
	while (1)
	{
		printf("|Time| %d is thinking \n", philo->id);
		usleep(1000 * 1000); // STILL NEED SOME CHANGES
		printf("|Time| %d is eating \n", philo->id);
		usleep(philo->manager.time_to_eat * 1000);
		philo->n_meals++;
		if (philo->n_meals == philo->manager.number_oftotal_meals)
			if (pthread_join(philo->thread, NULL) != 0)
				return (printf("|Time| %d has eaten his last meal\n", philo->id), NULL);
		printf("|Time| %d is sleeping \n", philo->id);
		usleep(philo->manager.time_to_sleep * 1000);
	}
	return (NULL);
}

// -------------- struct funcs -----------------------
/// @brief creates new struct
/// @param content content to be given new struct
/// @return returns the created struct
t_philo	*ft_createphilo(int i, t_manager manager)
{
	t_philo	*new_struct;

	new_struct = malloc(sizeof(t_philo));
	if (!new_struct)
		return (NULL);
	new_struct->id = i + 1;
	new_struct->manager = manager;
	new_struct->n_meals = 0;
	if (pthread_create(&new_struct->thread, NULL, &routine, new_struct) != 0)
		return (printf("Error while creating philosofer\n"), NULL);
	return (new_struct);
}

t_manager	*ft_createmanager(int argc, char **argv)
{
	t_manager	*new_struct;

	new_struct = malloc(sizeof(t_manager));
	if (!new_struct)
		return (NULL);
	new_struct->n_philos = ft_atoi(argv[1]);
	new_struct->time_to_die = ft_atoi(argv[2]);
	new_struct->time_to_eat = ft_atoi(argv[3]);
	new_struct->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		new_struct->number_oftotal_meals = ft_atoi(argv[5]);
	else
		new_struct->number_oftotal_meals = -1;
	return (new_struct);
}

void	ft_free_philo(t_philo **stack, int n_philos)
{
	int		i;

	i = 0;
	while (i < n_philos)
	{
		printf("Philosopher %d was freed\n", stack[i]->id);
		free(stack[i]);
		i++;
	}
	free(stack);
}

int	main(int argc, char *argv[])
{
	t_philo		**arr_philos;
	t_philo		*aux_philo;
	t_manager	*manager;
	int			n_philos;
	int			i;

	// -------------- Parcing ---------------
	if (argc < 4)
		return (printf("Not enough arguments!\n"), 1);
	if (argc > 6)
		return (printf("Too many arguments!\n"), 1);
	if (ft_str_isdigit(argv[1]) || !ft_atoi(argv[1]) || ft_atoi(argv[1]) < 0)
		return (printf("Error on number of Philosofers !\n"), 1);
	if (ft_str_isdigit(argv[2]) || !ft_atoi(argv[2]) || ft_atoi(argv[2]) < 0)
		return (printf("Error on time_to_die!\n"), 1);
	if (ft_str_isdigit(argv[3]) || !ft_atoi(argv[3]) || ft_atoi(argv[3]) < 0)
		return (printf("Error on time_to_eat!\n"), 1);
	if (ft_str_isdigit(argv[4]) || !ft_atoi(argv[4]) || ft_atoi(argv[4]) < 0)
		return (printf("Error on time_to_sleep!\n"), 1);
	if (argc == 6)
		if (ft_str_isdigit(argv[5]) || !ft_atoi(argv[5]) || ft_atoi(argv[5]) < 0)
			return (printf("Error on number_oftotal_meals!\n"), 1);
	// -------------------------------------
	// ---------- Create Manager -----------
	manager = ft_createmanager(argc, argv);
	// ---------- Create Philosophers ------------
	n_philos = ft_atoi(argv[1]);
	arr_philos = ft_calloc(n_philos, sizeof(t_philo *));
	i = 0;
	while (i < n_philos)
	{
		aux_philo = ft_createphilo(i, *manager);
		if (!aux_philo)
			return (printf("Error on philosofer creation!\n"), 1);
		arr_philos[i] = aux_philo;
		//printf("Thread %d has started.\n", arr_philos[i]->id);
		i++;
	}
	i = 0;
	while (i < n_philos)
	{
		if (pthread_join(arr_philos[i]->thread, NULL) != 0)
			return (printf("Error on pthread_join!\n"), 1);
		printf("Thread %d has finished.\n", arr_philos[i]->id);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	//printf("Number of mails: %d\n", mails);
	ft_free_philo(arr_philos, n_philos);
	free(manager);
	return (0);
}
