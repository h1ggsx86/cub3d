/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:48:34 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/03 23:42:27 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_pos_player(int c, int *player)
{
	if (c == 'N')
		(*player)++;
	else if (c == 'S')
		(*player)++;
	else if (c == 'E')
		(*player)++;
	else if (c == 'W')
		(*player)++;
	if (*player)
		return (1);
	else
		return (0);
}

int	is_door_valid(t_game *g, int j, int i)
{
	if (g->d->mapper[j][i] != 'C')
		return (0);
	if (g->d->mapper[j][i - 1] && g->d->mapper[j][i + 1])
	{
		if (g->d->mapper[j][i - 1] == '1' && g->d->mapper[j][i + 1] == '1')
		{
			g->d->i_doors++;
			return (0);
		}
	}
	if (g->d->mapper[j - 1][i] && g->d->mapper[j + 1][i])
	{
		if (g->d->mapper[j - 1][i] == '1' && g->d->mapper[j + 1][i] == '1')
		{
			g->d->i_doors++;
			return (0);
		}
	}
	return (1);
}

void	check_map(t_game *g)
{
	if (check_left_right(g))
		err_message(g, "map", "invalid", 4);
	if (check_top_bottom(g))
		err_message(g, "map", "invalid", 4);
	g->d->map_parsed = true;
	if (check_inside(g))
		exit_game(g, 5);
}

void	init_colors(t_game *g, int idc)
{
	if (idc == 'F')
		g->d->ground_color = bitshift_op(g);
	else
		g->d->roof_color = bitshift_op(g);
	g->d->i_colors++;
	if (g->d->i_colors == 2)
		g->d->all_colors = true;
}

void	check_all_parsed(t_game *g)
{
	if (!g->d->all_text || !g->d->all_colors || !g->d->map_parsed)
	{
		perror("");
		exit_game(g, 6);
	}
}
