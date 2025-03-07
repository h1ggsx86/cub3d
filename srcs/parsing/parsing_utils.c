/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:26:41 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/07 19:45:36 by arotondo         ###   ########.fr       */
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
	return (1);
}
