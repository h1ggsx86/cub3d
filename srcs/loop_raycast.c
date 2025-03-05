/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:27:31 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/05 16:12:17 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ray_loop(t_game *g, t_player *pl)
{
	int	x;
	int	hit = 0;
	int	side;
	int	line_height;
	int	color;
	int	draw_start, draw_end;
	int	stepX, stepY;
	int	mapX = (int)pl->posX, mapY = (int)pl->posY;
	double	cameraX;
	double	wall_dist;
	double	ray_dirX, ray_dirY;
	double	side_distX, side_distY;
	double	delta_distX, delta_distY;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cameraX = 2 * x / (double)WIN_WIDTH - 1;
		ray_dirX = pl->dirX + pl->viewX * cameraX;
		ray_dirY = pl->dirY + pl->viewY * cameraX;

		delta_distX = abs(1 / ray_dirX);
		delta_distY = abs(1 / ray_dirY);

		if (ray_dirX < 0)
		{
			stepX = -1;
			side_distX = (pl->posX - mapX) * delta_distX;
		}
		else
		{
			stepX = 1;
			side_distX = (mapX + 1.0 - pl->posX) * delta_distX;
		}
		if (ray_dirY < 0)
		{
			stepY = -1;
			side_distY = (pl->posY - mapY) * delta_distY;
		}
		else
		{
			stepY = 1;
			side_distY = (mapY + 1.0 - pl->posY) * delta_distY;
		}

		while (!hit)
		{
			if (side_distX < side_distY)
			{
				side_distX += delta_distX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				side_distY += delta_distY;
				mapY += stepY;
				side = 1;
			}

			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		if (!side)
			wall_dist = (side_distX - delta_distX);
		else
			wall_dist = (side_distY - delta_distY);

		line_height = (int)(WIN_HEIGHT / wall_dist);
		draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		
		color = g->d->color;
		if (side == 1)
			color = color / 2;
	}
}