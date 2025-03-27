/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/27 17:37:53 by xenon            ###   ########.fr       */
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

void	moves_input(int keycode, t_game *g)
{
	double	rot_speed;
	double	move_speed;
	t_player	*p;

	rot_speed = 0.09f;
	move_speed = 0.2f;
	p = g->pl;
	if (keycode == XK_Left)
	{
		double oldDirX = p->dirX;
		p->dirX = p->dirX * cosf(rot_speed) - p->dirY * sinf(rot_speed);
		p->dirY = oldDirX * sinf(rot_speed) + p->dirY * cosf(rot_speed);
		double oldPlaneX = p->viewX;
		p->viewX = p->viewX * cosf(rot_speed) - p->viewY * sinf(rot_speed);
		p->viewY = oldPlaneX * sinf(rot_speed) + p->viewY * cosf(rot_speed);
		redraw_img(g);
	}
	else if (keycode == XK_Right)
	{
		double oldDirX = p->dirX;
		p->dirX = p->dirX * cosf(-rot_speed) - p->dirY * sinf(-rot_speed);
		p->dirY = oldDirX * sinf(-rot_speed) + p->dirY * cosf(-rot_speed);
		double oldPlaneX = p->viewX;
		p->viewX = p->viewX * cosf(-rot_speed) - p->viewY * sinf(-rot_speed);
		p->viewY = oldPlaneX * sinf(-rot_speed) + p->viewY * cosf(-rot_speed);
		redraw_img(g);
	}
	else if (keycode == XK_w)
	{
		if (g->d->mapper[(int)(p->y + p->dirY * move_speed)][(int)p->x] != '1')
			p->y += p->dirY * move_speed;
		if (g->d->mapper[(int)p->y][(int)(p->x + p->dirX * move_speed)] != '1')
			p->x += p->dirX * move_speed;
		redraw_img(g);
	}
	else if (keycode == XK_s)
	{
		if (g->d->mapper[(int)(p->y - p->dirY * move_speed)][(int)p->x] != '1')
			p->y -= p->dirY * move_speed;
		if (g->d->mapper[(int)p->y][(int)(p->x - p->dirX * move_speed)] != '1')
			p->x -= p->dirX * move_speed;
		redraw_img(g);
	}
	else if (keycode == XK_a)
	{
		if (g->d->mapper[(int)(p->y + p->dirX * move_speed)][(int)p->x] != '1')
			p->y += p->dirX * move_speed;
		if (g->d->mapper[(int)p->y][(int)(p->x - p->dirY * move_speed)] != '1')
			p->x -= p->dirY * move_speed;
		redraw_img(g);
	}
	else if (keycode == XK_d)
	{
		if (g->d->mapper[(int)(p->y - p->dirX * move_speed)][(int)p->x] != '1')
			p->y -= p->dirX * move_speed;
		if (g->d->mapper[(int)p->y][(int)(p->x + p->dirY * move_speed)] != '1')
			p->x += p->dirY * move_speed;
		redraw_img(g);
	}
}
