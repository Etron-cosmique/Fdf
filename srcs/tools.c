/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:20:09 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/01 15:44:03 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_grid(t_data *img, t_grid *grid)
{
	int	y;
	int	x;

	x = ((1920 - grid->size_p_x * (grid->size_x - 1)) / 2);
	while (x < ((1920 + grid->size_p_x * (grid->size_x - 1)) / 2 + 1))
	{
		y = ((1080 - grid->size_p_y * (grid->size_y - 1)) / 2);
		while (y < ((1080 + grid->size_p_y * grid->size_y - 1) / 2 + 1))
		{
			grid->index_y = get_pos(y, grid, 'y');
			printf("grid->index_y = %d\n", grid->index_y);
			color_line(grid, img, x, y++);
		}
		x += grid->size_p_x;
		grid->index_x = get_pos(x, grid, 'x');
		printf("grid->index_x = %d\n", grid->index_x);
	}
	y = ((1080 - grid->size_p_y * (grid->size_y - 1)) / 2);
	grid->index_y = 0;
	while (y < ((1080 + grid->size_p_y * (grid->size_y - 1)) / 2 + 1))
	{
		x = ((1920 - grid->size_p_x * (grid->size_x - 1)) / 2);
		while (x < (1920 + grid->size_p_x * (grid->size_x - 1)) / 2 + 1)
		{
			grid->index_x = get_pos(x, grid, 'x');
			printf("grid->index_x = %d\n", grid->index_x);
			color_line(grid, img, x++, y);
		}
		y += grid->size_p_y;
		grid->index_y = get_pos(y, grid, 'y');
		printf("grid->index_y = %d\n", grid->index_y);
	}
}

// void	ft_grid(t_data *img, t_grid *grid)
// {
// 	int	y;
// 	int	x;

// 	x = 0;
// 	while (x < 1920)
// 	{
// 		y = 0;
// 		while (y < 1080)
// 		{
// 			color_line(grid, img, x, y);
// 			y++;
// 		}	
// 		x ++;
// 	}
// }

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

void	color_line(t_grid *grid, t_data *img, int x, int y)
{
	int	alt_0;
	int color;

	if (grid->min_alt > 0)
		alt_0 = grid->min_alt;
	else if (grid->max_alt < 0)
		alt_0 = grid->max_alt;
	else
		alt_0 = 0;
	color = current_color(255, grid, alt_0);
	if (grid->tab[grid->index_y][grid->index_x] > 0)
		my_mlx_pixel_put(img, x, y, get_rgb(255, color, color));		
	if (grid->tab[grid->index_y][grid->index_x] < 0)
		my_mlx_pixel_put(img, x, y, get_rgb(color, color, 255));
	if (grid->tab[grid->index_y][grid->index_x] == 0)
		my_mlx_pixel_put(img, x, y, get_rgb(color, color, 255));
}

int		current_color(int i, t_grid *grid, int alt)
{
	if (grid->tab[grid->index_y][grid->index_x] > 0)
		i -= (i / (grid->max_alt / grid->tab[grid->index_y][grid->index_x]));
	else if (grid->tab[grid->index_y][grid->index_x] < 0)
		i -= (i / (grid->min_alt / grid->tab[grid->index_y][grid->index_x]));
	else if (grid->tab[grid->index_y][grid->index_x] == alt)
		return (i);
	return (i);
}

int		get_pos(int i, t_grid *grid, char c)
{
	int res;

	if (c == 'y')
	{
		res = i - ((1080 - grid->size_p_y * (grid->size_y - 1)) / 2);
		printf("res y = %d\n", res);
		res /= grid->size_p_y;	
		if (res >= grid->size_y)
			res = grid->size_y - 1;
	}		
	if (c == 'x')
	{
		res = i - ((1920 - grid->size_p_x * (grid->size_x - 1)) / 2);
		printf("res x = %d\n", res);
		res /= grid->size_p_x;
		if (res >= grid->size_x)
			res = grid->size_x - 1;
	}
	return (res);
}
