/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:09:15 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/15 13:50:32 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	threads_init(int numphilos, t_philos *philos, t_game *game)
{
	pthread_t	mainthread;
	int			i;

	i = 0;
	if (numphilos == 1)
	{
		pthread_create(&mainthread, NULL, &one_philo, (void *)game);
		pthread_join(mainthread, NULL);
		return (free(philos->philo), 0);
	}
	while (i < numphilos)
	{
		philos->philo[i].id = i + 1;
		philos->philo[i].state = THINKING;
		philos->philo[i].actionmade = -1;
		i++;
	}
	game->philos = *philos;
	setup_philos(&game->philos);
	run(game, 0);
	return (free(philos->philo), 0);
}

void	*one_philo(void *arg)
{
	t_game	*game;
	int		start;

	start = 0;
	game = (t_game *)arg;
	while (start < game->time_to_die)
	{
		if (start++ == 0)
			printf("%d %d has taken a fork\n", start - 1, 1);
		usleep(1000);
	}
	return (printf("%d %d died\n", start, 1), NULL);
}

void	run(t_game *game, int i)
{
	pthread_t		timet;
	t_col			col;

	col.game = game;
	col.game->time = 0;
	pthread_mutex_init(&col.count_mutex, NULL);
	while (i < game->philos.size)
	{
		pthread_mutex_lock(&col.count_mutex);
		col.philoid = i + 1;
		pthread_create(&get_by_id(&game->philos, i + 1)->thread,
			NULL, &circle_of_life, (void *)&col);
		i++;
	}
	pthread_create(&timet, NULL, &addtime, (void *)&col);
	pthread_join(get_by_id(&game->philos, 1)->thread, NULL);
	pthread_mutex_destroy(&col.count_mutex);
}
