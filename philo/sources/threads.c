/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 20:34:52 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/09/29 21:12:12 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	abstain(t_menu *m)
{
	long	temp;

	get_currtime(&temp);
	temp = ((m->info.die / 2) * 1000) - (temp - m->lasteat);
	if (temp > 0 && m->hand == right)
		myusleep(temp);
}

void	eat(t_menu *m)
{
	if (m->hand == left)
		pthread_mutex_lock(m->left_fork);
	else
		pthread_mutex_lock(m->right_fork);
	display_message(m, TYPE_FORK);
	if (m->hand == left)
		pthread_mutex_lock(m->right_fork);
	else
		pthread_mutex_lock(m->left_fork);
	display_message(m, TYPE_EAT);
	get_currtime(&(m->lasteat));
	mysleep(m->info.eat);
	pthread_mutex_unlock(m->right_fork);
	pthread_mutex_unlock(m->left_fork);
}

void	*philosopher(void *menu)
{
	t_menu	*m;
	long	i;

	i = 0;
	m = (t_menu *)menu;
	while (*(m->info.epoch) == 0)
		usleep(1);
	while (1)
	{
		abstain(m);
		eat(m);
		if (m->info.appetite > 0 && ++i == m->info.appetite)
		{
			display_message(menu, TYPE_OVER);
			break ;
		}
		display_message(m, TYPE_SLEEP);
		mysleep(m->info.sleep);
		display_message(m, TYPE_THINK);
	}
	while (1)
		usleep(INT_MAX);
}
