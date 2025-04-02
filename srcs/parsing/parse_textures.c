/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:01:40 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/02 13:15:56 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_north_or_south(t_game *g, char *line, int idc)
{
	int	i;

	i = 0;
	if (idc == 78)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		line[i] = '\0';
		g->d->north_path = ft_strdup(line);
		if (!g->d->north_path)
			err_message(g, g->d->north_path, NULL, 5);
		g->d->i_text++;
	}
	else if (idc == 83)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		line[i] = '\0';
		g->d->south_path = ft_strdup(line);
		if (!g->d->south_path)
			err_message(g, g->d->south_path, NULL, 5);
		g->d->i_text++;
	}
}

void	get_east_or_west(t_game *g, char *line, int idc)
{
	int	i;

	i = 0;
	if (idc == 87)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		line[i] = '\0';
		g->d->west_path = ft_strdup(line);
		if (!g->d->west_path)
			err_message(g, g->d->west_path, NULL, 5);
		g->d->i_text++;
	}
	else if (idc == 69)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		line[i] = '\0';
		g->d->east_path = ft_strdup(line);
		if (!g->d->east_path)
			err_message(g, g->d->east_path, NULL, 5);
		g->d->i_text++;
	}
}

void	get_textures(t_game *g, char *line, int idc)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] != '.' && line[i] != '/'))
		i++;
	if (idc == 78)
		get_north_or_south(g, line + i, 78);
	else if (idc == 83)
		get_north_or_south(g, line + i, 83);
	else if (idc == 87)
		get_east_or_west(g, line + i, 87);
	else if (idc == 69)
		get_east_or_west(g, line + i, 69);
	if (g->d->i_text == 4)
		g->d->all_text = true;
}

int	is_indicator(t_game *g, char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' && !g->d->north_path)
		get_textures(g, line, 78);
	else if (line[i] == 'S' && !g->d->south_path)
		get_textures(g, line, 83);
	else if (line[i] == 'W' && !g->d->west_path)
		get_textures(g, line, 87);
	else if (line[i] == 'E' && !g->d->east_path)
		get_textures(g, line, 69);
	else
		err_message(g, "textures", "not found", 5);
	return (0);
}
