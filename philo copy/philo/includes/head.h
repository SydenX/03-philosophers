/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:26:03 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/15 13:55:35 by jtollena         ###   ########.fr       */
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
	t_state			state;
	int				timetodie;
	struct s_philo	*left;
	struct s_philo	*right;
	pthread_t		thread;
	int				finished_eat;
	int				actionmade;
	int				start;
	int				timevar;
	int				timeate;
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
	t_game			*game;
	int				philoid;
	pthread_mutex_t	count_mutex;
}	t_col;

t_philo	*get_by_id(t_philos *philos, int id);
int		isint(char *str);
int		isposint(char *str);
int		error(char *str);
long	ft_atoi(const char *str);

//Circle of life 1
int		cof_check_death(t_col *col, int timevar, t_philo *philo);
void	cof_end(t_col *col, t_philo *philo);
int		cof_check_eatatleast(t_col *col, t_philo *philo, int timeate);
void	cof_setupvar(t_col *col, t_philo *philo);
void	*circle_of_life(void *arg);

//Circle of life 2
void	cof_checkto_eat(t_col *col, t_philo *philo);
void	cof_checkto_think(t_col *col, t_philo *philo);
void	cof_checkto_sleep(t_col *col, t_philo *philo);

//Threads
int		threads_init(int numphilos, t_philos *philos, t_game *game);
void	*one_philo(void *arg);
void	run(t_game *game, int i);

//Philo
int		can_eat(t_philo philo);
void	setup_philos(t_philos *philos);
void	setup_eat(t_col *col, t_philo *philo);

//Tick
int		check_to_addtime(void *arg);
int		go_next_tick(t_col *col);
void	*addtime(void *arg);

#endif