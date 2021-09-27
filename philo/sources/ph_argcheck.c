/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_argcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:32:20 by gohar             #+#    #+#             */
/*   Updated: 2021/09/27 15:41:17 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ph_argcheck(int argc, char **argv, t_philo *data)
{
	int 	ind;
	long	*temp;

	memset(data, 0, sizeof(t_philo));
	if (argc < 5 || argc > 6)
		return (ft_err("Wrong number of inputs.\n"));
	ind = 0;
	temp = (long *)data;
	while (++ind < argc)
	{
		if (*argv[ind] == '\0' || !ft_isnum(argv[ind]))
			return (ft_err("Non-numeric, negative or empty input found.\n"));
		if (ft_strlen(argv[ind]) > 19 || (ft_strlen(argv[ind]) == 19
			&& ft_strncmp(argv[ind], "9223372036854775807", 19) > 0))
			return (ft_err("Too large input found.\n"));
		*temp = ft_atol(argv[ind]);
		temp += 1;
	}
	return (0);
}