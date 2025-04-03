/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:27:31 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/03 19:12:41 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_var(t_ray *r, t_player p, int x)
{
	r->camera_x = 2 * (double)x / (double)WIN_WIDTH - 1;
	fvector_init(&r->ray, (p.dir.x + p.view.x * r->camera_x), \
				(p.dir.y + p.view.y * r->camera_x));
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

static void	chose_texture(t_data *d, t_ray *r, t_player p, double *wall_x)
{
	if (!r->side)
	{
		r->wall_dist = (r->side_d.x - r->delta_d.x) + 0.0001f;
		*wall_x = p.y + r->wall_dist * r->ray.y;
		if (r->ray.x > 0)
			d->the_chosen = *d->textures[WEST];
		else
			d->the_chosen = *d->textures[EAST];
	}
	else
	{
		r->wall_dist = (r->side_d.y - r->delta_d.y) + 0.0001f;
		*wall_x = p.x + r->wall_dist * r->ray.x;
		if (r->ray.y > 0)
			d->the_chosen = *d->textures[SOUTH];
		else
			d->the_chosen = *d->textures[NORTH];
	}
	// if (d->mapper[r->map.y][r->map.x] == 'C')
	// 	d->the_chosen = d->tex_door[12];
}

static void	draw_wall(t_game *g, t_ray *r, t_player p, int x)
{
	int		y;
	double	wall_x;
	double	step;
	double	tex_pos;

	chose_texture(g->d, r, p, &wall_x);
	calculate_tex(r, wall_x);
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
			put_pixel(g->d, x, y, pixel_color(g->d->the_chosen, r->tex.x, r->tex.y));
			y++;
		}
		put_pixel(g->d, x, y, g->d->ground_color);
		y++;
	}
}

void	door_loop(t_game *g, t_ray *r, t_player p, int x)
{
	r->door = 0;
	ivector_init(&r->map, (int)p.x, (int)p.y);
	fvector_init(&r->side_d, r->door_side_d.x, r->door_side_d.y);
	while (!r->door)
	{
		if (dda_algo(g, r))
			break;
		if (g->d->mapper[r->map.y][r->map.x] == '1')
			break;
		if (g->d->mapper[r->map.y][r->map.x] == 'O' || \
			g->d->mapper[r->map.y][r->map.x] == 'C')
			r->door = 1;
	}
	if (r->door)
		draw_door(g, r, p, x);
}

int	ray_loop(t_game *g, t_player p)
{
	int		x;
	int		hit;
	t_ray	r;

	init_ray(&r);
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
			if (g->d->mapper[r.map.y][r.map.x] == '1')// ||
				// g->d->mapper[r.map.y][r.map.x] == 'C')
				hit = 1;
		}
		draw_wall(g, &r, p, x);
		door_loop(g, &r, p, x);
		x++;
	}
	g->old_time = g->time;
	g->time = ft_get_time();
	return (EXIT_SUCCESS);
}
