/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:16:20 by tnedel            #+#    #+#             */
/*   Updated: 2025/02/28 13:27:00 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	data_init(t_data *data)
{
	data->img1 = malloc(sizeof(t_mimg));
	if (!data->img1)
		return (EXIT_FAILURE);
	data->img1->img = NULL;
	data->img2 = malloc(sizeof(t_mimg));
	if (!data->img2)
		return (EXIT_FAILURE);
	data->img2->img = NULL;
	data->height = 600;
	data->width = 800;
	data->active_img = 1;
	return (EXIT_SUCCESS);
}

void	player_init(t_player *pl)
{
	pl->posX = 350;
	pl->posY = 250;
	pl->dirX = -1;
	pl->dirY = 0;
	pl->viewX = 0;
	pl->viewY = 0.66;
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
