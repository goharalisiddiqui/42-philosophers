/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_argcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gohar <gohar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:32:20 by gohar             #+#    #+#             */
/*   Updated: 2021/09/26 20:22:54 by gohar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ph_argcheck(int argc, char **argv)
{
	int ind;

	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Wrong number of inputs.", STDERR_FILENO);
		return (1);
	}
	ind = 1;
	while (ind++ < argc)
	{
		if (*argv[ind] == '\0' || !ft_isnum(argv[ind]))
		{
			ft_putendl_fd("Non-numeric or empty input found.", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}