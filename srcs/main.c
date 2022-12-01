/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:57:29 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/01 14:18:32 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdio.h>

int	main(void)
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_grid	grid;

	grid.index_x = 0;
	grid.index_y = 0;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "fdf");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.length, &img.endian);
	grid.fd = open("test.fdf", O_RDONLY);
	if (-1 == width_and_length(&grid, &img))
		return (1);
	l_c_size(&grid);
	input_maker(&grid);
	set_alt(&grid);
	ft_grid(&img, &grid);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}
