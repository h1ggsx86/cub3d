/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:37:30 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/05 18:00:35 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	get_mapper(t_data *d)
// {
	
// }

void	parse_map(t_game *g)
{
	char	*line;

	line = get_next_line(g->map);
	while (line)
	{
		free(line);
		line = get_next_line(g->map);
		if (!line)
			break ;
		get_mapper();
	}
	get_next_line(-1);
	close(g->map);
}

void	parsing_the_thing(t_game *g, char *file)
{
	g->map = open(file, O_RDONLY, 0664);
	if (g->map < 0)
		exit(1);
	parse_map(g);
}
