/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:43:07 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/12 17:49:40 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fix_angle(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

float	deg_to_rad(int a)
{
	return (a * PI / 180.0);
}

int	ray_loop(t_game *g, t_player p)
{
	int	ray, mx, my, mp, dof; double	rx, ry, ra, xo, yo;
	double aTan;

	ra = deg_to_rad(p.pa);
	ray = 0;
	while (ray < 1)
	{
		dof = 0;
		aTan = -1 / tanf(p.pa);
		printf("aTan -> %f\n", aTan);
		if (ra > PI)
		{
			printf("> PI\n");
			ry = (((int)p.posY >> 6) << 6) - 0.001;
			rx = (p.posY - ry) * aTan + p.posX;
			yo = -64;
			xo = 64 / tanf(p.pa);
		}
		if (ra < PI)
		{
			printf("< PI\n");
			ry = (((int)p.posY >> 6) << 6) + 64;
			rx = (p.posY - ry) * aTan + p.posX;
			yo = 64;
			xo = 64 / tanf(p.pa);
		}
		if (ra == 0 || ra == PI)
		{
			printf("== PI -> %f\n", ra);
			rx = p.posX;
			ry = p.posY;
			dof = 8;
		}
		printf("rx -> %f | ry -> %f\n", rx, ry);
		while (dof < 8)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			mp = my * MAP_WIDTH + mx;
			if (mp < MAP_WIDTH * MAP_HEIGHT && worldMap[mp] == 1)
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (rx > WIN_WIDTH)
			rx = WIN_WIDTH - 1;
		if (rx < 0)
			rx = 0;
		if (ry > WIN_HEIGHT)
			ry = WIN_HEIGHT - 1;
		if (ry < 0)
			ry = 0;
		printf("FINAL rx -> %f | ry -> %f\n", rx, ry);
		put_player_line(g, rx, ry);
		ray++;
	}
	return (EXIT_SUCCESS);
}
