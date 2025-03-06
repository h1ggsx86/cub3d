/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:37:30 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/06 10:34:24 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
void	parse_map(t_game *g)
{
	char	*line;

	line = get_next_line(g->map);
	while (line)
	{
		line = get_next_line(g->map);
	}
	get_next_line(-1);
	close(g->map);
}
*/

void	parsing_the_thing(t_game *g, char *file)
{
	g->map = open(file, O_RDONLY, 0664);
	if (g->map < 0)
		exit(1);
	// parse_map(g);
}
