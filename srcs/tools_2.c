/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:55:21 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/14 20:29:16 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_in_grid(int x, int y, t_grid *grid)
{
	if (x < grid->start_x || y < grid->start_y)
		return (1);
	if ((x - grid->start_x) % grid->size_p_x == 0 && x < grid->scx - grid->start_x)
		if (y >= grid->start_y && y < grid->scy - grid->start_y)
			return (0);
	if ((y - grid->start_y) % grid->size_p_y == 0 && y < grid->scy - grid->start_y)
		if (x >= grid->start_x && x < grid->scx - grid->start_x)
			return (0);
	return (1);
}

void	struct_filler(t_grid *grid)
{
	grid->alt_0 = 0;
	grid->start_x = (grid->scx - grid->size_p_x * (grid->size_x - 1)) / 2;
	grid->start_y = (grid->scy - grid->size_p_y * (grid->size_y - 1)) / 2;
}

int	color_maker(t_grid *grid, int x, int y)
{
	int		prev;
	int		current;
	float	ratio;

	get_pos(x, y, grid);
	prev = prev_color(grid);
	if ((y - grid->start_y) % grid->size_p_y == 0 &&
		(x - grid->start_x) % grid->size_p_x == 0)
		return (prev * 2);
	if ((x - grid->start_x) % grid->size_p_x != 0)
	{
		ratio = (float)((x - grid->start_x) % grid->size_p_x) / (float)grid->size_p_x;
		current = final_color(x, y, ratio, grid);
	}
	if ((y - grid->start_y) % grid->size_p_y != 0)
	{
		ratio = (float)((y - grid->start_y) % grid->size_p_y) / (float)grid->size_p_y;
		current = final_color(x, y, ratio, grid);
	}
	return (current * 2);
}

int	final_color(int x, int y, float ratio, t_grid *grid)
{
	int		prev;
	int		next;

	prev = prev_color(grid);
	grid->flag = 0;
	if ((x - grid->start_x) % grid->size_p_x != 0)
		next = next_color(grid, 'x');
	else
		next = next_color(grid, 'y');
	if ((grid->c_alt > grid->alt_0 && grid->next_alt < grid->alt_0) ||
		(grid->c_alt < grid->alt_0 && grid->next_alt > grid->alt_0))
		return (ex_shader(x_y(x, y, grid), next, grid));
	else
		return (reg_shader(prev, next, ratio));
	return (-1);
}

int	next_color(t_grid *grid, char c)
{
	float	next;
	
	next = 255;
	if (c == 'x')
		grid->next_alt = grid->tab[grid->index_y][grid->index_x + 1];
	if (c == 'y')
		grid->next_alt = grid->tab[grid->index_y + 1][grid->index_x];
	if (grid->next_alt > grid->alt_0)
		next -= next / (float)(grid->max_alt / grid->next_alt);
	if (grid->next_alt < grid->alt_0)
		next -= next / (float)(grid->min_alt / grid->next_alt);
	if (grid->next_alt == grid->alt_0)
		return ((int)next);
	return ((int)next);
}
