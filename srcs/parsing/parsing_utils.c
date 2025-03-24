/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:26:41 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/24 16:03:35 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

size_t	ft_vert_len(char **tab, int row, int max)
{
	size_t	i;

	if (!tab[0][row])
	{
		perror("HERE4");
		return (0);
	}
	else if (tab[0][row] == '\n')
	{
		perror("HERE5");
		return (0);
	}
	i = 0;
	while (tab[i][row] && i < (size_t)max)
	{
		if (tab[i][0] == '\n')
			break ;
		i++;
	}
	return (i);
}
