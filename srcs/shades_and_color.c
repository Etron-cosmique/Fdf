/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shades_and_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:57:43 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/14 20:25:42 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	shade_zero(t_grid *grid, int color)
{
	if (grid->next_alt > grid->alt_0)
		return (get_rgb(255, splitter(color, 1), splitter(color, 2)));
	if (grid->next_alt < grid->alt_0)
		return (get_rgb(splitter(color, 2), splitter(color, 1), 255));
	return (get_rgb(255, 255, 255));
}

int	splitter(int color, int flag)
{
	if (color >= 510)
		return (255);
	if (flag == 1)
	{
		if (color <= 255)
			return (color);
		else
			return (255);
	}
	if (flag == 2)
	{
		if (color <= 255)
			return (0);
		else
			return (color - 255);
	}
	return (255);
}

int reg_shader(int prev, int next, float ratio)
{
	int res;

	res = prev;
	if (prev > next)
		res -= (float)(prev - next) * ratio;
	if (prev < next)
		res += (float)(next - prev) * ratio;
	return (res);
}

int	ex_shader(int x_y, int next, t_grid *grid)
{
	float	range;
	float	loc;
	float	neg;

	if (grid->c_alt > grid->next_alt)
	{
		neg = -grid->next_alt;
		range = grid->c_alt + neg;
		loc = ((1 - (neg / range)) * (float)grid->size_p_x);
		printf("neg = %f\nrange = %f\n", neg, range);
	}
	else
	{
		neg = -grid->c_alt;
		range = grid->next_alt + neg;
		loc = ((neg / range) * (float)grid->size_p_x);
		printf("neg = %f\nrange = %f\n", neg, range);
	}
	if (x_y < (int)loc)
	{
		printf("%d < %f\n", x_y, loc);
		grid->flag = 0;
		return (reg_shader(prev_color(grid), 255, ((float)x_y / loc)));
	}
	else if (x_y == (int)loc)
	{
		printf("%d == %f\n", x_y, loc);
		grid->flag = 0;
		return (255);
	}
	if (x_y > (int)loc)
	{
		printf("%d > %f\n", x_y, loc);
		grid->flag = 1;
		return (reg_shader(255, next, (((float)x_y - loc) / (grid->size_p_x - loc))));
	}
	return (-1);
}

int	x_y(int x, int y, t_grid *grid)
{
	if ((x - grid->start_x) % grid->size_p_x == 0)
		return ((y - grid->start_y) % grid->size_p_y);
	if ((y - grid->start_y) % grid->size_p_y == 0)
		return ((x - grid->start_x) % grid->size_p_x);
	return(0);
}
