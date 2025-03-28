/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:29:22 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/28 19:51:39 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_vline(t_game *g, int y_start, int y_end, int x, int color)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		while (y < y_start)
		{
			put_pixel(g->d, x, y, g->d->roof_color);
			y++;
		}
		while (y <= y_end)
		{
			put_pixel(g->d, x, y, color);
			y++;
		}
		put_pixel(g->d, x, y, g->d->ground_color);
		y++;
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
		put_pixel(g->d, x_start, pl.y * 5 + y, 0x00ae24cd);
		x_start++;
	}
	while (x < x_end)
	{
		put_pixel(g->d, x, pl.y * 5 - y, 0x00ae24cd);
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
		put_pixel(g->d, x0, y0, 0x00ff00ff);
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
		put_pixel(g->d, x0, y0, 0x00ff00ff);
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
