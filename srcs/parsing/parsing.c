/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:37:30 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/13 17:37:49 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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
			is_indicator(g, line);
		// else if (g->d->all_colors == false)
			// parse_colors(line);
	}
	parse_map(g);
}
