/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:26:03 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/11 15:29:50 by jtollena         ###   ########.fr       */
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
	THINKING
}	t_state;

typedef struct s_philo {
	int		id;
	t_state state;
	int 	timeToDie;
	int		leftId;
	int		rightId;
}	t_philo;

typedef struct s_philos {
	t_philo	*philo;
	int		size;
}	t_philos;

int		launch(int time, void *runnable, void *arg);
int		isInt(char *str);
int		isPosInt(char *str);
int		error(char *str);
long	ft_atoi(const char *str);

#endif