/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:32:09 by bel-barb          #+#    #+#             */
/*   Updated: 2024/07/13 04:19:38 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

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

int	check_spaces(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (num[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_number(char *num)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (no_digits(num) == 1 || overflow(num) == 1)
		return (1);
	while (num[i] == ' ')
		i++;
	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num[i] && (num[i] == '.' || (num[i] >= '0' && num[i] <= '9')))
	{
		if (num[i] == '.')
		{
			if (dot == 1)
				return (1);
			dot++;
		}
		i++;
	}
	if (check_spaces((num + i)) == 1)
		return (1);
	return (0);
}

int	parsing(int argc, char **argv)
{
	int	i;

	ft_tolower(&argv[1]);
	i = parse_name(argv[1]);
	if (i == 0)
		return (write(1, "Wrong set", 10), 1);
	if (i == 3 && argc > 2)
	{
		write(1, "mandelbrot set does not need more arguments\n", 45);
		return (1);
	}
	if ((i == 2 && argc != 4))
	{
		write(1, "julia set values between -2 and 2 for both Im and Re\n", 54);
		return (1);
	}
	if (i == 2)
	{
		if (check_number(argv[2]) == 1 || check_number(argv[3]) == 1)
		{
			write(1, "julia values between -2 and 2 for both Im and Re\n", 50);
			return (1);
		}
	}
	return (i);
}
