/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:12:09 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/25 18:49:00 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

int	img_init(t_mimg *img, t_game *g, void *init)
{
	img->img = mlx_new_image(init, g->win_width, g->win_height);
	if (!img->img)
		return (EXIT_FAILURE);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, \
									&img->line_length, &img->endian);
	return (EXIT_SUCCESS);
}

void	game_init(t_game *g)
{
	g->init = mlx_init();
	if (!g->init)
		exit_game(g, 1);
	g->win = mlx_new_window(g->init, g->win_width, g->win_height, "CUB3D");
	if (!g->win)
		exit_game(g, 1);
	init_img_player(g, g->d);
}

void	init_img_player(t_game *g, t_data *d)
{
	if (img_init(d->img_player, g, g->init))
		exit_game(g, 1);
	if (img_init(d->img_player + 1, g, g->init))
		exit_game(g, 1);
}
