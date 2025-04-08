/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_lines_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:29:22 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/08 10:38:14 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	put_line_l(t_game *g, t_ivector start, int x1, int y1)
{
	int			yi;
	int			d;
	t_ivector	dcoor;

	ivector_init(&dcoor, x1 - start.x, y1 - start.y);
	yi = 1;
	if (dcoor.y < 0)
	{
		yi = -1;
		dcoor.y = -dcoor.y;
	}
	d = (2 * dcoor.y) - dcoor.x;
	while (start.x <= x1)
	{
		put_pixel(g->d, start.x, start.y, 0x00ff00ff);
		if (d > 0)
		{
			start.y += yi;
			d += (2 * (dcoor.y - dcoor.x));
		}
		else
			d += 2 * dcoor.y;
		start.x++;
	}
}

void	put_line_h(t_game *g, t_ivector start, int x1, int y1)
{
	int			xi;
	int			d;
	t_ivector	dcoor;

	ivector_init(&dcoor, x1 - start.x, y1 - start.y);
	xi = 1;
	if (dcoor.x < 0)
	{
		xi = -1;
		dcoor.x = -dcoor.x;
	}
	d = (2 * dcoor.x) - dcoor.y;
	while (start.y <= y1)
	{
		put_pixel(g->d, start.x, start.y, 0x00ff00ff);
		if (d > 0)
		{
			start.x += xi;
			d += (2 * (dcoor.x - dcoor.y));
		}
		else
			d += 2 * dcoor.x;
		start.y++;
	}
}
