/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:25:29 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/11 15:19:57 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	*myfun(void *var)
{
	usleep(*(int *)(var));
	printf("I'm rested in %d\n", *(int *)var);
	return (NULL);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error("Should be 4 or 5 arguments"));
	if (!isPosInt(argv[1]) || !isPosInt(argv[2]) || !isPosInt(argv[3]) || !isPosInt(argv[4]))
		return (error("Args can only be (positive) numbers."));
	if (argc == 6)
		if (!isPosInt(argv[5]))
			return (error("Args can only be (positive) numbers."));



	pthread_t threadid;
	int timeToEat = 1000000; // = 1 sec
	
	launch(timeToEat, myfun, (void *)&timeToEat);
	printf("Lezgo to work.\n");
	return (0);
}