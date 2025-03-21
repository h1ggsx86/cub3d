/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:23:54 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/06 18:54:37 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	err_message(t_game *g, char *arg, char *mess)
{
	ft_putstr_fd("Club3D: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		write(2, ": ", 2);
	}
	if (!mess)
		perror("");
	else
		ft_putendl_fd(mess, 2);
	if (g->d->img_map)
		free(g->d->img_map);
	if (g->map > 0)
		close(g->map);
	exit(1);
}
