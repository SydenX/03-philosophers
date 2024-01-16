/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:25:29 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/16 14:34:16 by jtollena         ###   ########.fr       */
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
// CHECKED
void	*one_philo(void *arg)
{
	t_game	*game;

	game = (t_game *)arg;
	printf("%d %d has taken a fork\n", 0, 1);
	ft_usleep(game->time_to_die);
	return (printf("%d %d died\n", game->time_to_die, 1), NULL);
}

t_philo	*get_by_id(t_game *game, int id)
{
	int	i;

	i = 0;
	while (i < game->size)
	{
		if (game->philos[i].id == id)
			return (&game->philos[i]);
		i++;
	}
	return (NULL);
}

int	is_fully_ate(t_game *game)
{
	int	i;
	int	hasate;

	hasate = 0;
	i = 0;
	if (game->eat_at_least == -1)
		return (0);
	while (i < game->size)
	{
		pthread_mutex_lock(&game->philos[i].statem);
		if (game->philos[i].timeate >= game->eat_at_least)
			hasate++;
		pthread_mutex_unlock(&game->philos[i].statem);
		i++;
	}
	if (hasate == game->size)
		return (1);
	return (0);
}

int	is_any_death(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->size)
	{
		pthread_mutex_lock(&game->philos[i].statem);
		if (game->tick - game->philos[i].start >= game->time_to_die)
			return (pthread_mutex_unlock(&game->philos[i].statem), game->philos[i].id);
		pthread_mutex_unlock(&game->philos[i].statem);
		i++;
	}
	return (0);
}

void	*timer(void *arg)
{
	t_game	*game;

	game = (t_game *)arg;
	game->tick = 0;
	while (1)
	{
		if (is_any_death(game) == 0 && is_fully_ate(game) == 0)
			game->tick++;
		else
		{
			if (is_fully_ate(game) == 0)
				printf("%d %d died.\n", game->tick, is_any_death(game));
			else
				printf("All philos ate at least %d times.\n", game->eat_at_least);
			break;
		}
		ft_usleep(1);
	}
	return (NULL);
}

void	run(t_game *game, int i)
{
	pthread_t		timert;

	// while (i < game->size)
	// {
	// 	pthread_create(&get_by_id(&game, i + 1)->thread,
	// 		NULL, &circle_of_life, (void *)&game);
	// 	i++;
	// }
	pthread_create(&timert, NULL, &timer, (void *)game);
	pthread_join(timert, NULL);
	// while (i < game->size)
	// 	pthread_mutex_destroy(game->philos[i++].fork_l);
}

int	threads_init(int numphilos, t_game *game)
{
	pthread_t	mainthread;
	t_philo		philos[200];
	int			i;

	i = 0;
	if (numphilos == 1)
	{
		pthread_create(&mainthread, NULL, &one_philo, (void *)game);
		pthread_join(mainthread, NULL);
		return (free(game->philos), 0);
	}
	while (i < numphilos)
	{
		pthread_mutex_init(&philos[i].statem, NULL);
		philos[i].id = i + 1;
		philos[i].state = THINKING;
		philos[i].fork_r = &game->forks[i];
		philos[i].timeate = 0;
		philos[i].start = 0;
		if (i == numphilos - 1)
			philos[i].fork_l = &game->forks[0];
		i++;
	}
	game->philos = philos;
	run(game, 0);
	i = 0;
	while (i < numphilos)
		pthread_mutex_destroy(&philos[i++].statem);
	// return (free(game->philos), 0);
	return 0;
}

pthread_mutex_t	*initforks(pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < 200)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

int	main(int argc, char **argv)
{
	t_game			game;
	pthread_mutex_t	forks[200];
	int				numphilos;

	if (check_args(argc, argv) == 1)
		return (1);
	numphilos = ft_atoi(argv[1]);
	if (numphilos > 200)
		return (error("Too many Philosophers (max 200)."));
	game.philos = malloc(numphilos * sizeof(t_philo));
	game.size = numphilos;
	game.time_to_die = ft_atoi(argv[2]);
	game.time_to_eat = ft_atoi(argv[3]);
	game.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		game.eat_at_least = ft_atoi(argv[5]);
	else
		game.eat_at_least = -1;
	if (game.eat_at_least == 0)
		return (free(game.philos), printf("All Philosophers ate 0 times!\n"), 0);
	game.finished_eat = 0;
	game.forks = initforks(forks);
	return (threads_init(numphilos, &game));
}
