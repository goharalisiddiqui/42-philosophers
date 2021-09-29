/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:31:26 by gohar             #+#    #+#             */
/*   Updated: 2021/09/29 17:23:54 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int 	ft_err(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (1);
}

void	*philosopher(void *menu)
{
	t_menu *m;
	long	temp;
	long	i;

	i = 0;
	m = (t_menu *)menu;
	while(*(m->info.epoch) == 0)
		usleep(1);
	while(1)
	{
		get_currtime(&temp);
		temp = ((m->info.die + 5) * 1000) - (temp - m->lasteat);
		//printf("temp=%ld\n", temp);
		if (temp > 0 && m->hand == left)
		{
			//printf("%d Going to sleep for %d usec.\n", m->nphil, temp);
			myusleep(temp);
		}
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
		if (m->info.appetite > 0 && ++i == m->info.appetite)
		{
			display_message(menu, TYPE_OVER);
			break;
		}
		display_message(m, TYPE_SLEEP);
		mysleep(m->info.sleep);
		display_message(m, TYPE_THINK);
	}
	//printf("%d Going to ethernal sleep.\n", m->nphil);
	while(1)
		usleep(INT_MAX);
}


pthread_mutex_t	*make_fork(void)
{
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(fork, NULL);
	return (fork);
}


t_menu	*prepare_menu(t_philo data, int i, pthread_mutex_t *pmutex, t_list *menulist)
{
	t_menu	*menu;
	static pthread_mutex_t *right_fork = NULL;
	
	menu = malloc(sizeof(t_menu));
	menu->info = data;
	menu->nphil = i;
	if (i == 1)
		menu->right_fork = make_fork();
	else
		menu->right_fork = right_fork;
	if (i == data.nphils)
		menu->left_fork = ((t_menu *)(menulist->content))->right_fork;
	else
		menu->left_fork = make_fork();
	right_fork = menu->left_fork;
	menu->print_mutex = pmutex;
	if (i % 2 == 0)
		menu->hand = left;
	else
		menu->hand = right;
	return (menu);
}

void	destroy_menu(t_menu *menu)
{
	pthread_mutex_destroy(menu->left_fork);
	free(menu->left_fork);
	menu->left_fork = NULL;
}

void	destroy_data(t_philo data, t_list **menulist, pthread_mutex_t **pmutex)
{
	int i;
	t_list	*temp;

	i = 0;
	free(data.epoch);
	pthread_mutex_destroy(*pmutex);
	free(*pmutex);
	temp = *menulist;
	while (i < data.nphils)
	{
		destroy_menu((t_menu *)(temp->content));
		i++;
		if (i == data.nphils)
			temp->next = NULL;
		temp = temp->next;
	}
	temp = NULL;
	ft_lstclear(menulist, free);
}

int	main(int argc, char **argv)
{
	pthread_t temp;
	t_list *menulist;
	t_philo	data;
	t_menu	*menu;
	pthread_mutex_t *pmutex;
	int i;

	if (ph_argcheck(argc, argv, &data))
		return (1);
	//printf("Nphils: %ld, die: %ld, eat: %ld, sleep: %ld\n", data.nphils, data.die, data.eat, data.sleep);
	pmutex = make_fork();
	i = 0;
	menulist = NULL;
	data.epoch = malloc(sizeof(long));
	*(data.epoch) = 0;
	//printf("epoch=%ld\n", *(data.epoch));
	while(i < data.nphils)
	{
		menu = prepare_menu(data, i + 1, pmutex, menulist);
		ft_lstadd_back(&menulist, ft_lstnew(menu));
		if (pthread_create(&temp, NULL, &philosopher, (void *)menu))
		 	return (ft_err("Thread creation failed.\n"));
		if (wake_philo(menu))
			return (ft_err("Could not get time of the day.\n"));
		pthread_detach(temp);
		i++;
	}
	//return (0);
	ft_lstlast(menulist)->next = menulist; // joining the list into a circle
	get_currtime(data.epoch);
	//printf("epoch=%ld\n", *(data.epoch));
	while(1) //checking for dead philosophers
	{
		myusleep(100);
		if (!check_pulse(((t_menu *)menulist->content)->lasteat, data.die))
		{
			if (data.appetite == 0)
				display_message((t_menu *)menulist->content, TYPE_DIE);
			break ;
		}
		menulist = menulist->next;
	}
	while (data.appetite != 0) // when number of max meals is given
	{
		data.appetite = 0;
		i = 0;
		while(i < data.nphils)
		{
			if (check_pulse(((t_menu *)menulist->content)->lasteat, data.die))
				data.appetite++;
			i++;
			menulist = menulist->next;
		}
	}
	destroy_data(data, &menulist, &pmutex);
	pthread_mutex_destroy(pmutex);
	return (0);
}