/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:46 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/12 16:21:59 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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
