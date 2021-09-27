/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_argcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gohar <gohar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:32:20 by gohar             #+#    #+#             */
/*   Updated: 2021/09/26 22:36:23 by gohar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ph_argcheck(int argc, char **argv, t_philo *data)
{
	int 	ind;
	long	*temp;

	memset(data, 0, sizeof(t_philo));
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Wrong number of inputs.", STDERR_FILENO);
		return (1);
	}
	ind = 0;
	temp = (long *)data;
	while (++ind < argc)
	{
		if (*argv[ind] == '\0' || !ft_isnum(argv[ind]))
		{
			ft_putendl_fd("Non-numeric, negative or empty input found.", STDERR_FILENO);
			return (1);
		}
		if (ft_strlen(argv[ind]) > 19 || (ft_strlen(argv[ind]) == 19
			&& ft_strncmp(argv[ind], "9223372036854775807", 19) > 0))
		{
			ft_putendl_fd("Too large input found.", STDERR_FILENO);
			return (1);
		}
		*temp = ft_atol(argv[ind]);
		temp += 1;
	}
	return (0);
}