/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:55:21 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/19 12:16:47 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_in_grid(int x, int y, t_fdf *f)
{
	if (x < f->m.start_x || y < f->m.start_y)
		return (1);
	if ((x - f->m.start_x) % f->m.size_p_x == 0 && x < f->scx - f->m.start_x)
		if (y >= f->m.start_y && y < f->scy - f->m.start_y)
			return (0);
	if ((y - f->m.start_y) % f->m.size_p_y == 0 && y < f->scy - f->m.start_y)
		if (x >= f->m.start_x && x < f->scx - f->m.start_x)
			return (0);
	return (1);
}

void	struct_filler(t_fdf *f)
{	
		f->m.start_x = (f->scx - f->m.size_p_x * (f->m.size_x - 1)) / 2;
		f->m.start_y = (f->scy - f->m.size_p_y * (f->m.size_y - 1)) / 2;	
}

int	color_maker(t_fdf *f, int x, int y)
{
	int		prev;
	int		current;
	float	ratio;

	get_pos(x, y, f);
	prev = prev_color(f);
	if ((y - f->m.start_y) % f->m.size_p_y == 0
		&& (x - f->m.start_x) % f->m.size_p_x == 0)
		return (prev * 2);
	if ((x - f->m.start_x) % f->m.size_p_x != 0)
	{
		ratio = (float)((x - f->m.start_x) % f->m.size_p_x) / f->m.size_p_x;
		current = final_color(x, y, ratio, f);
	}
	if ((y - f->m.start_y) % f->m.size_p_y != 0)
	{
		ratio = (float)((y - f->m.start_y) % f->m.size_p_y) / f->m.size_p_y;
		current = final_color(x, y, ratio, f);
	}
	return (current * 2);
}

int	final_color(int x, int y, float ratio, t_fdf *f)
{
	int		prev;
	int		next;

	prev = prev_color(f);
	f->m.flag = 0;
	if ((x - f->m.start_x) % f->m.size_p_x != 0)
		next = next_color(f, 'x');
	else
		next = next_color(f, 'y');
	if ((f->m.c_alt > f->m.alt_0 && f->m.next_alt < f->m.alt_0)
		|| (f->m.c_alt < f->m.alt_0 && f->m.next_alt > f->m.alt_0))
		return (ex_shader(x_y(x, y, f), next, f));
	else
		return (reg_shader(prev, next, ratio));
	return (-1);
}

int	next_color(t_fdf *f, char c)
{
	float	next;

	next = 255;
	if (c == 'x')
		f->m.next_alt = f->tab[f->m.index_y][f->m.index_x + 1];
	if (c == 'y')
		f->m.next_alt = f->tab[f->m.index_y + 1][f->m.index_x];
	if (f->m.next_alt > f->m.alt_0)
		next -= next / (float)(f->m.max_alt / f->m.next_alt);
	if (f->m.next_alt < f->m.alt_0)
		next -= next / (float)(f->m.min_alt / f->m.next_alt);
	if (f->m.next_alt == f->m.alt_0)
		return ((int)next);
	return ((int)next);
}
