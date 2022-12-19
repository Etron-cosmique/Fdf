/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:39:35 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/19 12:03:35 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->length + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

int	get_rgb(int r, int g, int b)
{
	int	rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

void	l_c_size(t_fdf *f)
{
	f->m.size_p_x = (f->scx - 1) / f->m.size_x;
	f->m.size_p_y = (f->scy - 1) / f->m.size_y;
	if (f->m.size_p_x > f->m.size_p_y)
		f->m.size_p_x = f->m.size_p_y;
	else
		f->m.size_p_y = f->m.size_p_x;
}

int	width_and_length(t_fdf *f)
{
	char	*line;

	line = NULL;
	f->str = get_next_line(f->fd);
	if (f->str == NULL)
		return (-1);
	else
		f->m.size_y = 1;
	f->m.size_x = get_n_col(f->str);
	while (1)
	{
		line = get_next_line(f->fd);
		if (line == NULL || input_checker(line) == 1)
		{
			free(line);
			return (0);
		}
		f->m.size_y++;
		if (f->m.size_x != get_n_col(line))
			return (-1);
		f->str = ft_strjoin(f->str, line);
		free(line);
	}
	return (0);
}

int	get_n_col(char *str)
{
	int		i;
	char	**strs;

	i = 0;
	strs = ft_split(str, ' ');
	while (strs[i])
		i++;
	ft_exit(strs);
	return (i);
}
