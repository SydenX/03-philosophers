/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circleof_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:07:09 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/15 13:35:31 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	cof_checkto_eat(t_col *col, t_philo *philo)
{
	if (can_eat(*philo) && philo->state == THINKING)
	{
		if (philo->timevar >= col->game->time_to_eat / 4
			&& col->game->philos.size % 2 != 0)
		{
			philo->start = 0;
			philo->timevar = 0;
			philo->state = EATING;
			printf("%d %d has taken a fork\n", col->game->time, philo->id);
			printf("%d %d has taken a fork\n", col->game->time, philo->id);
			printf("%d %d is eating\n", col->game->time, philo->id);
		}
		if (col->game->philos.size % 2 == 0)
		{
			philo->start = 0;
			philo->timevar = 0;
			philo->state = EATING;
			printf("%d %d has taken a fork\n", col->game->time, philo->id);
			printf("%d %d has taken a fork\n", col->game->time, philo->id);
			printf("%d %d is eating\n", col->game->time, philo->id);
		}
	}
}

void	cof_checkto_think(t_col *col, t_philo *philo)
{
	if (philo->state == SLEEPING)
	{
		if (philo->timevar == col->game->time_to_sleep)
		{
			philo->state = THINKING;
			philo->timevar = 0;
			printf("%d %d is thinking\n", col->game->time, philo->id);
		}
		philo->timevar++;
	}
}

int	cof_checkto_sleep(t_col *col, t_philo *philo)
{
	cof_checkto_eat(col, philo);
	philo->timeate = 0;
	if (philo->state == EATING)
	{
		if (philo->timevar == col->game->time_to_eat)
		{
			philo->timeate++;
			philo->state = SLEEPING;
			philo->timevar = 0;
			printf("%d %d is sleeping\n", col->game->time, philo->id);
		}
		else
			col->philo->timevar++;
	}
	cof_checkto_think(col, philo);
	philo->start++;
	return (philo->timeate);
}
