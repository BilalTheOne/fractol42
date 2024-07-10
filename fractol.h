/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:26:55 by bel-barb          #+#    #+#             */
/*   Updated: 2024/07/10 00:48:09 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 800
# define HEIGHT 800
# define ITER 40

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	double	zoom;
	double	offset_x;
	double	offset_y;
	int		theme;
	int		iterations;
	double	julia_re;
	double	julia_im;
	char	set;
}	t_data;

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

double		ft_atof(const char *str);
int			handle_keys(int key, t_data *data);
void		fractol(t_data *data);
int			get_color(int iteration, int theme);
t_complex	pixel_to_complex(int x, int y, t_data *data);
void		put_pixel_to_image(t_data *data, int x, int y, int color);
int			parsing(int argc, char **argv);

#endif