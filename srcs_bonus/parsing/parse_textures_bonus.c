/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:01:40 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/09 15:45:44 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

int	texture_is_valid(t_game *g, int flag)
{
	int	i;

	if (!g->d->text_path[flag])
		return (1);
	g->d->i_text++;
	i = ft_strlen(g->d->text_path[flag]) - 4;
	if (ft_strcmp(".xpm", g->d->text_path[flag] + i))
		return (1);
	g->d->fd_texture[flag] = open(g->d->text_path[flag], O_RDONLY, 0664);
	if (g->d->fd_texture[flag] < 0)
		return (1);
	close(g->d->fd_texture[flag]);
	return (0);
}

int	get_north_or_south(t_game *g, char *line, int idc)
{
	int	i;

	i = 0;
	if (idc == 78)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		line[i] = '\0';
		g->d->text_path[NORTH] = ft_strdup(line);
		if (texture_is_valid(g, NORTH))
			return (1);
	}
	else if (idc == 83)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		line[i] = '\0';
		g->d->text_path[SOUTH] = ft_strdup(line);
		if (texture_is_valid(g, SOUTH))
			return (1);
	}
	return (0);
}

int	get_east_or_west(t_game *g, char *line, int idc)
{
	int	i;

	i = 0;
	if (idc == 87)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		line[i] = '\0';
		g->d->text_path[WEST] = ft_strdup(line);
		if (texture_is_valid(g, WEST))
			return (1);
	}
	else if (idc == 69)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		line[i] = '\0';
		g->d->text_path[EAST] = ft_strdup(line);
		if (texture_is_valid(g, EAST))
			return (1);
	}
	return (0);
}

void	get_textures(t_game *g, char *line, int idc)
{
	int	i;
	int	flag;

	i = 0;
	flag = -1;
	while (line[i] && (line[i] != '.' && line[i] != '/'))
		i++;
	if (idc == 78 && get_north_or_south(g, line + i, 78))
		flag = NORTH;
	else if (idc == 83 && get_north_or_south(g, line + i, 83))
		flag = SOUTH;
	else if (idc == 87 && get_east_or_west(g, line + i, 87))
		flag = WEST;
	else if (idc == 69 && get_east_or_west(g, line + i, 69))
		flag = EAST;
	if (g->d->i_text == 4)
		g->d->all_text = true;
	if (flag >= 0)
	{
		free(line);
		err_message(g, g->d->text_path[flag], NULL, 5);
	}
}

int	is_indicator(t_game *g, char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] && (line[i + 1] == 'O' || \
		!ft_isspace(line[i + 1])) && !g->d->text_path[NORTH])
		get_textures(g, line, 78);
	else if (line[i] == 'S' && line[i + 1] && (line[i + 1] == 'O' || \
		!ft_isspace(line[i + 1])) && !g->d->text_path[SOUTH])
		get_textures(g, line, 83);
	else if (line[i] == 'W' && line[i + 1] && (line[i + 1] == 'E' || \
		!ft_isspace(line[i + 1])) && !g->d->text_path[WEST])
		get_textures(g, line, 87);
	else if (line[i] == 'E' && line[i + 1] && (line[i + 1] == 'A' || \
		!ft_isspace(line[i + 1])) && !g->d->text_path[EAST])
		get_textures(g, line, 69);
	else if (line[0] == '\n')
		return (0);
	else
	{
		free(line);
		err_message(g, "textures", "not found", 5);
	}
	return (0);
}
