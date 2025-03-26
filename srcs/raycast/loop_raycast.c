/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:27:31 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/26 11:38:02 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ray_loop(t_game *g, t_player p)
{
	int		x;
	int		hit;
	int		color;
	t_ray	*r;

	r = g->r;
	x = 0;
	while (x < WIN_WIDTH)
	{
		r->cameraX = 2 * (double)x / (double)WIN_WIDTH - 1;
		r->ray_x = (p.dirX + p.viewX * r->cameraX);
		r->ray_y = (p.dirY + p.viewY * r->cameraX);
		r->mapX = (int)p.x;
		r->mapY = (int)p.y;
		// printf("mapX -> %d\t| mapY -> %d\n", mapX, mapY);
		if (r->ray_x == 0)
			r->delta_distX = 1e30;
		else
			r->delta_distX = fabs(1 / r->ray_x);
		if (r->ray_y == 0)
			r->delta_distY = 1e30;
		else
			r->delta_distY = fabs(1 / r->ray_y);
		// printf("[DEBUG] ray_dirX    :\t%f | ray_dirY    :\t%f\n", ray_dirX, ray_dirY);
		// printf("[DEBUG] delta_distX :\t%f | delta_distY :\t%f\n", delta_distX, delta_distY);


		if (r->ray_x < 0)
		{
			r->stepX = -1;
			r->side_distX = (p.x - r->mapX) * r->delta_distX;
		}
		else
		{
			r->stepX = 1;
			r->side_distX = (r->mapX + 1.0 - p.x) * r->delta_distX;
		}
		if (r->ray_y < 0)
		{
			r->stepY = -1;
			r->side_distY = (p.y - r->mapY) * r->delta_distY;
		}
		else
		{
			r->stepY = 1;
			r->side_distY = (r->mapY + 1.0 - p.y) * r->delta_distY;
		}

		// printf("[DEBUG] side_distX :\t%f | side_distY :\t%f\n", side_distX, side_distY);
		hit = 0;
		while (hit == 0)
		{
			// printf("DDA LOOP\n");
			if (r->side_distX < r->side_distY)
			{
				// printf("!!! 0 !!!!!! 1 !!!\n");
				r->side_distX += r->delta_distX;
				r->mapX += r->stepX;
				r->side = 0;
			}
			else
			{
				// printf("!!! 2 !!!!!! 0 !!!\n");
				r->side_distY += r->delta_distY;
				r->mapY += r->stepY;
				r->side = 1;
			}
			if (r->mapY > 24 || r->mapX > 24)
				break ;
			if (worldMap[r->mapX][r->mapY] > 0)
				hit = 1;
		}

		// printf("final mapX -> %d\t| final mapY -> %d\n", mapX, mapY);
		// printf("[DEBUG] FINAL side_distX :\t%f | side_distY :\t%f\n", side_distX, side_distY);

		if (!r->side)
			r->wall_dist = (r->side_distX - r->delta_distX);
		else
			r->wall_dist = (r->side_distY - r->delta_distY);

		// printf("line_height %d\n", line_height);
		r->line_height = (int)(WIN_HEIGHT / r->wall_dist);
		r->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
		if (r->draw_start < 0)
			r->draw_start = 0;
		r->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
		if (r->draw_end >= WIN_HEIGHT)
			r->draw_end = WIN_HEIGHT - 1;
		
		color = g->d->color;
		if (r->side == 1)
			color = color / 2;
		// printf("draw_start %d draw_end %d\n", draw_start, draw_end);
		put_vline(g, r->draw_start, r->draw_end, x, color);
		// printf("x -> %d\n", x);
		put_player_line(g, p.x * 5 + r->ray_x * r->wall_dist * 5, p.y  * 5 + r->ray_y * r->wall_dist * 5);
		x++;
	}
	return (EXIT_SUCCESS);
}
