/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:33:13 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/02 16:27:41 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct s_ivector	t_ivector;
typedef struct s_fvector	t_fvector;
typedef struct s_ray		t_ray;
typedef struct s_color		t_color;
typedef struct s_mimg		t_mimg;
typedef struct s_data		t_data;
typedef struct s_player		t_player;
typedef struct s_game		t_game;

/* init_game */
int		img_init(t_mimg *img, t_game *g, void *init);
void	game_init(t_game *g);
void	init_imgs(t_game *g, t_data *d);
void	init_ray(t_ray *r);

/* init_struct */
int		data_init(t_data *data);
int		color_init(t_data *data);
void	player_init(t_player *pl);
void	struct_init(t_game *new, t_data *data, t_player *pl);
void	ivector_init(t_ivector *vec, int x, int y);
void	fvector_init(t_fvector *vec, double x, double y);

/* get_textures */
t_mimg	*init_north_texture(t_game *g);
t_mimg	*init_south_texture(t_game *g);
t_mimg	*init_west_texture(t_game *g);
t_mimg	*init_east_texture(t_game *g);

# endif