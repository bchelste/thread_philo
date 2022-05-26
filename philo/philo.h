/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 11:26:39 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/03 02:00:47 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_fork
{
	int				id;
	int				lock;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_philo
{
	int				nbr;
	int				state;
	int				nbr_of_eat;
	int				nbr_cycle;
	t_fork			*l_fork;
	t_fork			*r_fork;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	long			tm_aft_meal;
	long			init_time;
	pthread_mutex_t	*output;
	pthread_mutex_t	*wait;
	int				*dead;
}					t_philo;

typedef struct s_data
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_eat;
	int				dead;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	output;
	pthread_mutex_t	wait;
}					t_data;

int					main(int argc, char **argv);
int					ft_parser(t_data *data, int argc, char **argv);
int					ft_create_philo(t_data *data);
int					ft_create_philo_thrds(t_data *data, pthread_t **ph_thread);
int					ft_atoi(const char *str);
int					ft_error_msg(t_data *data, pthread_t *ph_thread, int msg);
void				*ft_philo(void *ptr);
long				ft_time(void);
void				ft_usleep(int interval);
void				ft_output(t_philo *philo);
int					ft_free_philo(t_data *data, pthread_t *ph_thread);
void				ft_checker(t_data *data);

#endif