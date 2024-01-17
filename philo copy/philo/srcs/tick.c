/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:16:27 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/17 15:32:27 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	check_to_addtime(void *arg)
{
	t_game	*game;
	int		death;
	int		i;

	game = (t_game *)arg;
	death = 0;
	i = 0;
	while (i < game->philos.size)
	{
		if (game->philos.philo[i].state == DEAD)
		{
			death++; 
			break ;
		}
		i++;
	}
	return (death);
}

int	go_next_tick(t_col *col)
{
	int	i;

	i = 0;
	while (i < col->game->philos.size)
	{
		if (col->game->philos.philo[i].actionmade != col->game->time)
			return (0);
		i++;
	}
	col->game->time++;
	return (1);
}

void	*addtime(void *arg)
{
	t_col	*col;
	int		d;

	col = (t_col *)arg;
	d = 0;
	while (d == 0)
	{
		d = check_to_addtime(col->game);
		go_next_tick(col);
	}
	return (NULL);
}
