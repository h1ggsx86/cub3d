/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:15:05 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/03 13:25:41 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	check_collisions(t_game *g, t_ray *r)
{
	int	hit;

	hit = 0;
	if (g->d->mapper[r->map.y][r->map.x] == 'C')
	{
		if (r->wall_dist < 3)
		{
			g->d->mapper[r->map.y][r->map.x] = 'O';
			hit = 1;
			return (hit);
		}
	}
	else if (g->d->mapper[r->map.y][r->map.x] == 'O')
	{
		if (r->wall_dist < 3)
		{
			g->d->mapper[r->map.y][r->map.x] = 'C';
			hit = 1;
			return (hit);
		}
	}
	return (EXIT_SUCCESS);
}


void	draw_door(t_game *g, t_ray *r, t_player p, int x)
{
	int		y;
	int		color;
	double	step;
	double	tex_pos;

	calculate_door(r, p);
	step = 1.0 * 64 / r->line_height;
	tex_pos = (r->draw_start - WIN_HEIGHT / 2 + r->line_height / 2) * step;
	y = 0;
	while (y < r->draw_start)
		y++;
	while (y < r->draw_end)
	{
		r->tex.y = (int)tex_pos;
		tex_pos += step;
		color = pixel_color(g->d->tex_door[0], r->tex.x, r->tex.y);
		if (color != 0)
			put_pixel(g->d, x, y, color);
		y++;
	}
}

static int	ray_check_door(t_game *g)
{
	int			x;
	t_ray		r;
	t_player	p;

	init_ray(&r);
	p = *g->pl;
	x = 0;
	while (x < WIN_WIDTH)
	{
		set_var(&r, p, x);
		calculate_dist(&r, p);
		r.door = 0;
		while (!r.door)
		{
			if (dda_algo(g, &r))
				break ;
			if (check_collisions(g, &r))
				return (EXIT_FAILURE);
		}
		x++;
	}
	return (EXIT_SUCCESS);
}

void	door_input(int keycode, t_game *g)
{
	if (keycode == XK_e)
		ray_check_door(g);
}
