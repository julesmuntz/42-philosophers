/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:20:42 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/26 18:55:14 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	invalid_argument(t_stoic *data, int id)
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

void	init_vars(t_stoic *data)
{
	data->launch = FALSE;
	data->failure = FALSE;
	data->working = TRUE;
}

int	var_is(int function, pthread_mutex_t *lock, int *value, int new)
{
	int	temp;

	if (function == EDITED)
	{
		pthread_mutex_lock(lock);
		*value = new;
		pthread_mutex_unlock(lock);
	}
	else if (function == CHECKED)
	{
		pthread_mutex_lock(lock);
		temp = *value;
		pthread_mutex_unlock(lock);
		return (temp);
	}
	return (0);
}
