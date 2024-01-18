/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:25:29 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/18 15:02:09 by jtollena         ###   ########.fr       */
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
	pthread_mutex_t	forks[200];
	t_philo			philos[200];
	int				init;

	if ((init = init_game(argc, argv, &game)) == 1)
		return (1);
	if (init = 2)
		return (0);
	return (0);
}
