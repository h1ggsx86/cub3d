/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:02:27 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/28 18:27:08 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// void	init_north_texture(t_game *g)
// {
	
// }

void	init_south_texture(t_game *g)
{
	void	*img;
	int		size;

	perror("DDDDDDDDDD");
	// south_img = NULL;
	// g->d->s_text = open(g->d->south_path, O_RDONLY, 0664);
	// if (g->d->s_text < 0)
	// 	err_message(g, g->d->south_path, NULL, 5);
	// south_img = malloc(sizeof(t_mimg));
	// if (!south_img)
	// 	err_message(g, "south_texture", "memory allocation failed", 7);
	size = 64;
	img = mlx_xpm_file_to_image(g->init, g->d->south_path, &size, &size);
}
