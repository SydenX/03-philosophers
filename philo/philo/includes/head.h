/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:26:03 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/16 14:00:09 by jtollena         ###   ########.fr       */
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

typedef enum e_state {
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_state;

typedef struct s_philo {
	int				id;
	int				timetodie;
	t_state			state;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*statem;
	pthread_t		thread;
	int				finished_eat;
	int				actionmade;
	int				start;
	int				timevar;
	int				timeate;
}	t_philo;

typedef struct s_game {
	t_philo			*philos;
	int				size;
	pthread_mutex_t	*forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_at_least;
	int				finished_eat;
	int				tick;
}	t_game;

long	ft_atoi(const char *str);
int	isint(char *str);
int	error(char *str);
int	isposint(char *str);
size_t	get_current_time(void);
int	ft_usleep(size_t milliseconds);

#endif