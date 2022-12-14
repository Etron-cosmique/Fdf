/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:20:09 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/14 20:38:36 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_grid(t_data *img, t_grid *grid)
{
	int	y;
	int	x;

	x = 0;
	while (x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			if (is_in_grid(x, y, grid) == 0)
				set_pix(grid, img, x, y);
			y++;
		}	
		x++;
	}
}

void	set_alt(t_grid *grid)
{
	int	x;
	int	y;
	
	y = 0;

	grid->min_alt = grid->tab[0][0];
	grid->max_alt = grid->tab[0][0];
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			if (grid->min_alt > grid->tab[y][x])
				grid->min_alt = grid->tab[y][x];
			if (grid->max_alt < grid->tab[y][x])
				grid->max_alt = grid->tab[y][x];
			x++;
		}
		y++;
	}
	if (grid->min_alt >= 0)
		grid->alt_0 = grid->min_alt;
	if (grid->max_alt <= 0)
		grid->alt_0 = grid->max_alt;
}

void	set_pix(t_grid *grid, t_data *img, int x, int y)
{
	int color;

	get_pos(x, y, grid);
	if (x_y(x, y, grid) == 0)
		grid->flag = 0;
	color = color_maker(grid, x, y);
	if (grid->c_alt > grid->alt_0 && grid->flag != 1)
		my_mlx_pixel_put(img, x, y, get_rgb(255, splitter(color, 1), splitter(color, 2)));
	if (grid->c_alt < grid->alt_0 && grid->flag != 1)
		my_mlx_pixel_put(img, x, y, get_rgb(splitter(color, 2), splitter(color, 1), 255));
	if (grid->c_alt > grid->alt_0 && grid->flag == 1)
		my_mlx_pixel_put(img, x, y, get_rgb(splitter(color, 2), splitter(color, 1), 255));
	if (grid->c_alt < grid->alt_0 && grid->flag == 1)
		my_mlx_pixel_put(img, x, y, get_rgb(255, splitter(color, 1), splitter(color, 2)));
	if (grid->c_alt == grid->alt_0)
		my_mlx_pixel_put(img, x, y, shade_zero(grid, color));
}

int		prev_color(t_grid *grid)
{
	float	x;

	x = 255;
	if (grid->c_alt > grid->alt_0)
		x -= x / (float)(grid->max_alt / grid->c_alt);
	if (grid->c_alt < grid->alt_0)
		x -= x / (float)(grid->min_alt / grid->c_alt);
	if (grid->c_alt == grid->alt_0)
		return ((int)x);
	return ((int)x);
}

void	get_pos(int x, int y, t_grid *grid)
{
	grid->index_y = (y - grid->start_y) / grid->size_p_y;
	grid->index_x = (x - grid->start_x) / grid->size_p_x;
	grid->c_alt = grid->tab[grid->index_y][grid->index_x];
}
