/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/03/31 13:56:09 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	put_player_circle(t_game *g, int color, int r)
{
	double x;
	double y;
	double	p;

	t_player (pl) = *g->pl;
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
		put_hline(g, pl.x * 10 + 10 - x, pl.x * 10 + 10 + x, y);
		put_hline(g, pl.x * 10 + 10 + y, pl.x * 10 + 10 - y, x);
		x++;
	}
}

void	put_player_line(t_game *g, int px, int py, int x, int y)
{
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

int	pixel_color(t_mimg texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x > 64 || y < 0 || y > 64)
		return (0xFFFFFF);
	pixel = texture.addr + (y * texture.line_length + x * (texture.bpp / 8));
	return (*(unsigned int *)pixel);
}
