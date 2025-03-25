/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:02:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/24 23:17:37 by xenon            ###   ########.fr       */
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

extern int	worldMap[];

typedef struct s_color
{
	unsigned char	*rgb;
	unsigned int	int_rgb[3];
}			t_color;

typedef struct s_tables
{
	float	sin_table[ANGLE360 + 1];
	float	isin_table[ANGLE360 + 1];
	float	cos_table[ANGLE360 + 1];
	float	icos_table[ANGLE360 + 1];
	float	tan_table[ANGLE360 + 1];
	float	itan_table[ANGLE360 + 1];
	float	fish_table[ANGLE360 + 1];
	float	xstep_table[ANGLE360 + 1];
	float	ystep_table[ANGLE360 + 1];
}			t_tables;

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
	t_tables	t;
}				t_game;

/* init */
int		img_init(t_mimg *img, t_game *g, void *init);
void	game_init(t_game *g);
void	struct_init(t_game *new, t_data *data, t_player *pl, t_tables *t);

/* exit */
void	exit_game(t_game *g, int ecode);

/* put & player */
void	put_pixel(t_data *d, int x, int y, int color);
void	put_square(t_data *d, int xc, int yc, int c);
void	put_player_circle(t_game *g, int color, int r);
void	put_vline(t_game *g, int y_start, int y_end, int x, int color);
void	put_player_line(t_game *g, int x, int y);
void	moves_input(int keycode, t_game *g);
void	draw_map(t_game *g);

/* LOOP */
int		ray_loop(t_game *g, t_player p);
void	the_loop(t_game *g);

/* error */
void	err_message(t_game *g, char *arg, char *mess);

/* MATH STUFF*/
int		fix_angle(int a);
float	deg_to_rad(int a);

#endif
