/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:37:04 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/08 10:37:04 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

static void	calculate_floor(t_floor *f, t_player p, int y)
{
	fvector_init(&f->ray0, p.dir.x - p.view.x, p.dir.y - p.view.y);
	fvector_init(&f->ray1, p.dir.x + p.view.x, p.dir.y + p.view.y);
	f->pos = y - WIN_HEIGHT / 2;
	f->pos_z = 0.5 * WIN_HEIGHT;
	f->row_dist = f->pos_z / f->pos;
	fvector_init(&f->f_step, f->row_dist * (f->ray1.x - f->ray0.x) / WIN_WIDTH, \
				f->row_dist * (f->ray1.y - f->ray0.y) / WIN_WIDTH);
	fvector_init(&f->floor, p.x + f->row_dist * f->ray0.x, \
				p.y + f->row_dist * f->ray0.y);
	f->intensity = 1 / fabs(f->row_dist) * MULTIPLIER;
	if (f->intensity > 1)
		f->intensity = 1;
}

void	draw_floor(t_game *g, t_player p)
{
	int		y;
	int		x;
	int		color;
	t_floor	f;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		calculate_floor(&f, p, y);
		x = -1;
		while (++x < WIN_WIDTH)
		{
			ivector_init(&f.tile, (int)f.floor.x, (int)f.floor.y);
			ivector_init(&f.tex, \
							(int)(64 * (f.floor.x - f.tile.x)) & (64 - 1), \
							(int)(64 * (f.floor.y - f.tile.y)) & (64 - 1));
			f.floor.x += f.f_step.x;
			f.floor.y += f.f_step.y;
			color = apply_intensity(pixel_color(g->d->floor, f.tex.x, f.tex.y), \
												f.intensity);
			put_pixel(g->d, x, y, color);
			color = apply_intensity(g->d->roof_color, f.intensity);
			put_pixel(g->d, x, WIN_HEIGHT - y - 1, color);
		}
	}
}
