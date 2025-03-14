/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:46 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/14 17:24:22 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	is_a_side(t_game *g)
{
	int	i;

	i = 0;
	while (g->d->mapper[i])
	{
		if (g->d->mapper[i] != '1' && g->d->mapper[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	is_pos_player(int c, bool player)
{
	if (player == true)
		return (0);
	if (c == 'N')
		return (1);
	else if (c == 'S')
		return (1);
	else if (c == 'E')
		return (1);
	else if (c == 'W')
		return (1);
	else
		return (0);
}

int	is_line_correct(t_game *g)
{
	int		i;
	bool	player;

	i = 0;
	player = false;
	while (g->d->mapper[i])
	{
		if (is_pos_player(g->d->mapper[i], player))
			player = true;
		
		i++;
	}
}

void	parse_map(t_game *game, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		game->d->mapper[i] = line[i];
		is_line_correct(game);
		i++;
	}
	game->d->height++;
}
