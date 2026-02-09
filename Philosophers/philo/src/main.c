/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vampaier2 <vampaier2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:46:54 by xalves            #+#    #+#             */
/*   Updated: 2026/02/08 19:41:03 by vampaier2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

long	get_timesincestart(long pstart_time)
{
	return (ft_get_time() - pstart_time);
}

int	odd_or_even (int id)
{
	if (id % 2 == 0)// Par
		return (2);
	else //Impar
		return (1);
	return (0);
}

void	lock_forks(t_philo *philo)
{
	if (odd_or_even(philo->id) == 2)//par - right->left
	{
		pthread_mutex_lock(philo->r_fork);
		printf("%ld %d  has taken a fork\n", get_timesincestart(philo->manager->pstart_time), philo->id);
		pthread_mutex_lock(philo->l_fork);
		printf("%ld %d  has taken a fork\n", get_timesincestart(philo->manager->pstart_time), philo->id);
	}
	else//impar- left->right
	{
		pthread_mutex_lock(philo->l_fork);
		printf("%ld %d  has taken a fork\n", get_timesincestart(philo->manager->pstart_time), philo->id);
		pthread_mutex_lock(philo->r_fork);
		printf("%ld %d  has taken a fork\n", get_timesincestart(philo->manager->pstart_time), philo->id);
	}
}

void unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
//eat function
void	*eat(t_philo *philo)
{
	lock_forks(philo);
	printf("%ld %d is eating\n",
		get_timesincestart(philo->manager->pstart_time),
		philo->id);
	philo->last_time_eat = ft_get_time();
	usleep(philo->manager->time_to_eat * 1000);
	unlock_forks(philo);

	philo->n_meals++;
	if (philo->n_meals == philo->manager->number_oftotal_meals)
	{//stop thread??? i don't know
		if (pthread_join(philo->thread, NULL) != 0)
			return (NULL);
	}
	return (philo);
}

long	time_since_last_eat(t_philo *philo)
{
	return (ft_get_time() - philo->last_time_eat);
}

int	check_if_philo_died(t_philo *philo)
{
	if (time_since_last_eat(philo) >= philo->manager->time_to_die)
		return (printf("%ld %d died\n", get_timesincestart(philo->manager->pstart_time) , philo->id), 1);
	return (0);
}

int	smartsleep(t_philo *philo)
{
	long	start_time;

	start_time = ft_get_time();
	while (philo->manager->time_to_sleep > start_time)
	{
		if (check_if_philo_died(philo) == 1)
			return (1);
		usleep(500);
		start_time += 500;
	}
	return (0);
}

// pthread_mutex_lock
void *routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo.manager.n_philos)// if only 1 philo-------------
		one_philo(philo);
	else
	{
		while (1)
		{
			/* if(check_if_philo_died(philo) == 1) // check if died before
				return (NULL); */
			if (eat(philo) == NULL)
				return (NULL);
			/* if(check_if_philo_died(philo) == 1) // check if died after
				return (NULL); */
			//------------------sleeping----------------------
			printf("%ld %d is sleeping\n", get_timesincestart(philo->manager->pstart_time) , philo->id);
			if (smartsleep(philo) == 1)
				return (NULL);
			//usleep(philo->manager->time_to_sleep * 1000);
			//------------------thinking----------------------
			printf("%ld %d is thinking\n", get_timesincestart(philo->manager->pstart_time) , philo->id);
		}
	}
	return (NULL);
}

// -------------- struct funcs -----------------------
/// @brief creates new struct
/// @param content content to be given new struct
/// @return returns the created struct
int	ft_createphilo(t_philo *philo, int i, t_manager *manager)
{
	philo->id = i + 1;
	philo->manager = manager;
	philo->n_meals = 0;
	philo->last_time_eat = ft_get_time();
	//---------FORKS---------
	//Left
	if (i == 0)//if first philo
		philo->l_fork = &manager->forks[manager->n_philos - 1];
	else
		philo->l_fork = &manager->forks[i - 1];
	//Right
	philo->r_fork = &manager->forks[i];
	if (pthread_create(&philo->thread, NULL, &routine, philo) != 0)
		return (1);
	return (0);
}

int	init_arrforks(t_manager	*manager)
{
	int	i;

	i = 0;

	manager->forks = ft_calloc(sizeof(pthread_mutex_t), manager->n_philos);
	if (manager->forks == NULL)
		return (1);
	while (i < manager->n_philos)
	{
		if (pthread_mutex_init(&manager->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_philo(t_manager *manager)
{
	int		i;

	i = 0;
	while (i < manager->n_philos)
	{
		//printf("Philosopher %d was freed\n", manager->arr_philos[i].id);
		pthread_mutex_destroy(&manager->forks[i]);
		i++;
	}
	free(manager->arr_philos);
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
	new_struct->pstart_time = ft_get_time();
	new_struct->arr_philos = ft_calloc(sizeof(t_philo), new_struct->n_philos);
	if (init_arrforks(new_struct) == 1)
		return (ft_free_philo(new_struct), NULL);
	return (new_struct);
}

int	main(int argc, char *argv[])
{
	t_manager		*manager;
	int				i;
	//pthread_mutex_t	*mutex;

//-------------- Parcing -------------------
	if (parcing(argc, argv) == 1)
		return (1);	
//----------- Create Manager ---------------
	manager = ft_createmanager(argc, argv);
	if (manager == NULL)
		return (printf("\n\nError creating manager!\n"), 1);
//---------- Create Philosophers ------------
	i = 0;
	while (i < manager->n_philos)
	{
		if (ft_createphilo(&manager->arr_philos[i], i, manager) == 1)
		{
			printf("\n\nError creating philosofer[%d]!\n", i + 1);
			return (ft_free_philo(manager), 1);
		}
		i++;
	}
	i = 0;
	while (i < manager->n_philos) // join threads
	{
		if (pthread_join(manager->arr_philos[i].thread, NULL) != 0)
			return (printf("Error on pthread_join!\n"), 1);
		//printf("Thread %d has finished.\n", manager->arr_philos[i].id);
		i++;
	}
//pthread_mutex_destroy(mutex);
	ft_free_philo(manager);
	free(manager);
	return (0);
}
