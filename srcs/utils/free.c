/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:27:34 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/08 09:27:11 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	free_incomp_text(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->d->text_path[i])
		{
			free(g->d->text_path[i]);
			g->d->text_path[i] = NULL;
			g->d->i_text--;
		}
		if (g->d->fd_texture[i] > 0)
			close(g->d->fd_texture[i]);
		i++;
	}
}

void	free_textures(void *init, t_mimg *img, t_game *g)
{
	if (img)
	{
		if (img->img)
			mlx_destroy_image(init, img->img);
	}
	if (g->d->textures[g->d->i_text - 1])
		free(g->d->textures[g->d->i_text - 1]);
	if (g->d->text_path[g->d->i_text - 1])
		free(g->d->text_path[g->d->i_text - 1]);
	g->d->text_path[g->d->i_text - 1] = NULL;
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
