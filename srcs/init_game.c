/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:12:09 by tnedel            #+#    #+#             */
/*   Updated: 2025/02/27 15:42:56 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	img_init(t_mimg *img, t_data *d, void *init)
{
	img->img = mlx_new_image(init, d->width, d->height);
	if (!img->img)
		return (EXIT_FAILURE);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, \
									&img->line_length, &img->endian);
	return (EXIT_SUCCESS);
}

static void	data_init(t_game *g, t_data *d)
{
	if (img_init(d->img1, d, g->init))
		exit_game(g, 1);
	if (img_init(d->img2, d, g->init))
		exit_game(g, 1);
}

void	game_init(t_game *g)
{
	g->init = mlx_init();
	if (!g->init)
		exit_game(g, 1);
	g->win = mlx_new_window(g->init, g->d->width, g->d->height, "CUB3D");
	if (!g->win)
		exit_game(g, 1);
	data_init(g, g->d);
}
