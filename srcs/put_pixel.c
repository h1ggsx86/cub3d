/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/10 15:10:18 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_data *d, int x, int y, int color)
{
	char	*dst;
	t_mimg	*img;

	if (d->active_img)
		img = d->img_map + 1;
	else
		img = d->img_map;
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
	while (y_start < y_end)
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
		put_pixel(g->d, x_start, pl.posY + y, g->d->color);
		x_start++;
	}
	while (x < x_end)
	{
		put_pixel(g->d, x, pl.posY - y, g->d->color);
		x++;
	}
}

void	put_player_circle(t_game *g, int color, int r)
{
	double x;
	double y;
	double	p;

	t_player (pl) = *g->pl;
	t_data *(d) = g->d;
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
		put_pixel(d, pl.posX + x, pl.posY + y, color);
		put_pixel(d, pl.posX - x, pl.posY + y, color);
		put_pixel(d, pl.posX + x, pl.posY - y, color);
		put_pixel(d, pl.posX - x, pl.posY - y, color);
		put_pixel(d, pl.posX + y, pl.posY + x, color);
		put_pixel(d, pl.posX - y, pl.posY + x, color);
		put_pixel(d, pl.posX + y, pl.posY - x, color);
		put_pixel(d, pl.posX - y, pl.posY - x, color);
		put_hline(g, pl.posX - x, pl.posX + x, y);
		put_hline(g, pl.posX + y, pl.posX - y, x);
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
	t_player	p;

	p = *g->pl;
	if (abs(x - (int)p.posX) > abs(y - (int)p.posY))
	{
		if (p.posX > x)
			put_lineL(g, x, y, p.posX, p.posY);
		else
			put_lineL(g, p.posX, p.posY, x, y);
	}
	else
	{
		if (p.posY > y)
			put_lineH(g, x, y, p.posX, p.posY);
		else
			put_lineH(g, p.posX, p.posY, x, y);
	}
}

void	draw_map(t_game *g)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (worldMap[y * MAP_WIDTH + x] == 0)
				g->d->color = 0x00565656;
			else
				g->d->color = 0x00dadada;
			xo = x * MAP_SIZE;
			yo = y * MAP_SIZE;
			put_square(g->d, xo, yo, MAP_SIZE - 1);
			x++;
		}
		y++;
	}
	g->d->color = 0x00dadada;
}