/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:37:30 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/17 19:45:30 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	init_my_map(t_game *g, char *file)
{
	char	*line;
	int		i;
	bool	in_map;

	line = NULL;
	i = 0;
	in_map = false;
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
		if (line[0] == '1' || line[0] == ' ' || line[0] == '\t')
			in_map = true;
		if (in_map == true && line[0] == '\n')
			in_map = false;
		else if (in_map == true)
			i++;
	}
	g->d->height = i;
	printf("height = %d\n", g->d->height);
}

void	parsing_the_thing(t_game *g, char *file)
{
	char	*line;
	int		i;

	i = 0;
	init_my_map(g, file);
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
		// if (g->d->all_text == false)
		// 	is_indicator(g, line);
		// else if (g->d->all_colors == false)
		// 	parse_colors(g, line);
		// else
		parse_map(g, line, i);
		i++;
	}
}
