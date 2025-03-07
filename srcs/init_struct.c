/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:16:20 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/07 19:41:59 by arotondo         ###   ########.fr       */
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
	data->all_text = false;
	data->i_text = 0;
	data->all_colors = false;
	data->north_path = NULL;
	data->south_path = NULL;
	data->west_path = NULL;
	data->east_path = NULL;
	return (0);
}

void	player_init(t_player *pl)
{
	pl->posX = 5;
	pl->posY = 5;
	// pl->posX = 220;
	// pl->posY = 120;
	pl->dirX = 1;
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
