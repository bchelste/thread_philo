/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 20:25:46 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/06 13:58:19 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_philo
{
	int		nbr;
	int		state;
	int		nbr_of_eat;
	long	tm_aft_meal;
	long	init_time;
	int		nbr_cycle;
	int		time_to_die;
	sem_t	*forks;
	sem_t	*output;
	sem_t	*counter;
	sem_t	*death;
}			t_philo;

typedef struct s_data
{	
	int		break_thread;
	int		nbr_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_of_eat;
	t_philo	*philos;
	sem_t	*forks;
	sem_t	*output;
	sem_t	*death;
	sem_t	*counter;
	pid_t	*pid;
}			t_data;

int			main(int argc, char **argv);
int			ft_parser(t_data *data, int argc, char **argv);
int			ft_create_philos(t_data *data, int i);
int			ft_init_philos(t_data *data);
int			ft_start_philos(t_data *data);
void		ft_philo_bonus(t_data *data, int i);
void		*ft_check_meal(void *ptr);
int			ft_atoi(const char *str);
long		ft_time(void);
void		ft_usleep(int interval);
void		ft_output(t_philo *philo);
int			ft_error_msg(t_data *data, int msg);
int			ft_finish(t_data *data);

#endif