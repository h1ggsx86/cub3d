/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:02:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/28 19:14:31 by tnedel           ###   ########.fr       */
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
# define ROT_SPEED 0.08f
# define MOVE_SPEED 0.15f

typedef struct s_ivector
{
	int	x;
	int	y;
}		t_ivector;

typedef struct s_ray
{
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	double	cameraX;
	double	wall_dist;
	double	ray_x;
	double	ray_y;
	double	side_distX;
	double	side_distY;
	double	delta_distX;
	double	delta_distY;
}			t_ray;

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
	t_color		*colors;
	int			active_img;
	char		**mapper;
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
	int			n_text;
	int			s_text;
	int			w_text;
	int			e_text;
}				t_data;

typedef struct s_player
{
	double	x;
	double	y;
	double	dirX;
	double	dirY;
	double	viewX;
	double	viewY;
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
	t_ray		*r;
}				t_game;

void	draw_map(t_game *g);

/* LOOP */
void	the_loop(t_game *g);

/* MATH STUFF*/
int		fix_angle(int a);
float	deg_to_rad(int a);

#endif
