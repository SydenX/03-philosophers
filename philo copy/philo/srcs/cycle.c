/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:05:53 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/19 14:21:22 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	cycle_check_death(int timevar, t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->game->count_mutex);
	i = 0;
	while (i < philo->game->size)
	{
		if (philo->state == DEAD)
			return (pthread_mutex_unlock(&philo->game->count_mutex), -1);
		i++;
	}
	if (philo->state == THINKING)
		return (timevar + 1);
	return (timevar);
}

void	cycle_end(t_philo *philo, t_philos *philos)
{
	int	death;
	int	i;

	pthread_mutex_lock(&philo->game->count_mutex);
	philo->state = DEAD;
	death = 0;
	i = 0;
	while (i < philo->game->size)
	{
		if (philos->philo[i].state == DEAD)
			death++;
		i++;
	}
	if (death == 1)
	{
		if (philo->game->finished_eat >= philo->game->size)
			printf("All philos has ate at least %d times\n",
				philo->game->eat_at_least);
		else
			printf("%d %d died\n", philo->game->time, philo->id);
	}
	pthread_mutex_unlock(&philo->game->count_mutex);
}

int	cycle_check_eatatleast(t_philos *philos, t_philo *philo, int timeate)
{
	if (philo->game->eat_at_least != -1)
	{
		if (timeate == philo->game->eat_at_least && philo->finished_eat == 0)
		{
			philo->game->finished_eat++;
			philo->finished_eat++;
			if (philo->game->finished_eat >= philo->game->size)
			{
				pthread_mutex_unlock(&philo->game->count_mutex);
				return (1);
			}
		}
	}
	return (0);
}

void	cycle_setupvar(t_philo *philo)
{
	philo->start = 0;
	philo->timeate = 0;
	philo->timevar = philo->game->time_to_eat;
}

void	*cycle(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	cycle_setupvar(philo);
	setup_eat(philo);
	while (philo->start < philo->game->time_to_die)
	{
		if (philo->actionmade <= philo->game->time)
		{
			philo->timevar = cycle_check_death(philo->timevar, philo);
			if (philo->timevar == -1)
				return (NULL);
			cycle_checkto_sleep(philo);
			if (cycle_check_eatatleast(philo, philo->timeate) == 1)
				break ;
			philo->actionmade = philo->game->time;
			pthread_mutex_unlock(&philo->game->count_mutex);
			ft_usleep(1);
		}
		usleep(1);
	}
	cycle_end(col, philo);
	return (NULL);
}
