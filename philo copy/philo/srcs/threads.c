/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:09:15 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/19 14:13:24 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	threads_init(int numphilos, t_philos *philos, t_game *game)
{
	pthread_t	mainthread;
	int			i;

	i = 0;
	pthread_mutex_init(&game->count_mutex, NULL);
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
		philos->philo[i].game = game;
		i++;
	}
	setup_philos(&philos, game);
	run(game, 0);
	pthread_mutex_destroy(&game->count_mutex);
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
		ft_usleep(1);
	}
	return (printf("%d %d died\n", start, 1), NULL);
}

void	run(t_philos *philos, int i)
{
	pthread_t		timet;

	philos->philo[0].game->time = 0;
	while (i < philos->philo[0].game->size)
	{
		pthread_create(&get_by_id(&philos, i + 1)->thread,
			NULL, &cycle, (void *)&philos);
		i++;
	}
	pthread_create(&timet, NULL, &addtime, (void *)&philos);
	start = get_current_time();
	i = 0;
	while (i < philos->size)
		pthread_join(get_by_id(&philos, ++i)->thread, NULL);
}
