/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:46 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/20 18:55:00 by arotondo         ###   ########.fr       */
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
	// printf("mapper[%d][%d]\n", *j, *i);
	// printf("len de mapper[j] = %d\n", (int)ft_strlen(g->d->mapper[*j]));
	if (!g->d->mapper[*j])
		return ;
	if ((*i) < (int)ft_strlen(g->d->mapper[*j])) // go right
	{
		while (g->d->mapper[*j][*i] && g->d->mapper[*j + 1][*i] && \
			g->d->mapper[*j + 1][*i] != '1')
			{printf("RIGHT mapper[%d][%d] = %c\n", *j, *i, g->d->mapper[*j][*i]); (*i)++;}
	}
	else // go left
	{
		while (g->d->mapper[*j][*i] && (g->d->mapper[*j + 1][*i] || \
			g->d->mapper[*j + 1][*i] != '1'))
			{printf("LEFT mapper[%d][%d] = %c\n", *j, *i, g->d->mapper[*j][*i]); (*i)--;}
	}
}

void	choose_top_bottom(t_game *g, int *i, int *j)
{
	if (*j < g->d->height) // go bottom
	{
		while (g->d->mapper[*j][*i] && g->d->mapper[*j][*i] == '1')
		{
			printf("BOTTOM mapper[%d][%d] = %c\n", *j, *i, g->d->mapper[*j][*i]); 
			(*j)++;
			// printf("add mapper[%d][%d] = %p", *j, *i, &g->d->mapper[*j][*i]);
		}
	}
	else // go top
	{
		while (g->d->mapper[*j][*i] && g->d->mapper[*j][*i] == '1')
		{printf("TOP mapper[%d][%d] = %c\n", *j, *i, g->d->mapper[*j][*i]); (*j)--;}
		(*j)--;
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
	int	i;

	i = 0;
	if (g->d->map_parsed == true)
		return ;
	if (!ft_strchr(line, 49))
		return ;
	if ((*j) > g->d->height)
		return ;
	g->d->mapper[*j] = (char *)ft_calloc(sizeof(char), ft_strlen(line) + 1);
	if (!g->d->mapper[*j])
		exit(1);
	while (line[i] && line[i] != '\n')
	{
		g->d->mapper[*j][i] = line[i];
		printf("%c", g->d->mapper[*j][i]);
		i++;
	}
	printf("\n");
	(*j)++;
}
