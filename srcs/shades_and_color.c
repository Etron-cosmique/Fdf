/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shades_and_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:57:43 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/19 11:59:42 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	shade_zero(t_fdf *f, int color)
{
	if (f->m.next_alt > f->m.alt_0)
		return (get_rgb(255, splitter(color, 1), splitter(color, 2)));
	if (f->m.next_alt < f->m.alt_0)
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

int	reg_shader(int prev, int next, float ratio)
{
	int	res;

	res = prev;
	if (prev > next)
		res -= (float)(prev - next) * ratio;
	if (prev < next)
		res += (float)(next - prev) * ratio;
	return (res);
}

int	ex_shader(int x_y, int next, t_fdf *f)
{
	float	range;
	float	loc;

	if (f->m.c_alt > f->m.next_alt)
	{
		range = -f->m.next_alt;
		range += f->m.c_alt;
		loc = ((1 - (-f->m.next_alt / range)) * (float)f->m.size_p_x);
	}
	else
	{
		range = -f->m.c_alt;
		range += f->m.next_alt;
		loc = ((-f->m.c_alt / range) * (float)f->m.size_p_x);
	}
	if (x_y < (int)loc)
		return (reg_shader(prev_color(f), 255, ((float)x_y / loc)));
	else if (x_y == (int)loc)
		return (255);
	if (x_y > (int)loc)
	{
		f->m.flag = 1;
		return (reg_shader(255, next, ((x_y - loc) / (f->m.size_p_x - loc))));
	}
	return (-1);
}

int	x_y(int x, int y, t_fdf *f)
{
	if ((x - f->m.start_x) % f->m.size_p_x == 0)
		return ((y - f->m.start_y) % f->m.size_p_y);
	if ((y - f->m.start_y) % f->m.size_p_y == 0)
		return ((x - f->m.start_x) % f->m.size_p_x);
	return (0);
}
