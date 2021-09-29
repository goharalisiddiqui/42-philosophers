/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:46:19 by gohar             #+#    #+#             */
/*   Updated: 2021/09/29 20:33:46 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static char	*get_message(int type)
{
	if (type == TYPE_EAT)
		return (" is eating\n");
	else if (type == TYPE_SLEEP)
		return (" is sleeping\n");
	else if (type == TYPE_FORK)
		return (" has taken a fork\n");
	else if (type == TYPE_THINK)
		return (" is thinking\n");
	else if (type == TYPE_OVER)
		return (" must eat count reached\n");
	return (" died\n");
}

void	display_message(t_menu *menu, int type)
{
	static	int done = 0;
	long	currtime;

	pthread_mutex_lock(menu->print_mutex);
	if (!done)
	{
		get_currtime(&currtime);
		ft_putnbr_fd((currtime - *(menu->info.epoch))/1000, STDOUT_FILENO);
		write(1, " ", 1);
		ft_putnbr_fd(menu->nphil, STDOUT_FILENO);
		write(1, get_message(type), ft_strlen(get_message(type)));
		if (type != TYPE_DIE)
			pthread_mutex_unlock(menu->print_mutex);
		else
			done = 1;
	}
	else
		mysleep(INT_MAX);
}