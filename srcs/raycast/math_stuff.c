/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:34:30 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/04 11:40:00 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	r->door_side_d.x = r->side_d.x;
	r->door_side_d.y = r->side_d.y;
}

void	calculate_tex(t_ray *r, double wall_x)
{
	wall_x -= floor(wall_x);
	r->line_height = (int)(WIN_HEIGHT / r->wall_dist);
	r->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_end >= WIN_HEIGHT)
		r->draw_end = WIN_HEIGHT - 1;
	r->tex.x = (int)(wall_x * (double)64);
	if (r->side == 0 && r->ray.x < 0)
		r->tex.x = 64 - r->tex.x - 1;
	if (r->side == 1 && r->ray.y > 0)
		r->tex.x = 64 - r->tex.x - 1;
}

void	calculate_door(t_ray *r, t_player p)
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
	calculate_tex(r, wall_x);
}