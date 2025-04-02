/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:18 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/02 16:28:09 by arotondo         ###   ########.fr       */
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

void	exit_game(t_game *g, int ecode)
{
	// mlx_mouse_show(g->init, g->win);
	free_img(g->init, g->d->img_player);
	free_doors(g->init, g->d->tex_door);
	free_map(g->d->mapper);
	while (g->d->i_text)
	{
		free_textures(g->init, g->d->textures[g->d->i_text - 1], g);
		g->d->i_text--;
	}
	if (g->d->colors)
		free(g->d->colors);
	if (g->win)
		mlx_destroy_window(g->init, g->win);
	if (g->init)
	{
		mlx_destroy_display(g->init);
		free(g->init);
	}
	exit(ecode);
}
