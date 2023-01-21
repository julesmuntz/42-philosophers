/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:23:19 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/21 19:42:44 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo id, t_stoic *data)
{
	if (data->fork_status[data->left_fork] == AVAILABLE
		&& data->fork_status[data->right_fork] == AVAILABLE)
	{
		data->fork_status[data->left_fork] = BUSY;
		data->fork_status[data->right_fork] = BUSY;
		return (TRUE);
	}
	return (FALSE);
}

int	drop_forks(t_philo id, t_stoic *data)
{
	if (data->fork_status[data->left_fork] == BUSY
		&& data->fork_status[data->right_fork] == BUSY)
	{
		data->fork_status[data->left_fork] = AVAILABLE;
		data->fork_status[data->right_fork] = AVAILABLE;
		return (TRUE);
	}
	return (FALSE);
}

void	*routine(void *ptr)
{
	int		i;
	t_stoic	*data;

	i = 1;
	data = (t_stoic *)ptr;
	while ((TRUE) || (data->philo.ate_n_times != 0))
	{
		if (data->elapsed >= (unsigned long)&data->philo.time_to_die)
		{
			printf("%lu\t%d died\n", data->elapsed, i);
			break ;
		}
		i = 1;
		while (i <= data->number_of_philosophers)
		{
			get_time(data);
			forks_pos(i, data);
			data->philo.status = THINKING;
			printf("%lu\t%d is thinking\n", data->elapsed, i);
			if (take_forks(data) == TRUE)
			{
				take_forks(data);
				pthread_mutex_lock(&data->philo.left_fork);
				get_time(data);
				printf("%lu\t%d has taken a fork\n", data->elapsed, i);
				pthread_mutex_lock(&data->philo.right_fork);
				get_time(data);
				printf("%lu\t%d has taken a fork\n", data->elapsed, i);
				pthread_mutex_lock(&data->lock);
				data->philo.status = EATING;
				printf("%lu\t%d is eating\n", data->elapsed, i);
				msleep(data->philo.time_to_eat);
				pthread_mutex_unlock(&data->lock);
				drop_forks(data);
				pthread_mutex_unlock(&data->philo.left_fork);
				pthread_mutex_unlock(&data->philo.right_fork);
			}
			i++;
		}
	}
	return (NULL);
}
