/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/04 14:26:38 by tnedel           ###   ########.fr       */
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
	init_doors(g, &size);
	g->d->pov.img = mlx_xpm_file_to_image(g->init, \
		"./textures/sprite1pov.xpm", &g->win_width, &g->win_height);
	g->d->pov.addr = mlx_get_data_addr(g->d->pov.img, \
		&g->d->pov.bpp, &g->d->pov.line_length, \
			&g->d->pov.endian);
	g->d->floor.img = mlx_xpm_file_to_image(g->init, \
		"./textures/damier.xpm", &size, &size);
	g->d->floor.addr = mlx_get_data_addr(g->d->floor.img, \
		&g->d->floor.bpp, &g->d->floor.line_length, \
			&g->d->floor.endian);
	g->d->door_map = init_door_map(g, g->d);
}

void	init_imgs(t_game *g, t_data *d)
{
	if (img_init(d->img_player, g, g->init))
		exit_game(g, 1);
	if (img_init(d->img_player + 1, g, g->init))
		exit_game(g, 1);
}

void	init_ray(t_ray *r)
{
	r->door = 0;
	r->side = 0;
	r->line_height = 0;
	r->draw_end = 0;
	r->draw_start = 0;
	r->camera_x = 0;
	r->wall_dist = 0;
	ivector_init(&r->map, 0, 0);
	ivector_init(&r->step, 0, 0);
	ivector_init(&r->tex, 0, 0);
	fvector_init(&r->ray, 0, 0);
	fvector_init(&r->side_d, 0, 0);
	fvector_init(&r->delta_d, 0, 0);
	fvector_init(&r->door_side_d, 0, 0);
}
