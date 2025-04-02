/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:12:09 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/02 17:07:13 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	p_pos_init(t_data d, t_player *p)
{
	if (d.player_dir == 'N')
	{
		p->dir.y = -1;
		p->view.x = 0.66f;
	}
	else if (d.player_dir == 'W')
	{
		p->dir.x = -1;
		p->view.y = -0.66f;
	}
	else if (d.player_dir == 'E')
	{
		p->dir.x = 1;
		p->view.y = 0.66f;
	}
	else
	{
		p->dir.y = 1;
		p->view.x = -0.66f;
	}
}

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
	int	size;

	size = 64;
	g->init = mlx_init();
	if (!g->init)
		exit_game(g, 1);
	g->win = mlx_new_window(g->init, g->win_width, g->win_height, "CUB3D");
	if (!g->win)
		exit_game(g, 1);
	init_imgs(g, g->d);
	p_pos_init(*g->d, g->pl);
	g->d->textures[SOUTH] = init_south_texture(g);
	g->d->textures[NORTH] = init_north_texture(g);
	g->d->textures[EAST] = init_east_texture(g);
	g->d->textures[WEST] = init_west_texture(g);
	g->d->tex_door[0].img = mlx_xpm_file_to_image(g->init, \
		"./textures/door_open.xpm", &size, &size);
	g->d->tex_door[0].addr = mlx_get_data_addr(g->d->tex_door[0].img, \
		&g->d->tex_door[0].bpp, &g->d->tex_door[0].line_length, \
			&g->d->tex_door[0].endian);
	g->d->tex_door[1].img = mlx_xpm_file_to_image(g->init, \
		"./textures/door_closed.xpm", &size, &size);
	g->d->tex_door[1].addr = mlx_get_data_addr(g->d->tex_door[1].img, \
		&g->d->tex_door[1].bpp, &g->d->tex_door[1].line_length, \
			&g->d->tex_door[1].endian);
}

void	init_imgs(t_game *g, t_data *d)
{
	if (img_init(d->img_player, g, g->init))
		exit_game(g, 1);
	if (img_init(d->img_player + 1, g, g->init))
		exit_game(g, 1);
}
