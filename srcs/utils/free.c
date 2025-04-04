/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:27:34 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/04 16:26:05 by arotondo         ###   ########.fr       */
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

void	free_doors(void *init, t_game *g)
{
	int	i;

	i = 0;
	while (i < 13)
	{
		if (g->d->tex_door[i].img)
			mlx_destroy_image(init, g->d->tex_door[i].img);
		i++;
	}
	if (g->d->floor.img)
		mlx_destroy_image(init, g->d->floor.img);
	if (g->d->pov.img)
		mlx_destroy_image(init, g->d->pov.img);
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
	if (g->d->fd_texture[g->d->i_text - 1] > 0)
		close(g->d->fd_texture[g->d->i_text - 1]);
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
