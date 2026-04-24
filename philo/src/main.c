/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:46:54 by xalves            #+#    #+#             */
/*   Updated: 2026/04/24 15:36:17 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_param	ft_createparam(int argc, char **argv)
{
	t_param	new_struct;

	new_struct.n_philos = ft_atoi(argv[1]);
	new_struct.time_to_die = ft_atoi(argv[2]);
	new_struct.time_to_eat = ft_atoi(argv[3]);
	new_struct.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		new_struct.number_oftotal_meals = ft_atoi(argv[5]);
	else
		new_struct.number_oftotal_meals = -1;
	return (new_struct);
}

t_manager	*ft_createmanager(int argc, char **argv)
{
	t_manager	*new_struct;

	new_struct = ft_calloc(1, sizeof(t_manager));
	if (!new_struct)
		return (NULL);
	new_struct->param = ft_createparam(argc, argv);
	new_struct->pstart_time = ft_get_time();
	new_struct->is_anyone_dead = false;
	new_struct->id_of_dead = -1;
	new_struct->n_philo_finished_eating = 0;
	if (pthread_mutex_init(&new_struct->print_mutex, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&new_struct->checkdead_mutex, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&new_struct->eating_mutex, NULL) != 0)
		return (NULL);
	new_struct->arr_philos = ft_calloc(sizeof(t_philo), \
new_struct->param.n_philos);
	if (init_arrforks(new_struct) == 1)
		return (ft_free_philo(new_struct), NULL);
	return (new_struct);
}

int	handle_one_philo(char **argv)
{
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi(argv[2]) * 1000);
		printf("%i 1 died\n", ft_atoi(argv[2]));
		return (1);
	}
	return (0);
}

void	routines(t_manager *manager)
{
	int	i;

	i = 0;
	while (i < manager->param.n_philos)
	{
		if (ft_createphilo(&manager->arr_philos[i], i, manager) == 1)
		{
			printf("\n\nError creating philosopher[%d]!\n", i + 1);
			ft_free_philo(manager);
			return ;
		}
		i++;
	}
	pthread_create(&manager->monitor, NULL, &monitor_routine, manager);
	pthread_join(manager->monitor, NULL);
	i = 0;
	while (i < manager->param.n_philos)
	{
		pthread_join(manager->arr_philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_manager		*manager;

	if (parcing(argc, argv) == 1)
		return (1);
	if (handle_one_philo(argv) == 1)
	{
		return (0);
	}
	manager = ft_createmanager(argc, argv);
	if (manager == NULL)
		return (printf("\n\nError creating manager!\n"), 1);
	routines(manager);
	pthread_mutex_destroy(&manager->print_mutex);
	pthread_mutex_destroy(&manager->checkdead_mutex);
	pthread_mutex_destroy(&manager->eating_mutex);
	ft_free_philo(manager);
	free(manager);
	return (0);
}
