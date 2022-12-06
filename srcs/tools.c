/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:20:09 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/06 17:15:47 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	ft_grid(t_data *img, t_grid *grid)
// {
// 	int	y;
// 	int	x;

// 	x = grid->start_x;
// 	while (x < (1920 - grid->start_x))
// 	{
// 		y = grid->start_y;
// 		while (y < 1080 - grid->start_y)
// 			color_line(grid, img, x, y++);
// 		x += grid->size_p_x;
// 		printf("grid->index_x = %d\ngrid->index_y = %d\n", grid->index_x, grid->index_y);
// 	}
// 	y = grid->start_y;
// 	while (y < (1080 - grid->start_y))
// 	{
// 		x = grid->start_x;
// 		while (x < 1920 - grid->start_x)
// 			color_line(grid, img, x++, y);
// 		y += grid->size_p_y;
// 		// printf("grid->index_x = %d\ngrid->index_y = %d\n", grid->index_x, grid->index_y);
// 	}
// }

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
			// printf("y = %d\n", y);
			if (is_in_grid(x, y, grid) == 0)
				color_line(grid, img, x, y);
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
}

void	color_line(t_grid *grid, t_data *img, int x, int y)
{
	int	alt_0;
	int color;

	get_pos(x, y, grid);
	// printf("grid->index_x = %d\ngrid->index_y = %d\n", grid->index_x, grid->index_y);
	color = current_color(255, grid, grid->alt_0);
	if (grid->tab[grid->index_y][grid->index_x] > 0)
		my_mlx_pixel_put(img, x, y, get_rgb(255, color, color));		
	if (grid->tab[grid->index_y][grid->index_x] < 0)
		my_mlx_pixel_put(img, x, y, get_rgb(color, color, 255));
	if (grid->tab[grid->index_y][grid->index_x] == 0)
		my_mlx_pixel_put(img, x, y, get_rgb(color, color, color));
}

int		prev_color(int i, t_grid *grid, int alt)
{
	if (grid->tab[grid->index_y][grid->index_x] > 0)
		i -= (i / (grid->max_alt / grid->tab[grid->index_y][grid->index_x]));
	else if (grid->tab[grid->index_y][grid->index_x] < 0)
		i -= (i / (grid->min_alt / grid->tab[grid->index_y][grid->index_x]));
	else if (grid->tab[grid->index_y][grid->index_x] == alt)
		return (i);
	return (i);
}

void	get_pos(int x, int y, t_grid *grid)
{
	grid->index_y = (y - grid->start_y) / grid->size_p_y;
	if (grid->index_y >= grid->size_y)
		grid->index_y = grid->size_y - 1;
	grid->index_x = (x - grid->start_x) / grid->size_p_x;
	if (grid->index_x >= grid->size_x)
		grid->index_x = grid->size_x - 1;
}
