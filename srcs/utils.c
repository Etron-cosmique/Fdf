/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:39:35 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/08 20:57:55 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int get_rgb(int r, int g, int b)
{
	int rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);	
}

void	l_c_size(t_grid *grid)
{
	grid->size_p_x = (grid->scx - 1) / grid->size_x;
	grid->size_p_y = (grid->scy - 1) / grid->size_y;
	if (grid->size_p_x > grid->size_p_y)
		grid->size_p_x = grid->size_p_y;
	else
		grid->size_p_y = grid->size_p_x;
}

int	width_and_length(t_grid *grid)
{
	char	*line;
	
	line = NULL;
	grid->str = get_next_line(grid->fd);
	if (grid->str == NULL)
		return (-1);
	else
		grid->size_y = 1;
	grid->size_x = get_n_col(grid->str);
	while (1)
	{
		line = get_next_line(grid->fd);
		if (line == NULL || input_checker(line) == 1)
		{
			free(line);
			return (0);
		}
		grid->size_y++;
		if (grid->size_x != get_n_col(line))
			return (-1);
		grid->str = ft_strjoin(grid->str, line);
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
