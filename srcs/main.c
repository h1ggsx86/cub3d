/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:03:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/21 15:22:48 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	worldMap[] =
{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1
};

int	main(int argc, char **argv)
{
	t_game		g;
	t_data		data;
	t_player	pl;
	t_tables	t;

	if (argc != 2)
		return (1);
	struct_init(&g, &data, &pl, &t);
	game_init(&g);
	parsing_the_thing(&g, argv[1]);
	the_loop(&g);
	return (exit_game(&g, 0), EXIT_SUCCESS);
}
