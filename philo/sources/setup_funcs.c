/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 20:59:52 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/10/02 21:54:44 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

pthread_mutex_t	*make_fork(void)
{
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(fork, NULL);
	return (fork);
}

t_menu	*prepare_menu(t_philo data, int i, pthread_mutex_t *pm, t_list *ml)
{
	t_menu					*menu;
	static pthread_mutex_t	*right_fork = NULL;

	menu = malloc(sizeof(t_menu));
	menu->info = data;
	menu->nphil = i;
	menu->eatcount = 0;
	if (i == 1)
		menu->right_fork = make_fork();
	else
		menu->right_fork = right_fork;
	if (i == data.nphils && data.nphils > 1)
		menu->left_fork = ((t_menu *)(ml->content))->right_fork;
	else if (data.nphils > 1)
		menu->left_fork = make_fork();
	else
		menu->left_fork = menu->right_fork;
	right_fork = menu->left_fork;
	menu->print_mutex = pm;
	if (i % 2 == 0)
		menu->hand = left;
	else
		menu->hand = right;
	return (menu);
}

int	make_philosophers(t_list **ml, t_philo data, pthread_mutex_t *pm)
{
	pthread_t	temp;
	t_menu		*menu;
	int			i;

	i = 0;
	while (i < data.nphils)
	{
		menu = prepare_menu(data, i + 1, pm, *ml);
		ft_lstadd_back(ml, ft_lstnew(menu));
		if (pthread_create(&temp, NULL, &philosopher, (void *)menu))
			return (ft_err("Thread creation failed.\n"));
		pthread_detach(temp);
		i++;
	}
	return (0);
}

void	monitor_philosophers(t_list *menulist, t_philo data)
{
	int	served;

	served = 0;
	while (served < data.nphils)
	{
		myusleep(50);
		if (!check_pulse(((t_menu *)menulist->content)->lasteat, data.die))
		{
			if (data.appetite == 0
				|| ((t_menu *)menulist->content)->eatcount != data.appetite)
			{
				display_message((t_menu *)menulist->content, TYPE_DIE);
				break ;
			}
			else
				served++;
		}
		menulist = menulist->next;
	}
}
