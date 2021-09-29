/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:46:01 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/09/29 21:07:59 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((*(s1 + i) || *(s2 + i)) && i < n)
	{
		if ((unsigned char)*(s1 + i) > (unsigned char)*(s2 + i))
			return (1);
		else if ((unsigned char)*(s1 + i) < (unsigned char)*(s2 + i))
			return (-1);
		i++;
	}
	return (0);
}

static long	ft_atol_digits(char *str)
{
	long	digits;

	digits = 0;
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		digits *= 10;
		digits += *str - '0';
		str++;
	}
	return (digits);
}

long	ft_atol(char *str)
{
	long	sign;
	long	digits;

	sign = 1;
	digits = 0;
	while (((*str >= 9 && *str <= 13) || *str == ' ') && *str != '\0')
		str++;
	if ((*str == '-' || *str == '+') && *str != '\0')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if ((sign == -1) && (ft_strncmp(str, "9223372036854775808", 20) == 0))
		return (-9223372036854775807 - 1);
	digits = ft_atol_digits(str);
	if (digits < 0)
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return (digits * sign);
}
