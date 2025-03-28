/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/28 09:25:49 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	redraw_img(t_game *g)
{
	t_player	p;
	t_mimg		*img;

	p = *g->pl;
	if (g->d->active_img)
		img = g->d->img_player + 1;
	else
		img = g->d->img_player;
	mlx_destroy_image(g->init, img->img);
	img->img = NULL;
	if (img_init(img, g, g->init))
		exit_game(g, 1);
	// draw_map(g);
	ray_loop(g, *g->pl);
	// put_player_circle(g, g->d->color, 5);
	// put_player_line(g, p.posX + p.dirX * 10, p.posY + p.dirY * 10);
	if (g->d->active_img)
		g->d->active_img = 0;
	else
		g->d->active_img = 1;
}

void	camera_move(t_game *g, int way, double rot)
{
	t_player	*p;

	p = g->pl;
	double oldDirX = p->dirX;
	p->dirX = p->dirX * cosf(rot * way) - p->dirY * sinf(rot * way);
	p->dirY = oldDirX * sinf(rot * way) + p->dirY * cosf(rot * way);
	double oldPlaneX = p->viewX;
	p->viewX = p->viewX * cosf(rot * way) - p->viewY * sinf(rot * way);
	p->viewY = oldPlaneX * sinf(rot * way) + p->viewY * cosf(rot * way);
	redraw_img(g);
}

void	moves_input(int keycode, t_game *g)
{
	t_player	*p;

	p = g->pl;
	if (keycode == XK_Left)
		camera_move(g, 1, ROT_SPEED);
	else if (keycode == XK_Right)
		camera_move(g, -1, ROT_SPEED);
	else if (keycode == XK_w)
	{
		if (g->d->mapper[(int)(p->y + p->dirY * MOVE_SPEED)][(int)p->x] != '1')
			p->y += p->dirY * MOVE_SPEED;
		if (g->d->mapper[(int)p->y][(int)(p->x + p->dirX * MOVE_SPEED)] != '1')
			p->x += p->dirX * MOVE_SPEED;
		redraw_img(g);
	}
	else if (keycode == XK_s)
	{
		if (g->d->mapper[(int)(p->y - p->dirY * MOVE_SPEED)][(int)p->x] != '1')
			p->y -= p->dirY * MOVE_SPEED;
		if (g->d->mapper[(int)p->y][(int)(p->x - p->dirX * MOVE_SPEED)] != '1')
			p->x -= p->dirX * MOVE_SPEED;
		redraw_img(g);
	}
	else if (keycode == XK_a)
	{
		if (g->d->mapper[(int)(p->y + p->dirX * MOVE_SPEED)][(int)p->x] != '1')
			p->y += p->dirX * MOVE_SPEED;
		if (g->d->mapper[(int)p->y][(int)(p->x - p->dirY * MOVE_SPEED)] != '1')
			p->x -= p->dirY * MOVE_SPEED;
		redraw_img(g);
	}
	else if (keycode == XK_d)
	{
		if (g->d->mapper[(int)(p->y - p->dirX * MOVE_SPEED)][(int)p->x] != '1')
			p->y -= p->dirX * MOVE_SPEED;
		if (g->d->mapper[(int)p->y][(int)(p->x + p->dirY * MOVE_SPEED)] != '1')
			p->x += p->dirY * MOVE_SPEED;
		redraw_img(g);
	}
}

void	mouse_move(t_game *g, t_mouse m)
{
	t_player	*p;
	
	p = g->pl;
	if (m.x < g->win_width / 2)
		camera_move(g, 1, ROT_SPEED / 3);
	else
		camera_move(g, -1, ROT_SPEED / 3);
}