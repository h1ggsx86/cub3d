/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:06:05 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/01 12:14:43 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_tile(t_ivector tile, t_data d, int *color)
{
	if ((tile.x < 0 || tile.y < 0) || \
		(tile.x >= (int)d.width || tile.y >= (int)d.height))
		*color = 0x00dadada / 2;
	else if (d.mapper[tile.y][tile.x] == '0' || d.mapper[tile.y][tile.x] == 'O')
		*color = 0x00dadada;
	else if (d.mapper[tile.y][tile.x] == 'C')
		*color = 0xffaa32d5;
	else
		*color = 0x00dadada / 2;
}

void	render_map(t_game *g, t_player p, t_data d)
{
	t_ivector	tile;
	t_ivector	index;

	tile.y = (int)p.y - 5;
	index.y = 0;
	while (index.y < 10)
	{
		tile.x = (int)p.x - 5;
		index.x = 0;
		while (index.x < 10)
		{
			check_tile(tile, d, &d.color);
			put_square(&d, index.x * 10 + 10, index.y * 10 + 10, 10);
			tile.x++;
			index.x++;
		}
		tile.y++;
		index.y++;
	}
	ivector_init(&tile, 64, 64);
	d.color = 0x00ff00ff;
	put_square(&d, 62, 62, 5);
	put_player_line(g, tile, tile.x + (p.dir.x * 6), \
									tile.x + (p.dir.y * 6));
}

void	render_img(t_game *g)
{
	t_player	p;
	t_mimg		*img;

	p = *g->pl;
	if (g->d->active_img)
		img = g->d->img_player + 1;
	else
		img = g->d->img_player;
	ray_loop(g, *g->pl);
	render_map(g, *g->pl, *g->d);
	if (g->d->active_img)
		g->d->active_img = 0;
	else
		g->d->active_img = 1;
}
