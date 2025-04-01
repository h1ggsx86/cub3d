/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:27:31 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/01 09:49:44 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_var(t_ray *r, t_player p, int x)
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

void	calculate_dist(t_ray *r, t_player p)
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
	// int	color;

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

	double	wallX;
	if (r->side == 0)
		wallX = p.y + r->wall_dist * r->ray_y;
	else
		wallX = p.x + r->wall_dist * r->ray_x;
	wallX -= floor(wallX);
	int texX = (int)(wallX * (double)64);
	if (r->side == 0 && r->ray_x > 0)
		texX = 64 - texX - 1;
	if (r->side == 0 && r->ray_y < 0)
		texX = 64 - texX - 1;
	double step = 1.0 * 64 / r->line_height;
	double texPos = (r->draw_start - WIN_HEIGHT / 2 + r->line_height / 2 ) * step;
	int	texY;
	int	y = 0;
	while (y < WIN_HEIGHT)
	{
		while (y < r->draw_start)
			put_pixel(g->d, x, y++, g->d->roof_color);
		while (y < r->draw_end)
		{
			texY = (int)texPos;
			texPos += step;
			put_pixel(g->d, x, y, pixel_color(g->text, texX, texY));
			y++;
		}
		put_pixel(g->d, x, y, g->d->ground_color);
		y++;
	}

	// put_vline(g, r->draw_start, r->draw_end, x, color);
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
			if ((r->mapY >= (int)g->d->height || r->mapX >= (int)g->d->width) ||
				(r->mapY < 0 || r->mapX < 0))
				break ;
			if (g->d->mapper[r->mapY][r->mapX] == '1' ||
				g->d->mapper[r->mapY][r->mapX] == 'C')
				hit = 1;
		}
		draw_wall(g, r, p, x);
		x++;
	}
	g->old_time = g->time;
	g->time = ft_get_time();
	return (EXIT_SUCCESS);
}
