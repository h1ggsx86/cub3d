/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:18 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/01 12:35:29 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	err_message(t_game *g, char *arg, char *mess, int ecode)
{
	ft_putstr_fd("Club3D: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (!mess)
		perror("");
	else
		ft_putendl_fd(mess, 2);
	if (g->map > 0)
		close(g->map);
	exit_game(g, ecode);
}

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
	// mlx_mouse_show(g->init, g->win);
	free_img(g->init, g->d->img_player);
	if (g->win)
		mlx_destroy_window(g->init, g->win);
	if (g->init)
	{
		mlx_destroy_display(g->init);
		free(g->init);
	}
	exit(ecode);
}
