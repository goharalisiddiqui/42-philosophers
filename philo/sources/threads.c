/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 20:34:52 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/10/02 21:46:55 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	abstain(t_menu *m)
{
	long	temp;

	get_currtime(&temp);
	temp = (m->info.die * 1000) - (temp - m->lasteat)
		- (m->info.eat * 1000) - (m->info.eat * 100);
	if (temp > 0)
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
	get_currtime(&(m->lasteat));
	display_message(m, TYPE_EAT);
	mysleep(m->info.eat);
	m->eatcount++;
	pthread_mutex_unlock(m->right_fork);
	pthread_mutex_unlock(m->left_fork);
}

void	*philosopher(void *menu)
{
	t_menu	*m;

	m = (t_menu *)menu;
	while (*(m->info.epoch) == 0)
		usleep(1);
	m->lasteat = *(m->info.epoch);
	if (m->hand == right)
		mysleep(m->info.eat / 2);
	while (1)
	{
		eat(m);
		if (m->info.appetite > 0 && m->eatcount == m->info.appetite)
		{
			display_message(menu, TYPE_OVER);
			break ;
		}
		display_message(m, TYPE_SLEEP);
		mysleep(m->info.sleep);
		display_message(m, TYPE_THINK);
		if (m->info.nphils % 2 && m->hand == right)
			abstain(m);
	}
	return (NULL);
}
