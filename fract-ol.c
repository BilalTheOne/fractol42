/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 21:50:58 by bel-barb          #+#    #+#             */
/*   Updated: 2024/07/16 00:17:56 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia_iterations(t_complex z, int max_iterations, t_data *data)
{
	int		iterations;
	double	z_re;
	double	z_im;

	iterations = 0;
	while (iterations < max_iterations)
	{
		z_re = z.re * z.re - z.im * z.im + data->julia_re;
		z_im = 2.0 * z.re * z.im + data->julia_im;
		if ((z_re * z_re + z_im * z_im) > 4.0)
			break ;
		z.re = z_re;
		z.im = z_im;
		iterations++;
	}
	if (iterations == max_iterations)
		return (-1);
	return (iterations);
}

int	mandelbrot_iterations(t_complex c, int max_iterations)
{
	t_complex	z;
	int			iterations;
	double		z_re;
	double		z_im;

	iterations = 0;
	z.im = 0.0;
	z.re = 0.0;
	while (iterations < max_iterations)
	{
		z_re = z.re * z.re - z.im * z.im + c.re;
		z_im = 2.0 * z.re * z.im + c.im;
		if ((z_re * z_re + z_im * z_im) > 4.0)
			break ;
		z.re = z_re;
		z.im = z_im;
		iterations++;
	}
	if (iterations == max_iterations)
		return (-1);
	return (iterations);
}

void	fractol(t_data *data)
{
	int			x;
	int			y;
	t_complex	c;
	int			iterations;
	int			color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			c = pixel_to_complex(x, y, data);
			if (data->set == 'm')
				iterations = mandelbrot_iterations(c, data->iterations);
			else if (data->set == 'j')
				iterations = julia_iterations(c, data->iterations, data);
			color = get_color(iterations, data->theme);
			put_pixel_to_image(data, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}

int	window_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "FRACTOL");
	if (data->win_ptr == NULL)
		return (1);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (data->img_ptr == NULL)
		return (1);
	data->img_data = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->size_line, &data->endian);
	if (data->img_data == NULL)
		return (1);
	data->zoom = 1.0;
	data->offset_x = 0.0;
	data->offset_y = 0.0;
	data->theme = 0;
	data->iterations = ITER;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc < 2)
	{
		write(1, "No set selected\n", 17);
		return (0);
	}
	i = parsing(argc, argv);
	if (i == 1)
		return (0);
	data.set = 'm';
	if (i == 2)
	{
		data.set = 'j';
		data.julia_re = ft_atof(argv[2]);
		data.julia_im = ft_atof(argv[3]);
	}
	if (window_init(&data) == 1)
		return (0);
	fractol(&data);
	all_hooks(&data);
	mlx_loop(data.mlx_ptr);
	return (free_all(&data), 0);
}
