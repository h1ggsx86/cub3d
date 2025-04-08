/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:27:31 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/08 15:08:58 by tnedel           ###   ########.fr       */
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

static void	chose_texture(t_data *d, t_ray *r, t_player p)
{
	if (!r->side)
	{
		r->wall_dist = (r->side_d.x - r->delta_d.x) + 0.0001f;
		r->wall_x = p.y + r->wall_dist * r->ray.y;
		if (r->ray.x > 0)
			d->the_chosen = *d->textures[WEST];
		else
			d->the_chosen = *d->textures[EAST];
	}
	else
	{
		r->wall_dist = (r->side_d.y - r->delta_d.y) + 0.0001f;
		r->wall_x = p.x + r->wall_dist * r->ray.x;
		if (r->ray.y > 0)
			d->the_chosen = *d->textures[SOUTH];
		else
			d->the_chosen = *d->textures[NORTH];
	}
}

static void	draw_wall(t_game *g, t_ray *r, t_player p, int x)
{
	int		color;
	double	step;
	double	tex_pos;

	chose_texture(g->d, r, p);
	calculate_tex(r, r->wall_x);
	r->intensity = 1 / r->wall_dist * MULTIPLIER;
	if (r->intensity > 1)
		r->intensity = 1;
	step = 1.0 * 64 / r->line_height;
	tex_pos = (r->draw_start - WIN_HEIGHT / 2 + r->line_height / 2) * step;
	int (y) = -1;
	while (++y < r->draw_start)
		put_pixel(g->d, x, y, apply_intensity(g->d->roof_color, r->intensity));
	while (y <= r->draw_end)
	{
		r->tex.y = (int)tex_pos;
		tex_pos += step;
		color = pixel_color(g->d->the_chosen, r->tex.x, r->tex.y);
		put_pixel(g->d, x, y, apply_intensity(color, r->intensity));
		y++;
	}
	while (++y < WIN_HEIGHT)
		put_pixel(g->d, x, y, \
			apply_intensity(g->d->ground_color, r->intensity));
}

int	dda_algo(t_game *g, t_ray *r)
{
	if (r->side_d.x < r->side_d.y)
	{
		r->side_d.x += r->delta_d.x;
		r->map.x += r->step.x;
		r->side = 0;
	}
	else
	{
		r->side_d.y += r->delta_d.y;
		r->map.y += r->step.y;
		r->side = 1;
	}
	if ((r->map.y >= (int)g->d->height || r->map.x >= (int)g->d->width) || \
		(r->map.y < 0 || r->map.x < 0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ray_loop(t_game *g, t_player p)
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
			if (g->d->mapper[r.map.y][r.map.x] == '1')
				hit = 1;
		}
		draw_wall(g, &r, p, x);
		x++;
	}
	g->old_time = g->time;
	g->time = ft_get_time();
}
