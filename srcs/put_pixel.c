/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/06 16:22:57 by tnedel           ###   ########.fr       */
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

void	put_player_square(t_data *d, t_player *pl, int c)
{
	int	y;
	int	x;

	y = 0;
	while (y < c)
	{
		x = 0;
		while (x < c)
		{
			put_pixel(d, pl->posX * 5 + x, pl->posY * 5 + y, d->color);
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

void	put_lineH(t_game *g, int vpos[2], int vend[2])
{
	int	x;
	int	y;
	int	p;
	int	dy;
	int	dx;
	int	dir;

	if (vpos[0] > vend[0])
	{
		x = vend[0];
		vend[0] = vpos[0];
		vpos[0] = x;
	}
	dy = vend[1] - vpos[1];
	dx = vend[0] - vpos[0];
	if (dy < 0)
		dir = -1;
	else
		dir = 1;
	dy *= dir;
	y = vpos[1];
	p = 2 * dy - dx;
	x = 0;
	while (x < dx)
	{
		put_pixel(g->d, vpos[0] + x, y, 0x00dadada);
		if (p > 0)
		{
			y += dir;
			p = p - 2 * (dy - dx);
		}
		else
			p = p + 2 * dy;
		x++;
	}
}

void	put_lineV(t_game *g, int vpos[2], int vend[2])
{
	int	x;
	int	y;
	int	p;
	int	dy;
	int	dx;
	int	dir;

	if (vpos[1] > vend[1])
	{
		x = vend[1];
		vend[1] = vpos[1];
		vpos[1] = x;
	}
	dy = vend[1] - vpos[1];
	dx = vend[0] - vpos[0];
	if (dx < 0)
		dir = -1;
	else
		dir = 1;
	dx *= dir;
	y = vpos[0];
	p = 2 * dy - dx;
	x = 0;
	while (x < dx)
	{
		put_pixel(g->d, y, vpos[1] + x, 0x00dadada);
		if (p >= 0)
		{
			y += dir;
			p = p - 2 * (dx - dy);
		}
		else
			p = p + 2 * dx;
		x++;
	}
}

void	put_player_line(t_game *g, int x, int y)
{
	int			vpos[2];
	int			vend[2];
	t_player	p;

	p = *g->pl;
	vpos[0] = p.posX;
	vpos[1] = p.posY;
	vend[0] = x;
	vend[1] = y;
	if (abs(x - (int)p.posX) > abs(y - (int)p.posY))
		put_lineH(g, vpos, vend);
	else
		put_lineV(g, vpos, vend);
}