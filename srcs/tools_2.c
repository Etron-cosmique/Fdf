/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:55:21 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/06 17:41:25 by clvicent         ###   ########.fr       */
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

void	struct_filer(t_grid *grid)
{
	grid->start_x = (grid->scx - grid->size_p_x * (grid->size_x - 1)) / 2;
	grid->start_y = (grid->scy - grid->size_p_y * (grid->size_y - 1)) / 2;
}

int	color_maker(t_grid *grid, int x, int y)
{
	int	prev;
	int	next;
	int	current;
	int	ratio;

	prev = prev_color(255, grid, grid->alt_0);
	if ((x - grid->scx) % grid->size_p_x != 0)
	{
		next = next_color(grid, 'x');
		if (next > prev)
			current = prev + ((next - prev) * (((x - grid->scx) % grid->size_p_x) / grid->size_p_x));

	if ((y - grid->scy) % grid->size_p_y != 0)
		next = next_color(grid, 'y');
	
}

int	next_color(t_grid *grid, char c)
{
	int	next;
	
	if (c == 'x')
	{
		grid->index_x++;
		next = current_color(255, grid, grid->alt_0);
		grid->index_x--;
	}
	if (c == 'y')
	{
		grid->index_y++;
		next = current_color(255, grid, grid->alt_0);
		grid->index_y--;
	}
	return (next);
}
