/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:18 by tnedel            #+#    #+#             */
/*   Updated: 2025/02/28 09:37:12 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_img(t_mimg *img)
{
	if (img)
		free(img);
}

void	exit_game(t_game *g, int ecode)
{
	if (g->d->img1->img)
		mlx_destroy_image(g->init, g->d->img1->img);
	if (g->d->img2->img)
		mlx_destroy_image(g->init, g->d->img2->img);
	free_img(g->d->img1);
	free_img(g->d->img2);
	if (g->win)
		mlx_destroy_window(g->init, g->win);
	if (g->init)
	{
		mlx_destroy_display(g->init);
		free(g->init);
	}
	exit(ecode);
}
