/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:01:40 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/04 16:06:33 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_north_or_south(t_game *g, char *line, int idc)
{
	int	i;

	i = 0;
	if (idc == 78)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		line[i] = '\0';
		g->d->text_path[0] = ft_strdup(line);
		if (!g->d->text_path[0])
			return (1);
		g->d->i_text++;
		g->d->fd_texture[0] = open(g->d->text_path[0], O_RDONLY, 0664);
		if (g->d->fd_texture[0] < 0)
			return (1);
	}
	else if (idc == 83)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		line[i] = '\0';
		g->d->text_path[3] = ft_strdup(line);
		if (!g->d->text_path[3])
			return (1);
		g->d->i_text++;
		g->d->fd_texture[3] = open(g->d->text_path[3], O_RDONLY, 0664);
		if (g->d->fd_texture[3] < 0)
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
		g->d->text_path[2] = ft_strdup(line);
		if (!g->d->text_path[2])
			return (1);
		g->d->i_text++;
		g->d->fd_texture[2] = open(g->d->text_path[2], O_RDONLY, 0664);
		if (g->d->fd_texture[2] < 0)
			return (1);
	}
	else if (idc == 69)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		line[i] = '\0';
		g->d->text_path[1] = ft_strdup(line);
		if (!g->d->text_path[1])
			return (1);
		g->d->i_text++;
		g->d->fd_texture[1] = open(g->d->text_path[1], O_RDONLY, 0664);
		if (g->d->fd_texture[1] < 0)
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
	if (line[i] == 'N' && !g->d->text_path[0])
		get_textures(g, line, 78);
	else if (line[i] == 'S' && !g->d->text_path[3])
		get_textures(g, line, 83);
	else if (line[i] == 'W' && !g->d->text_path[2])
		get_textures(g, line, 87);
	else if (line[i] == 'E' && !g->d->text_path[1])
		get_textures(g, line, 69);
	else
	{
		free(line);
		err_message(g, "textures", "not found", 5);
	}
	return (0);
}
