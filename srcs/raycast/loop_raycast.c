/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:27:31 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/02 13:29:26 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_var(t_ray *r, t_player p, int x)
{
	r->cameraX = 2 * (double)x / (double)WIN_WIDTH - 1;
	fvector_init(&r->ray, (p.dir.x + p.view.x * r->cameraX), \
				(p.dir.y + p.view.y * r->cameraX));
	ivector_init(&r->map, (int)p.x, (int)p.y);
	if (r->ray.x == 0)
		r->delta_d.x = 1e30;
	else
		r->delta_d.x = fabs(1 / r->ray.x);
	if (r->ray.y == 0)
		r->delta_d.y = 1e30;
	else
		r->delta_d.y = fabs(1 / r->ray.y);
}

void	calculate_dist(t_ray *r, t_player p)
{
	if (r->ray.x < 0)
	{
		r->step.x = -1;
		r->side_d.x = (p.x - r->map.x) * r->delta_d.x;
	}
	else
	{
		r->step.x = 1;
		r->side_d.x = (r->map.x + 1.0 - p.x) * r->delta_d.x;
	}
	if (r->ray.y < 0)
	{
		r->step.y = -1;
		r->side_d.y = (p.y - r->map.y) * r->delta_d.y;
	}
	else
	{
		r->step.y = 1;
		r->side_d.y = (r->map.y + 1.0 - p.y) * r->delta_d.y;
	}
}

static void	calculate_wall(t_ray *r, t_player p)
{
	double	wall_x;

	if (!r->side)
	{
		r->wall_dist = (r->side_d.x - r->delta_d.x) + 0.0001f;
		wall_x = p.y + r->wall_dist * r->ray.y;
	}
	else
	{
		r->wall_dist = (r->side_d.y - r->delta_d.y) + 0.0001f;
		wall_x = p.x + r->wall_dist * r->ray.x;
	}
	wall_x -= floor(wall_x);
	r->line_height = (int)(WIN_HEIGHT / r->wall_dist);
	r->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_end >= WIN_HEIGHT)
		r->draw_end = WIN_HEIGHT - 1;
	r->tex.x = (int)(wall_x * (double)64);
	if (r->side == 0 && r->ray.x > 0)
		r->tex.x = 64 - r->tex.x - 1;
	if (r->side == 0 && r->ray.y < 0)
		r->tex.x = 64 - r->tex.x - 1;
}

static void	draw_wall(t_game *g, t_ray *r, t_player p, int x)
{
	int		y;
	double	step;
	double	tex_pos;

	calculate_wall(r, p);
	step = 1.0 * 64 / r->line_height;
	tex_pos = (r->draw_start - WIN_HEIGHT / 2 + r->line_height / 2) * step;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		while (y < r->draw_start)
			put_pixel(g->d, x, y++, g->d->roof_color);
		while (y < r->draw_end)
		{
			r->tex.y = (int)tex_pos;
			tex_pos += step;
			put_pixel(g->d, x, y, pixel_color(g->text, r->tex.x, r->tex.y));
			y++;
		}
		put_pixel(g->d, x, y, g->d->ground_color);
		y++;
	}
}

static void	draw_door(t_game *g, t_ray *r, t_player p, int x)
{
	int		y;
	int		color;
	double	step;
	double	tex_pos;

	calculate_wall(r, p);
	step = 1.0 * 64 / r->line_height;
	tex_pos = (r->draw_start - WIN_HEIGHT / 2 + r->line_height / 2) * step;
	y = 0;
	while (y < r->draw_start)
		y++;
	while (y < r->draw_end)
	{
		r->tex.y = (int)tex_pos;
		tex_pos += step;
		color = pixel_color(g->text, r->tex.x, r->tex.y);
		if (color != 0)
			put_pixel(g->d, x, y, color);
		y++;
	}
}

int	ray_loop(t_game *g, t_player p)
{
	int		x;
	int		hit;
	t_ray	r;

	x = 0;
	while (x < WIN_WIDTH)
	{
		set_var(&r, p, x);
		calculate_dist(&r, p);
		hit = 0;
		while (hit == 0)
		{
			if (dda_algo(g, &r))
				break ;
			if (g->d->mapper[r.map.y][r.map.x] == '1' ||
				g->d->mapper[r.map.y][r.map.x] == 'C')
				hit = 1;
		}
		draw_wall(g, &r, p, x);
		set_var(&r, p, x);
		calculate_dist(&r, p);
		r.door = 0;
		while (!r.door)
		{
			if (dda_algo(g, &r))
				break ;
			if (g->d->mapper[r.map.y][r.map.x] == '1' ||
				g->d->mapper[r.map.y][r.map.x] == 'C')
				break ;
			if (g->d->mapper[r.map.y][r.map.x] == 'O')
				r.door = 1;
		}
		if (r.door)
		{
			draw_door(g, &r, p, x);
		}
		x++;
	}
	g->old_time = g->time;
	g->time = ft_get_time();
	return (EXIT_SUCCESS);
}
