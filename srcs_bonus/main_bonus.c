/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:03:39 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/08 11:18:48 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	check_arg(char **argv)
{
	int	i;

	i = 0;
	if (!argv[1] || !ft_strlen(argv[1]))
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Empty argument detected", 2);
		exit(1);
	}
	else if (ft_strlen(argv[1]) < 5)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Bad argument detected", 2);
		exit(1);
	}
	while (i != (int)(ft_strlen(argv[1]) - 4))
		i++;
	if (ft_strcmp(".cub", argv[1] + i))
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Bad file format : '.cub' is expected", 2);
		exit(1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		g;
	t_data		data;
	t_player	pl;

	if (argc != 2)
		return (ft_putendl_fd("Error\nTwo arguments expected", 2), 1);
	check_arg(argv);
	struct_init(&g, &data, &pl);
	parsing_the_thing(&g, argv[1]);
	game_init(&g);
	the_loop(&g);
	return (exit_game(&g, 0), EXIT_SUCCESS);
}
