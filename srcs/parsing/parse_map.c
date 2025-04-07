/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:46 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/07 15:17:58 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	keep_pos_player(t_game *g, int *j, int *i)
{
	g->pl->y = (double)*j;
	g->pl->x = (double)*i;
	g->d->player_dir = g->d->mapper[*j][*i];
	g->d->mapper[*j][*i] = '0';
}

int	check_inside(t_game *g)
{
	int	i;
	int	j;
	int	n_player;

	j = 0;
	n_player = 0;
	while (g->d->mapper[j])
	{
		i = 0;
		while (g->d->mapper[j][i] && g->d->mapper[j][i] != '\n')
		{
			if (!n_player && is_pos_player(g->d->mapper[j][i], &n_player))
				keep_pos_player(g, &j, &i);
			else if (is_pos_player(g->d->mapper[j][i], &n_player) \
				&& n_player > 1)
				err_message(g, "player", "only one allowed", 6);
			else if (g->d->mapper[j][i] != '1' && g->d->mapper[j][i] != '0' && \
						g->d->mapper[j][i] != 'C' && g->d->mapper[j][i] != 'O')
				return (1);
			else if (is_door_valid(g, j, i))
				err_message(g, "door", "invalid position", 6);
			check_map_closed(g, j, i);
			i++;
		}
		j++;
	}
	return (0);
}

int	check_top_bottom(t_game *g)
{
	int	i;
	int	max_hight;

	i = 0;
	while (i < (int)g->d->width)
	{
		max_hight = ft_vert_len(g->d->mapper, i, g->d->height) - 1;
		if (max_hight <= 0)
			return (1);
		if (i == (int)ft_strlen(g->d->mapper[max_hight]) - 1 \
			&& g->d->mapper[max_hight][i] == '\n')
			break ;
		if (g->d->mapper[0][i] && g->d->mapper[0][i] != '1')
			return (1);
		if (g->d->mapper[max_hight][i] && g->d->mapper[max_hight][i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_left_right(t_game *g)
{
	int		j;
	size_t	max_len;

	j = 0;
	while (j < g->d->height)
	{
		max_len = ft_strlen(g->d->mapper[j]);
		if (max_len == 0)
			return (1);
		if (g->d->mapper[j] && g->d->mapper[j][0] != '1')
			return (1);
		if (g->d->mapper[j] && g->d->mapper[j][max_len - 2] != '1')
			return (1);
		j++;
	}
	return (0);
}

void	parse_map(t_game *g, char *line, int *j)
{
	size_t	i;

	i = 0;
	if (g->d->map_parsed == true)
		return ;
	if ((*j) >= g->d->height)
		return ;
	if (!ft_strchr(line, 49) && !(*j))
		return ;
	g->d->mapper[*j] = (char *)ft_calloc(sizeof(char), g->d->width + 1);
	if (!g->d->mapper[*j])
		exit(1);
	while (line[i] && i < g->d->width)
	{
		if (line[i] == ' ')
			line[i] = '1';
		g->d->mapper[*j][i] = line[i];
		i++;
	}
	(*j)++;
}
