/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/05 16:12:10 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	redraw_img(t_game *g)
{
	t_mimg	*img;

	if (g->d->active_img)
		img = g->d->img_map + 1;
	else
		img = g->d->img_map;
	mlx_destroy_image(g->init, img->img);
	img->img = NULL;
	if (img_init(img, g->d, g->init))
		exit_game(g, 1);
	put_player_circle(g, g->d->color, 25);
	if (g->d->active_img)
		g->d->active_img = 0;
	else
		g->d->active_img = 1;
}

void	moves_input(int keycode, t_game *g)
{
	t_player	*pl;

	pl = g->pl;
	if (keycode == XK_a || keycode == XK_Left)
	{
		pl->posX -= 25;
		redraw_img(g);
	}
	if (keycode == XK_d || keycode == XK_Right)
	{
		pl->posX += 25;
		redraw_img(g);
	}
	if (keycode == XK_s || keycode == XK_Down)
	{
		pl->posY += 25;
		redraw_img(g);
	}
	if (keycode == XK_w || keycode == XK_Up)
	{
		pl->posY -= 25;
		redraw_img(g);
	}
}