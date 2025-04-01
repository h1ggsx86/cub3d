/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:57:25 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/01 09:10:27 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	draw_map(t_game *g)
{
	int			y;
	int			x;
	int			i;
	int			j;
	t_data		d;
	t_player	p;

	d = *g->d;
	p = *g->pl;
	y = p.y - 5;
	if (y < 0)
		y = 0;
	j = 0;
	while (j < 10)
	{
		i = 0;
		x = p.x - 5;
		if (x < 0)
			x = 0;
		while (i < 10)
		{
			if (d.mapper[y][x] == '1')
				d.color = 0x00dadada / 2;
			else
				d.color = 0x00dadada;
			put_square(&d, i * 10, j * 10, 10);
			x++;
			i++;
			if (x >= (int)d.width)
				break;
		}
		y++;
		j++;
		if (y >= (int)d.height)
			break;
	}
	d.color = 0x00ff00ff;
	put_square(&d, 5 * 10, 5 * 10, 5);
}
*/

void	draw_map(t_game *g)
{
	t_ivector	tile;
	t_ivector	index;
	t_data		d;
	t_player	p;

	d = *g->d;
	p = *g->pl;
	tile.y = (int)p.y - 5;
	index.y = 0;
	while (index.y < 10)
	{
		tile.x = (int)p.x - 5;
		index.x = 0;
		while (index.x < 10)
		{
			if ((tile.x < 0 || tile.y < 0) || (tile.x >= (int)d.width || tile.y >= (int)d.height))
				d.color = 0x00dadada / 2;
			else if (d.mapper[tile.y][tile.x] == '0' || d.mapper[tile.y][tile.x] == 'O')
				d.color = 0x00dadada;
			else
				d.color = 0x00dadada / 2;
			put_square(&d, index.x * 10 + 10, index.y * 10 + 10, 10);
			tile.x++;
			index.x++;
		}
		tile.y++;
		index.y++;
	}
	tile.x = 5 * 10 + 14;
	d.color = 0x00ff00ff;
	put_square(&d, 5 * 10 + 12, 5 * 10 + 12, 5);
	// put_player_circle(g, d.color, 5);
	put_player_line(g, tile.x, tile.x, tile.x + (p.dirX * 6), tile.x + (p.dirY * 6));
}