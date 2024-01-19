/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:07:09 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/19 14:20:21 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	cycle_checkto_eat(t_philo *philo)
{
	if (can_eat(*philo) && philo->state == THINKING)
	{
		if (philo->timevar >= philo->game->time_to_eat / 4
			&& philo->game->size % 2 != 0)
		{
			philo->start = 0;
			philo->timevar = 0;
			philo->state = EATING;
			printf("%d %d has taken a fork\n", philo->game->time, philo->id);
			printf("%d %d has taken a fork\n", philo->game->time, philo->id);
			printf("%d %d is eating\n", philo->game->time, philo->id);
		}
		if (philo->game->size % 2 == 0)
		{
			philo->start = 0;
			philo->timevar = 0;
			philo->state = EATING;
			printf("%d %d has taken a fork\n", philo->game->time, philo->id);
			printf("%d %d has taken a fork\n", philo->game->time, philo->id);
			printf("%d %d is eating\n", philo->game->time, philo->id);
		}
	}
}

void	cycle_checkto_think(t_philo *philo)
{
	if (philo->state == SLEEPING)
	{
		if (philo->timevar == philo->game->time_to_sleep)
		{
			philo->state = THINKING;
			philo->timevar = 0;
			printf("%d %d is thinking\n", philo->game->time, philo->id);
		}
		philo->timevar++;
	}
}

void	cycle_checkto_sleep(t_philo *philo)
{
	cycle_checkto_eat(philo);
	if (philo->state == EATING)
	{
		if (philo->timevar == philo->game->time_to_eat)
		{
			philo->timeate++;
			philo->state = SLEEPING;
			philo->timevar = 0;
			printf("%d %d is sleeping\n", philo->game->time, philo->id);
		}
		else
			philo->timevar++;
	}
	cycle_checkto_think(philo);
	philo->start++;
}
