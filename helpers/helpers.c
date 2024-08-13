/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:51:48 by bel-barb          #+#    #+#             */
/*   Updated: 2024/07/16 00:01:33 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	handle_keys(int key, t_data *data)
{
	if (key == 53)
	{
		free_all(data);
		exit(0);
	}
	else if (key == 69)
		data->zoom *= 1.1;
	else if (key == 78)
		data->zoom /= 1.1;
	else if (key == 123)
		data->offset_x -= 0.1 / data->zoom;
	else if (key == 124)
		data->offset_x += 0.1 / data->zoom;
	else if (key == 125)
		data->offset_y += 0.1 / data->zoom;
	else if (key == 126)
		data->offset_y -= 0.1 / data->zoom;
	else if (key == 49)
		data->theme = (data->theme + 1) % 3;
	else if (key == 34)
		data->iterations += 1;
	fractol(data);
	return (0);
}

int	get_color(int iteration, int theme)
{
	int	r;
	int	g;
	int	b;

	if (iteration == -1)
		return (0);
	if (theme == 0)
	{
		r = (iteration * 18) % 255;
		g = (iteration * 11) % 255;
		b = (iteration * 1) % 255;
	}
	if (theme == 1)
	{
		r = (iteration * 1) % 255;
		g = (iteration * 7) % 255;
		b = (iteration * 17) % 255;
	}
	if (theme == 2)
	{
		r = (iteration * 9) % 255;
		g = (iteration * 15) % 255;
		b = (iteration * 8) % 255;
	}
	return (r << 16 | g << 8 | b);
}

t_complex	pixel_to_complex(int x, int y, t_data *data)
{
	t_complex	c;
	double		min_re;
	double		max_re;
	double		min_im;
	double		max_im;

	min_re = -2.0;
	max_re = 1.0;
	min_im = -1.5;
	max_im = 1.5 * HEIGHT / WIDTH;
	min_re = min_re / data->zoom + data->offset_x;
	max_re = max_re / data->zoom + data->offset_x;
	min_im = min_im / data->zoom + data->offset_y;
	max_im = max_im / data->zoom + data->offset_y;
	c.re = min_re + x * (max_re - min_re) / (double)(WIDTH - 1);
	c.im = min_im + y * (max_im - min_im) / (double)(HEIGHT - 1);
	return (c);
}

void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	int	pixel;

	pixel = (y * data->size_line) + (x * (data->bpp) / 8);
	data->img_data[pixel + 0] = color;
	data->img_data[pixel + 1] = color >> 8;
	data->img_data[pixel + 2] = color >> 16;
}
