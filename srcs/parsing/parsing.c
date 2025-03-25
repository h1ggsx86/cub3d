/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:37:30 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/24 23:24:17 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	init_my_map(t_game *g, char *file)
{
	char	*line;
	int		i;
	bool	in_map;

	i = 0;
	in_map = false;
	g->map = open(file, O_RDONLY, 0664);
	if (g->map < 0)
		exit(1);
	line = malloc(sizeof(char) * 1);
	if (!line)
		exit(1);
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
	g->d->height = i;
	close(g->map);
	get_next_line(-1);
	g->d->mapper = (char **)ft_calloc(sizeof(char *), g->d->height + 1);
	if (!g->d->mapper)
		exit(1);
}

void	check_map(t_game *g)
{
	if (check_left_right(g))
		exit_game(g, 4);
	if (check_top_bottom(g))
		exit_game(g, 4);
	g->d->map_parsed = true;
	if (check_inside(g))
		exit_game(g, 5);
}

void	parsing_the_thing(t_game *g, char *file)
{
	char	*line;
	int		i;

	init_my_map(g, file);
	g->map = open(file, O_RDONLY, 0664);
	if (g->map < 0)
		exit(1);
	line = malloc(1 * sizeof(char));
	if (!line)
		exit(1);
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
	close(g->map);
	check_map(g);
}
