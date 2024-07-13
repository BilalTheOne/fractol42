/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:26:24 by bel-barb          #+#    #+#             */
/*   Updated: 2024/07/11 02:44:44 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static char	*sp_neg(char *str, int *neg)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		*neg = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;
	long	max;
	char	*st;

	i = 0;
	sign = 1;
	result = 0;
	max = 0;
	st = sp_neg((char *)str, &sign);
	while (st[i] >= '0' && st[i] <= '9')
	{
		result = result * 10 + st[i] - '0';
		if (result < max && sign == -1)
			return (0);
		if (result < max && sign == 1)
			return (-1);
		i++;
		max = result;
	}
	return (result * sign);
}

double	ft_atof(const char *str)
{
	double	before;
	double	after;
	int		divisor;
	int		i;

	i = 0;
	divisor = 1;
	before = (double)ft_atoi(str);
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			after = after * 10 + (str[i] - '0');
			divisor *= 10;
			i++;
		}
		after = after / divisor;
	}
	if (before < 0)
		return (before - after);
	return ((after + before));
}
