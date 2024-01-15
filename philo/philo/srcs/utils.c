/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:02:44 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/15 14:23:50 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_philo	*get_by_id(t_philos *philos, int id)
{
	int	i;

	i = 0;
	while (i < philos->size)
	{
		if (philos->philo[i].id == id)
			return (&philos->philo[i]);
		i++;
	}
	return (NULL);
}

int	isposint(char *str)
{
	if (!isint(str))
		return (0);
	if (*str == '-')
		return (0);
	return (1);
}

int	isint(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	error(char *str)
{
	printf("\nError;\n%s\n", str);
	return (1);
}
