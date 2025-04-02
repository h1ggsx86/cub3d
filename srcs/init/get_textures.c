/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:02:27 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/02 10:08:40 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_mimg	*init_north_texture(t_game *g)
{
	t_mimg	*n_img;
	int		size;

	n_img = NULL;
	g->d->n_text = open(g->d->north_path, O_RDONLY, 0664);
	if (g->d->n_text < 0)
		err_message(g, g->d->north_path, NULL, 5);
	n_img = malloc(sizeof(t_mimg));
	if (!n_img)
		err_message(g, "north_texture", "memeory allocation failed", 7);
	size = 64;
	n_img->img = mlx_xpm_file_to_image(g->init, g->d->north_path, &size, &size);
	n_img->addr = mlx_get_data_addr(n_img->img, &n_img->bpp, \
		&n_img->line_length, &n_img->endian);
	if (!n_img)
		err_message(g, "north_data_addr", "mlx_failed", 7);
	return (n_img);
}

t_mimg	*init_south_texture(t_game *g)
{
	t_mimg	*s_img;
	int		size;

	s_img = NULL;
	g->d->s_text = open(g->d->south_path, O_RDONLY, 0664);
	if (g->d->s_text < 0)
		err_message(g, g->d->south_path, NULL, 5);
	s_img = malloc(sizeof(t_mimg));
	if (!s_img)
		err_message(g, "south_texture", "memory allocation failed", 7);
	size = 64;
	printf("south_path = %s\n", g->d->south_path);
	s_img->img = mlx_xpm_file_to_image(g->init, g->d->south_path, &size, &size);
	if (!s_img->img)
		err_message(g, "xpm file to image", "failed", 7);
	s_img->addr = mlx_get_data_addr(s_img->img, &s_img->bpp, \
		&s_img->line_length, &s_img->endian);
	if (!s_img)
		err_message(g, "south_data_addr", "mlx_failed", 7);
	return (s_img);
}

t_mimg	*init_west_texture(t_game *g)
{
	t_mimg	*w_img;
	int		size;

	w_img = NULL;
	g->d->w_text = open(g->d->west_path, O_RDONLY, 0664);
	if (g->d->w_text < 0)
		err_message(g, g->d->west_path, NULL, 5);
	w_img = malloc(sizeof(t_mimg));
	if (!w_img)
		err_message(g, "west_texture", "memory allocation failed", 7);
	size = 64;
	w_img->img = mlx_xpm_file_to_image(g->init, g->d->west_path, &size, &size);
	w_img->addr = mlx_get_data_addr(w_img->img, &w_img->bpp, \
		&w_img->line_length, &w_img->endian);
	if (!w_img)
		err_message(g, "west_data_addr", "mlx_failed", 7);
	return (w_img);
}

t_mimg	*init_east_texture(t_game *g)
{
	t_mimg	*e_img;
	int		size;

	e_img = NULL;
	g->d->e_text = open(g->d->east_path, O_RDONLY, 0664);
	if (g->d->e_text < 0)
		err_message(g, g->d->east_path, NULL, 5);
	e_img = malloc(sizeof(t_mimg));
	if (!e_img)
		err_message(g, "east_texture", "memory allocation failed", 7);
	size = 64;
	e_img->img = mlx_xpm_file_to_image(g->init, g->d->east_path, &size, &size);
	e_img->addr = mlx_get_data_addr(e_img->img, &e_img->bpp, \
		&e_img->line_length, &e_img->endian);
	if (!e_img)
		err_message(g, "east_data_addr", "mlx_failed", 7);
	return (e_img);
}
