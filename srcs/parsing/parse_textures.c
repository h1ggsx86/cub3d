/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:01:40 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/17 18:52:58 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	get_north_or_south(t_data *d, char *line, int i, int idc)
{
	int	j;

	j = i;
	if (idc == 78)
	{
		while (line[j] && ft_isspace(line[j]))
			j++;
		d->north_path = ft_substr(line, i, j);
		d->i_text++;
	}
	else if (idc == 83)
	{
		while (line[j] && ft_isspace(line[j]))
			j++;
		d->south_path = ft_substr(line, i, j);
		d->i_text++;
	}
}

void	get_east_or_west(t_data *d, char *line, int i, int idc)
{
	int	j;

	j = i;
	if (idc == 87)
	{
		while (line[j] && ft_isspace(line[j]))
			j++;
		d->west_path = ft_substr(line, i, j);
		d->i_text++;
	}
	else if (idc == 69)
	{
		while (line[j] && ft_isspace(line[j]))
			j++;
		d->east_path = ft_substr(line, i, j);
		d->i_text++;
	}
}

void	get_textures(t_data *d, char *line, int idc)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] != '.' || line[i] != '/'))
		i++;
	if (idc == 78)
		get_north_or_south(d, line, i, 78);
	else if (idc == 83)
		get_north_or_south(d, line, i, 83);
	else if (idc == 87)
		get_east_or_west(d, line, i, 87);
	else if (idc == 69)
		get_east_or_west(d, line, i, 69);
	if (d->i_text == 4)
		d->all_text = true;
}

int	is_indicator(t_game *g, char *line)
{
	int	i;

	i = 0;
	while (!ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' && !g->d->north_path)
		get_textures(g->d, line, 78);
	else if (line[i] == 'S' && !g->d->south_path)
		get_textures(g->d, line, 83);
	else if (line[i] == 'W' && !g->d->west_path)
		get_textures(g->d, line, 87);
	else if (line[i] == 'E' && !g->d->east_path)
		get_textures(g->d, line, 69);
	else
		err_message(g, "textures", "Invalid texture path");
	return (0);
}
