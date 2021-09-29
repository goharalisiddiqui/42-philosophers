/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 20:57:26 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/09/29 21:04:44 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	destroy_menu(t_menu *menu)
{
	pthread_mutex_destroy(menu->left_fork);
	free(menu->left_fork);
	menu->left_fork = NULL;
}

void	destroy_data(t_philo data, t_list **menulist)
{
	int i;
	t_list	*temp;

	i = 0;
	free(data.epoch);
	temp = *menulist;
	while (i < data.nphils)
	{
		destroy_menu((t_menu *)(temp->content));
		i++;
		if (i == data.nphils)
			temp->next = NULL;
		temp = temp->next;
	}
	ft_lstclear(menulist, free);
}