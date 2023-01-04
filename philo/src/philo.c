/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:39:35 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/04 22:22:50 by julmuntz         ###   ########.fr       */
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
	data->test_var = 0;
	pthread_mutex_init(&data->mutex, NULL);
	while (i != data->number_of_philosophers)
	{
		if (pthread_create(&data->thread[i], NULL, &routine, data) != 0)
			break ;
		i++;
	}
	i = 0;
	while (i != data->number_of_philosophers)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
			break ;
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
}

int	init(t_stoic *data, int arc, char **arv)
{
	int		i;

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
	data->time_to_die = p_atoi(data, arv[2]);
	data->time_to_eat = p_atoi(data, arv[3]);
	data->time_to_sleep = p_atoi(data, arv[4]);
	if (arc == 6)
		data->number_of_times_each_philosopher_must_eat = p_atoi(data, arv[5]);
	data->thread = malloc(sizeof(int) * data->number_of_philosophers);
	if (!data->thread)
		return (ERROR);
	return (0);
}

int	main(int arc, char **arv)
{
	t_stoic	data;

	if (init(&data, arc, arv) != 0)
		return (0);
	create_threads(&data);
	printf("%d\n", data.test_var);
	free(data.thread);
	return (0);
}
