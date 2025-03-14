/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:01:10 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/14 12:59:42 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

u_int32_t	bitshift_op(t_game *g)
{
	u_int32_t	ret;
	int			i;

	while (i < 3)
	{
		if (g->d->colors->int_rgb > 255)
			err_message(g, "colors", "color range between 0 and 255");
		i++;
	}
	return ((g->d->colors->int_rgb[0] << 16) | \
	(g->d->colors->int_rgb[1] << 8) | (g->d->colors->int_rgb[2]));
}

void	get_color(t_game *g, char *line, int i, int idc)
{
	int	j;

	j = 0;
	while (line[i])
	{
		while (ft_isdigit(line[i]))
		{
			g->d->colors->rgb[j] = line[i];
			i++;
		}
		g->d->colors->int_rgb[j] = ft_atoi(g->d->colors->rgb[j]);
		j++;
		if (line[i] == ',' || !ft_isspace(line[i]))
			i++;
		else
			break ;
	}
	if (idc == 'F')
		g->d->roof_color = bitshift_op(g);
	else
		g->d->ground_color = bitshift_op(g);
	g->d->i_colors++;
	if (g->d->i_colors == 2)
		g->d->all_colors == true;
}

int	is_color(t_game *g, char *line, int i)
{
	if (line[i] == 'F' && !g->d->roof_color)
		get_color(g, line, i, 'F');
	else if (line[i] == 'C' && !g->d->ground_color)
		get_color(g, line, i, 'C');
	else
		return (1);
	return (0);
}

void	parse_colors(t_game *g, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (!ft_isspace(line[i]))
			i++;
		if (is_color(g, line, i))
			err_message(g, "colors", "invalid indicator");
	}
}
