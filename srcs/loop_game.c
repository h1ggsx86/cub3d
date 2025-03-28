/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:30:37 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/28 15:55:18 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	input_handler(int keycode, t_game *g)
{
	if (keycode == XK_Escape)
		exit_game(g, 0);
	moves_input(keycode, g);
	return (EXIT_SUCCESS);
}

int	close_win_pointer(t_game *g)
{
	exit_game(g, 0);
	return (EXIT_SUCCESS);
}

int	handle_no_event(t_game *g)
{
	mouse_move(g);
	if (g->d->active_img)
		mlx_put_image_to_window(g->init, g->win, g->d->img_player[0].img, \
									0, 0);
	else
		mlx_put_image_to_window(g->init, g->win, g->d->img_player[1].img, \
									0, 0);
	return (EXIT_SUCCESS);
}

void	the_loop(t_game *g)
{
	printf("img1 at %p\n", g->d->img_player);
	printf("img2 at %p\n", g->d->img_player + 1);
	// mlx_mouse_hide(g->init, g->win);
	mlx_mouse_move(g->init, g->win, g->win_width / 2, g->win_height / 2);
	ray_loop(g, *g->pl);
	draw_map(g);
	g->d->active_img = 0;
	ray_loop(g, *g->pl);
	draw_map(g);
	mlx_loop_hook(g->init, &handle_no_event, g);
	mlx_hook(g->win, KeyPress, KeyPressMask, &input_handler, g);
	// mlx_hook(g->win, MotionNotify, PointerMotionMask, &mouse_move, g);
	mlx_hook(g->win, DestroyNotify, NoEventMask, &close_win_pointer, g);
	mlx_loop(g->init);
}
