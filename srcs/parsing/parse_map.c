/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:46 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/22 14:52:54 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	is_inside(t_game *g, bool player, int j)
{
	int	i;

	i = 0;
	while (g->d->mapper[j][i])
	{
		if (is_pos_player(g->d->mapper[j][i]) && player == true)
				err_message(g, "player", "only one allowed");
		else if (g->d->mapper[j][i] != '1' && g->d->mapper[j][i] != '0')
			return (1);
	}
	return (0);
}

void	choose_left_right(t_game *g, int *i, int *j)
{
	if (!g->d->mapper[*j])
		return ;
	// printf("i = %d\n", *i);
	// printf("len de line = %zu\n", ft_strlen(g->d->mapper[*j]));
	if ((*i) < (int)ft_strlen(g->d->mapper[*j]) - 2) // go right
	{
		while (g->d->mapper[*j][*i] && (!g->d->mapper[*j - 1][*i] || \
		g->d->mapper[*j - 1][*i] != '1'))
		{
			printf("RIGHT mapper[%d][%d] = %c\n", *j, *i, g->d->mapper[*j][*i]);
			if ((*i) == (int)ft_strlen(g->d->mapper[*j]))
				break ;
			(*i)++;
		}
	}
	else // go left
	{
		while (g->d->mapper[*j][*i] && (!g->d->mapper[*j + 1][*i] || \
		g->d->mapper[*j + 1][*i] != '1'))
		{
			printf("LEFT mapper[%d][%d] = %c\n", *j, *i, g->d->mapper[*j][*i]);
			if ((*i) == 0)
				break ;
			else if (g->d->mapper[*j][*i - 1] == ' ')
				break ;
			(*i)--;
		}
	}
}

void	choose_top_bottom(t_game *g, int *i, int *j)
{
	if (!g->d->mapper[*j])
		return ;
	// printf("LASTg->d->mapper[%d][%d] = %d\n", *j, *i, g->d->mapper[*j][*i]);
	if (*j < g->d->height - 1) // go bottom
	{
		while (g->d->mapper[*j][*i] && g->d->mapper[*j][*i] == '1')
		{
			printf("BOTTOM mapper[%d][%d] = %c\n", *j, *i, g->d->mapper[*j][*i]);
			if (!g->d->mapper[*j + 1][*i])
				break ;
			(*j)++;
		}
	}
	else // go top
	{
		while (g->d->mapper[*j][*i] && (g->d->mapper[*j][*i] == '1' || \
		g->d->mapper[*j][*i - 1] == ' '))
		{
			printf("TOP mapper[%d][%d] = %c\n", *j, *i, g->d->mapper[*j][*i]);
			if (!g->d->mapper[*j - 1][*i])
				break ;
			if (g->d->mapper[*j][*i - 1] == ' ')
				// if (g->d->mapper[*j][*i + 1] == '1' || g->d->mapper[*j][*i - 1] == '1')
			// 	break ;
			(*j)--;
		}
	}
}

void	is_map_parsed(t_game *g, int i, int j)
{
	if (j == '0' && g->d->mapper[j][i] == '1')
	{
		perror("HERE");
		g->d->map_parsed = true;
	}
	else if (j == '0' && g->d->mapper[j][i] != '1')
		return ; // implementer code d erreur
}

int	check_sides(t_game *g)
{
	int	i; // gauche a droit
	int	j; // haut en bas

	i = 0;
	j = 0;
	while (g->d->mapper[j][i] && g->d->mapper[j][i] != '1')
		i++;
	while (g->d->mapper[j][i] && g->d->mapper[j][i] == '1')
		i++;
	i--;
	// printf("len de [6][32] = %d\n", (int)ft_strlen(g->d->mapper[6]));
	// printf("mapper[%d][%d] = %d\n", 6, 32, g->d->mapper[6][32]);
	while (g->d->map_parsed == false)
	{
		choose_top_bottom(g, &i, &j);
		// printf("MIDg->d->mapper[%d][%d] = %d\n", j, i, g->d->mapper[j][i]);
		choose_left_right(g, &i, &j);
		is_map_parsed(g, i, j);
	}
	return (0);
}

int	is_pos_player(int c)
{
	if (c == 'N')
		return (1);
	else if (c == 'S')
		return (1);
	else if (c == 'E')
		return (1);
	else if (c == 'W')
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
	// printf("height = %d\n", g->d->height);
	if ((*j) > g->d->height)
		return ;
	g->d->mapper[*j] = (char *)ft_calloc(sizeof(char), g->d->width + 1);
	if (!g->d->mapper[*j])
		exit(1);
	while (line[i] && i < g->d->width)
	{
		g->d->mapper[*j][i] = line[i];
		printf("%c", g->d->mapper[*j][i]);
		i++;
	}
	(*j)++;
}
