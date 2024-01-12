/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:26:03 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/12 17:54:55 by jtollena         ###   ########.fr       */
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
	t_state 		state;
	int 			timeToDie;
	struct s_philo	*left;
	struct s_philo	*right;
	pthread_t		thread;
	int				finished_eat;
	int				actionmade;
}	t_philo;

typedef struct s_philos {
	t_philo	*philo;
	int		size;
}	t_philos;

typedef struct s_game {
	t_philos	philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_at_least;
	int			finished_eat;
	int			time;
}	t_game;

typedef struct s_col {
	t_game	*game;
	int		philoid;
	pthread_mutex_t count_mutex;
}	t_col;

int		launch(int time, void *runnable, void *arg);
int		isInt(char *str);
int		isPosInt(char *str);
int		error(char *str);
long	ft_atoi(const char *str);

#endif