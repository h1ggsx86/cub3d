/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:10:29 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/07 18:29:34 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ivector_init(t_ivector *vec, int x, int y)
{
	vec->x = x;
	vec->y = y;
}

void	fvector_init(t_fvector *vec, double x, double y)
{
	vec->x = x;
	vec->y = y;
}

void	player_init(t_player *pl)
{
	pl->x = 0;
	pl->y = 0;
	pl->dir.x = 0;
	pl->dir.y = 0;
	pl->view.x = 0.0f;
	pl->view.y = 0.0f;
}

void	key_init(t_game *new)
{
	int	i;

	i = 0;
	while (i < 6)
		new->key[i++] = 0;
}

void	init_doors(t_game *g, int *size)
{
	char	*path;
	char	*ret;

	while (g->d->i_frames < 13)
	{
		ret = ft_itoa(g->d->i_frames);
		path = ft_strjoin2("./textures/close_door/frame", ret);
		free(ret);
		path = ft_strjoin(path, ".xpm");
		if (check_closing_door(path))
			err_message(g, "door texture", NULL, 7);
		g->d->tex_door[g->d->i_frames].img = mlx_xpm_file_to_image(g->init, \
			path, size, size);
		if (!g->d->tex_door[g->d->i_frames].img)
			exit_game(g, 7);
		g->d->tex_door[g->d->i_frames].addr = mlx_get_data_addr \
			(g->d->tex_door[g->d->i_frames].img, &g->d->tex_door \
				[g->d->i_frames].bpp, &g->d->tex_door[g->d->i_frames] \
					.line_length, &g->d->tex_door[g->d->i_frames].endian);
		if (!g->d->tex_door[g->d->i_frames].addr)
			exit_game(g, 7);
		g->d->i_frames++;
		free(path);
	}
}
