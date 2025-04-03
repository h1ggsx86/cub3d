/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:02:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/03 17:02:32 by tnedel           ###   ########.fr       */
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
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define ROT_SPEED 0.002f
# define MOVE_SPEED 0.005f

enum e_kcode
{
	W,
	S,
	A,
	D,
	LEFT,
	RIGHT
};

enum e_cardinal
{
	NORTH,
	EAST,
	WEST,
	SOUTH
};

typedef struct s_ivector
{
	int	x;
	int	y;
}		t_ivector;

typedef struct s_fvector
{
	double	x;
	double	y;
}		t_fvector;

typedef struct	s_floor
{
	int			pos;
	double		pos_z;
	double		row_dist;
	t_ivector	tile;
	t_ivector	tex;
	t_fvector	floor;
	t_fvector	f_step;
	t_fvector	ray0;
	t_fvector	ray1;
}				t_floor;

typedef struct s_ray
{
	int			door;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		camera_x;
	double		wall_dist;
	t_ivector	map;
	t_ivector	step;
	t_ivector	tex;
	t_fvector	ray;
	t_fvector	side_d;
	t_fvector	delta_d;
	t_fvector	door_side_d;
}				t_ray;

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
	t_mimg		*img_player;
	t_mimg		*textures[4];
	t_mimg		the_chosen;
	t_mimg		tex_door[2];
	t_mimg		pov;
	t_mimg		floor;
	t_color		*colors;
	int			active_img;
	char		**mapper;
	int			height;
	size_t		width;
	int			i_text;
	int			i_colors;
	u_int32_t	ground_color;
	u_int32_t	roof_color;
	bool		all_text;
	bool		all_colors;
	bool		map_parsed;
	char		*text_path[4];
	int			fd_texture[4];
	char		player_dir;
}				t_data;

typedef struct s_player
{
	double		x;
	double		y;
	t_fvector	dir;
	t_fvector	view;
}			t_player;

typedef struct s_game
{
	int			key[6];
	int			map;
	int			win_height;
	int			win_width;
	int			color;
	long		time;
	long		old_time;
	void		*init;
	void		*win;
	t_data		*d;
	t_player	*pl;
}				t_game;

/* LOOP */
void	the_loop(t_game *g);

#endif
