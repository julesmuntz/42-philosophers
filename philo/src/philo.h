/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:41:02 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/26 00:47:03 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TRUE 1
# define FALSE 0
# define ERROR -2
# define THINKING -3
# define EATING -4
# define SLEEPING -5
# define TAKING_A_FORK -6
# define DIED -7

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_stoic
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	char			*error;
	int				stops;
	int				delay;
	pthread_mutex_t	print_lock;
	struct timeval	launch_time;
	struct timeval	current_time;
}	t_stoic;

typedef struct s_philo
{
	t_stoic			*data;
	pthread_t		philosopher;
	int				id;
	int				ate_n_times;
	struct timeval	last_meal;
	pthread_mutex_t	lock;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

/////////////  R  O  U  T  I  N  E  ///////////////////////////////////////////
void	*routine(void *ptr);
int		get_time(struct timeval launch_time, struct timeval current_time);
void	check(t_philo *philo, t_stoic *data);
int		print_status(t_philo *philo, char *s);
void	join_threads(t_philo *philo, int i);

/////////////  U  T  I  L  S  /////////////////////////////////////////////////
int		p_atoi(t_stoic *data, char *s);
int		p_strcmp(char *s1, char *s2);

#endif