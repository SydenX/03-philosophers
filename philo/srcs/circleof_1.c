/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circleof_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:05:53 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/15 13:38:04 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	cof_check_death(t_col *col, int timevar, t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&col->count_mutex);
	i = 0;
	while (i < col->game->philos.size)
	{
		if (col->game->philos.philo[i].state == DEAD)
			return (pthread_mutex_unlock(&col->count_mutex), -1);
		i++;
	}
	if (philo->state == THINKING)
		return (timevar + 1);
	return (timevar);
}

void	cof_end(t_col *col, t_philo *philo)
{
	int	death;
	int	i;

	pthread_mutex_lock(&col->count_mutex);
	philo->state = DEAD;
	death = 0;
	i = 0;
	while (i < col->game->philos.size)
	{
		if (col->game->philos.philo[i].state == DEAD)
			death++;
		i++;
	}
	if (death == 1)
	{
		if (col->game->finished_eat >= col->game->philos.size)
			printf("All philos has ate at least %d times",
				col->game->eat_at_least);
		else
			printf("%d %d died\n", col->game->time, philo->id);
	}
	pthread_mutex_unlock(&col->count_mutex);
}

int	cof_check_eatatleast(t_col *col, t_philo *philo, int timeate)
{
	if (col->game->eat_at_least != -1)
	{
		if (timeate == col->game->eat_at_least && philo->finished_eat == 0)
		{
			col->game->finished_eat++;
			philo->finished_eat++;
			if (col->game->finished_eat >= col->game->philos.size)
			{
				pthread_mutex_unlock(&col->count_mutex);
				return (1);
			}
		}
	}
	return (0);
}

void	cof_setupvar(t_col *col)
{
	col->philo->start = 0;
	col->philo->timeate = 0;
	col->philo->timevar = col->game->time_to_eat;
}

void	*circle_of_life(void *arg)
{
	t_col	*col;

	col = (t_col *)arg;
	setup_eat(col, col->philo);
	while (col->philo->start < col->game->time_to_die)
	{
		if (col->philo->actionmade <= col->game->time)
		{
			col->philo->timevar = cof_check_death(col, col->philo->timevar, col->philo);
			if (col->philo->timevar == -1)
				return (NULL);
			col->philo->timeate += cof_checkto_sleep(col, col->philo);
			if (cof_check_eatatleast(col, col->philo, col->philo->timeate) == 1)
				break ;
			col->philo->actionmade = col->game->time;
			pthread_mutex_unlock(&col->count_mutex);
			usleep(1000);
		}
		usleep(10);
	}
	cof_end(col, col->philo);
	return (NULL);
}
