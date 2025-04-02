/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:48:34 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/02 14:49:19 by arotondo         ###   ########.fr       */
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
			return (0);
	}
	if (g->d->mapper[j - 1][i] && g->d->mapper[j + 1][i])
	{
		if (g->d->mapper[j - 1][i] == '1' && g->d->mapper[j + 1][i] == '1')
			return (0);
	}
	return (1);
}
