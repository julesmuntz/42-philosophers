/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:23:19 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/26 00:53:44 by julmuntz         ###   ########.fr       */
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

int	print_status(t_philo *philo, char *s)
{
	gettimeofday(&philo->data->current_time, 0);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%d %d %s\n", get_time(philo->data->launch_time,
			philo->data->current_time), philo->id, s);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (0);
}

static int	status(t_philo *philo, int status)
{
	if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == SLEEPING)
	{
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
	else
	{
		pthread_mutex_lock(&philo->lock);
		gettimeofday(&philo->last_meal, 0);
		pthread_mutex_unlock(&philo->lock);
		print_status(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_lock(&philo->lock);
		philo->ate_n_times++;
		pthread_mutex_unlock(&philo->lock);
	}
	return (0);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, "has taken a fork");
	}
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->data->delay = FALSE;
	pthread_mutex_lock(&philo->lock);
	gettimeofday(&philo->last_meal, 0);
	pthread_mutex_unlock(&philo->lock);
	if (philo->id % 2 == 0)
	{
		status(philo, THINKING);
		usleep(philo->data->time_to_eat * 1000);
	}
	else if (philo->id == 1 && philo->data->delay == FALSE)
	{
		philo->data->delay = TRUE;
		status(philo, THINKING);
		usleep(philo->data->time_to_eat * 2000);
	}
	take_forks(philo);
	status(philo, EATING);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	status(philo, SLEEPING);
	status(philo, THINKING);
	return (NULL);
}
