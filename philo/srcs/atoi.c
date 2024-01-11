/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:21:39 by jtollena          #+#    #+#             */
/*   Updated: 2024/01/11 15:22:05 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isoverflow(unsigned long long nb, const char *str, int negation)
{
	if (nb >= 9223372036854775807 / 10 && 
		(nb > 9223372036854775807 / 10 
		|| str[0] - '0' > 9223372036854775807 % 10))
	{
		if (negation == 1)
			return (-1);
		else
			return (0);
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	int					i;
	int					negation;
	unsigned long long	nb;

	nb = 0;
	negation = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			negation = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ft_isoverflow(nb, &str[i], negation) != 1)
			return (ft_isoverflow(nb, &str[i], negation));
		nb = (nb * 10) + str[i++] - '0';
	}
	return (nb * negation);
}