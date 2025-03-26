/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.obs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/26 11:05:51 by arotondo         ###   ########.fr       */
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
	// ray_loop(g, *g->pl);
	put_player_circle(g, g->d->color, 10);
	// put_player_line(g, g->pl->posX + g->pl->dirX * 50, g->pl->posY + g->pl->dirY * 50);
	if (g->d->active_img)
		g->d->active_img = 0;
	else
		g->d->active_img = 1;
}

void	moves_input(int keycode, t_game *g)
{
	double	old_dirX, old_viewX;
	t_player	*pl;

	pl = g->pl;
	old_dirX = pl->dirX;
	old_viewX = pl->viewX;
	// if (keycode == XK_a || keycode == XK_Left)
	// {
	// 	pl->posX -= 25;
	// 	redraw_img(g);
	// }
	if (keycode == XK_Right)
	{
		pl->dirX = pl->dirX * cosf(-3.0) - pl->dirY * sinf(-3.0);
		pl->dirY = old_dirX * sinf(-3.0) + pl->dirY * cosf(-3.0);
		pl->viewX = pl->viewX * cosf(-3.0) - pl->viewY * sinf(-3.0);
		pl->viewY = old_viewX * sinf(-3.0) + pl->viewY * cosf(-3.0);
		// printf("[DEBUG] dirX :\t%f\t| dirY :\t%f\n", pl->dirX, pl->dirY);
		redraw_img(g);
	}
	// else if (keycode == XK_d || keycode == XK_Right)
	// {
	// 	pl->posX += 25;
	// 	redraw_img(g);
	// }
	else if (keycode == XK_Left)
	{
		pl->dirX = pl->dirX * cosf(3.0) - pl->dirY * sinf(3.0);
		pl->dirY = old_dirX * sinf(3.0) + pl->dirY * cosf(3.0);
		pl->viewX = pl->viewX * cosf(3.0) - pl->viewY * sinf(3.0);
		pl->viewY = old_viewX * sinf(3.0) + pl->viewY * cosf(3.0);
		// printf("[DEBUG] dirX :\t%f\t| dirY :\t%f\n", pl->dirX, pl->dirY);
		redraw_img(g);
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		// if (!worldMap[(int)(pl->posX - pl->dirX * 00.33)][(int)pl->posY])
		// 	pl->posX -= pl->dirX * 00.33;
		// if (!worldMap[(int)pl->posX][(int)(pl->posY - pl->dirY * 00.33)])
		// 	pl->posY -= pl->dirY * 00.33;
		pl->posX -= pl->dirX * 5;
		pl->posY -= pl->dirY * 5;
		// printf("[DEBUG] posX :\t%f\t| posY :\t%f\n", pl->posX, pl->posY);
		redraw_img(g);
	}
	else if (keycode == XK_w || keycode == XK_Up)
	{
		// if (!worldMap[(int)(pl->posX + pl->dirX * 00.33)][(int)pl->posY])
		// 	pl->posX += pl->dirX * 00.33;
		// if (!worldMap[(int)pl->posX][(int)(pl->posY + pl->dirY * 00.33)])
		// 	pl->posY += pl->dirY * 00.33;
		pl->posX += pl->dirX * 5;
		pl->posY += pl->dirY * 5;
		// printf("[DEBUG] posX :\t%f\t| posY :\t%f\n", pl->posX, pl->posY);
		redraw_img(g);
	}
}
