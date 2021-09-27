/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:34:48 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/09/27 16:13:11 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*elem;

	if (*lst != NULL)
	{
		elem = ft_lstlast(*lst);
		(*elem).next = new;
	}
	else
		*lst = new;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	(*new).next = *lst;
	*lst = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buff;

	while (*lst != NULL)
	{
		del((**lst).content);
		buff = (**lst).next;
		free(*lst);
		*lst = buff;
	}
	lst = NULL;
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f((*lst).content);
		lst = (*lst).next;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (elem == NULL)
		return (NULL);
	(*elem).content = content;
	(*elem).next = NULL;
	return (elem);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = (*lst).next;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL && (*lst).next != NULL)
		lst = (*lst).next;
	return (lst);
}