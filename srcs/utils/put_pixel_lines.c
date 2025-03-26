/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:29:22 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/26 11:17:13 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	put_vline(t_game *g, int y_start, int y_end, int x, int color)
{
	while (y_start <= y_end)
	{
		put_pixel(g->d, x, y_start, color);
		y_start++;
	}
}

void	put_hline(t_game *g, int x_start, int x_end, int y)
{
	int	x;
	t_player	pl;

	pl = *g->pl;
	x = x_start;
	while (x_start < x_end)
	{
		put_pixel(g->d, x_start, pl.y * 5 + y, g->d->color);
		x_start++;
	}
	while (x < x_end)
	{
		put_pixel(g->d, x, pl.y * 5 - y, g->d->color);
		x++;
	}
}

void	put_lineL(t_game *g, int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	yi;
	int	D;

	dx = x1 - x0;
	dy = y1 - y0;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	D = (2 * dy) - dx;
	while (x0 <= x1)
	{
		put_pixel(g->d, x0, y0, g->d->color);
		if (D > 0)
		{
			y0 += yi;
			D += (2 * (dy - dx));
		}
		else
			D += 2 * dy;
		x0++;
	}
}

void	put_lineH(t_game *g, int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	xi;
	int	D;

	dx = x1 - x0;
	dy = y1 - y0;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = (2 * dx) - dy;
	while (y0 <= y1)
	{
		put_pixel(g->d, x0, y0, g->d->color);
		if (D > 0)
		{
			x0 += xi;
			D += (2 * (dx - dy));
		}
		else
			D += 2 * dx;
		y0++;
	}
}
