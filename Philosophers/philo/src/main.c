/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:46:54 by xalves            #+#    #+#             */
/*   Updated: 2026/02/10 15:35:22 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_param ft_createparam(int argc, char **argv)
{
	t_param new_struct;

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
	new_struct->dead_flag = 0;
	if (pthread_mutex_init(&new_struct->print_mutex, NULL) != 0)
			return (NULL);
	if (pthread_mutex_init(&new_struct->deadflag_mutex, NULL) != 0)
			return (NULL);
	new_struct->arr_philos = ft_calloc(sizeof(t_philo), new_struct->param.n_philos);
	if (init_arrforks(new_struct) == 1)
		return (ft_free_philo(new_struct), NULL);
	return (new_struct);
}

void *monitor(void *arg)
{
    t_manager *manager = (t_manager *)arg;
    int i;

    while (1)
    {
        i = 0;
        while (i < manager->param.n_philos)
        {
            if (time_since_last_eat(&manager->arr_philos[i]) >= manager->param.time_to_die)
            {
                msg(manager, manager->arr_philos[i].id, "died");
                pthread_mutex_lock(&manager->deadflag_mutex);
                manager->dead_flag = 1;
                pthread_mutex_unlock(&manager->deadflag_mutex);
                return (NULL);
            }
            i++;
        }
        if (checkdead_flag(manager) == 1)
            return (NULL);
        usleep(500);
    }
    return (NULL);
}

int	main(int argc, char *argv[])
{
	t_manager		*manager;
	int				i;

//-------------- Parcing -------------------
	if (parcing(argc, argv) == 1)
		return (1);	
//----------- Create Manager ---------------
	manager = ft_createmanager(argc, argv);
	if (manager == NULL)
		return (printf("\n\nError creating manager!\n"), 1);

 	if (manager->param.n_philos == 1)
    {
        printf("0 1 has taken a fork\n");
        usleep(manager->param.time_to_die * 1000);
        printf("%ld 1 died\n", manager->param.time_to_die);
        return (1);
    }
	//---------- Create Philosophers ------------
	i = 0;
	while (i < manager->param.n_philos)
	{
		if (ft_createphilo(&manager->arr_philos[i], i, manager) == 1)
		{
			printf("\n\nError creating philosofer[%d]!\n", i + 1);
			return (ft_free_philo(manager), 1);
		}
		i++;
	}
	//pthread_create(&manager->monitor_thread, NULL, &monitor, manager);
	

	i = 0;
	while (i < manager->param.n_philos) // join threads
	{
		if (pthread_join(manager->arr_philos[i].thread, NULL) != 0)
			return (printf("Error on pthread_join!\n"), 1);
		//printf("Thread %d has finished.\n", manager->arr_philos[i].id);
		i++;
	}
	//pthread_join(manager->monitor_thread, NULL);
	//pthread_mutex_destroy(mutex);
	ft_free_philo(manager);
	free(manager);
	return (0);
}
