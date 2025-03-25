/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/02/28 13:27:31 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/25 12:35:51 by tnedel           ###   ########.fr       */
=======
/*   Created: 2025/03/10 10:43:07 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/24 13:29:08 by arotondo         ###   ########.fr       */
>>>>>>> origin
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

<<<<<<< HEAD
	x = 0;
	while (x < WIN_WIDTH)
=======
	int	x_index, y_index;

	float d_h_grid_h, d_v_grid_h;

		d_v_grid_h = 0;
	ra = p.pa;
	ra -= ANGLE30;
	// printf("ra -> %f\n", ra);
	if (ra < 0)
		ra = ANGLE360 + ra;
	ray = 0;
	while (ray < WIN_WIDTH)
>>>>>>> origin
	{
		cameraX = 2 * (double)x / (double)WIN_WIDTH - 1;
		ray_dirX = (p.dirX + p.viewX * cameraX);
		ray_dirY = (p.dirY + p.viewY * cameraX);
		mapX = (int)p.posX;
		mapY = (int)p.posY;
		// printf("mapX -> %d\t| mapY -> %d\n", mapX, mapY);
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
			side_distX = (p.posX - mapX) * delta_distX;
		}
		else
		{
			stepX = 1;
			side_distX = (mapX + 1.0 - p.posX) * delta_distX;
		}
		if (ray_dirY < 0)
		{
			stepY = -1;
			side_distY = (p.posY - mapY) * delta_distY;
		}
		else
		{
			stepY = 1;
			side_distY = (mapY + 1.0 - p.posY) * delta_distY;
		}

		// printf("[DEBUG] side_distX :\t%f | side_distY :\t%f\n", side_distX, side_distY);
		hit = 0;
		while (hit == 0)
		{
			// printf("DDA LOOP\n");
			if (side_distX < side_distY)
			{
<<<<<<< HEAD
				// printf("!!! 0 !!!!!! 1 !!!\n");
				side_distX += delta_distX;
				mapX += stepX;
				side = 0;
=======
				x_index = (int)(x_inter / MAP_SIZE);
				y_index = h_grid / MAP_SIZE;
				if ((x_index >= MAP_WIDTH) ||
					(y_index >= MAP_HEIGHT) ||
					(x_index < 0) | (y_index < 0))
				{
					d_h_grid_h = 9999999;
					break;
				}
				else if (worldMap[y_index * MAP_WIDTH + x_index] != 0)
				{
					d_h_grid_h = (x_inter - p.posX) * g->t.icos_table[(int)ra];
					break;
				}
				else
				{
					x_inter += d_x_inter;
					y_inter += d_h_grid;
				}
>>>>>>> origin
			}
			else
			{
<<<<<<< HEAD
				// printf("!!! 2 !!!!!! 0 !!!\n");
				side_distY += delta_distY;
				mapY += stepY;
				side = 1;
=======
				x_index = (v_grid / MAP_SIZE);
				y_index = (int)(y_inter / MAP_SIZE);
				if ((x_index >= MAP_WIDTH) ||
					(y_index >= MAP_HEIGHT) ||
					(x_index < 0) | (y_index < 0))
				{
					d_h_grid_h = 9999999;
					break;
				}
				else if (worldMap[y_index * MAP_WIDTH + x_index] != 0)
				{
					d_v_grid_h = (y_inter - p.posY) * g->t.isin_table[(int)ra];
					break;
				}
				else
				{
					y_inter += d_y_inter;
					v_grid += d_v_grid;
				}
>>>>>>> origin
			}
			if (mapY > 24 || mapX > 24)
				break ;
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		// printf("final mapX -> %d\t| final mapY -> %d\n", mapX, mapY);
		// printf("[DEBUG] FINAL side_distX :\t%f | side_distY :\t%f\n", side_distX, side_distY);

		if (!side)
			wall_dist = (side_distX - delta_distX);
		else
<<<<<<< HEAD
			wall_dist = (side_distY - delta_distY);

		// printf("wall_dist %f\n", wall_dist);
		line_height = (int)(WIN_HEIGHT / wall_dist);
		// printf("line_height %d\n", line_height);
		draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		
		color = g->d->color;
		if (side == 1)
			color = color / 2;
		// printf("draw_start %d draw_end %d\n", draw_start, draw_end);
		put_vline(g, draw_start, draw_end, x, color);
		// printf("x -> %d\n", x);
		put_player_line(g, p.posX * 5 + ray_dirX * wall_dist * 5, p.posY  * 5 + ray_dirY * wall_dist * 5);
		x++;
=======
		{
			dist = d_v_grid_h;
			color = g->d->color / 2;
		}
		int	proj_wall = (int)(MAP_SIZE * (float)277 / dist);
		bottom_wall = WIN_HEIGHT / 2 + (int)(proj_wall * 0.5f);
		top_wall = WIN_HEIGHT - bottom_wall;
		// printf("[DEBUG] bottom_wall -> %d | top_wall -> %d\n", bottom_wall, top_wall);
		// printf("[DEBUG] ray         -> %d\n", ray);
		if (bottom_wall >= WIN_HEIGHT)
			bottom_wall = WIN_HEIGHT - 1;
		for (int x = 0; x < 5; x++)
		{
			// printf("[DEBUG] color     -> %d\n", color);
			put_vline(g, top_wall, proj_wall, ray + x, color);
		}
		ra += 5;
		if (ra >= ANGLE360)
			ra -= ANGLE360;
		ray += 5;
>>>>>>> origin
	}
	return (EXIT_SUCCESS);
}
