/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_helper_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:43:25 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/08 10:37:00 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	handle_framerate(t_game *g, t_data *d, t_ray *r)
{
	if (g->fps % 4 == 0 && g->is_active)
	{
		d->door_map[r->map.y * d->width + r->map.x].tex += \
			d->door_map[r->map.y * g->d->width + r->map.x].way;
		if (d->door_map[r->map.y * g->d->width + r->map.x].tex < 0)
			d->door_map[r->map.y * g->d->width + r->map.x].tex = 0;
		if (d->door_map[r->map.y * d->width + r->map.x].tex > 12)
			d->door_map[r->map.y * d->width + r->map.x].tex = 12;
		g->is_active = false;
	}
}

int	check_collisions_next(t_data *d, t_ray *r, int *hit, t_player p)
{
	if (d->mapper[r->map.y][r->map.x] == 'O')
	{
		if (!r->side)
		{
			r->wall_dist = (r->side_d.x - r->delta_d.x) + 0.0001f;
			r->wall_x = p.y + r->wall_dist * r->ray.y;
		}
		else
		{
			r->wall_dist = (r->side_d.y - r->delta_d.y) + 0.0001f;
			r->wall_x = p.x + r->wall_dist * r->ray.x;
		}
		if (r->wall_dist < 2)
		{
			d->mapper[r->map.y][r->map.x] = 'C';
			*hit = 1;
			d->door_map[r->map.y * d->width + r->map.x].tex = 0;
			d->door_map[r->map.y * d->width + r->map.x].way = 1;
			return (*hit);
		}
	}
	return (EXIT_SUCCESS);
}

void	door_input(int keycode, t_game *g)
{
	if (keycode == XK_e)
		ray_check_door(g);
}
