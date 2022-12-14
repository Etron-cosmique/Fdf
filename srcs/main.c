/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:57:29 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/08 18:33:19 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_grid	grid;

	if (ac != 2)
	{
		printf("Usage : ./fdf <filename.fdf>\n");
		return(1);
	}
	grid.fd = open(av[1], O_RDONLY);
	grid.scx = 1920;
	grid.scy = 1080;
	mlx = mlx_init();
	win = mlx_new_window(mlx, grid.scx, grid.scy, "fdf");
	img.img = mlx_new_image(mlx, grid.scx, grid.scy);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.length, &img.endian);
	if (-1 == width_and_length(&grid))
		return (1);
	l_c_size(&grid);
	struct_filler(&grid);
	input_maker(&grid);
	set_alt(&grid);
	ft_grid(&img, &grid);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}
