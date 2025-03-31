/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:16:20 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/31 13:51:52 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	data_init(t_data *data)
{
	data->img_player = malloc(sizeof(t_mimg) * 2);
	if (!data->img_player)
		return (1);
	data->img_player[0].img = NULL;
	data->img_player[1].img = NULL;
	data->height = 0;
	data->width = 0;
	data->mapper = NULL;
	data->active_img = 1;
	data->color = 0x00dadada;
	data->i_colors = 0;
	data->i_text = 0;
	data->all_text = false;
	data->all_colors = false;
	data->map_parsed = false;
	data->north_path = NULL;
	data->south_path = NULL;
	data->west_path = NULL;
	data->east_path = NULL;
	data->n_text = 0;
	data->s_text = 0;
	data->w_text = 0;
	data->e_text = 0;
	data->roof_color = 0;
	data->ground_color = 0;
	return (0);
}

int	color_init(t_data *data)
{
	t_color *color;

	color = malloc(sizeof(t_color ));
	if (!color)
		return (1);
	data->colors = color;
	return (0);
}

void	player_init(t_player *pl)
{
	pl->x = 0;
	pl->y = 0;
	pl->dirX = 0;
	pl->dirY = 0;
	pl->viewX = 0.0f;
	pl->viewY = 0.0f;
}

void	struct_init(t_game *new, t_data *data, t_player *pl)
{
	new->init = NULL;
	new->win = NULL;
	new->d = data;
	new->pl = pl;
	new->win_height = WIN_HEIGHT;
	new->win_width = WIN_WIDTH;
	new->r = malloc(sizeof(t_ray));
	if (!new->r)
		exit_game(new, 1);
	if (data_init(new->d))
		exit_game(new, 1);
	if (color_init(new->d))
		exit_game(new, 1);
	player_init(new->pl);
}
