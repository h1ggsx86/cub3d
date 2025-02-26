/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:03:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/02/26 13:49:21 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(/*int ac, char *av[]*/)
{
	int			i;
	int			j;
	int			color;
	int			nbr;
	t_game		g;
	t_data		data;
	t_player	pl;

	struct_init(&g, &data, &pl);
	game_init(&g);
	color = 0x54fb08;
	nbr = 8;
	put_square(&data, 0, 0, color, 1);
	i = 0;
	while (i < nbr)
	{
		j = 0;
		while (j < nbr)
		{
			put_square(&data, i * (data.width / nbr), j * (data.height / nbr), color, nbr);
			j++;
		}
		color += 10;
		i++;
	}
	mlx_put_image_to_window(g.init, g.win, g.data->img, \
								0, 0);
	mlx_loop(g.init);
	return (exit_game(&g, 0), EXIT_SUCCESS);
}