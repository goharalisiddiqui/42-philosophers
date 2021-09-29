/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:31:26 by gohar             #+#    #+#             */
/*   Updated: 2021/09/29 21:08:50 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	main(int argc, char **argv)
{
	t_list			*menulist;
	t_philo			data;
	pthread_mutex_t	*pmutex;
	int				i;

	if (ph_argcheck(argc, argv, &data))
		return (1);
	pmutex = make_fork();
	i = 0;
	menulist = NULL;
	data.epoch = malloc(sizeof(long));
	*(data.epoch) = 0;
	if (make_philosophers(&menulist, data, pmutex))
		return (1);
	ft_lstlast(menulist)->next = menulist;
	get_currtime(data.epoch);
	monitor_philosophers(menulist, data);
	mysleep(data.die + data.eat + data.sleep);
	destroy_data(data, &menulist);
	pthread_mutex_destroy(pmutex);
	free(pmutex);
	return (0);
}
