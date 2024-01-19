/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:19:43 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/19 14:18:43 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	can_eat(t_philo philo)
{
	if (philo.state == EATING)
		return (0);
	if (philo.left->state == EATING || philo.right->state == EATING)
		return (0);
	return (1);
}

void	setup_philos(t_philos *philos, t_game *game)
{
	int	i;

	i = 1;
	while (i <= philos->size && philos->size > 1)
	{
		philos->philo->game = game;
		if (i == philos->size)
			philos->philo[i - 1].left = get_by_id(philos, 1);
		else
			philos->philo[i - 1].left = get_by_id(philos, i + 1);
		if (i == 1)
			philos->philo[i - 1].right = get_by_id(philos, philos->size);
		else
			philos->philo[i - 1].right = get_by_id(philos, i - 1);
		i++;
	}
}

void	setup_eat(t_philo *philo)
{
	if (philo->id % 2 == 0 && can_eat(*philo))
	{
		philo->state = EATING;
		pthread_mutex_unlock(&philo->game->count_mutex);
	}
	else
		pthread_mutex_unlock(&philo->game->count_mutex);
	philo->start = 0;
	philo->timeate = 0;
}
