/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:15:05 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/31 11:00:42 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ray_check_door(t_game *g)
{
	int			x;
	int			hit;
	t_ray		*r;
	t_player	p;

	r = g->r;
	p = *g->pl;
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
			if (!r->side)
				r->wall_dist = (r->side_distX - r->delta_distX) + 0.0001f;
			else
				r->wall_dist = (r->side_distY - r->delta_distY) + 0.0001f;
			if (g->d->mapper[r->mapY][r->mapX] == 'C')
			{
				if (r->wall_dist < 3)
				{
					g->d->mapper[r->mapY][r->mapX] = 'O';
					hit = 1;
					return (hit);
				}
			}
			else if (g->d->mapper[r->mapY][r->mapX] == 'O')
			{
				if (r->wall_dist < 3)
				{
					g->d->mapper[r->mapY][r->mapX] = 'C';
					hit = 1;
					return (hit);
				}
			}
		}
		x++;
	}
	return (EXIT_SUCCESS);
}

void	door_input(int keycode, t_game *g)
{
	if (keycode == XK_e)
	{
		if (ray_check_door(g))
			redraw_img(g);
	}
}