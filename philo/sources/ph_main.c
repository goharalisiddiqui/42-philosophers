/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gohar <gohar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:31:26 by gohar             #+#    #+#             */
/*   Updated: 2021/09/26 19:31:57 by gohar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int mails = 0;
pthread_mutex_t	mutex;

void	*philosopher(void *arg)
{
	int i;

	i = 0;
	while(i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pthread_t th[10];
	int i;

	
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while(i < 10)
	{
		if (pthread_create(&th[i], NULL, &philosopher, NULL))
		 	return (1);
		i++;
	}
	i = 0;
	while(i < 10)
	{
		if (pthread_join(th[i], NULL))
			return (1);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of Mails: %d\n", mails);
	return (0);
}