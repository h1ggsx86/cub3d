/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:03:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/02/28 12:20:38 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(/*int ac, char *av[]*/)
{
	t_game		g;
	t_data		data;
	t_player	pl;

	struct_init(&g, &data, &pl);
	game_init(&g);
	the_loop(&g);
	return (exit_game(&g, 0), EXIT_SUCCESS);
}