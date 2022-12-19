/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:57:29 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/19 14:06:38 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdio.h>

int	exit_cross(t_fdf *f)
{
	(void)f;
	exit(0);
}

int	key_press(int keycode, t_fdf *f)
{
	(void)f;
	printf("key_press()         : %d\n", keycode);
	if (keycode == 65307)
		destroyer(f);
	return (0);
}

void    ft_bzero(void *s, size_t n)
{
        size_t  i;

        i = 0;
        while (i != n)
        {
                ((unsigned char *)s)[i] = 0;
                i++;
        }
}

// void	print_param(t_math *m)
// {
// 	printf("index_x = %d\n", m->index_x);
// 	printf("index_y = %d\n", m->index_y);
// 	printf("size_x = %d\n", m->size_x);
// 	printf("size_p_x = %d\n", m->size_p_x);
// 	printf("size_y = %d\n", m->size_y);
// 	printf("size_p_y = %d\n", m->size_p_y);
// 	printf("max_alt = %d\n", m->max_alt);
// 	printf("min_alt = %d\n", m->min_alt);
// 	printf("start_x = %d\n", m->start_x);
// 	printf("start_y = %d\n", m->start_y);
// 	printf("alt_0 = %d\n", m->alt_0);
// 	printf("next_alt = %d\n", m->next_alt);
// 	printf("c_alt = %d\n", m->c_alt);
// 	printf("flag = %d\n", m->flag);
// }

int	main(int ac, char **av)
{
	t_fdf	f;
	t_data	img;

	ft_bzero(&f.m, sizeof(t_math));
	if (ac != 2)
	{
		printf("Usage : ./fdf <filename.fdf>\n");
		return (1);
	}
	f.fd = open(av[1], O_RDONLY);
	f.scx = 1920;
	f.scy = 1080;
	f.mlx = mlx_init();
	f.win = mlx_new_window(f.mlx, f.scx, f.scy, "fdf");
	img.img = mlx_new_image(f.mlx, f.scx, f.scy);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.length, &img.endian);
	f.img = img;
	if (-1 == width_and_length(&f))
		return (1);
	l_c_size(&f);
	struct_filler(&f);
	input_maker(&f);
	set_alt(&f);
	ft_grid(&f);
	mlx_put_image_to_window(f.mlx, f.win, f.img.img, 0, 0);
	mlx_key_hook(f.win, key_press, &f);
	mlx_hook(f.win, 17, 1L << 0, exit_cross, &f);
	mlx_loop(f.mlx);
}
