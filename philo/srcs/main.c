/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:25:29 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/15 13:17:29 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error("Should be 4 or 5 arguments"));
	if (!isposint(argv[1]) || !isposint(argv[2])
		|| !isposint(argv[3]) || !isposint(argv[4]))
		return (error("Args can only be (positive) numbers."));
	if (argc == 6)
		if (!isposint(argv[5]))
			return (error("Args can only be (positive) numbers."));
	return (1);
}

int	main(int argc, char **argv)
{
	t_philos	philos;
	t_game		game;
	int			numphilos;

	if (check_args(argc, argv) == 0)
		return (0);
	numphilos = ft_atoi(argv[1]);
	philos.philo = malloc(numphilos * sizeof(t_philo));
	if (philos.philo == NULL)
		return (error("Memory allocation error."));
	philos.size = numphilos;
	game.time_to_die = ft_atoi(argv[2]);
	game.time_to_eat = ft_atoi(argv[3]);
	game.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		game.eat_at_least = ft_atoi(argv[5]);
	else
		game.eat_at_least = -1;
	game.finished_eat = 0;
	return (threads_init(numphilos, &philos, &game));
}
