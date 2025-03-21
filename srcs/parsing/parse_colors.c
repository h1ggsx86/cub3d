/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:01:10 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/20 15:12:50 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

u_int32_t	bitshift_op(t_game *g)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (g->d->colors->int_rgb[i] > 255)
			err_message(g, "colors", "color range between 0 and 255");
		i++;
	}
	return ((g->d->colors->int_rgb[0] << 16) | \
	(g->d->colors->int_rgb[1] << 8) | (g->d->colors->int_rgb[2]));
}

int	get_color(t_game *g, char *line, int n)
{
	int	i;
	
	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	g->d->colors->rgb = ft_calloc(sizeof(char), i + 1);
	if (!g->d->colors->rgb)
		exit_game(g, 3);
	ft_strlcpy((char *)g->d->colors->rgb, line, i + 1);
	if (n < 3)
		g->d->colors->int_rgb[n] = ft_atoi((const char *)g->d->colors->rgb);
	else
		exit_game(g, 3);
	free(g->d->colors->rgb);
	return (i);
}

void	cut_color(t_game *g, char *line, int idc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && j < 3)
	{
		i += get_color(g, line + i, j);
		j++;
		while (line[i] && (line[i] == ',' || !ft_isspace(line[i])))
			i++;
	}
	if (idc == 'F')
		g->d->roof_color = bitshift_op(g);
	else
		g->d->ground_color = bitshift_op(g);
	g->d->i_colors++;
	if (g->d->i_colors == 2)
		g->d->all_colors = true;
}

int	is_color(t_game *g, char *line)
{
	int	i;

	i = 0;
	if (line[i] == 'F' && !g->d->roof_color)
	{
		while (!ft_isdigit(line[i]))
			i++;
		cut_color(g, line + i, 'F');
	}
	else if (line[i] == 'C' && !g->d->ground_color)
	{
		while (!ft_isdigit(line[i]))
			i++;
		cut_color(g, line + i, 'C');
	}
	else
		return (1);
	return (0);
}

void	parse_colors(t_game *g, char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (is_color(g, line + i))
		return ; // implementer sortie d erreur
}
