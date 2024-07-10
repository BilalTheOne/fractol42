/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 00:47:21 by bel-barb          #+#    #+#             */
/*   Updated: 2024/07/10 01:32:10 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	no_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_number(char *num)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (no_digits(num) == 1)
		return (1);
	while (num[i] == ' ')
		i++;
	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num[i])
	{
		if (num[i] == '.')
		{
			if (dot == 1)
				return (1);
			dot++;
		}
		else if (num[i] < '0' || num[i] > '9')
			break ;
		i++;
	}
	while (num[i])
	{
		if (num[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	parsing(int argc, char **argv)
{
	if (((argv[1][0] != 'j' && argv[1][0] != 'm')
		&& argv[1][0] != '\0') || ft_strlen(argv[1]) > 1)
	{
		write(1, "please choose a right fractol set m/j\n", 39);
		return (1);
	}
	if (argv[1][0] == 'm' && argc > 2)
	{
		write(1, "mandelbrot set does not need more arguments\n", 45);
		return (1);
	}
	if ((argv[1][0] == 'j' && argc != 4))
	{
		write(1, "julia set values between -2 and 2 for both Im and Re\n", 54);
		return (1);
	}
	if (argv[1][0] == 'j')
	{
		if (check_number(argv[2]) == 1 || check_number(argv[3]) == 1)
		{
			write(1, "julia values between -2 and 2 for both Im and Re\n", 50);
			return (1);
		}
	}
	return (0);
}
