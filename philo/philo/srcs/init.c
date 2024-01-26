/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:15:02 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/26 16:30:30 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	join_threads(t_philo philos[200])
{
	int	i;

	i = 0;
	while (i < philos[0].game->size)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(philos[0].game->thread, NULL);
}

void	init_threads(t_game *game, t_philo philos[200])
{
	int	i;

	game->start = get_current_time();
	i = 0;
	while (i < game->size)
	{
		pthread_create(&philos[i].thread, NULL, &cycle, &philos[i]);
		i++;
	}
	pthread_create(&philos[0].game->thread,
		NULL, &timing, (void*)philos);
	join_threads(philos);
}

void	init_philos(t_game *game, t_philo philos[200], t_fork forks[200])
{
	int	i;

	i = 0;
	while (i < game->size)
	{
		philos[i].id = i;
		philos[i].fork_r = &forks[i];
		if (i == game->size - 1)
			philos[i].fork_l = &forks[0];
		else
			philos[i].fork_l = &forks[i + 1];
		philos[i].fork_r->taken = 0;
		philos[i].fork_r->taken_by = -1;
		philos[i].game = game;
		philos[i].last_ate_time = 0;
		philos[i].times_ate = 0;
		philos[i].is_over = 1;
		pthread_mutex_init(&philos[i].fork_l->locker, NULL);
		pthread_mutex_init(&philos[i].last_ate, NULL);
		i++;
	}
	init_threads(game, philos);
}

int	init_game(int argc, char *argv[], t_game *game)
{
	int	numphilos;

	if (check_args(argc, argv) == 1)
		return (1);
	numphilos = ft_atoi(argv[1]);
	if (numphilos > 200)
		return (error("Too many Philosophers (max 200)."));
	game->size = numphilos;
	game->time_to_die = ft_atoi(argv[2]);
	game->time_to_eat = ft_atoi(argv[3]);
	game->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		game->eat_at_least = ft_atoi(argv[5]);
	else
		game->eat_at_least = -1;
	if (game->eat_at_least == 0)
		return (printf("All Philosophers ate 0 times!\n"), 2);
	pthread_mutex_init(&game->locker, NULL);
	pthread_mutex_init(&game->logger, NULL);
	return (0);
}

void	*timing(void *arg)
{
	t_philo	*philos;
	long	tick;
	int		i;

	philos = (t_philo *)arg;
	while (1)
	{
		tick = get_current_time() - philos[0].game->start;
		if (philos[0].game->eat_at_least != -1)
			if (has_everyone_ate(philos) == 1)
				everyone_ate(philos);
		i = 0;
		while (i < philos[0].game->size)
		{
			if (should_be_dead(&philos[i], tick) == 1)
			{
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
			i++;
		}
		ft_usleep(1);
	}
	pthread_exit(NULL);
}
