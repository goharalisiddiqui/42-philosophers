/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 13:22:57 by edavid            #+#    #+#             */
/*   Updated: 2021/10/02 21:45:33 by gsiddiqu         ###   ########.fr       */
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

// Macros
# define TYPE_DIE	0
# define TYPE_EAT 	1
# define TYPE_SLEEP 2
# define TYPE_FORK	3
# define TYPE_THINK	4
# define TYPE_OVER	5

// enums and unions
enum e_handedness
{
	left,
	right
};

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Strcuture Definitions

typedef struct s_philo
{
	long	nphils;	
	long	die;
	long	eat;
	long	sleep;
	long	appetite;
	long	*epoch;
}	t_philo;

typedef struct s_menu
{
	long				nphil;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*print_mutex;
	enum e_handedness	hand;
	long				lasteat;
	t_philo				info;
	int					eatcount;
}	t_menu;

// Function declarations
pthread_mutex_t	*make_fork(void);
void			*philosopher(void *menu);
t_menu			*prepare_menu(t_philo data, int i,
					pthread_mutex_t *pm, t_list *ml);
int				make_philosophers(t_list **ml, t_philo data,
					pthread_mutex_t *pm);
void			monitor_philosophers(t_list *menulist, t_philo data);
int				ph_argcheck(int argc, char **argv, t_philo *data);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
int				ft_isnum(char *str);
int				ft_strlen(char *str);
void			ft_putnbr_fd(long n, int fd);
void			myusleep(long usec);
int				check_pulse(long lasteat, long die);
int				wake_philo(t_menu *menu);
int				get_currtime(long *time);
void			mysleep(long msec);
long			ft_atol(char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
t_list			*ft_lstlast(t_list *lst);
int				ft_err(char *str);
void			display_message(t_menu *menu, int type);
void			destroy_data(t_philo data, t_list **menulist);
void			destroy_menu(t_menu *menu);

#endif
