/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:25:29 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/11 15:35:52 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	*myfun(void *var)
{
	usleep(*(int *)(var));
	printf("I'm rested in %d\n", *(int *)var);
	return (NULL);
}

int	get_pos_by_id(t_philos *philos, int id)
{
	int i = 0;
	while (i < philos->size)
	{
		if (philos->philo[i].id == id)
			return (i);
		i++;
	}
	return (-1);
}

// int	can_eat(t_philo *philos, t_philo philo)
// {
// 	if (philo)
// }

int	main(int argc, char **argv)
{
	t_philos	philos;
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
	i = 0;
	while (i < numphilos)
	{
		philos.philo[i].id = i + 1;
		philos.philo[i].timeToDie = ft_atoi(argv[2]);
		if (i + 2 == numphilos)
			philos.philo[i].leftId = 1;
		else
			philos.philo[i].leftId = i + 2;
		if (i == 0)
			philos.philo[i].rightId = numphilos;
		else
			philos.philo[i].rightId = i;
		i++;
	}

	pthread_t threadid;
	int timeToEat = 1000000; // = 1 sec
	
	launch(timeToEat, myfun, (void *)&timeToEat);
	printf("Lezgo to work.\n");
	return (0);
}