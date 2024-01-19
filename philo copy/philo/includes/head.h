/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:26:03 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/19 14:23:18 by jtollena         ###   ########.fr       */
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

size_t	start;
size_t	end;

typedef enum e_state {
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_state;

typedef struct s_game {
	int			size;
	int			over;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_at_least;
	int			finished_eat;
	int			time;
	pthread_mutex_t	count_mutex;
}	t_game;

typedef struct s_philo {
	t_game			*game;
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

//Cycle
int		cycle_check_death(int timevar, t_philo *philo);
void	cycle_end(t_philo *philo);
int		cycle_check_eatatleast(t_philos *philos, t_philo *philo, int timeate);
void	cycle_setupvar(t_philo *philo);
void	*cycle(void *arg);

//Cycle state
void	cycle_checkto_eat(t_philo *philo);
void	cycle_checkto_think(t_philo *philo);
void	cycle_checkto_sleep(t_philo *philo);

//Threads
int		threads_init(int numphilos, t_philos *philos, t_game *game);
void	*one_philo(void *arg);
void	run(t_philos *philos, int i);

//Philo
int		can_eat(t_philo philo);
void	setup_philos(t_philos *philos, t_game *game);
void	setup_eat(t_philo *philo);

//Tick
int		check_to_addtime(void *arg);
int		go_next_tick(t_col *col);
void	*addtime(void *arg);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

#endif