/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:41:24 by gohar             #+#    #+#             */
/*   Updated: 2021/09/29 16:44:32 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	get_currtime(long *time)
{
	struct timeval temp;

	if (gettimeofday(&temp, NULL))
		return (1);
	*time = temp.tv_usec;
	*time += (temp.tv_sec * 1000000);
	return (0);
}

int	wake_philo(t_menu *menu)
{
	if (get_currtime(&(menu->lasteat)))
		return (1);
	return (0);
}

int	check_pulse(long lasteat, long die)
{
	long	temp;

	get_currtime(&temp);
	if ((temp - lasteat) > (die * 1000))
		return (0);
	return (1);
}

void myusleep(long usec)
{
	long start;
	long end;

	get_currtime(&start);
	while (1)
	{
		usleep(10);
	 	get_currtime(&end);
	 	if ((end - start) >= usec)
	 		break;
	}
}

void mysleep(long msec)
{
	myusleep(msec * 1000);
}