/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:46 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/26 12:54:37 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_pos_player(int c, int *player)
{
	if (c == 'N')
		(*player)++;
	else if (c == 'S')
		(*player)++;
	else if (c == 'E')
		(*player)++;
	else if (c == 'W')
		(*player)++;
	if (*player)
		return (1);
	else
		return (0);
}

int	check_inside(t_game *g)
{
	int		n_player;
	int		j;
	int		i;

	n_player = 0;
	j = 0;
	while (g->d->mapper[j])
	{
		i = 0;
		while(g->d->mapper[j][i] && g->d->mapper[j][i] != '\n')
		{
			if (!n_player && is_pos_player(g->d->mapper[j][i], &n_player))
			{
				g->pl->y = (double)j;
				g->pl->x = (double)i;
				g->d->mapper[j][i] = '0';
			}
			else if (is_pos_player(g->d->mapper[j][i], &n_player) && n_player > 1)
				err_message(g, "player", "only one allowed", 6);
			else if (g->d->mapper[j][i] != '1' && g->d->mapper[j][i] != '0')
				return (1);
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
		if (i == (int)ft_strlen(g->d->mapper[max_hight]) - 1 && g->d->mapper[max_hight][i] == '\n')
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
	int	j;
	int	max_len;

	j = 0;
	while (j < g->d->height)
	{
		max_len = ft_strlen(g->d->mapper[j]) - 2;
		if (max_len == 0)
			return (1);
		if (g->d->mapper[j] && g->d->mapper[j][0] != '1')
			return (1);
		if (g->d->mapper[j] && g->d->mapper[j][max_len] != '1')
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
	if (!ft_strchr(line, 49))
		return ;
	if ((*j) >= g->d->height)
		return ;
	g->d->mapper[*j] = (char *)ft_calloc(sizeof(char), g->d->width + 1);
	if (!g->d->mapper[*j])
		exit(1);
	while (line[i] && i < g->d->width)
	{
		if (line[i] == ' ')
			line[i] = '1';
		g->d->mapper[*j][i] = line[i];
		printf("%c", g->d->mapper[*j][i]);
		i++;
	}
	(*j)++;
}
