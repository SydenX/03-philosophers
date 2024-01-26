/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:17:39 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/26 16:31:31 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	should_be_dead(t_philo *philos, long tick)
{
	int		last_ate_time;
	int		i;

	i = 0;
	pthread_mutex_lock(&philos->last_ate);
	last_ate_time = tick - philos->last_ate_time;
	if (last_ate_time >= philos->game->time_to_die)
	{
		philos[i].is_over = 1;
		pthread_mutex_lock(&philos->game->logger);
		printf("%ld %d died\n", tick, philos->id + 1);
		pthread_mutex_unlock(&philos->game->logger);
		return (pthread_mutex_unlock(&philos->last_ate), 1);
	}
	pthread_mutex_unlock(&philos->last_ate);
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
		// pthread_mutex_lock(&philos[i].last_ate);
		if (philos[i].times_ate >= philos[0].game->eat_at_least)
			hasate++;
		// pthread_mutex_unlock(&philos[i].last_ate);
		i++;
	}
	if (hasate == philos[0].game->size)
		return (1);
	return (0);
}

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_ate);
	if (philo->is_over == 1)
		return (pthread_mutex_unlock(&philo->last_ate), 0);
	pthread_mutex_unlock(&philo->last_ate);
	return (1);
}

void	everyone_ate(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].game->size)
	{
		pthread_mutex_lock(&philos[i].last_ate);
		philos[i].is_over = 1;
		pthread_mutex_unlock(&philos[i].last_ate);
		i++;
	}
	pthread_exit(NULL);
}
