/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:06:05 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/08 15:11:22 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_pov(t_game *g)
{
	int		y;
	int		x;
	int		color;

	x = 0;
	while (x < g->win_width)
	{
		y = 0;
		while (y < g->win_height)
		{
			color = pixel_color(g->d->pov, x, y);
			color = apply_intensity(color, 0.9);
			if (color != 0)
				put_pixel(g->d, x, y, color);
			y++;
		}
		x++;
	}
}

void	render_img(t_game *g)
{
	ray_loop(g, *g->pl);
	render_pov(g);
	if (g->d->active_img)
		g->d->active_img = 0;
	else
		g->d->active_img = 1;
}
