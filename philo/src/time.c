/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:28:53 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/23 16:21:46 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_time(t_stoic *data)
{
	gettimeofday(&data->present, 0);
	data->elapsed = (data->present.tv_sec - data->start.tv_sec) * 1000;
	data->elapsed += (data->present.tv_usec - data->start.tv_usec) / 1000;
}