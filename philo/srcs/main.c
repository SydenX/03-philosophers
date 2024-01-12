/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:25:29 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/12 18:08:36 by jtollena         ###   ########.fr       */
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

int	go_next_tick(t_game *game)
{
	int i;

	i = 0;
	while(i < game->philos.size)
	{
		if (game->philos.philo[i].actionmade != game->time)
			return (0);
		i++;
	}
	game->time++;
	return (1);
}

void	*circle_of_life(void *arg)
{
	t_col 	*col;
	t_philo	*philo;
	int 	start;
	int 	timevar;
	int		timeate;

	col = (t_col *)arg;
	philo = get_by_id(&col->game->philos, col->philoid);
	pthread_mutex_unlock(&col->count_mutex);
	philo->actionmade = -1;
	start = (1 * (philo->id - 1));
	while (start < col->game->time_to_die)
	{
		pthread_mutex_lock(&col->count_mutex);
		if (philo->actionmade != col->game->time)
		{
			int death = 0;
			int i = 0;
			while (i < col->game->philos.size)
			{
				if (col->game->philos.philo[i].state == DEAD)
					return (pthread_mutex_unlock(&col->count_mutex), NULL);
				i++;
			}
			if (can_eat(*philo) && philo->state == THINKING)
			{
				start = 0;
				timevar = 0;
				philo->state = EATING;
				printf("%d %d has taken a fork\n", col->game->time, philo->id);
				printf("%d %d has taken a fork\n", col->game->time, philo->id);
				printf("%d %d is eating\n", col->game->time, philo->id);
			}
			else if (philo->state == EATING)
			{
				timeate++;
				if (timevar == col->game->time_to_eat)
				{
					philo->state = SLEEPING;
					timevar = 0;
					printf("%d %d is sleeping\n", col->game->time, philo->id);
				}
				else
					timevar++;
			}
			else if (philo->state == SLEEPING)
			{
				if (timevar == col->game->time_to_sleep)
				{
					philo->state = THINKING;
					printf("%d %d is thinking\n", col->game->time, philo->id);
				}
				timevar++;
			}
			if (col->game->eat_at_least != -1)
			{
				if (timeate - 1 >= col->game->eat_at_least && philo->finished_eat == 0)
				{
					col->game->finished_eat++;
					philo->finished_eat++;
					if (col->game->finished_eat >= col->game->philos.size)
					{
						pthread_mutex_unlock(&col->count_mutex);
						break;
					}
				}
			}
			philo->actionmade = col->game->time;
			if (philo->actionmade == col->game->time)
				go_next_tick(col->game);
			start++;
		}
		pthread_mutex_unlock(&col->count_mutex);
		usleep(1000);
	}
	pthread_mutex_lock(&col->count_mutex);
	philo->state = DEAD;
	if (col->game->finished_eat >= col->game->philos.size)
		printf("All philos has ate at least %dms", col->game->eat_at_least);
	else
		printf("%d %d died\n", col->game->time, philo->id);
	pthread_mutex_unlock(&col->count_mutex);	
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

int	check_to_addtime(void *arg)
{
	t_game	*game = (t_game *)arg;

	int death = 0;
	int i = 0;
	while (i < game->philos.size)
	{
		if (game->philos.philo[i].state == DEAD){
			death++; break;}
		i++;
	}	
	return (death);
}

void	*addtime(void *arg)
{
	t_col	*col;

	col = (t_col *)arg;
	int	d = 0;
	while (d == 0){
		d = check_to_addtime(col->game);
		col->game->time++;
		pthread_mutex_unlock(&col->count_mutex);
		usleep(1000);
	}
	return (NULL);
}

void	*run(void *arg)
{
	int		i;
	pthread_t	debugt;
	pthread_t	timet;
	t_game 	*game;
	t_col 	col;
	pthread_mutex_t count_mutex;

	game = (t_game *)arg;
	col.game = game;
	col.game->time = 0;
	i = 0;
	col.count_mutex = count_mutex;
	pthread_mutex_init(&col.count_mutex, NULL);
	while (i < game->philos.size)
	{	
		pthread_mutex_lock(&col.count_mutex);
		col.philoid = game->philos.philo[i].id;
		pthread_create(&get_by_id(&game->philos, i + 1)->thread, NULL, &circle_of_life, (void *)&col);
		i++;
	}
	// pthread_create(&debugt, NULL, &debug, (void *)game);
	// pthread_create(&timet, NULL, &addtime, (void *)&col);
	i = 0;
	while (i < game->philos.size)
	{
		pthread_join(get_by_id(&game->philos, i + 1)->thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&col.count_mutex);
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
	if (argc == 6)
		game.eat_at_least = ft_atoi(argv[5]);
	else
		game.eat_at_least = -1;
	game.finished_eat = 0;
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