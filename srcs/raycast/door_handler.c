/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:15:05 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/07 17:18:33 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*init_door_map(t_game *g, t_data *d)
{
	int		y;
	int		x;
	t_door	*door_map;

	door_map = (t_door *)ft_calloc(sizeof(t_door), d->height * d->width);
	if (!door_map)
		err_message(g, "malloc", "memory allocation failed", 2);
	y = 0;
	while (y < (int)d->height)
	{
		x = 0;
		while (x < (int)d->width)
		{
			if (d->mapper[y][x] == 'C')
				door_map[y * d->width + x].tex = 12;
			x++;
		}
		y++;
	}
	return (door_map);
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

static int	check_collisions(t_data *d, t_ray *r)
{
	int	hit;

	hit = 0;
	if (d->mapper[r->map.y][r->map.x] == 'C')
	{
		if (r->wall_dist < 6)
		{
			d->mapper[r->map.y][r->map.x] = 'O';
			hit = 1;
			d->door_map[r->map.y * d->width + r->map.x].tex = 12;
			d->door_map[r->map.y * d->width + r->map.x].way = -1;
			return (hit);
		}
	}
	else if (check_collisions_next(d, r, &hit))
		return (hit);
	return (EXIT_SUCCESS);
}

void	draw_door(t_game *g, t_ray *r, t_player p, int x)
{
	int		y;
	int		color;

	double (step) = 0.0;
	double (tex_pos) = 0.0;
	t_data *(d) = g->d;
	calculate_door(r, p, &step, &tex_pos);
	handle_framerate(g, g->d, r);
	y = 0;
	while (y < r->draw_start)
		y++;
	while (y < r->draw_end)
	{
		r->tex.y = (int)tex_pos;
		tex_pos += step;
		color = apply_intensity(pixel_color( \
			d->tex_door[d->door_map[r->map.y * d->width + r->map.x].tex], \
			r->tex.x, r->tex.y), r->intensity);
		if (color != 0)
			put_pixel(g->d, x, y, color);
		y++;
	}
}

int	ray_check_door(t_game *g)
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
			if (check_collisions(g->d, &r))
				return (EXIT_FAILURE);
		}
		x++;
	}
	return (EXIT_SUCCESS);
}
