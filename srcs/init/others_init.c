/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:10:29 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/02 17:11:05 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ivector_init(t_ivector *vec, int x, int y)
{
	vec->x = x;
	vec->y = y;
}

void	fvector_init(t_fvector *vec, double x, double y)
{
	vec->x = x;
	vec->y = y;
}

void	player_init(t_player *pl)
{
	pl->x = 0;
	pl->y = 0;
	pl->dir.x = 0;
	pl->dir.y = 0;
	pl->view.x = 0.0f;
	pl->view.y = 0.0f;
}

void	key_init(t_game *new)
{
	int	i;

	i = 0;
	while (i < 6)
		new->key[i++] = 0;
}
