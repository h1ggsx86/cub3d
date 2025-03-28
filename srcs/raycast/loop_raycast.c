/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:27:31 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/28 19:18:05 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_var(t_ray *r, t_player p, int x)
{
	r->cameraX = 2 * (double)x / (double)WIN_WIDTH - 1;
	r->ray_x = (p.dirX + p.viewX * r->cameraX);
	r->ray_y = (p.dirY + p.viewY * r->cameraX);
	r->mapX = (int)p.x;
	r->mapY = (int)p.y;
	if (r->ray_x == 0)
		r->delta_distX = 1e30;
	else
		r->delta_distX = fabs(1 / r->ray_x);
	if (r->ray_y == 0)
		r->delta_distY = 1e30;
	else
		r->delta_distY = fabs(1 / r->ray_y);
}

static void	calculate_dist(t_ray *r, t_player p)
{
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
}

static void	draw_wall(t_game *g, t_ray *r, t_player p, int x)
{
	int	color;

	(void)p;
	if (!r->side)
		r->wall_dist = (r->side_distX - r->delta_distX) + 0.0001f;
	else
		r->wall_dist = (r->side_distY - r->delta_distY) + 0.0001f;
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
	put_vline(g, r->draw_start, r->draw_end, x, color);
	// put_player_line(g, p.x * 5 + r->ray_x * r->wall_dist * 5, p.y * 5 + r->ray_y * r->wall_dist * 5);
}

int	ray_loop(t_game *g, t_player p)
{
	int		x;
	int		hit;
	t_ray	*r;

	r = g->r;
	x = 0;
	while (x < WIN_WIDTH)
	{
		set_var(r, p, x);
		calculate_dist(r, p);
		hit = 0;
		while (hit == 0)
		{
			if (r->side_distX < r->side_distY)
			{
				r->side_distX += r->delta_distX;
				r->mapX += r->stepX;
				r->side = 0;
			}
			else
			{
				r->side_distY += r->delta_distY;
				r->mapY += r->stepY;
				r->side = 1;
			}
			// if (r->mapY > (int)g->d->height || r->mapX > (int)g->d->width)
			// 	break ;
			if (g->d->mapper[r->mapY][r->mapX] == '1')
				hit = 1;
		}
		draw_wall(g, r, p, x);
		x++;
	}
	return (EXIT_SUCCESS);
}
