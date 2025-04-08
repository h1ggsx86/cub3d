/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/08 14:59:47 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	camera_move(t_game *g, int way, double rot)
{
	double		frametime;
	double		old_dir_x;
	double		old_view_x;
	t_player	*p;

	frametime = g->time - g->old_time;
	rot = frametime * rot;
	p = g->pl;
	old_dir_x = p->dir.x;
	p->dir.x = p->dir.x * cosf(rot * way) - p->dir.y * sinf(rot * way);
	p->dir.y = old_dir_x * sinf(rot * way) + p->dir.y * cosf(rot * way);
	old_view_x = p->view.x;
	p->view.x = p->view.x * cosf(rot * way) - p->view.y * sinf(rot * way);
	p->view.y = old_view_x * sinf(rot * way) + p->view.y * cosf(rot * way);
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
	int (new_y) = (int)(p->y + (p->dir.y * move_speed * way));
	int (new_x) = (int)(p->x + (p->dir.x * move_speed * way));
	if (map[new_y][(int)p->x] && map[new_y][(int)p->x] != '1')
		p->y = p->y + (p->dir.y * move_speed * way);
	if (map[(int)p->y][new_x] && map[(int)p->y][new_x] != '1')
		p->x = p->x + (p->dir.x * move_speed * way);
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
	int (new_y) = (int)(p->y + (p->dir.x * move_speed * way));
	int (new_x) = (int)(p->x - (p->dir.y * move_speed * way));
	if (map[new_y][(int)p->x] != '1')
		p->y += p->dir.x * move_speed * way;
	if (map[(int)p->y][new_x] != '1')
		p->x -= p->dir.y * move_speed * way;
}

void	moves_input(t_game *g)
{
	if (g->key[LEFT])
		camera_move(g, -1, ROT_SPEED);
	if (g->key[RIGHT])
		camera_move(g, 1, ROT_SPEED);
	if (g->key[W])
		ws_move(g, 1);
	if (g->key[S])
		ws_move(g, -1);
	if (g->key[D])
		ad_move(g, 1);
	if (g->key[A])
		ad_move(g, -1);
}
