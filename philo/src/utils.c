/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:20:42 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/23 16:48:30 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_atoi(t_stoic *data, char *s)
{
	int		i;
	long	res;
	int		minus;

	i = 0;
	res = 0;
	minus = 0;
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		i++;
	if (s[i] == '-')
		minus = TRUE;
	while (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - 48;
		if ((unsigned long)res > INT_MAX)
			return (data->error = "Integer overflow", ERROR);
		i++;
	}
	if (s[i] != 0)
		return (data->error = "Not a number", ERROR);
	if (res == 0 || minus == TRUE)
		return (data->error = "Less than 1", ERROR);
	return (res);
}

int	p_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	print_status(t_philo *philo, int status)
{
	gettimeofday(&philo->data->present, 0);
	philo->data->elapsed = (philo->data->present.tv_sec - philo->data->start.tv_sec) * 1000;
	philo->data->elapsed += (philo->data->present.tv_usec - philo->data->start.tv_usec) / 1000;
	if (status == THINKING)
	{
		// pthread_mutex_lock(&philo->data->lock);
		printf("%lld\t%d\t%s.\n", philo->data->elapsed, philo->id, "is thinking");
		// pthread_mutex_unlock(&philo->data->lock);
	}
	else if (status == EATING)
	{
		// pthread_mutex_lock(&philo->data->lock);
		printf("%lld\t%d\t%s.\n", philo->data->elapsed, philo->id, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		// pthread_mutex_unlock(&philo->data->lock);
	}
	else if (status == SLEEPING)
	{
		// pthread_mutex_lock(&philo->data->lock);
		printf("%lld\t%d\t%s.\n", philo->data->elapsed, philo->id, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		// pthread_mutex_unlock(&philo->data->lock);
	}
}