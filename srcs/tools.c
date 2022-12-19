/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:20:09 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/19 12:07:18 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_grid(t_fdf *f)
{
	int	y;
	int	x;

	x = 0;
	while (x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			if (is_in_grid(x, y, f) == 0)
				set_pix(f, x, y);
			y++;
		}	
		x++;
	}
}

void	set_alt(t_fdf *f)
{
	int	x;
	int	y;

	y = 0;
	f->m.min_alt = f->tab[0][0];
	f->m.max_alt = f->tab[0][0];
	while (y < f->m.size_y)
	{
		x = 0;
		while (x < f->m.size_x)
		{
			if (f->m.min_alt > f->tab[y][x])
				f->m.min_alt = f->tab[y][x];
			if (f->m.max_alt < f->tab[y][x])
				f->m.max_alt = f->tab[y][x];
			x++;
		}
		y++;
	}
	if (f->m.min_alt >= 0)
		f->m.alt_0 = f->m.min_alt;
	if (f->m.max_alt <= 0)
		f->m.alt_0 = f->m.max_alt;
}

void	set_pix(t_fdf *f, int x, int y)
{
	int color;

	get_pos(x, y, f);
	if (x_y(x, y, f) == 0)
		f->m.flag = 0;
	color = color_maker(f, x, y);
	if (f->m.c_alt > f->m.alt_0 && f->m.flag != 1)
		my_mlx_pixel_put(&f->img, x, y, get_rgb(255, splitter(color, 1), splitter(color, 2)));
	if (f->m.c_alt < f->m.alt_0 && f->m.flag != 1)
		my_mlx_pixel_put(&f->img, x, y, get_rgb(splitter(color, 2), splitter(color, 1), 255));
	if (f->m.c_alt > f->m.alt_0 && f->m.flag == 1)
		my_mlx_pixel_put(&f->img, x, y, get_rgb(splitter(color, 2), splitter(color, 1), 255));
	if (f->m.c_alt < f->m.alt_0 && f->m.flag == 1)
		my_mlx_pixel_put(&f->img, x, y, get_rgb(255, splitter(color, 1), splitter(color, 2)));
	if (f->m.c_alt == f->m.alt_0)
		my_mlx_pixel_put(&f->img, x, y, shade_zero(f, color));
}

int		prev_color(t_fdf *f)
{
	float	x;

	x = 255;
	if (f->m.c_alt > f->m.alt_0)
		x -= x / (float)(f->m.max_alt / f->m.c_alt);
	if (f->m.c_alt < f->m.alt_0)
		x -= x / (float)(f->m.min_alt / f->m.c_alt);
	if (f->m.c_alt == f->m.alt_0)
		return ((int)x);
	return ((int)x);
}

void	get_pos(int x, int y, t_fdf *f)
{
	f->m.index_y = (y - f->m.start_y) / f->m.size_p_y;
	f->m.index_x = (x - f->m.start_x) / f->m.size_p_x;
	f->m.c_alt = f->tab[f->m.index_y][f->m.index_x];
}
