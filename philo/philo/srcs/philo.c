/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:17:39 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/29 11:52:47 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	should_be_dead(t_philo *philos, long tick)
{
	int		last_ate_time;

	pthread_mutex_lock(&philos->last_ate);
	last_ate_time = tick - philos->last_ate_time;
	pthread_mutex_unlock(&philos->last_ate);
	if (last_ate_time >= philos->game->time_to_die)
	{
		pthread_mutex_lock(&philos->game->locker);
		philos->game->is_over = 1;
		pthread_mutex_unlock(&philos->game->locker);
		pthread_mutex_lock(&philos->game->logger);
		printf("%ld %d died\n", tick, philos->id + 1);
		pthread_mutex_unlock(&philos->game->logger);
		return (1);
	}
	return (0);
}

int	has_everyone_ate(t_philo *philos)
{
	int	i;
	int	hasate;

	hasate = 0;
	i = 0;
	while (i < philos[0].game->size)
	{
		pthread_mutex_lock(&philos[i].last_ate);
		if (philos[i].times_ate >= philos[0].game->eat_at_least)
			hasate++;
		pthread_mutex_unlock(&philos[i].last_ate);
		i++;
	}
	if (hasate == philos[0].game->size)
		return (1);
	return (0);
}

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->locker);
	if (philo->game->is_over == 1)
		return (pthread_mutex_unlock(&philo->game->locker), 0);
	pthread_mutex_unlock(&philo->game->locker);
	return (1);
}

void	everyone_ate(t_philo *philos)
{
	pthread_mutex_lock(&philos[0].game->locker);
	philos[0].game->is_over = 1;
	pthread_mutex_unlock(&philos[0].game->locker);
	pthread_exit(NULL);
}
