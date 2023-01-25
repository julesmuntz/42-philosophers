/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:23:19 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/25 17:29:34 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(struct timeval launch_time, struct timeval current_time)
{
	if (launch_time.tv_sec == current_time.tv_sec)
		return ((current_time.tv_usec - launch_time.tv_usec) / 1000);
	return ((((current_time.tv_sec - launch_time.tv_sec - 1) * 1000000)
			+ current_time.tv_usec + 999999 - launch_time.tv_usec) / 1000);
}

static int	print_status(t_philo *philo, int status)
{
	gettimeofday(&philo->data->current_time, 0);
	if (status == THINKING)
	{
		pthread_mutex_lock(&philo->data->lock);
		printf("%d %d %s\n", get_time(philo->data->launch_time,
				philo->data->current_time), philo->id, "is thinking");
		pthread_mutex_unlock(&philo->data->lock);
		return (0);
	}
	else if (status == TAKING_A_FORK)
	{
		pthread_mutex_lock(&philo->data->lock);
		printf("%d %d %s\n", get_time(philo->data->launch_time,
				philo->data->current_time), philo->id, "has taken a fork");
		pthread_mutex_unlock(&philo->data->lock);
		return (0);
	}
	else if (status == EATING)
	{
		pthread_mutex_lock(&philo->data->lock);
		gettimeofday(&philo->last_meal, 0);
		printf("%d %d %s\n", get_time(philo->data->launch_time,
				philo->data->current_time), philo->id, "is eating");
		philo->ate_n_times++;
		pthread_mutex_unlock(&philo->data->lock);
		return (0);
	}
	else if (status == SLEEPING)
	{
		pthread_mutex_lock(&philo->data->lock);
		printf("%d %d %s\n", get_time(philo->data->launch_time,
				philo->data->current_time), philo->id, "is sleeping");
		pthread_mutex_unlock(&philo->data->lock);
		return (0);
	}
	return (0);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, TAKING_A_FORK);
		pthread_mutex_lock(&philo->right_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, TAKING_A_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, TAKING_A_FORK);
		pthread_mutex_lock(philo->left_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, TAKING_A_FORK);
	}
}

void	*routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	gettimeofday(&philo->last_meal, 0);
	if (philo->id % 2 == 0)
	{
		print_status(philo, THINKING);
		usleep(1000);
	}
	take_forks(philo);
	print_status(philo, EATING);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	print_status(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
	print_status(philo, THINKING);
	return (NULL);
}
