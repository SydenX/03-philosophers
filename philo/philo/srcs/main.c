/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:25:29 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/18 15:53:43 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

// CHECKED
int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error("Should be 4 or 5 arguments"));
	if (!isposint(argv[1]))
		return (error("Args can only be (positive) numbers."));
	if (argv[1][0] == '0')
		return (error("At least one philosopher is required."));
	if (!isposint(argv[2]) || !isposint(argv[3]) || !isposint(argv[4]))
		return (error("Args can only be (positive) numbers."));
	if (argc == 6)
		if (!isposint(argv[5]))
			return (error("Args can only be (positive) numbers."));
	return (0);

}

void	*timing(void *arg)
{
	return (NULL);
}

void	*cycle(void *arg)
{
	return (NULL);
}

void	join_threads(t_philo philos[200])
{
	int	i;

	i = 0;
	while (i < philos[0].game->size)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	init_philos(t_game *game, t_philo philos[200], t_fork forks[200])
{
	int	i;

	i = 0;
	game->start = get_current_time();
	while (i < game->size)
	{
		philos[i].id = i;
		philos[i].fork_r = &forks[i];
		if (i == game->size - 1)
			philos[i].fork_l = &forks[0];
		else
			philos[i].fork_l = &forks[i + 1];
		philos[i].game = game;
		philos[i].last_ate_time = 0;
		philos[i].times_ate = 0;
		pthread_mutex_init(&philos[i].fork_r->locker, NULL);
		pthread_mutex_init(&philos[i].last_ate, NULL);
		pthread_create(i, NULL, &cycle, &philos[i]);
		i++;
	}
	pthread_create(i, NULL, &timing, &philos);
	join_threads(philos);
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
	game->is_over = 0;
	if (argc == 6)
		game->eat_at_least = ft_atoi(argv[5]);
	else
		game->eat_at_least = -1;
	if (game->eat_at_least == 0)
		return (printf("All Philosophers ate 0 times!\n"), 2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game			game;
	t_fork			forks[200];
	t_philo			philos[200];
	int				init;

	if ((init = init_game(argc, argv, &game)) == 1)
		return (1);
	if (init == 2)
		return (0);
	init_philos(&game, philos, forks);
	return (0);
}
