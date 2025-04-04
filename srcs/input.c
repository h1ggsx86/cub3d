/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/04 11:51:09 by tnedel           ###   ########.fr       */
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
	if (map[(int)(p->y + (p->dir.y * move_speed * way))][(int)p->x] != '1' &&
		map[(int)(p->y + (p->dir.y * move_speed * way))][(int)p->x] != 'C')
		p->y += p->dir.y * move_speed * way;
	if (map[(int)p->y][(int)(p->x + (p->dir.x * move_speed * way))] != '1' &&
		map[(int)p->y][(int)(p->x + (p->dir.x * move_speed * way))] != 'C')
		p->x += p->dir.x * move_speed * way;
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
	if (map[(int)(p->y + (p->dir.x * move_speed * way))][(int)p->x] != '1' &&
		map[(int)(p->y + (p->dir.x * move_speed * way))][(int)p->x] != 'C')
		p->y += p->dir.x * move_speed * way;
	if (map[(int)p->y][(int)(p->x - (p->dir.y * move_speed * way))] != '1' &&
		map[(int)p->y][(int)(p->x - (p->dir.y * move_speed * way))] != 'C')
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

int	mouse_move(t_game *g)
{
	t_ivector	m;

	m.x = 0;
	m.y = 0;
	mlx_mouse_get_pos(g->init, g->win, &m.x, &m.y);
	if ((m.x > g->win_width || m.x < 0) ||(m.y > g->win_height || m.y < 0))
		return (EXIT_FAILURE);
	if (m.x != g->win_width / 2)
	{
		if (m.x < g->win_width / 2)
			camera_move(g, -1, ROT_SPEED * 2.5);
		else
			camera_move(g, 1, ROT_SPEED * 2.5);
		mlx_mouse_move(g->init, g->win, g->win_width / 2, g->win_height / 2);
	}
	return (EXIT_SUCCESS);
}
