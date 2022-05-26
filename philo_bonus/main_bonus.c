/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 20:26:05 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/06 13:54:12 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_parser(t_data *data, int argc, char **argv)
{
	data->philos = NULL;
	data->pid = NULL;
	data->break_thread = 0;
	if ((argc < 5) || (argc > 6))
		return (2);
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

int	ft_create_philos(t_data *data, int i)
{
	data->philos[i].nbr = i + 1;
	data->philos[i].state = 0;
	data->philos[i].nbr_cycle = 0;
	data->philos[i].nbr_of_eat = data->nbr_of_eat;
	data->philos[i].time_to_die = data->time_to_die;
	data->philos[i].init_time = ft_time();
	data->philos[i].tm_aft_meal = data->philos[i].init_time;
	data->philos[i].forks = data->forks;
	data->philos[i].output = data->output;
	data->philos[i].counter = data->counter;
	data->philos[i].death = data->death;
	return (0);
}

int	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (data->philos == NULL)
		return (-1);
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->nbr_of_philo);
	if (data->pid == NULL)
		return (-1);
	sem_unlink("forks");
	sem_unlink("output");
	sem_unlink("counter");
	sem_unlink("death");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->nbr_of_philo);
	data->output = sem_open("output", O_CREAT | O_EXCL, 0644, 1);
	data->counter = sem_open("counter", O_CREAT | O_EXCL, 0644, 0);
	data->death = sem_open("death", O_CREAT | O_EXCL, 0644, 0);
	while (i < data->nbr_of_philo)
	{
		ft_create_philos(data, i);
		i++;
	}
	return (0);
}

int	ft_start_philos(t_data *data)
{
	pthread_t	thread;
	int			i;

	i = 0;
	if (data->nbr_of_eat != -1)
	{
		pthread_create(&thread, NULL, ft_check_meal, data);
		pthread_detach(thread);
	}
	while (i < data->nbr_of_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			ft_philo_bonus(data, i);
		i++;
	}
	sem_wait(data->death);
	data->break_thread = 1;
	ft_finish(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			msg;

	msg = ft_parser(&data, argc, argv);
	if (msg != 0)
		return (ft_error_msg(&data, msg));
	msg = ft_init_philos(&data);
	if (msg != 0)
		return (ft_error_msg(&data, msg));
	ft_start_philos(&data);
	return (0);
}
