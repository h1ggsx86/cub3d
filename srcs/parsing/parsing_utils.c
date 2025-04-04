/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:26:41 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/26 11:29:17 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
