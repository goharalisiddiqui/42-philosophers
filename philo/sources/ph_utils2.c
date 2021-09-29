/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:09:28 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/09/29 21:10:36 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_putnbr_fd(long n, int fd)
{
	long		i;

	i = 1;
	if (n == LONG_MIN)
	{
		ft_putstr_fd("-9223372036854775807", fd);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

int	ft_err(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (1);
}
