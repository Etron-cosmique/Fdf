/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:48:19 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/19 18:14:00 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_fdf *f)
{
	int	dx;
	int	dy;
	int	er;
	int	sx;
	int	sy;
	
	dx = abs(f->m->x1 - f->m->x0);
	dy = -abs(f->m->y1 - f->m->y0);
	er = dx + dy;
	if (f->m->x0 < f->m->x1)
		sx = 1;
	else
		sx = -1;
	if (f->m->y0 < f->m->y1)
		sy = 1;
	else
		sy = -1;
	while (1)
	{
		set_pix(f, f->m->x0, f->m->y0)
		if (f->m->x0 == f->m->x1 && f->m->y0 == f->m->y1)
			break ;
		if (2 * er >= dy)
		{
			er += dy;
			f->m->x0 += sx;
		}
		if (2 * er <= dx)
		{
			er += dx;
			f->m->y0 += sy;
		}
	}	
}