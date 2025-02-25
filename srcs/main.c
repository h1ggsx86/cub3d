/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:03:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/02/25 16:45:15 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(/*int ac, char *av[]*/)
{
	int			i;
	int			j;
	int			color;
	t_game		g;
	t_data		data;
	t_player	pl;

	struct_init(&g, &data, &pl);
	game_init(&g);
	color = 0x54fb08;
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			put_square(&data, i * (data.width / 5), j * (data.height / 5), color);
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