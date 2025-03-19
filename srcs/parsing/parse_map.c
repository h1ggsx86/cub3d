/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:46 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/19 15:33:59 by arotondo         ###   ########.fr       */
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
	if ((size_t)(*i) < ft_strlen(g->d->mapper[*j])) // go right
	{
		while (g->d->mapper[*j][*i] && g->d->mapper[*j + 1][*i] && \
			g->d->mapper[*j + 1][*i] != '1')
			(*i)++;
	}
	else // go left
	{
		while (g->d->mapper[*j][*i] && g->d->mapper[*j + 1][*i] && \
			g->d->mapper[*j + 1][*i] != '1')
			(*i)--;
	}
}

void	choose_top_bottom(t_game *g, int *i, int *j)
{
	if (*j < g->d->height) // go low
	{
		while (g->d->mapper[*j][*i] && g->d->mapper[*j][*i])
			(*j)++;
	}
	else // go top
	{
		while (g->d->mapper[*j][*i] && g->d->mapper[*j][*i])
			(*j)--;
	}
}

void	if_finish(t_game *g, int i, int j, bool *done)
{
	if (j == '0' && g->d->mapper[j][i] == '1')
	{
		perror("HERE");
		*done = true;
	}
	else if (j == '0' && g->d->mapper[j][i] != '1')
		return ; // implementer code d erreur
}

int	check_sides(t_game *g)
{
	int		i; // gauche a droit
	int		j; // haut en bas
	bool	all_around;

	i = 0;
	j = 0;
	all_around = false;
	while (g->d->mapper[j][i] && g->d->mapper[j][i] != '1')
		i++;
	while (g->d->mapper[j][i] && g->d->mapper[j][i] == '1')
		i++;
	// while (g->d->mapper[j][i] && g->d->mapper[j][i] == '1')
	// 	j++;
	while (all_around == false)
	{
		choose_top_bottom(g, &i, &j);
		choose_left_right(g, &i, &j);
		if_finish(g, i, j, &all_around);
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

void	parse_map(t_game *g, char *line, int j)
{
	int	i;

	i = 0;
	g->d->mapper[j] = (char *)ft_calloc(sizeof(char), ft_strlen(line) + 1);
	if (!g->d->mapper[j])
		exit(1);
	while (line[i])
	{
		g->d->mapper[j][i] = line[i];
		printf("%c", g->d->mapper[j][i]);
		i++;
	}
	check_sides(g);
	// if (is_line_correct(g, j))
}
