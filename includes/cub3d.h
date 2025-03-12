/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:02:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/08 19:58:32 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include "../mlx-linux/mlx.h"
# include "../mlx-linux/mlx_int.h"
# include "../libft/libft.h"

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

extern int	worldMap[MAP_WIDTH][MAP_HEIGHT];


typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
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
	int			height;
	int			width;
	int			i_text;
	u_int32_t	ground_color;
	u_int32_t	roof_color;
	bool		all_text;
	bool		all_colors;
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
}			t_player;

typedef struct s_game
{
	int			map;
	void		*init;
	void		*win;
	t_data		*d;
	t_player	*pl;
}				t_game;

/* INIT */
int		img_init(t_mimg *img, t_data *d, void *init);
void	game_init(t_game *g);
void	struct_init(t_game *new, t_data *data, t_player *pl);

/* EXIT */
void	exit_game(t_game *g, int ecode);

/* PUT & PLAYER*/
void	put_pixel(t_data *d, int x, int y, int color);
void	put_player_square(t_data *d, t_player *pl, int c);
void	put_player_circle(t_game *g, int color, int r);
void	put_vline(t_game *g, int y_start, int y_end, int x, int color);
void	put_player_line(t_game *g, int x, int y);
void	moves_input(int keycode, t_game *g);

/* LOOP */
int		ray_loop(t_game *g, t_player *pl);
void	the_loop(t_game *g);

/* parsing */
void	parsing_the_thing(t_game *g, char *file);
void	parse_map(t_game *g);

/* parsing_utils */
int		is_indicator(t_data *d, char *line);

/* error */
void	err_message(t_game *g, char *arg, char *mess);

#endif
