/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:03:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/27 12:06:34 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_arg(char **argv)
{
	int	i;

	i = 0;
	if (!argv[1] || !ft_strlen(argv[1]))
	{
		ft_putendl_fd("Empty argument detected", 2);
		exit(1);
	}
	while (i != (int)(ft_strlen(argv[1]) - 4))
		i++;
	if (ft_strcmp(".cub", argv[1] + i))
	{
		ft_putendl_fd("Bad file format : '.cub' is expected", 2);
		exit(1);
	}
	// printf("argv[1][i] = %s\n", argv[1] + i);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		g;
	t_data		data;
	t_player	pl;

	if (argc != 2)
		return (ft_putendl_fd("Two arguments expected", 2), 1);
	check_arg(argv);
	struct_init(&g, &data, &pl);
	game_init(&g);
	parsing_the_thing(&g, argv[1]);
	the_loop(&g);
	return (exit_game(&g, 0), EXIT_SUCCESS);
}
