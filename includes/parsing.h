/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:04 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/17 18:50:21 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

typedef struct s_color	t_color;
typedef struct s_mimg	t_mimg;
typedef struct s_data	t_data;
typedef struct s_player	t_player;
typedef struct s_game	t_game;

/* parsing */
void	parsing_the_thing(t_game *g, char *file);

/* parsing_utils */

/* parse_textures */
void		get_north_or_south(t_data *d, char *line, int i, int idc);
void		get_east_or_west(t_data *d, char *line, int i, int idc);
void		get_textures(t_data *d, char *line, int idc);
int			is_indicator(t_game *g, char *line);

/* parse_map */
int			is_inside(t_game *g, bool player, int j);
int			is_a_side(t_game *g, int j);
int			is_pos_player(int c);
int			is_line_correct(t_game *g, int j);
void		parse_map(t_game *game, char *line, int j);

/* parse_colors */
u_int32_t	bitshift_op(t_game *g);
void		get_color(t_game *g, char *line, int i, int idc);
int			is_color(t_game *g, char *line, int i);
void		parse_colors(t_game *g, char *line);

# endif
