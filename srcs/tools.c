/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:20:09 by clvicent          #+#    #+#             */
/*   Updated: 2022/11/24 16:08:10 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_grid(t_data *img, t_grid *grid)
{
	int	y;
	int	x;

	grid->index_x = 0;
	grid->index_y = 0;
	x = ((1919 - grid->size_p_x * grid->size_x) / 2);
	while (x < ((1919 + grid->size_p_x * grid->size_x) / 2) + 1)
	{
		y = ((1079 - grid->size_p_y * grid->size_y) / 2);
		while (y < ((1079 + grid->size_p_y * grid->size_y) / 2))
			my_mlx_pixel_put(img, x, y++, get_rgb(255, 255, 255));
		x += grid->size_p_x;
	}
	y = ((1079 - grid->size_p_y * grid->size_y) / 2);
	while (y < ((1079 + grid->size_p_y * grid->size_y) / 2) + 1)
	{
		x = ((1919 - grid->size_p_x * grid->size_x) / 2);
		while (x < (1919 + grid->size_p_x * grid->size_x) / 2)
			my_mlx_pixel_put(img, x++, y, get_rgb(255, 255, 255));
		y += grid->size_p_y;
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
}

void	color_line(t_grid *grid, t_img *img, int x, int y)
{
	int	alt_0;
	int color;
	
	color = 255;
	if (grid->min_alt > 0)
		alt_0 = grid->min_alt;
	else if (grid->max_alt < 0)
		alt_0 = grid->max_alt;
	else
		alt_0 = 0;
	if (grid->tab[grid->index_y][grid->index_x] > 0)
		my_mlx_pixel_put(img, x++, y, get_rgb(color, CURRENT_CP, CURRENT_CP));		
	if (grid->tab[grid->index_y][grid->index_x] < 0)
		my_mlx_pixel_put(img, x++, y, get_rgb(CURRENT_CN, CURRENT_CN, color));
}