/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:48:34 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/08 12:05:23 by arotondo         ###   ########.fr       */
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

void	check_map(t_game *g)
{
	if (check_left_right(g))
		err_message(g, "map", "1invalid", 4);
	if (check_top_bottom(g))
		err_message(g, "map", "2invalid", 4);
	if (check_inside(g))
		err_message(g, "map", "3invalid", 4);
	g->d->map_parsed = true;
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
		ft_putendl_fd("Error", 2);
		exit_game(g, 6);
	}
}
