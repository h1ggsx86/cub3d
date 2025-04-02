/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:02:27 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/02 15:58:47 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

t_mimg	*init_north_texture(t_game *g)
{
	t_mimg	*n_img;
	int		size;

	n_img = NULL;
	g->d->fd_texture[0] = open(g->d->text_path[0], O_RDONLY, 0664);
	if (g->d->fd_texture[0] < 0)
		err_message(g, g->d->text_path[0], NULL, 5);
	n_img = malloc(sizeof(t_mimg));
	if (!n_img)
		err_message(g, "north_texture", "memeory allocation failed", 7);
	size = 64;
	n_img->img = mlx_xpm_file_to_image(g->init, g->d->text_path[0], &size, &size);
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
	g->d->fd_texture[3] = open(g->d->text_path[3], O_RDONLY, 0664);
	if (g->d->fd_texture[3] < 0)
		err_message(g, g->d->text_path[3], NULL, 5);
	s_img = malloc(sizeof(t_mimg));
	if (!s_img)
		err_message(g, "south_texture", "memory allocation failed", 7);
	size = 64;
	s_img->img = mlx_xpm_file_to_image(g->init, g->d->text_path[3], &size, &size);
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
	g->d->fd_texture[2] = open(g->d->text_path[2], O_RDONLY, 0664);
	if (g->d->fd_texture[2] < 0)
		err_message(g, g->d->text_path[2], NULL, 5);
	w_img = malloc(sizeof(t_mimg));
	if (!w_img)
		err_message(g, "west_texture", "memory allocation failed", 7);
	size = 64;
	w_img->img = mlx_xpm_file_to_image(g->init, g->d->text_path[2], &size, &size);
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
	g->d->fd_texture[1] = open(g->d->text_path[1], O_RDONLY, 0664);
	if (g->d->fd_texture[1] < 0)
		err_message(g, g->d->text_path[1], NULL, 5);
	e_img = malloc(sizeof(t_mimg));
	if (!e_img)
		err_message(g, "east_texture", "memory allocation failed", 7);
	size = 64;
	e_img->img = mlx_xpm_file_to_image(g->init, g->d->text_path[1], &size, &size);
	e_img->addr = mlx_get_data_addr(e_img->img, &e_img->bpp, \
		&e_img->line_length, &e_img->endian);
	if (!e_img)
		err_message(g, "east_data_addr", "mlx_failed", 7);
	return (e_img);
}
