/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:23:19 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/27 08:52:56 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *s)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->data->print_lock);
	if (var_is(CHECKED, &philo->data->check_lock, &philo->data->working, 0))
		printf("%d %d %s\n",
			get_time(philo->data->launch_time, current_time), philo->id, s);
	pthread_mutex_unlock(&philo->data->print_lock);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->lock);
	print_status(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->lock);
	philo->ate_n_times++;
	pthread_mutex_unlock(&philo->lock);
}

static int	status(t_philo *philo, int status)
{
	if (var_is(CHECKED, &philo->data->check_lock, &philo->data->working, 0))
	{
		if (status == THINKING)
		{
			print_status(philo, "is thinking");
			usleep(((philo->data->time_to_die - (philo->data->time_to_eat \
			+ philo->data->time_to_sleep)) / 2) * 1000);
		}
		else if (status == SLEEPING)
		{
			print_status(philo, "is sleeping");
			usleep(philo->data->time_to_sleep * 1000);
		}
		else
			eat(philo);
	}
	return (0);
}

static void	take_forks(t_philo *philo)
{
	struct timeval	current_time;

	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->left_fork);
		gettimeofday(&current_time, NULL);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		gettimeofday(&current_time, NULL);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		gettimeofday(&current_time, NULL);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork);
		gettimeofday(&current_time, NULL);
		print_status(philo, "has taken a fork");
	}
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (var_is(CHECKED, &philo->data->check_lock,
			&philo->data->launch, 0) == FALSE)
		if (var_is(CHECKED, &philo->data->check_lock, &philo->data->failure, 0))
			return (0);
	pthread_mutex_lock(&philo->lock);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->lock);
	status(philo, THINKING);
	if (one_philo(philo) == TRUE)
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (var_is(CHECKED, &philo->data->check_lock, &philo->data->working, 0))
	{
		take_forks(philo);
		status(philo, EATING);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		status(philo, SLEEPING);
		status(philo, THINKING);
	}
	return (NULL);
}
