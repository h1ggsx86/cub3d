/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:37:30 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/08 19:38:01 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// void	get_textures(char *line, int idx)
// {
// 	if ()
// }

void	parse_textures(t_data *d, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (!ft_isspace(line[i]))
			i++;
		if (!is_indicator(d, ft_substr(line, i, 2)))
			break ;
	}
}

void	parse_colors(t_data *d, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (!ft_isspace(line[i])
			i++;
		if (!is_color(d, line[i]))
	}
}

void	parse_map(t_game *game)
{
	char	*line;

	line = get_next_line(game->map);
	while (line)
	{
		free(line);
		line = get_next_line(game->map);
		if (!line)
			break ;
		if (game->d->all_text == false)
			get_textures(line);
		get_mapper();
	}
	get_next_line(-1);
	close(game->map);
}

void	parsing_the_thing(t_game *g, char *file)
{
	char	*line;

	g->map = open(file, O_RDONLY, 0664);
	if (g->map < 0)
		exit(1);
	line = get_next_line(g->map);
	while (line)
	{
		free(line);
		line = get_next_line(g->map);
		if (!line)
			break ;
		if (g->d->all_text == false)
			parse_textures(g->map, line);
		else if (g->d->all_colors == false)
			parse_colors(line);
	}
	parse_map(g);
}
