/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:25:29 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/29 12:23:18 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

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

void	print_msg(t_philo *philo, char *msg)
{
	int	tick;

	tick = get_current_time() - philo->game->start;
	if (is_alive(philo))
	{
		pthread_mutex_lock(&philo->game->logger);
		printf("%d %d %s\n", tick, philo->id + 1, msg);
		pthread_mutex_unlock(&philo->game->logger);
	}
	else
		pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	t_game			game;
	t_fork			forks[200];
	t_philo			philos[200];
	int				init;

	init = init_game(argc, argv, &game);
	if (init == 1)
		return (1);
	if (init == 2)
		return (0);
	init_philos(&game, philos, forks);
	pthread_mutex_destroy(&game.locker);
	pthread_mutex_destroy(&game.logger);
	init = 0;
	while (init < game.size)
	{
		pthread_mutex_destroy(&philos[init].fork_l->locker);
		pthread_mutex_destroy(&philos[init].last_ate);
		init++;
	}
	return (0);
}
