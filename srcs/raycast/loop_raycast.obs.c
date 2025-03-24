/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast.obs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:27:31 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/24 13:29:18 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ray_loop(t_game *g, t_player p)
{
	int	x;
	int	hit = 0;
	int	side;
	int	line_height;
	int	color;
	int	draw_start, draw_end;
	int	stepX, stepY;
	int	mapX, mapY;
	double	cameraX;
	double	wall_dist;
	double	ray_dirX, ray_dirY;
	double	side_distX, side_distY;
	double	delta_distX, delta_distY;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cameraX = 2 * (double)x / (double)WIN_WIDTH - 1;
		ray_dirX = (p.dirX + p.viewX * cameraX);
		ray_dirY = (p.dirY + p.viewY * cameraX);
		mapX = (int)p.posX;
		mapY = (int)p.posY;
		printf("mapX -> %d\t| mapY -> %d\n", mapX, mapY);
		if (ray_dirX == 0)
			delta_distX = 1e30;
		else
			delta_distX = fabs(1 / ray_dirX);
		if (ray_dirY == 0)
			delta_distY = 1e30;
		else
			delta_distY = fabs(1 / ray_dirY);
		// printf("[DEBUG] ray_dirX    :\t%f | ray_dirY    :\t%f\n", ray_dirX, ray_dirY);
		// printf("[DEBUG] delta_distX :\t%f | delta_distY :\t%f\n", delta_distX, delta_distY);


		if (ray_dirX < 0)
		{
			stepX = -1;
			side_distX = (p.posX - (double)mapX) * delta_distX;
		}
		else
		{
			stepX = 1;
			side_distX = ((double)mapX + 1.0 - p.posX) * delta_distX;
		}
		if (ray_dirY < 0)
		{
			stepY = -1;
			side_distY = (p.posY - (double)mapY) * delta_distY;
		}
		else
		{
			stepY = 1;
			side_distY = ((double)mapY + 1.0 - p.posY) * delta_distY;
		}

		// printf("[DEBUG] side_distX :\t%f | side_distY :\t%f\n", side_distX, side_distY);

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

		// printf("[DEBUG] FINAL side_distX :\t%f | side_distY :\t%f\n", side_distX, side_distY);

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
		put_vline(g, draw_start, draw_end, x, color);
		// put_player_line(g, (p.posX + wall_dist) * 5, (p.posY + wall_dist) * 5);
		x++;
	}
	return (EXIT_SUCCESS);
}
