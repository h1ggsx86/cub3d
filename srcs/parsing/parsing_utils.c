/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:26:41 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/07 14:45:46 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t	ft_vert_len(char **tab, int row, int max)
{
	size_t	i;

	if (!tab[0][row])
		return (0);
	else if (tab[0][row] == '\n')
		return (0);
	i = 0;
	while (i < (size_t)max && tab[i][row])
	{
		if (tab[i][0] == '\n')
			break ;
		i++;
	}
	return (i);
}

int	non_wall_char(int c)
{
	if (c == '0' || c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

void	check_map_closed(t_game *g, int j, int i)
{
	if (!non_wall_char(g->d->mapper[j][i]))
		return ;
	else
	{
		if (!g->d->mapper[j + 1][i] || !g->d->mapper[j - 1][i])
			err_message(g, "parsing", "map must be surronded by walls", 6);
		else if (!g->d->mapper[j][i + 1] || !g->d->mapper[j][i - 1])
			err_message(g, "parsing", "map must be surronded by walls", 6);
	}
}
