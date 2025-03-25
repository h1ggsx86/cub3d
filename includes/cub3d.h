/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:02:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/25 18:47:13 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <string.h>
# include <inttypes.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>

# include "../mlx-linux/mlx.h"
# include "../mlx-linux/mlx_int.h"
# include "../libft/libft.h"

# include "../includes/parsing.h"
# include "../includes/utils.h"
# include "../includes/init.h"
# include "../includes/raycast.h"

# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define MAP_SIZE 64
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define PI 3.1415926535
# define PI2 PI/2
# define PI3 3*PI/2
# define DR 0.0174533
# define ANGLE60 WIN_WIDTH
# define ANGLE30 (ANGLE60 / 2)
# define ANGLE15 (ANGLE30 / 2)
# define ANGLE90 (ANGLE30 * 3)
# define ANGLE180 (ANGLE90 * 2)
# define ANGLE270 (ANGLE90 * 3)
# define ANGLE360 (ANGLE60 * 6)
# define ANGLE0 0
# define ANGLE5 (ANGLE30 / 6)
# define ANGLE10 (ANGLE5 * 2)

extern int	worldMap[24][24];

typedef struct s_color
{
	unsigned char	*rgb;
	unsigned int	int_rgb[3];
}			t_color;

typedef struct s_mimg
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_mimg;

typedef struct s_data
{
	t_mimg		*img_map;
	t_mimg		*img_player;
	t_color		*colors;
	int			active_img;
	char		**mapper;
	int			pos_player[2];
	int			height;
	size_t		width;
	int			i_text;
	int			i_colors;
	int			color;
	u_int32_t	ground_color;
	u_int32_t	roof_color;
	bool		all_text;
	bool		all_colors;
	bool		map_parsed;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
}				t_data;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	viewX;
	double	viewY;
	double	pa;
	double	pdx;
	double	pdy;
}			t_player;

typedef struct s_game
{
	int			map;
	int			win_height;
	int			win_width;
	void		*init;
	void		*win;
	t_data		*d;
	t_player	*pl;
}				t_game;

void	moves_input(int keycode, t_game *g);
void	draw_map(t_game *g);

/* LOOP */
int		ray_loop(t_game *g, t_player p);
void	the_loop(t_game *g);

/* MATH STUFF*/
int		fix_angle(int a);
float	deg_to_rad(int a);

#endif
