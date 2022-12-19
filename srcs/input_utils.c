/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:12:29 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/19 12:00:41 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	how_many_d(char *str)
{
	int	i;

	i = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	nb;

	i = 0;
	neg = 1;
	nb = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	return (nb * neg);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	input_checker(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[0]))
		return (1);
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isdigit(str[i]) && str[i] && str[i] != '\n'
			&& str[i] != ' ' && str[i] != '-' && str[i] != '+')
			return (1);
		else
			i++;
	}
	return (0);
}

int	input_maker(t_fdf *f)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	f->tab = malloc(sizeof(int *) * f->m.size_y);
	if (f->tab == NULL)
		return (1);
	while (f->str && f->str[i])
	{
		x = 0;
		f->tab[y] = malloc(sizeof(int) * f->m.size_x);
		if (f->tab[y] == NULL)
			return (y);
		while (x < f->m.size_x)
		{
			f->tab[y][x] = ft_atoi(&f->str[i]);
			i += how_many_d(&(f->str[i]));
			x++;
		}
		y++;
	}
	return (0);
}
