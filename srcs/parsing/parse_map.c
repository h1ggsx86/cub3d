/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:46 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/17 18:33:06 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	is_inside(t_game *g, bool player, int j)
{
	int	i;

	i = 0;
	while (g->d->mapper[j][i])
	{
		if (is_pos_player(g->d->mapper[j][i]) && player == true)
				err_message(g, "player", "only one allowed");
		else if (g->d->mapper[j][i] != '1' && g->d->mapper[j][i] != '0')
			return (1);
	}
	return (0);
}

int	is_a_side(t_game *g, int j)
{
	int	i;

	i = 0;
	while (g->d->mapper[j][i])
	{
		if (g->d->mapper[j][i] != '1' && g->d->mapper[j][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	is_pos_player(int c)
{
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

int	is_line_correct(t_game *g, int j)
{
	int		i;
	bool	player;

	i = 0;
	player = false;
	while (g->d->mapper[j][i])
	{
		if (is_a_side(g, j))
			err_message(g, "side", "must be closed");
		if (is_pos_player(g->d->mapper[j][i]) && player == false)
			player = true;
		else if (is_pos_player(g->d->mapper[j][i]) && player == true)
			return (1);
		i++;
	}
	return (0);
}

void	parse_map(t_game *game, char *line, int j)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		game->d->mapper[j][i] = line[i];
		if (is_line_correct(game, j))
			break ;
		printf("%c", game->d->mapper[j][i]);
		i++;
	}
	printf("\n");
	game->d->height++;
}
