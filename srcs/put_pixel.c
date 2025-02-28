/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/02/28 16:33:01 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_data *d, int x, int y, int color)
{
	char	*dst;
	t_mimg	*img;

	if (d->active_img)
		img = d->img2;
	else
		img = d->img1;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_player_square(t_data *d, t_player *pl, int color, int c)
{
	int	y;
	int	x;

	y = 0;
	while (y < c)
	{
		x = 0;
		while (x < c)
		{
			put_pixel(d, pl->posX + x, pl->posY + y, color);
			x++;
		}
		y++;
	}
}

void	put_line(t_data *d, t_player *pl, int color, double xy[2])
{
	double	x;

	x = -xy[0];
	while (x < xy[0])
	{
		put_pixel(d, pl->posX + x, pl->posY + xy[1], color);
		x++;
	}
	x = -xy[0];
	while (x < xy[0])
	{
		put_pixel(d, pl->posX + x, pl->posY - xy[1], color);
		x++;
	}
	x = -xy[1];
	while (x < xy[1])
	{
		put_pixel(d, pl->posX + x, pl->posY + xy[0], color);
		x++;
	}
	x = -xy[1];
	while (x < xy[1])
	{
		put_pixel(d, pl->posX + x, pl->posY - xy[0], color);
		x++;
	}
}

void	put_player_circle(t_data *d, t_player *pl, int color, int r)
{
	double	xy[2];
	double	p;

	xy[1] = -r;
	p = -r;
	xy[0] = 0;
	while (xy[0] < -xy[1])
	{
		if (p > 0)
		{
			xy[1] += 1;
			p += 2 * (xy[0] + xy[1]) + 1;
		}
		else
			p += 2 * xy[0] + 1;
		put_pixel(d, pl->posX + xy[0], pl->posY + xy[1], color);
		put_pixel(d, pl->posX - xy[0], pl->posY + xy[1], color);
		put_pixel(d, pl->posX + xy[0], pl->posY - xy[1], color);
		put_pixel(d, pl->posX - xy[0], pl->posY - xy[1], color);
		put_pixel(d, pl->posX + xy[1], pl->posY + xy[0], color);
		put_pixel(d, pl->posX - xy[1], pl->posY + xy[0], color);
		put_pixel(d, pl->posX + xy[1], pl->posY - xy[0], color);
		put_pixel(d, pl->posX - xy[1], pl->posY - xy[0], color);
		put_line(d, pl, color, xy);
		xy[0]++;
	}
}