/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:33:13 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/28 17:02:35 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct s_color	t_color;
typedef struct s_mimg	t_mimg;
typedef struct s_data	t_data;
typedef struct s_player	t_player;
typedef struct s_game	t_game;

/* init_game */
int		img_init(t_mimg *img, t_game *g, void *init);
void	game_init(t_game *g);
void	init_img_player(t_game *g, t_data *d);

/* init_struct */
int		data_init(t_data *data);
int		color_init(t_data *data);
void	player_init(t_player *pl);
void	struct_init(t_game *new, t_data *data, t_player *pl);

/* get_textures */
void	init_north_texture(t_game *g);
void	init_south_texture(t_game *g);
void	init_west_texture(t_game *g);
void	init_east_texture(t_game *g);

# endif