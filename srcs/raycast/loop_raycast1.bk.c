/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast1.bk.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:43:07 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/25 18:47:46 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycast.h"

int	fix_angle(int a)
{
	if (a > 359)
		a = 0;
	if (a < 0)
		a = 359;
	return (a);
}

float	deg_to_rad(int a)
{
	return (fix_angle(a) * PI / 180.0);
}

float	dist_to_wall(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int	ray_loop(t_game *g, t_player p)
{
	float	ra;
	int		ray;
	int	h_grid, v_grid;
	int	d_h_grid, d_v_grid;
	float	x_inter, y_inter;
	float	d_x_inter, d_y_inter;
	int	top_wall;
	int	bottom_wall;
	float	dist;

	int	x_index, y_index;

	float d_h_grid_h, d_v_grid_h;

	ra = p.pa;
	ra -= ANGLE30;
	// printf("ra -> %f\n", ra);
	if (ra < 0)
		ra = ANGLE360 + ra;
	ray = 0;
	while (ray < WIN_WIDTH)
	{
		if (ra > ANGLE0 && ra < ANGLE180)
		{
			h_grid = (p.posY / MAP_SIZE) * MAP_SIZE + MAP_SIZE;
			d_h_grid = MAP_SIZE;
			float xtemp = g->t.itan_table[(int)ra] * (h_grid - p.posY);
			x_inter = xtemp + p.posX;
		}
		else
		{
			h_grid = (p.posY / MAP_SIZE) * MAP_SIZE;
			d_h_grid = -MAP_SIZE;
			float xtemp = g->t.itan_table[(int)ra] * (h_grid - p.posY);
			x_inter = xtemp + p.posX;
			h_grid--;
		}
		if (ra == ANGLE0 || ra == ANGLE180)
			d_h_grid_h = 9999999;
		else
		{
			d_x_inter = g->t.xstep_table[(int)ra];
			while (1)
			{
				x_index = (int)(x_inter / MAP_SIZE);
				y_index = h_grid / MAP_SIZE;
				if ((x_index >= MAP_WIDTH) ||
					(y_index >= MAP_HEIGHT) ||
					x_index < 0 | y_index < 0)
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
			}
		}
		if (ra < ANGLE90 || ra > ANGLE270)
		{
			v_grid = MAP_SIZE + (p.posX / MAP_SIZE) * MAP_SIZE;
			d_v_grid = MAP_SIZE;
			float ytemp = g->t.tan_table[(int)ra] * (v_grid - p.posX);
			y_inter = ytemp + p.posY;
		}
		else
		{
			v_grid = (p.posX / MAP_SIZE) * MAP_SIZE;
			d_v_grid = -MAP_SIZE;
			float ytemp = g->t.tan_table[(int)ra] * (v_grid - p.posX);
			y_inter = ytemp + p.posY;
			v_grid--;
		}
		if (ra == ANGLE90 || ra == ANGLE270)
			d_v_grid_h = 9999999;
		else
		{
			d_y_inter = g->t.ystep_table[(int)ra];
			while (1)
			{
				x_index = (v_grid / MAP_SIZE);
				y_index = (int)(y_inter / MAP_SIZE);
				if ((x_index >= MAP_WIDTH) ||
					(y_index >= MAP_HEIGHT) ||
					x_index < 0 | y_index < 0)
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
			}
		}
		// put_player_line(g, d_v_grid_h, d_h_grid_h);
		int	color;
		if (d_h_grid_h < d_v_grid_h)
		{
			dist = d_h_grid_h;
			color = g->d->color;
		}
		else
		{
			dist = d_v_grid_h;
			color = g->d->color / 2;
		}
		printf("[DEBUG] dist        -> %f\n", dist);
		int	proj_wall = (int)(MAP_SIZE * (float)277 / dist);
		printf("[DEBUG] proj_wall   -> %d\n", proj_wall);
		bottom_wall = WIN_HEIGHT / 2 + (int)(proj_wall * 0.5f);
		top_wall = WIN_HEIGHT - bottom_wall;
		printf("[DEBUG] bottom_wall -> %d | top_wall -> %d\n", bottom_wall, top_wall);
		printf("[DEBUG] ray         -> %d\n", ray);
		if (bottom_wall >= WIN_HEIGHT)
			bottom_wall = WIN_HEIGHT - 1;
		else if (bottom_wall < 0)
			bottom_wall = 0;
		printf("[DEBUG] color       -> %d\n", color);
		for (int x = 0; x < 5; x++)
			put_vline(g, top_wall, proj_wall, ray + x, color);
		ra += 5;
		if (ra >= ANGLE360)
			ra -= ANGLE360;
		ray += 5;
	}
	return (EXIT_SUCCESS);
}
