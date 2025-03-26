/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:01:10 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/26 12:37:12 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

u_int32_t	bitshift_op(t_game *g)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (g->d->colors->int_rgb[i] > 255)
			g->d->colors->int_rgb[i] %= 256;
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
		err_message(g, "colors", "memory allocation failed", 3);
	ft_strlcpy((char *)g->d->colors->rgb, line, i + 1);
	if (n < 3)
		g->d->colors->int_rgb[n] = ft_atoi((const char *)g->d->colors->rgb);
	// else
	// 	exit_game(g, 3);
	free(g->d->colors->rgb);
	return (i);
}

void	cut_color(t_game *g, char *line, int idc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while(line[i] == '+' || line[i] == '-')
		{
			if (line[i] == '-')
				err_message(g, "colors", "RGB values can't be negative", 4);
			i++;
		}
		i += get_color(g, line + i, j);
		j++;
		while (line[i] && (line[i] == ',' || !ft_isspace(line[i])))
			i++;
	}
	if (j != 3)
		err_message(g, "colors", "RGB must contains 3 values", 4);
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
		while (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
			i++;
		printf("line[i] = %c\n", line[i]);
		cut_color(g, line + i, 'F');
	}
	else if (line[i] == 'C' && !g->d->ground_color)
	{
		while (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
			i++;
		printf("line[i] = %c\n", line[i]);
		cut_color(g, line + i, 'C');
	}
	return (0);
}

void	parse_colors(t_game *g, char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (is_color(g, line + i))
	{
		err_message(g, "colors", "invalid format", 4);
		exit_game(g, 255);
	}
}
