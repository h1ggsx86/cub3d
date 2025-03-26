/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/25 22:32:33 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

	rot_speed = 0.07f;
	move_speed = 0.1f;
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
		// printf("[DEBUG] pa :\t%f | pdx :\t%f | pdy :\t%f\n", p->pa, p->pdx, p->pdy);
		redraw_img(g);
	}
	else if (keycode == XK_w)
	{
		if (worldMap[(int)(p->posX + p->dirX * move_speed)][(int)p->posY] != 1)
			p->posX += p->dirX * move_speed;
		if (worldMap[(int)p->posX][(int)(p->posY + p->dirY * move_speed)] != 1)
			p->posY += p->dirY * move_speed;
		// printf("[DEBUG] pa :\t%f | pdx :\t%f | pdy :\t%f\n", p->pa, p->pdx, p->pdy);
		redraw_img(g);
	}
	else if (keycode == XK_s)
	{
		if (worldMap[(int)(p->posX - p->dirX * move_speed)][(int)p->posY] != 1)
			p->posX -= p->dirX * move_speed;
		if (worldMap[(int)p->posX][(int)(p->posY - p->dirY * move_speed)] != 1)
			p->posY -= p->dirY * move_speed;
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