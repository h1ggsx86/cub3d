/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:16:20 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/07 14:33:25 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_door_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 13)
	{
		data->tex_door[i].img = NULL;
		i++;
	}
}

void	data_init2(t_data *data)
{
	init_door_texture(data);
	data->img_player[0].img = NULL;
	data->img_player[1].img = NULL;
	data->textures[0] = NULL;
	data->textures[1] = NULL;
	data->textures[2] = NULL;
	data->textures[3] = NULL;
	data->text_path[0] = NULL;
	data->text_path[1] = NULL;
	data->text_path[2] = NULL;
	data->text_path[3] = NULL;
	data->floor.img = NULL;
	data->pov.img = NULL;
}

int	data_init(t_data *data)
{
	data->img_player = malloc(sizeof(t_mimg) * 2);
	if (!data->img_player)
		return (1);
	data->mapper = NULL;
	data->height = 0;
	data->width = 0;
	data->active_img = 1;
	data->i_doors = 0;
	data->i_colors = 0;
	data->i_text = 0;
	data->i_frames = 0;
	data->tex_way = 1;
	data->roof_color = 0;
	data->ground_color = 0;
	data->all_text = false;
	data->all_colors = false;
	data->map_parsed = false;
	data->fd_texture[0] = 0;
	data->fd_texture[1] = 0;
	data->fd_texture[2] = 0;
	data->fd_texture[3] = 0;
	data_init2(data);
	return (0);
}

int	color_init(t_data *data)
{
	t_color	*color;

	color = malloc(sizeof(t_color));
	if (!color)
		return (1);
	data->colors = color;
	return (0);
}

void	struct_init(t_game *new, t_data *data, t_player *pl)
{
	new->init = NULL;
	new->win = NULL;
	new->d = data;
	new->pl = pl;
	new->win_height = WIN_HEIGHT;
	new->win_width = WIN_WIDTH;
	new->time = 0;
	new->old_time = 0;
	new->color = 0x00dadada;
	new->fps = 0;
	key_init(new);
	if (data_init(new->d))
		exit_game(new, 1);
	if (color_init(new->d))
		exit_game(new, 1);
	player_init(new->pl);
}
