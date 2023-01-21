/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:39:35 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/21 19:38:51 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	invalid_argument(t_stoic *data, int id)
{
	if (data->stops == FALSE)
		printf("Error\n");
	if (p_strcmp(data->error, "Less than 1") == 0)
		printf("The value of Argument %d is less than 1.\n", id);
	else if (p_strcmp(data->error, "Integer overflow") == 0)
		printf("The value of Argument %d exceeds the INT_MAX.\n", id);
	else if (p_strcmp(data->error, "Not a number") == 0)
		printf("The input of Argument %d is an invalid value.\n", id);
	data->stops = TRUE;
	return ;
}

void	create_threads(t_stoic *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->lock, NULL);
	while (i != data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->philo.left_fork, NULL) != 0)
			break ;
		if (pthread_mutex_init(&data->philo.right_fork, NULL) != 0)
			break ;
		i++;
	}
	i = 0;
	while (i != data->number_of_philosophers)
	{
		if (pthread_create(&data->philos[i], NULL, &routine, data) != 0)
			break ;
		i++;
	}
	i = 0;
	while (i != data->number_of_philosophers)
	{
		if (pthread_join(data->philos[i], NULL) != 0)
			break ;
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&data->lock);
	while (i != data->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&data->philo.left_fork) != 0)
			break ;
		if (pthread_mutex_destroy(&data->philo.right_fork) != 0)
			break ;
		i++;
	}
}

int	init(t_stoic *data, int arc, char **arv)
{
	int	i;

	i = 1;
	data->stops = FALSE;
	if (arc < 5 || arc > 6)
		return (printf("Error\nInvalid number of arguments. \
It must be 4 or 5, not %d.\n", (arc - 1)), ERROR);
	while (i < arc)
	{
		if ((p_atoi(data, arv[i]) == ERROR))
			invalid_argument(data, i);
		i++;
	}
	data->error = "tbd";
	if (data->stops == TRUE)
		return (ERROR);
	data->number_of_philosophers = p_atoi(data, arv[1]);
	data->philo.time_to_die = p_atoi(data, arv[2]);
	data->philo.time_to_eat = p_atoi(data, arv[3]);
	data->philo.time_to_sleep = p_atoi(data, arv[4]);
	if (arc == 6)
		data->philo.ate_n_times = p_atoi(data, arv[5]);
	data->philos = malloc(sizeof(int) * data->number_of_philosophers);
	if (!data->philo.status)
		return (ERROR);
	return (0);
}

int	main(int arc, char **arv)
{
	int		i;
	t_stoic	data;
	t_philo	philo[data.number_of_philosophers];

	if (init(&data, arc, arv) != 0)
		return (0);
	gettimeofday(&data.start, 0);
	data.philo.status = THINKING;
	memset(philo, 0, (size_t)data.number_of_philosophers * sizeof(data.philo));
	data.fork_status = malloc(sizeof(int) * data.number_of_philosophers);
	i = 0;
	while (++i <= data.number_of_philosophers)
		data.fork_status = AVAILABLE;
	create_threads(&data);
	free(data.fork_status);
	free(data.philo.status);
	free(data.philos);
	return (0);
}
