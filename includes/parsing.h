/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:04 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/20 16:45:46 by arotondo         ###   ########.fr       */
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
void	init_my_map(t_game *g, char *file);
void	parsing_the_thing(t_game *g, char *file);

/* parsing_utils */

/* parse_textures */
void		get_north_or_south(t_data *d, char *line, int idc);
void		get_east_or_west(t_data *d, char *line, int idc);
void		get_textures(t_data *d, char *line, int idc);
int			is_indicator(t_game *g, char *line);

/* parse_map */
int			is_inside(t_game *g, bool player, int j);
void		choose_left_right(t_game *g, int *i, int *j);
void		choose_top_bottom(t_game *g, int *i, int *j);
void		is_map_parsed(t_game *g, int i, int j);
int			check_sides(t_game *g);
int			is_pos_player(int c);
void		parse_map(t_game *g, char *line, int *j);

/* parse_colors */
u_int32_t	bitshift_op(t_game *g);
int			get_color(t_game *g, char *line, int n);
void		cut_color(t_game *g, char *line, int idc);
int			is_color(t_game *g, char *line);
void		parse_colors(t_game *g, char *line);

# endif
