/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/02/28 16:21:53 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	redraw_img(t_game *g)
{
	t_mimg	*img;

	if (g->d->active_img)
		img = g->d->img2;
	else
		img = g->d->img1;
	mlx_destroy_image(g->init, img->img);
	img->img = NULL;
	if (img_init(img, g->d, g->init))
		exit_game(g, 1);
	put_player_circle(g->d, g->pl, 0x00f187b3 , 100);
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
		pl->posX -= 10;
		redraw_img(g);
	}
	if (keycode == XK_d || keycode == XK_Right)
	{
		pl->posX += 10;
		redraw_img(g);
	}
	if (keycode == XK_s || keycode == XK_Down)
	{
		pl->posY += 10;
		redraw_img(g);
	}
	if (keycode == XK_w || keycode == XK_Up)
	{
		pl->posY -= 10;
		redraw_img(g);
	}
}