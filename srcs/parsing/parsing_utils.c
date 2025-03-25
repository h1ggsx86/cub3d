/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:26:41 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/24 23:40:48 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

size_t	ft_vert_len(char **tab, int row, int max)
{
	size_t	i;

	if (!tab[0][row])
		return (0);
	else if (tab[0][row] == '\n')
		return (0);
	i = 0;
	while (i < (size_t)max && tab[i][row])
	{
		if (tab[i][0] == '\n')
			break ;
		i++;
	}
	return (i);
}
