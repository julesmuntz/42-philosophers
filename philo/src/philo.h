/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:41:02 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/07 21:11:58 by julmuntz         ###   ########.fr       */
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

typedef struct s_stoic
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	char			*error;
	int				stops;
	pthread_t		*philo;
	pthread_mutex_t	mutex;
	enum e_philo	*status;
	enum e_fork		*fork;
	int				time;
}	t_stoic;

typedef enum e_philo
{
	THINKING,
	HUNGRY,
	EATING
}	t_philo;

typedef enum e_fork
{
	BUSY,
	AVAILABLE
}	t_fork;

////////////////////////////////////////////////////////////////
/////////////  R  O  U  T  I  N  E  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void	*routine(void *ptr);

////////////////////////////////////////////////////////////////
/////////////  E S S E N T I A L S  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int		p_atoi(t_stoic *data, char *s);
int		p_strcmp(char *s1, char *s2);
void	msleep(int ms);

#endif