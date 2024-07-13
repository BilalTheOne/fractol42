/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:45:22 by bel-barb          #+#    #+#             */
/*   Updated: 2024/07/13 01:57:18 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	ft_tolower(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] >= 'A' && (*str)[i] <= 'Z')
			(*str)[i] = (*str)[i] + 32;
		i++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s2[i] != '\0' || s1[i] != '\0') && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int	parse_name(char	*str)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 'j')
	{
		s = 2;
		if (ft_strncmp(str + i, "julia", 5) != 0)
			return (0);
		i = i + 5;
	}
	if (str[i] == 'm')
	{
		s = 3;
		if (ft_strncmp(str + i, "mandelbrot", 10) != 0)
			return (0);
		i = i + 10;
	}
	if (check_spaces((str + i)) == 1)
		return (0);
	return (s);
}
