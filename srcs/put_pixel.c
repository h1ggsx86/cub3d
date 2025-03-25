/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/25 12:07:07 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_data *d, int x, int y, int color)
{
	char	*dst;
	t_mimg	*img;

	if (d->active_img)
		img = d->img_player + 1;
	else
		img = d->img_player;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_square(t_data *d, int xc, int yc, int c)
{
	int	y;
	int	x;

	y = 0;
	while (y < c)
	{
		x = 0;
		while (x < c)
		{
			put_pixel(d, xc + x, yc + y, d->color);
			x++;
		}
		y++;
	}
}

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
		put_pixel(g->d, x_start, pl.posY * 5 + y, g->d->color);
		x_start++;
	}
	while (x < x_end)
	{
		put_pixel(g->d, x, pl.posY * 5 - y, g->d->color);
		x++;
	}
}

void	put_player_circle(t_game *g, int color, int r)
{
	double x;
	double y;
	double	p;

	t_player (pl) = *g->pl;
	// t_data *(d) = g->d;
	(void)color;
	y = -r;
	p = -r;
	x = 0;
	while (x < -y)
	{
		if (p > 0)
		{
			y += 1;
			p += 2 * (x + y) + 1;
		}
		else
			p += 2 * x + 1;
		// put_pixel(d, pl.posX * 10 + x, pl.posY * 10 + y, color);
		// put_pixel(d, pl.posX * 10 - x, pl.posY * 10 + y, color);
		// put_pixel(d, pl.posX * 10 + x, pl.posY * 10 - y, color);
		// put_pixel(d, pl.posX * 10 - x, pl.posY * 10 - y, color);
		// put_pixel(d, pl.posX * 10 + y, pl.posY * 10 + x, color);
		// put_pixel(d, pl.posX * 10 - y, pl.posY * 10 + x, color);
		// put_pixel(d, pl.posX * 10 + y, pl.posY * 10 - x, color);
		// put_pixel(d, pl.posX * 10 - y, pl.posY * 10 - x, color);
		put_hline(g, pl.posX * 5 - x, pl.posX * 5 + x, y);
		put_hline(g, pl.posX * 5 + y, pl.posX * 5 - y, x);
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

void	put_player_line(t_game *g, int x, int y)
{
	double px;
	double py;

	px = g->pl->posX * 5;
	py = g->pl->posY * 5;
	if (abs(x - (int)px) > abs(y - (int)py))
	{
		if (px > x)
			put_lineL(g, x, y, px, py);
		else
			put_lineL(g, px, py, x, y);
	}
	else
	{
		if (py > y)
			put_lineH(g, x, y, px, py);
		else
			put_lineH(g, px, py, x, y);
	}
}
