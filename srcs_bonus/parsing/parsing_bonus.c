/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:37:30 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/08 10:36:42 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	get_map_height(t_game *g, int i)
{
	close(g->map);
	get_next_line(-1);
	g->d->height = i;
	g->d->mapper = (char **)ft_calloc(sizeof(char *), g->d->height + 1);
	if (!g->d->mapper)
		err_message(g, "mapper", "memory allocation failed", 2);
	else if (!g->d->height)
		err_message(g, "parsing", "no map detected", 2);
}

void	init_my_map(t_game *g, char *file)
{
	char	*line;
	int		i;
	bool	in_map;

	i = 0;
	in_map = false;
	line = init_tmp(g, file);
	while (line)
	{
		free(line);
		line = get_next_line(g->map);
		if (!line)
			break ;
		if (line[0] == '1' || line[0] == ' ' || line[0] == '\t')
			in_map = true;
		if (in_map == true && line[0] == '\n')
			break ;
		if (in_map == true)
			i++;
		if (in_map == true && ft_strlen(line) > g->d->width)
			g->d->width = ft_strlen(line);
	}
	if (line)
		free(line);
	get_map_height(g, i);
}

void	parsing_the_thing(t_game *g, char *file)
{
	char	*line;
	int		i;

	init_my_map(g, file);
	line = init_tmp(g, file);
	i = 0;
	while (line)
	{
		free(line);
		line = get_next_line(g->map);
		if (!line)
			break ;
		if (g->d->all_text == false)
			is_indicator(g, line);
		else if (g->d->all_colors == false)
			parse_colors(g, line);
		else
			parse_map(g, line, &i);
		if (g->d->map_parsed == true)
			break ;
	}
	get_next_line(-1);
	close(g->map);
	check_map(g);
	check_all_parsed(g);
}

char	*init_tmp(t_game *g, char *file)
{
	char	*line;

	line = NULL;
	g->map = open(file, O_RDONLY, 0664);
	if (g->map < 0)
		err_message(g, file, "invalid fd", 2);
	line = malloc(1 * sizeof(char));
	if (!line)
		err_message(g, "line", "memory allocation failed", 2);
	return (line);
}
