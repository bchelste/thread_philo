/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 11:24:25 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/05 14:34:49 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parser(t_data *data, int argc, char **argv)
{
	if ((argc < 5) || (argc > 6))
		return (2);
	data->forks = NULL;
	data->philos = NULL;
	data->nbr_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if ((data->nbr_of_philo < 1) || (data->time_to_die < 1)
		|| (data->time_to_eat < 1) || (data->time_to_sleep < 1))
		return (1);
	if (argc == 6)
	{
		data->nbr_of_eat = ft_atoi(argv[5]);
		if (data->nbr_of_eat < 1)
			return (1);
	}
	else if (argc == 5)
		data->nbr_of_eat = -1;
	return (0);
}

int	ft_create_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->nbr_of_philo);
	if (data->forks == NULL)
		return (-1);
	pthread_mutex_init(&data->output, NULL);
	pthread_mutex_init(&data->wait, NULL);
	while (i < data->nbr_of_philo)
	{
		data->forks[i].id = i;
		data->forks[i].lock = 0;
		pthread_mutex_init(&data->forks[i].fork, NULL);
		i++;
	}
	return (0);
}

int	ft_create_philo(t_data *data)
{
	int	i;

	i = 0;
	data->dead = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (data->philos == NULL)
		return (-1);
	while (i < data->nbr_of_philo)
	{
		data->philos[i].nbr = i + 1;
		data->philos[i].state = 0;
		data->philos[i].nbr_of_eat = data->nbr_of_eat;
		data->philos[i].nbr_cycle = 0;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->nbr_of_philo];
		data->philos[i].output = &data->output;
		data->philos[i].wait = &data->wait;
		data->philos[i].dead = &data->dead;
		i++;
	}
	return (0);
}

int	ft_create_philo_threads(t_data *data, pthread_t **ph_thread)
{
	int	i;

	i = 0;
	*ph_thread = (pthread_t *)malloc(sizeof(pthread_t) * data->nbr_of_philo);
	if ((*ph_thread) == NULL)
		return (-1);
	while (i < data->nbr_of_philo)
	{
		pthread_create(&(*ph_thread)[i], NULL, ft_philo, &data->philos[i]);
		pthread_detach((*ph_thread)[i]);
		data->philos[i].init_time = ft_time();
		data->philos[i].tm_aft_meal = data->philos[i].init_time;
		i = i + 2;
	}
	i = 1;
	while (i < data->nbr_of_philo)
	{
		pthread_create(&(*ph_thread)[i], NULL, ft_philo, &data->philos[i]);
		pthread_detach((*ph_thread)[i]);
		data->philos[i].init_time = ft_time();
		data->philos[i].tm_aft_meal = data->philos[i].init_time;
		i = i + 2;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*ph_thread;
	int			msg;

	ph_thread = NULL;
	msg = ft_parser(&data, argc, argv);
	if (msg != 0)
		return (ft_error_msg(&data, ph_thread, msg));
	msg = ft_create_mutex(&data);
	if (msg != 0)
		return (ft_error_msg(&data, ph_thread, msg));
	msg = ft_create_philo(&data);
	if (msg != 0)
		return (ft_error_msg(&data, ph_thread, msg));
	msg = ft_create_philo_threads(&data, &ph_thread);
	if (msg != 0)
		return (ft_error_msg(&data, ph_thread, msg));
	ft_checker(&data);
	ft_free_philo(&data, ph_thread);
	return (0);
}
