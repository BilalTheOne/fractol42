/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 02:25:41 by bel-barb          #+#    #+#             */
/*   Updated: 2024/07/16 00:24:10 by bel-barb         ###   ########.fr       */
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
	while ((str[i] == ' ' || str[i] == '0') && str[i])
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

int	handle_mouse(int key, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (key == 5)
		data->zoom *= 1.1;
	else if (key == 4)
		data->zoom /= 1.1;
	fractol(data);
	return (0);
}

int	closeit(t_data *data)
{
	free_all(data);
	exit(0);
}

void	all_hooks(t_data *data)
{
	mlx_key_hook(data->win_ptr, handle_keys, data);
	mlx_hook(data->win_ptr, 17, 0, closeit, data);
	mlx_mouse_hook(data->win_ptr, handle_mouse, data);
}
