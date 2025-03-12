/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:30:37 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/10 14:59:50 by tnedel           ###   ########.fr       */
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
	mlx_clear_window(g->init, g->win);
	if (g->d->active_img)
		mlx_put_image_to_window(g->init, g->win, g->d->img_map[0].img, \
									0, 0);
	else
		mlx_put_image_to_window(g->init, g->win, g->d->img_map[1].img, \
									0, 0);
	return (EXIT_SUCCESS);
}

void	the_loop(t_game *g)
{
	printf("img1 at %p\n", g->d->img_map);
	printf("img2 at %p\n", g->d->img_map + 1);
	draw_map(g);
	put_player_circle(g, g->d->color, 5);
	g->d->active_img = 0;
	draw_map(g);
	put_player_circle(g, g->d->color, 5);
	mlx_loop_hook(g->init, &handle_no_event, g);
	mlx_hook(g->win, KeyPress, KeyPressMask, &input_handler, g);
	mlx_hook(g->win, DestroyNotify, NoEventMask, &close_win_pointer, g);
	mlx_loop(g->init);
}