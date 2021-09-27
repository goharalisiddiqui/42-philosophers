/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gohar <gohar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 13:22:57 by edavid            #+#    #+#             */
/*   Updated: 2021/09/26 22:08:56 by gohar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>


// enums and unions
enum e_handedness
{
	left,
	right
};


// Strcuture Definitions

typedef struct s_philo
{
	long	nphils;		
	long	die;
	long	eat;
	long	sleep;
	long	appetite;
}	t_philo;

typedef struct s_menu
{
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*print_mutex;
	enum e_handedness	hand;
	t_philo				info;
}	t_menu;

// Function declarations

// ph_argcheck.c
int		ph_argcheck(int argc, char **argv, t_philo *data);

// ph_utils1.c
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_isnum(char *str);
int		ft_strlen(char *str);

// ft_atoil.c
long	ft_atol(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
