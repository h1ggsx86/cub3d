/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:01:10 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/04 16:26:12 by arotondo         ###   ########.fr       */
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

int	get_color(t_game *g, char *line, int n, char *pointer)
{
	int	i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	g->d->colors->rgb = ft_calloc(sizeof(char), i + 1);
	if (!g->d->colors->rgb)
	{
		free(pointer);
		err_message(g, "colors", "memory allocation failed", 3);
	}
	ft_strlcpy((char *)g->d->colors->rgb, line, i + 1);
	if (n < 3)
		g->d->colors->int_rgb[n] = ft_atoi((const char *)g->d->colors->rgb);
	free(g->d->colors->rgb);
	return (i);
}

void	cut_color(t_game *g, char *line, int idc, char *pointer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] && (line[i] == '+' || line[i] == '-'))
		{
			if (line[i] == '-')
			{
				free(pointer);
				err_message(g, "colors", "RGB values can't be negative", 4);
			}
			i++;
		}
		i += get_color(g, line + i, j, pointer);
		j++;
		while (line[i] && (line[i] == ',' || !ft_isspace(line[i])))
			i++;
		if (line[i] && line[i] != ',' && ft_isspace(line[i]) \
			&& !ft_isdigit(line[i]))
		{
			free(pointer);
			err_message(g, "colors", "bad separator", 4);
		}
	}
	if (j != 3)
	{
		free(pointer);
		err_message(g, "colors", "RGB must contains 3 values", 4);
	}
	init_colors(g, idc);
}

void	is_color(t_game *g, char *line, char *pointer)
{
	int	i;

	i = 0;
	if (line[i] == 'F' && !g->d->ground_color)
	{
		while (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
			i++;
		cut_color(g, line + i, 'F', pointer);
	}
	else if (line[i] == 'C' && !g->d->roof_color)
	{
		while (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
			i++;
		cut_color(g, line + i, 'C', pointer);
	}
	else
	{
		free(pointer);
		err_message(g, "colors", "bad indicator", 4);
	}
}

void	parse_colors(t_game *g, char *line)
{
	int	i;

	i = 0;
	if (!line || line[i] == '\n')
		return ;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	is_color(g, line + i, line);
}
