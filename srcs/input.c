/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/12 15:36:17 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	redraw_img(t_game *g)
{
	t_player	p;
	t_mimg	*img;

	p = *g->pl;
	if (g->d->active_img)
		img = g->d->img_map + 1;
	else
		img = g->d->img_map;
	mlx_destroy_image(g->init, img->img);
	img->img = NULL;
	if (img_init(img, g->d, g->init))
		exit_game(g, 1);
	draw_map(g);
	ray_loop(g, *g->pl);
	put_player_circle(g, g->d->color, 5);
	put_player_line(g, p.posX + p.pdx * 5, p.posY + p.pdy * 5);
	if (g->d->active_img)
		g->d->active_img = 0;
	else
		g->d->active_img = 1;
}

void	moves_input(int keycode, t_game *g)
{
	t_player	*p;

	p = g->pl;
	if (keycode == XK_Right)
	{
		p->pa += 0.1;
		if (p->pa < 0)
			p->pa -= 2 * PI;
		p->pdx = cosf(p->pa) * 5;
		p->pdy = sinf(p->pa) * 5;
		// printf("[DEBUG] pa :\t%f | pdx :\t%f | pdy :\t%f\n", p->pa, p->pdx, p->pdy);
		redraw_img(g);
	}
	else if (keycode == XK_Left)
	{
		p->pa -= 0.1;
		if (p->pa < 0)
			p->pa += 2 * PI;
		p->pdx = cosf(p->pa) * 5;
		p->pdy = sinf(p->pa) * 5;
		// printf("[DEBUG] pa :\t%f | pdx :\t%f | pdy :\t%f\n", p->pa, p->pdx, p->pdy);
		redraw_img(g);
	}
	else if (keycode == XK_s)
	{
		p->posX -= p->pdx * 5;
		p->posY -= p->pdy * 5;
		// printf("[DEBUG] pa :\t%f | pdx :\t%f | pdy :\t%f\n", p->pa, p->pdx, p->pdy);
		redraw_img(g);
	}
	else if (keycode == XK_w)
	{
		p->posX += p->pdx * 5;
		p->posY += p->pdy * 5;
		// printf("[DEBUG] pa :\t%f | pdx :\t%f | pdy :\t%f\n", p->pa, p->pdx, p->pdy);
		redraw_img(g);
	}
	// if (keycode == XK_a || keycode == XK_Left)
	// {
	// 	pl->posX -= 25;
	// 	redraw_img(g);
	// }
	// else if (keycode == XK_d || keycode == XK_Right)
	// {
	// 	pl->posX += 25;
	// 	redraw_img(g);
	// }
}