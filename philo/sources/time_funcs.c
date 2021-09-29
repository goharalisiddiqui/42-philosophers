/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gohar <gohar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:41:24 by gohar             #+#    #+#             */
/*   Updated: 2021/09/28 22:00:24 by gohar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	get_currtime(suseconds_t *time)
{
	struct timeval temp;

	if (gettimeofday(&temp, NULL))
		return (1);
	*time = temp.tv_usec;
	return (0);
}

int	wake_philo(t_menu *menu)
{
	struct timeval temp;

	if (gettimeofday(&temp, NULL))
		return (1);
	menu->lasteat = temp.tv_usec;
	return (0);
}

int	check_pulse(suseconds_t lasteat, long die)
{
	struct timeval temp;

	if (gettimeofday(&temp, NULL))
		return (1);
	if ((temp.tv_usec - lasteat) > die)
		return (1);
	return (0);
}

void myusleep(long usec)
{
	suseconds_t start;
	suseconds_t end;

	get_currtime(&start);
	while (1)
	{
		get_currtime(&end);
		if (end - start >= usec)
			break;
	}
}