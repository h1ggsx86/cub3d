/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:04 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/13 17:37:43 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

/* parsing */

/* parsing_utils */

/* parse_textures */
void	get_north_or_south(t_data *d, char *line, int i, int idc);
void	get_east_or_west(t_data *d, char *line, int i, int idc);
void	get_textures(t_data *d, char *line, int idc);
int		is_indicator(t_game *g, char *line);

/* parse_map */
void	parse_map(t_game *game);

/* parse_colors */
void	parse_colors(t_data *d, char *line);

# endif PARSING_H