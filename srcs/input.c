/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/01 10:03:39 by tnedel           ###   ########.fr       */
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
	ray_loop(g, *g->pl);
	draw_map(g);
	if (g->d->active_img)
		g->d->active_img = 0;
	else
		g->d->active_img = 1;
}

void	camera_move(t_game *g, int way, double rot)
{
	double		frametime;
	t_player	*p;

	frametime = g->time - g->old_time;
	rot = frametime * rot;
	p = g->pl;
	double oldDirX = p->dirX;
	p->dirX = p->dirX * cosf(rot * way) - p->dirY * sinf(rot * way);
	p->dirY = oldDirX * sinf(rot * way) + p->dirY * cosf(rot * way);
	double oldPlaneX = p->viewX;
	p->viewX = p->viewX * cosf(rot * way) - p->viewY * sinf(rot * way);
	p->viewY = oldPlaneX * sinf(rot * way) + p->viewY * cosf(rot * way);
	// redraw_img(g);
}

void	ws_move(t_game *g, int way)
{
	double		frametime;
	double		move_speed;
	char		**map;
	t_player	*p;

	frametime = g->time - g->old_time;
	move_speed = frametime * MOVE_SPEED;
	p = g->pl;
	map = g->d->mapper;
	if (map[(int)(p->y + (p->dirY * move_speed * way))][(int)p->x] != '1' &&
		map[(int)(p->y + (p->dirY * move_speed * way))][(int)p->x] != 'C')
		p->y += p->dirY * move_speed * way;
	if (map[(int)p->y][(int)(p->x + (p->dirX * move_speed * way))] != '1' &&
		map[(int)p->y][(int)(p->x + (p->dirX * move_speed * way))] != 'C')
		p->x += p->dirX * move_speed * way;
}

void	ad_move(t_game *g, int way)
{
	double		frametime;
	double		move_speed;
	char		**map;
	t_player	*p;

	frametime = g->time - g->old_time;
	move_speed = frametime * MOVE_SPEED;
	p = g->pl;
	map = g->d->mapper;
	if (map[(int)(p->y + (p->dirX * move_speed * way))][(int)p->x] != '1' &&
		map[(int)(p->y + (p->dirX * move_speed * way))][(int)p->x] != 'C')
		p->y += p->dirX * move_speed * way;
	if (map[(int)p->y][(int)(p->x - (p->dirY * move_speed * way))] != '1' &&
		map[(int)p->y][(int)(p->x - (p->dirY * move_speed * way))] != 'C')
		p->x -= p->dirY * move_speed * way;
}

void	moves_input(t_game *g)
{
	t_player	*p;

	p = g->pl;
	if (g->key[LEFT])
		camera_move(g, -1, ROT_SPEED);
	else if (g->key[RIGHT])
		camera_move(g, 1, ROT_SPEED);
	else if (g->key[W])
		ws_move(g, 1);
	else if (g->key[S])
		ws_move(g, -1);
	else if (g->key[D])
		ad_move(g, 1);
	else if (g->key[A])
		ad_move(g, -1);
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
			camera_move(g, -1, ROT_SPEED * 2);
		else
			camera_move(g, 1, ROT_SPEED * 2);
		mlx_mouse_move(g->init, g->win, g->win_width / 2, g->win_height / 2);
	}
	return (EXIT_SUCCESS);
}