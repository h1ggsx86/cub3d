/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:15:05 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/01 11:11:54 by tnedel           ###   ########.fr       */
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

static int	ray_check_door(t_game *g)
{
	int			x;
	t_ray		r;
	t_player	p;

	p = *g->pl;
	x = 0;
	while (x < WIN_WIDTH)
	{
		set_var(&r, p, x);
		calculate_dist(&r, p);
		while (1)
		{
			if (dda_algo(g, &r))
				break ;
			if (!r.side)
				r.wall_dist = (r.side_d.x - r.delta_d.x) + 0.0001f;
			else
				r.wall_dist = (r.side_d.y - r.delta_d.y) + 0.0001f;
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
