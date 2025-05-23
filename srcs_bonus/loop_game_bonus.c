/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:30:37 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/15 16:51:09 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	input_handler(int keycode, t_game *g)
{
	if (keycode == XK_Escape)
		exit_game(g, 0);
	if (keycode == XK_Left)
		g->key[LEFT] = 1;
	else if (keycode == XK_Right)
		g->key[RIGHT] = 1;
	else if (keycode == XK_w)
		g->key[W] = 1;
	else if (keycode == XK_s)
		g->key[S] = 1;
	else if (keycode == XK_d)
		g->key[D] = 1;
	else if (keycode == XK_a)
		g->key[A] = 1;
	door_input(keycode, g);
	return (EXIT_SUCCESS);
}

int	release_handler(int keycode, t_game *g)
{
	if (keycode == XK_Escape)
		exit_game(g, 0);
	if (keycode == XK_Left)
		g->key[LEFT] = 0;
	else if (keycode == XK_Right)
		g->key[RIGHT] = 0;
	else if (keycode == XK_w)
		g->key[W] = 0;
	else if (keycode == XK_s)
		g->key[S] = 0;
	else if (keycode == XK_d)
		g->key[D] = 0;
	else if (keycode == XK_a)
		g->key[A] = 0;
	return (EXIT_SUCCESS);
}

int	close_win_pointer(t_game *g)
{
	exit_game(g, 0);
	return (EXIT_SUCCESS);
}

int	handle_no_event(t_game *g)
{
	moves_input(g);
	mouse_move(g);
	render_img(g);
	if (g->d->active_img)
		mlx_put_image_to_window(g->init, g->win, g->d->img_player[0].img, \
			0, 0);
	else
		mlx_put_image_to_window(g->init, g->win, g->d->img_player[1].img, \
			0, 0);
	g->fps++;
	if (g->fps > 24)
		g->fps = 0;
	g->is_active = true;
	return (EXIT_SUCCESS);
}

void	the_loop(t_game *g)
{
	mlx_mouse_hide(g->init, g->win);
	mlx_mouse_move(g->init, g->win, g->win_width / 2, g->win_height / 2);
	mlx_loop_hook(g->init, &handle_no_event, g);
	mlx_hook(g->win, KeyPress, KeyPressMask, &input_handler, g);
	mlx_hook(g->win, KeyRelease, KeyReleaseMask, &release_handler, g);
	mlx_hook(g->win, DestroyNotify, NoEventMask, &close_win_pointer, g);
	mlx_loop(g->init);
}
