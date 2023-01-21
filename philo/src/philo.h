/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:41:02 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/21 19:38:54 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TRUE 1
# define FALSE 0
# define ERROR -2

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				ate_n_times;

	enum e_status	status;

	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
}	t_philo;

typedef struct s_stoic
{
	int				number_of_philosophers;

	char			*error;
	int				stops;

	pthread_mutex_t	lock;
	pthread_t		*philos;
	enum e_fork		*fork_status;

	struct timeval	start;
	struct timeval	present;
	unsigned long	elapsed;
	struct s_philo	philo;
}	t_stoic;

typedef enum e_status
{
	THINKING,
	HUNGRY,
	EATING
}	t_status;

typedef enum e_fork
{
	BUSY,
	AVAILABLE
}	t_fork;

////////////////////////////////////////////////////////////////
/////////////  R  O  U  T  I  N  E  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void	*routine(void *ptr);
void	forks_pos(int philo_id, t_stoic *data);
void	get_time(t_stoic *data);

////////////////////////////////////////////////////////////////
/////////////  E S S E N T I A L S  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int		p_atoi(t_stoic *data, char *s);
int		p_strcmp(char *s1, char *s2);
void	msleep(int ms);

#endif