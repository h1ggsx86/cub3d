/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:43:07 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/19 15:52:29 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int	ray, mx, my, mp, dof; double	rx, ry, ra, xo, yo;
	double aTan;
	double nTan;
	float	distF, distH, distV, hx, hy, vx, vy;
	float	lineH, lineO;
	int	side;

	ra = p.pa;
	ra -= ANGLE30;
	// printf("ra -> %f\n", ra);
	if (ra < 0)
		ra = ANGLE360 + ra;
	ray = 0;
	while (ray < WIN_WIDTH)
	{
		distH = 1000000;
		hx = p.posX;
		hy = p.posY;
		dof = 0;
		aTan = -1 / tanf(ra);
		// aTan = atanf(ra);
		// printf("aTan -> %f\n", aTan);
		if (ra > ANGLE180)
		{
			ry = (((int)p.posY >> 6) << 6) - 0.0001;
			rx = (p.posY - ry) * aTan + p.posX;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < ANGLE180)
		{
			ry = (((int)p.posY >> 6) << 6) + 64;
			rx = (p.posY - ry) * aTan + p.posX;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == ANGLE180)
		{
			rx = p.posX;
			ry = p.posY;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			mp = my * MAP_WIDTH + mx;
			// printf("mp -> %d\n", mp);
			if (mp > 0 && mp < MAP_WIDTH * MAP_HEIGHT && worldMap[mp] == 1)
			{
				hx = rx;
				hy = ry;
				distH = dist_to_wall(p.posX, p.posY, hx, hy);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		distV = 1000000;
		vx = p.posX;
		vy = p.posY;
		dof = 0;
		nTan = -tanf(ra);
		// aTan = atanf(ra);
		if (ra > ANGLE90 && ra < ANGLE270)
		{
			rx = (((int)p.posX >> 6) << 6) - 0.0001;
			ry = (p.posX - rx) * nTan + p.posY;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < ANGLE90 || ra > ANGLE270)
		{
			rx = (((int)p.posX >> 6) << 6) + 64;
			ry = (p.posX - rx) * nTan + p.posY;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = p.posX;
			ry = p.posY;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			mp = my * MAP_WIDTH + mx;
			if (mp > 0 && mp < MAP_WIDTH * MAP_HEIGHT && worldMap[mp] == 1)
			{
				vx = rx;
				vy = ry;
				distV = dist_to_wall(p.posX, p.posY, vx, vy);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (distV < distH)
		{
			rx = vx;
			ry = vy;
			distF = distV;
			side = g->d->color;
		}
		else
		{
			rx = hx;
			ry = hy;
			distF = distH;
			side = g->d->color / 2;
		}

		// printf("FINAL rx -> %f | ry -> %f\n", rx, ry);
		put_player_line(g, rx, ry);
		lineH = (MAP_SIZE * g->d->height) / distF;
		if (lineH > g->d->height)
		{
			lineH = g->d->height;
		}
		lineO = g->d->height / 2 - lineH /2;
		// printf("lineH -> %f\n", lineH);
		for (int i = 0; i < 5; i++)
		{
			put_vline(g, lineO, lineH + lineO, ray + i, side);
		}
		// put_vline(g, 0, lineH, ray + 530, 0x00dadadada);
		ray += 5;
		ra += 5;
		if (ra >= ANGLE360)
			ra -= ANGLE360;
	}
	return (EXIT_SUCCESS);
}
