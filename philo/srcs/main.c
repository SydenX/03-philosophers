/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:25:29 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/12 16:16:30 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	*myfun(void *var)
{
	usleep(*(int *)(var));
	printf("I'm rested in %d\n", *(int *)var);
	return (NULL);
}

t_philo	*get_by_id(t_philos *philos, int id)
{
	int i = 0;
	while (i < philos->size)
	{
		if (philos->philo[i].id == id)
			return (&philos->philo[i]);
		i++;
	}
	return (NULL);
}

int	can_eat(t_philo philo)
{
	if (philo.state == EATING)
		return (0);
	if (philo.left->state == EATING || philo.right->state == EATING)
		return (0);
	return (1);
}

void	setup_philos(t_philos *philos)
{
	int i;

	i = 1;
	while (i <= philos->size && philos->size > 1)
	{
		if (i == philos->size)
			philos->philo[i - 1].left = get_by_id(philos, 1);
		else
			philos->philo[i - 1].left = get_by_id(philos, i + 1);

		if (i == 1)
			philos->philo[i - 1].right = get_by_id(philos, philos->size);
		else
			philos->philo[i - 1].right = get_by_id(philos, i - 1);
		i++;
	}
}

float	time_diff(struct timeval *start, struct timeval *end) {
  return (end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
}

void	*circle_of_life(void *arg)
{
	t_col 	*col;
	t_philo	*philo;
	int 	start;
	int 	timevar;

	col = (t_col *)arg;
	philo = get_by_id(&col->game->philos, col->philoid);
	start = (1 * (philo->id - 1));
	while (start < col->game->time_to_die)
	{
		if (can_eat(*philo) && philo->state == THINKING)
		{
			start = 0;
			timevar = 0;
			philo->state = EATING;
			// printf("Philo %d is now EATING\n", philo->id);
		}
		if (philo->state == EATING)
		{
			if (timevar == col->game->time_to_eat)
			{
				philo->state = SLEEPING;
				timevar = 0;
				// printf("Philo %d is now SLEEPING\n", philo->id);
			}
			else
				timevar++;
		}
		if (philo->state == SLEEPING)
		{
			if (timevar == col->game->time_to_sleep)
			{
				philo->state = THINKING;
				// printf("Philo %d is now THINKING\n", philo->id);
			}
			timevar++;
		}
		start++;
		usleep(1000);
	}
	philo->state = DEAD;
	printf("!!! Philo %d is now DEAD\n", philo->id);
	return (NULL);
}

int	exec_debug(t_game *game)
{
	int i = 0;
	int death = 0;
	printf("Now eating >>");
	while (i < game->philos.size)
	{
		if (game->philos.philo[i].state == EATING)
			printf(" %d", game->philos.philo[i].id);
		if (game->philos.philo[i].state == DEAD){
			death++; break;}
		i++;
	}
	printf("\n");
	return (death);
}

void	*debug(void *arg)
{
	t_game	*game = (t_game *)arg;
	int	d = 0;
	while (d == 0){
		d = exec_debug(game);
		usleep(100000);
	}
	return (NULL);
}

void	*run(void *arg)
{
	int		i;
	pthread_t	debugt;
	t_game 	*game;
	t_col 	col;

	game = (t_game *)arg;
	col.game = game;
	i = 0;
	while (i < game->philos.size)
	{	
		col.philoid = game->philos.philo[i].id;
		pthread_create(&get_by_id(&game->philos, i + 1)->thread, NULL, &circle_of_life, (void *)&col);
		usleep(1000);
		i++;
	}
	pthread_create(&debugt, NULL, &debug, (void *)game);
	i = 0;
	while (i < game->philos.size)
	{
		pthread_join(get_by_id(&game->philos, i + 1)->thread, NULL);
		i++;
	}

	return (NULL);
}

// USAGE ./philo <Number of philos> <time to die> <time to eat> <time to sleep> (<time must eat>)
int	main(int argc, char **argv)
{
	t_philos	philos;
	t_game		game;
	int			numphilos;
	int			i;

	if (argc < 5 || argc > 6)
		return (error("Should be 4 or 5 arguments"));
	if (!isPosInt(argv[1]) || !isPosInt(argv[2]) || !isPosInt(argv[3]) || !isPosInt(argv[4]))
		return (error("Args can only be (positive) numbers."));
	if (argc == 6)
		if (!isPosInt(argv[5]))
			return (error("Args can only be (positive) numbers."));
	numphilos = ft_atoi(argv[1]);
	philos.philo = malloc(numphilos * sizeof(t_philo));
	if (philos.philo == NULL)
		return (error("Memory allocation error."));
	philos.size = numphilos;
	game.time_to_die = ft_atoi(argv[2]);
	game.time_to_eat = ft_atoi(argv[3]);
	game.time_to_sleep = ft_atoi(argv[4]);
	i = 0;
	while (i < numphilos)
	{
		philos.philo[i].id = i + 1;
		philos.philo[i].state = THINKING;
		i++;
	}
	game.philos = philos;
	setup_philos(&game.philos);
	
	pthread_t mainthread;
	
	pthread_create(&mainthread, NULL, &run, (void *)&game);
	pthread_join(mainthread, NULL);
	return (0);
}