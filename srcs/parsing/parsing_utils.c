/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:26:41 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/12 16:23:49 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_indicator(t_data *d, char *line)
{
	int	i;

	i = 0;
	if (ft_strnstr(line, "SO", ft_strlen(line)) && !d->south_path)
	{
		while (line[i] && line[i] != '/')
			i++;
		if (line[i])
			d->south_path = ft_substr(line, i, ft_strlen(line) - i);
		d->i_text++;
		return (0);
	}
	else if (ft_strnstr(line, "EA", ft_strlen(line)) && !d->east_path)
	{
		while (line[i] && line[i] != '/')
			i++;
		if (line[i])
			d->east_path = ft_substr(line, i, ft_strlen(line) - i);
		d->i_text++;
		return (0);
	}
	else if (ft_strnstr(line, "WE", ft_strlen(line)) && !d->west_path)
	{
		while (line[i] && line[i] != '/')
			i++;
		if (line[i])
			d->west_path = ft_substr(line, i, ft_strlen(line) - i);
		d->i_text++;
		return (0);
	}
	else if (ft_strnstr(line, "NO", ft_strlen(line)) && !d->north_path)
	{
		while (line[i] && line[i] != '/')
			i++;
		if (line[i])
			d->north_path = ft_substr(line, i, ft_strlen(line) - i);
		d->i_text++;
		return (0);
	}
	if (d->i_text == 4)
		d->all_text == true;
	return (1);
}

void	get_color(t_data *d, char *line, int i)
{
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (ft_isdigit(line[i]))
	{
		d->colors->r = line[i];
		i++;
	}
}

int		is_color(t_data *d, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			i++;
		else if (line[i] == 'F' &&)
			get_color(d, line, i++);
	}
}
