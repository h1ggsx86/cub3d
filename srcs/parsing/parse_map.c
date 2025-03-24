/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:46 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/24 17:13:35 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	check_inside(t_game *g)
{
	bool	is_player;
	int		j;
	int		i;
	int		pos[2];

	is_player = false;
	j = 0;
	while (g->d->mapper[j])
	{
		i = 0;
		while(g->d->mapper[j][i] && g->d->mapper[j][i] != '\n') 
		{
			if (is_player == true && is_pos_player(g->d->mapper[j][i], &is_player))
				err_message(g, "player", "only one allowed");
			else if (is_pos_player(g->d->mapper[j][i], &is_player))
			{
				perror("HERE");
				pos[0] = ft_atoi(g->d->mapper[j]);
				printf("%d\n", pos[0]);
				pos[1] = ft_atoi(&g->d->mapper[j][i]);
				printf("%d\n", pos[1]);
				g->d->mapper[j][i] = '0';
			}
			else if (g->d->mapper[j][i] != '1' && g->d->mapper[j][i] != '0')
			{
				perror("EXIT");
				printf("g->d->mapper[%d][%d] = %d\n", j, i, g->d->mapper[j][i]);
				return (1);
			}
			printf("i = %d\n", i);
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
		// printf("TP BEG== mapper[%d][%d] = %d\n", 0, i, g->d->mapper[0][i]);
		// printf("TP END == mapper[%d][%d] = %d\n", max_hight, i, g->d->mapper[max_hight][i]);
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
		// printf("LR BEG == mapper[%d][%d] = %d\n", j, 0, g->d->mapper[j][0]);
		// printf("LR END == mapper[%d][%d] = %d\n", j, max_len, g->d->mapper[j][max_len]);
		j++;
	}
	return (0);
}

int	is_pos_player(int c, bool *player)
{
	if (c == 'N')
		*player = true;
	else if (c == 'S')
		*player = true;
	else if (c == 'E')
		*player = true;
	else if (c == 'W')
		*player = true;
	if (*player == true)
		return (1);
	else
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
