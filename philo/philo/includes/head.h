/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:26:03 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/19 15:27:51 by jtollena         ###   ########.fr       */
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

typedef enum e_forktype {
	LEFT,
	RIGHT
}	t_forktype;

typedef struct s_fork {
	int				taken;
	int				taken_by;
	pthread_mutex_t	locker;
}	t_fork;

typedef struct s_game {
	int				size;
	pthread_mutex_t	locker;
	pthread_mutex_t	logger;
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
	int				took_l;
	int				took_r;
	pthread_mutex_t	last_ate;
	int				last_ate_time;
	pthread_t		thread;
	int				times_ate;
	t_game			*game;
}	t_philo;

//atoi
long	ft_atoi(const char *str);

//utils
int		isint(char *str);
int		error(char *str);
int		isposint(char *str);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

//cycle
void	*cycle(void *arg);
void	cycle_sleep_think(t_philo *philo);
void	release_a_fork(t_forktype fork, t_philo *philo);
void	take_a_fork(t_forktype fork, t_philo *philo);

//init
void	join_threads(t_philo philos[200]);
void	init_threads(t_game *game, t_philo philos[200]);
void	init_philos(t_game *game, t_philo philos[200], t_fork forks[200]);
int		init_game(int argc, char *argv[], t_game *game);
void	*timing(void *arg);

//philo
int		should_be_dead(t_philo *philos, long tick);
int		has_everyone_ate(t_philo *philos);
int		is_alive(t_philo *philo);
void	everyone_ate(t_philo *philos);

//main
int		check_args(int argc, char **argv);
void	print_msg(t_philo *philo, char *msg);

#endif