/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:26:03 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/18 14:55:11 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct s_fork {
	int				taken;
	int				takenBy;
	pthread_mutex_t	locker;
}	t_fork;

typedef struct s_game {
	int				size;
	pthread_mutex_t	locker;
	pthread_t		thread;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_at_least;
	int				is_over;
	long			start;
}	t_game;

typedef struct s_philo {
	int				id;
	t_fork			*fork_l;
	t_fork			*fork_r;
	pthread_mutex_t	last_ate;
	pthread_t		thread;
	int				times_ate;
	t_game			*game;
}	t_philo;

long	ft_atoi(const char *str);
int	isint(char *str);
int	error(char *str);
int	isposint(char *str);
size_t	get_current_time(void);
int	ft_usleep(size_t milliseconds);

#endif