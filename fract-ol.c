/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 21:50:58 by bel-barb          #+#    #+#             */
/*   Updated: 2024/07/09 00:38:25 by bel-barb         ###   ########.fr       */
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
	data->zoom = 1.0;
	data->offset_x = 0.0;
	data->offset_y = 0.0;
	data->theme = 0;
	data->iterations = ITER;
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	check_number(char *num)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	while (num[i] == ' ')
		i++;
	while (num[i])
	{
		if (num[i] == '.')
			dot++;
		else if (num[i] < '0' || num[i] > '9' || dot == 2)
			return (1);
		if (num[i] == ' ')
			break ;
		i++;
	}
	while (num[i])
	{
		if (num[i] != ' ')
			return (1);
		i++;
	}
	return 0;
}

int	parsing(int argc, char **argv)
{
	if (((argv[1][0] != 'j' && argv[1][0] != 'm') && argv[1][0] != '\0') || ft_strlen(argv[1]) > 1)
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
			write(1, "julia set values between -2 and 2 for both Im and Re\n", 54);
			return (1);
		}
	}
	return 0;
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (parsing(argc, argv) == 1)
		return 0;
	if (argv[1][0] == 'j')
	{
		data.julia_re = ft_atof(argv[2]);
		data.julia_im = ft_atof(argv[3]);
	}
	if (window_init(&data) == 1)
		return (0);
	data.set = argv[1][0];
	fractol(&data);
	mlx_key_hook(data.win_ptr, handle_keys, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
