/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:05:56 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/22 10:41:15 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	take_a_fork(t_forktype fork, t_philo *philo)
{
	if (fork == LEFT)
	{
		pthread_mutex_lock(&philo->fork_l->locker);
		if (philo->fork_l->taken == 0 && philo->fork_l->taken_by != philo->id 
			&& is_alive(philo))
		{
			philo->fork_l->taken = 1;
			philo->fork_l->taken_by = philo->id;
			philo->took_l = 1;
			print_msg(philo, "has taken a fork");
		}
		pthread_mutex_unlock(&philo->fork_l->locker);
		return ;
	}
	pthread_mutex_lock(&philo->fork_r->locker);
	if (philo->fork_r->taken == 0 && philo->fork_r->taken_by != philo->id
		&& is_alive(philo))
	{
		philo->fork_r->taken = 1;
		philo->fork_r->taken_by = philo->id;
		philo->took_r = 1;
		print_msg(philo, "has taken a fork");
	}
	pthread_mutex_unlock(&philo->fork_r->locker);
}

void	release_a_fork(t_forktype fork, t_philo *philo)
{
	if (fork == RIGHT)
	{
		pthread_mutex_lock(&philo->fork_r->locker);
		philo->fork_r->taken = 0;
		philo->fork_r->taken_by = -1;
		philo->took_r = 0;
		pthread_mutex_unlock(&philo->fork_r->locker);
	}
	else
	{
		pthread_mutex_lock(&philo->fork_l->locker);
		philo->fork_l->taken = 0;
		philo->fork_l->taken_by = -1;
		philo->took_l = 0;
		pthread_mutex_unlock(&philo->fork_l->locker);
	}
}

void	cycle_sleep_think(t_philo *philo)
{
	if (is_alive(philo))
	{
		pthread_mutex_lock(&philo->last_ate);
		philo->last_ate_time = get_current_time() - philo->game->start;
		pthread_mutex_unlock(&philo->last_ate);
		if (is_alive(philo))
		{
			print_msg(philo, "is sleeping");
			ft_usleep(philo->game->time_to_sleep);
			if (is_alive(philo))
				print_msg(philo, "is thinking");
		}
	}
}

void	*cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(philo->game->time_to_eat);
	while (is_alive(philo))
	{
		take_a_fork(LEFT, philo);
		if (philo->took_l == 1 && is_alive(philo))
			take_a_fork(RIGHT, philo);
		if (philo->took_l && philo->took_r && is_alive(philo))
		{
			print_msg(philo, "is eating");
			ft_usleep(philo->game->time_to_eat);
			pthread_mutex_lock(&philo->last_ate);
			philo->times_ate++;
			pthread_mutex_unlock(&philo->last_ate);
			release_a_fork(LEFT, philo);
			release_a_fork(RIGHT, philo);
			cycle_sleep_think(philo);
		}
	}
	pthread_exit(NULL);
}
