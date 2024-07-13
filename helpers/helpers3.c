/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 02:25:41 by bel-barb          #+#    #+#             */
/*   Updated: 2024/07/13 04:27:27 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	free_all(t_data *data)
{
	if (data->img_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		data->img_ptr = NULL;
	}
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
}

int	overflow(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i] != ' ' && str[i])
	{
		i++;
		j++;
		if (j > 15)
			return (1);
	}
	return (0);
}
