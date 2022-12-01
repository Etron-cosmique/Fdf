/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:54:02 by clvicent          #+#    #+#             */
/*   Updated: 2022/12/01 13:53:49 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define LOG    printf("%s:%d %s()\n", __FILE__,__LINE__, __FUNCTION__);
# define DEBUG 1
# define PAUSE    if (DEBUG) {getchar();};

# include "../mlx_linux/mlx.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_data {
	void 	*img;
	char 	*addr;
	int		bpp;
	int		length;
	int		endian;
}	t_data;

typedef struct s_grid {
	int		index_x;
	int		index_y;
	int		size_x;
	int		size_p_x;
	int		size_y;
	int		size_p_y;
	int		fd;
	int		max_alt;
	int		min_alt;
	int		**tab;
	char	*str;
	
}	t_grid;

// main
int		main(void);


//utils
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
int 	get_rgb(int r, int g, int b);
int		width_and_length(t_grid *grid, t_data *img);
int		get_n_col(char *str);
void	l_c_size(t_grid *grid);

// input_utils
int		input_checker(char *str);
int		ft_isdigit(char c);
int		input_maker(t_grid *grid);
int		ft_atoi(const char *str);
int		how_many_d(char *str);

//tools
void	set_alt(t_grid *grid);
int		current_color(int i, t_grid *grid, int alt);
void	ft_grid(t_data *img, t_grid *grid);
void	color_line(t_grid *grid, t_data *img, int x, int y);
int		get_pos(int i, t_grid *grid, char c);

//ft_split
char	**ft_split(char const *s, char c);
char	**ft_exit(char **strs);

#endif
