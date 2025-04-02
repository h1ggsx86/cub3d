/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:04 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/02 18:55:02 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_color	t_color;
typedef struct s_mimg	t_mimg;
typedef struct s_data	t_data;
typedef struct s_player	t_player;
typedef struct s_game	t_game;

/* parsing */
void		init_my_map(t_game *g, char *file);
void		parsing_the_thing(t_game *g, char *file);
char		*init_tmp(t_game *g, char *file);

/* parsing_utils */
size_t		ft_vert_len(char **tab, int row, int max);

/* parse_textures */
void		get_north_or_south(t_game *g, char *line, int idc);
void		get_east_or_west(t_game *g, char *line, int idc);
void		get_textures(t_game *g, char *line, int idc);
int			is_indicator(t_game *g, char *line);

/* parsing_checks */
int			is_pos_player(int c, int *player);
int			is_door_valid(t_game *g, int j, int i);
void		check_map(t_game *g);
void		init_colors(t_game *g, int idc);
void		check_all_parsed(t_game *g);

/* parse_map */
void		keep_pos_player(t_game *g, int *j, int *i);
int			check_inside(t_game *g);
int			check_left_right(t_game *g);
int			check_top_bottom(t_game *g);
void		parse_map(t_game *g, char *line, int *j);

/* parse_colors */
u_int32_t	bitshift_op(t_game *g);
int			get_color(t_game *g, char *line, int n);
void		cut_color(t_game *g, char *line, int idc);
void		is_color(t_game *g, char *line);
void		parse_colors(t_game *g, char *line);

#endif