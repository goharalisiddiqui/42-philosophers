/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:34:48 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/09/29 21:08:19 by gsiddiqu         ###   ########.fr       */
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

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL && (*lst).next != NULL)
		lst = (*lst).next;
	return (lst);
}
