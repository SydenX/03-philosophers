/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:02:44 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/11 15:11:17 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	launch(int time, void *runnable, void *arg)
{
	pthread_t thread;

	pthread_create(&thread, NULL, runnable, arg);
	pthread_join(thread, NULL);
	return ((int)thread);
}

int	isPosInt(char *str)
{
	if (!isInt(str))
		return (0);
	if (*str == '-')
		return (0);
	return (1);
}

int	isInt(char *str)
{
	if (*str == '-')
		str++;
	while(*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int error(char *str)
{
	printf("\nError;\n%s\n", str);
	return (1);	
}
