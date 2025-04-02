/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:16:20 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/02 16:05:09 by arotondo         ###   ########.fr       */
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
	data->text_path[0] = NULL;
	data->text_path[1] = NULL;
	data->text_path[2] = NULL;
	data->text_path[3] = NULL;
	data->fd_texture[0] = 0;
	data->fd_texture[1] = 0;
	data->fd_texture[2] = 0;
	data->fd_texture[3] = 0;
	data->roof_color = 0;
	data->ground_color = 0;
	return (0);
}

int	color_init(t_data *data)
{
	t_color *color;

	color = malloc(sizeof(t_color));
	if (!color)
		return (1);
	data->colors = color;
	return (0);
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
	key_init(new);
	if (data_init(new->d))
		exit_game(new, 1);
	if (color_init(new->d))
		exit_game(new, 1);
	player_init(new->pl);
}
