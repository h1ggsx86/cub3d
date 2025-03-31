/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/31 13:30:38 by tnedel           ###   ########.fr       */
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
	// mlx_destroy_image(g->init, img->img);
	// img->img = NULL;
	// if (img_init(img, g, g->init))
	// 	exit_game(g, 1);
	ray_loop(g, *g->pl);
	draw_map(g);
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

void	ws_move(t_game *g, int way)
{
	char		**map;
	t_player	*p;

	p = g->pl;
	map = g->d->mapper;
	if (map[(int)(p->y + (p->dirY * MOVE_SPEED * way))][(int)p->x] != '1' &&
		map[(int)(p->y + (p->dirY * MOVE_SPEED * way))][(int)p->x] != 'C')
		p->y += p->dirY * MOVE_SPEED * way;
	if (map[(int)p->y][(int)(p->x + (p->dirX * MOVE_SPEED * way))] != '1' &&
		map[(int)p->y][(int)(p->x + (p->dirX * MOVE_SPEED * way))] != 'C')
		p->x += p->dirX * MOVE_SPEED * way;
}

void	ad_move(t_game *g, int way)
{
	char		**map;
	t_player	*p;

	p = g->pl;
	map = g->d->mapper;
	if (map[(int)(p->y + (p->dirX * MOVE_SPEED * way))][(int)p->x] != '1' &&
		map[(int)(p->y + (p->dirX * MOVE_SPEED * way))][(int)p->x] != 'C')
		p->y += p->dirX * MOVE_SPEED * way;
	if (map[(int)p->y][(int)(p->x - (p->dirY * MOVE_SPEED * way))] != '1' &&
		map[(int)p->y][(int)(p->x - (p->dirY * MOVE_SPEED * way))] != 'C')
		p->x -= p->dirY * MOVE_SPEED * way;
}

void	moves_input(int keycode, t_game *g)
{
	t_player	*p;

	p = g->pl;
	if (keycode == XK_Left)
		camera_move(g, -1, ROT_SPEED);
	else if (keycode == XK_Right)
		camera_move(g, 1, ROT_SPEED);
	else if (keycode == XK_w)
	{
		ws_move(g, 1);
		redraw_img(g);
	}
	else if (keycode == XK_s)
	{
		ws_move(g, -1);
		redraw_img(g);
	}
	else if (keycode == XK_d)
	{
		ad_move(g, 1);
		redraw_img(g);
	}
	else if (keycode == XK_a)
	{
		ad_move(g, -1);
		redraw_img(g);
	}
}

int	mouse_move(/*int x, int y,*/ t_game *g)
{
	t_ivector	m;
	
	m.x = 0;
	m.y = 0;
	mlx_mouse_get_pos(g->init, g->win, &m.x, &m.y);
	if (m.x != g->win_width / 2)
	{
		if (m.x < g->win_width / 2)
			camera_move(g, -1, ROT_SPEED / 3);
		else
			camera_move(g, 1, ROT_SPEED / 3);
		mlx_mouse_move(g->init, g->win, g->win_width / 2, g->win_height / 2);
	}
	return (EXIT_SUCCESS);
}