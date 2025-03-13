/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:01:10 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/13 17:45:12 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	get_color(t_data *d, char *line, int i)
{
	if (line[i] == 'F')
	{
		while (ft_isdigit(line[i]))
		{
			d->colors->r = line[i];
			i++;
		}
	}
}

int		is_color(t_data *d, char *line, int i)
{
	if (line[i] == 'F' && !d->roof_color)
		get_color(d, line, i);
	else if (line[i] == 'C' && !d->ground_color)
		get_color(d, line, i);
	else
		return (1);
	return (0);
}

void	parse_colors(t_data *d, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (!ft_isspace(line[i]))
			i++;
		if (!is_color(d, line[i], i))
	}
}
