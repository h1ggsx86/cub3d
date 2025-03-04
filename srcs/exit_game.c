/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:18 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/04 14:32:50 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_img(void *init, t_mimg *img)
{
	if (img)
	{
		if (img[0].img)
			mlx_destroy_image(init, img[0].img);
		if (img[1].img)
			mlx_destroy_image(init, img[1].img);
		free(img);
	}
}

void	exit_game(t_game *g, int ecode)
{
	free_img(g->init, g->d->img_map);
	if (g->win)
		mlx_destroy_window(g->init, g->win);
	if (g->init)
	{
		mlx_destroy_display(g->init);
		free(g->init);
	}
	exit(ecode);
}
