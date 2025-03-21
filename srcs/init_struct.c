/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:16:20 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/21 13:51:23 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	tables_init(t_tables *t)
{
	int	i;
	float	radian;

	i = -1;
	while (++i <= ANGLE360)
	{
		radian = ((float)(i * PI) / (float)ANGLE180);
		t->sin_table[i] = (float)sinf(radian);
		t->isin_table[i] = (1.0f / t->sin_table[i]);
		t->cos_table[i] = (float)cosf(radian);
		t->icos_table[i] = (1.0f / t->cos_table[i]);
		t->tan_table[i] = (float)tanf(radian);
		t->itan_table[i] = (1.0f / t->tan_table[i]);
		if (i >= ANGLE90 && i < ANGLE270)
		{
			t->xstep_table[i] = (float)(MAP_SIZE / t->tan_table[i]);
			if (t->xstep_table[i] > 0)
				t->xstep_table[i] = -t->xstep_table[i];
		}
		else
		{
			t->xstep_table[i] = (float)(MAP_SIZE / t->tan_table[i]);
			if (t->xstep_table[i] < 0)
				t->xstep_table[i] = -t->xstep_table[i];
		}
		if (i >= ANGLE0 && i < ANGLE180)
		{
			t->ystep_table[i] = (float)(MAP_SIZE * t->tan_table[i]);
			if (t->ystep_table[i] > 0)
				t->ystep_table[i] = -t->ystep_table[i];
		}
		else
		{
			t->ystep_table[i] = (float)(MAP_SIZE * t->tan_table[i]);
			if (t->ystep_table[i] < 0)
				t->ystep_table[i] = -t->ystep_table[i];
		}
		// i = -ANGLE30;
		// while (i <= ANGLE30)
		// {
		// 	radian = (float)(i * PI) / (float)ANGLE180;
		// 	t->fish_table[i + ANGLE30] = (float)(1.0f / cosf(radian));
		// 	i++;
		// }
	}
}

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
	// pl->posX = 22;
	// pl->posY = 12;
	pl->posX = 140;
	pl->posY = 300;
	pl->pa = 0;
	pl->pdx = cosf(pl->pa);
	pl->pdy = sinf(pl->pa);
	pl->dirX = -1;
	pl->dirY = 0;
	pl->viewX = 0;
	pl->viewY = 0.66;
}

void	struct_init(t_game *new, t_data *data, t_player *pl, t_tables *t)
{
	new->init = NULL;
	new->win = NULL;
	new->d = data;
	new->pl = pl;
	tables_init(t);
	new->t = *t;
	if (data_init(new->d))
		exit_game(new, 1);
	player_init(new->pl);
}
