/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:16:20 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/12 15:10:31 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	data_init(t_data *data)
{
	data->img_map = malloc(sizeof(t_mimg) * 2);
	if (!data->img_map)
		return (1);
	data->img_map[0].img = NULL;
	data->img_map[1].img = NULL;
	data->height = WIN_HEIGHT;
	data->width = WIN_WIDTH;
	data->active_img = 1;
	data->color = 0x00dadada;
	return (0);
}

void	player_init(t_player *pl)
{
	// pl->posX = 5;
	// pl->posY = 5;
	pl->posX = 140;
	pl->posY = 300;
	pl->pa = 90;
	pl->pdx = cosf(pl->pa) * 5;
	pl->pdy = sinf(pl->pa) * 5;
}

void	struct_init(t_game *new, t_data *data, t_player *pl)
{
	new->init = NULL;
	new->win = NULL;
	new->d = data;
	new->pl = pl;
	if (data_init(new->d))
		exit_game(new, 1);
	player_init(new->pl);
}
