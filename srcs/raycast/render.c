/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:06:05 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/03 18:50:48 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_tile(t_ivector tile, t_data d, int *color)
{
	if ((tile.x < 0 || tile.y < 0) || \
		(tile.x >= (int)d.width || tile.y >= (int)d.height))
		*color = d.roof_color;
	else if (d.mapper[tile.y][tile.x] == '0' || d.mapper[tile.y][tile.x] == 'O')
		*color = d.ground_color;
	else if (d.mapper[tile.y][tile.x] == 'C')
		*color = d.ground_color / 2;
	else
		*color = d.roof_color;
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
			check_tile(tile, d, &g->color);
			put_square(g, index.x * 10 + 10, index.y * 10 + 10, 10);
			tile.x++;
			index.x++;
		}
		tile.y++;
		index.y++;
	}
	ivector_init(&tile, 64, 64);
	g->color = 0x00ff00ff;
	put_square(g, 62, 62, 5);
	put_player_line(g, tile, tile.x + (p.dir.x * 6), \
									tile.x + (p.dir.y * 6));
}

void	render_pov(t_game *g)
{
	int		y;
	int		x;
	int		color;

	x = 0;
	while (x < g->win_width)
	{
		y = 0;
		while (y < g->win_height)
		{
			color = pixel_color(g->d->pov, x, y);
			color = apply_intensity(color, 0.9);
			if (color != 0)
				put_pixel(g->d, x, y, color);
			y++;
		}
		x++;
	}
}

void	render_img(t_game *g)
{
	draw_floor(g, *g->pl);
	ray_loop(g, *g->pl);
	render_map(g, *g->pl, *g->d);
	render_pov(g);
	if (g->d->active_img)
		g->d->active_img = 0;
	else
		g->d->active_img = 1;
}
