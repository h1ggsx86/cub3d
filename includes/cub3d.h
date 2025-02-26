/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:02:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/02/26 13:44:07 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}			t_data;

typedef struct s_player
{
	double	x;
	double	y;
}			t_player;

typedef struct s_game
{
	void		*init;
	void		*win;
	t_data		*data;
	t_player	*pl;
}				t_game;

void	game_init(t_game *g);
void	exit_game(t_game *g, int ecode);
void	struct_init(t_game *new, t_data *data, t_player *pl);
void	put_pixel(t_data *d, int x, int y, int color);
void	put_square(t_data *d, int x_start, int y_start, int color, int nbr);

#endif