/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:04 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/14 12:59:10 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

/* parsing */

/* parsing_utils */

/* parse_textures */
void		get_north_or_south(t_data *d, char *line, int i, int idc);
void		get_east_or_west(t_data *d, char *line, int i, int idc);
void		get_textures(t_data *d, char *line, int idc);
int			is_indicator(t_game *g, char *line);

/* parse_map */
void		parse_map(t_game *game, char *line);

/* parse_colors */
u_int32_t	bitshift_op(t_game *g);
void		get_color(t_game *g, char *line, int i, int idc);
int			is_color(t_game *g, char *line, int i);
void		parse_colors(t_game *g, char *line);

# endif
