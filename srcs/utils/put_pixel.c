/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/07 18:08:35 by tnedel           ###   ########.fr       */
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

void	put_square(t_game *g, int xc, int yc, int c)
{
	int	y;
	int	x;

	y = 0;
	while (y < c)
	{
		x = 0;
		while (x < c)
		{
			put_pixel(g->d, xc + x, yc + y, g->color);
			x++;
		}
		y++;
	}
}

void	put_player_line(t_game *g, t_ivector p, int x, int y)
{
	t_ivector	xy;

	ivector_init(&xy, x, y);
	if (abs(x - (int)p.x) > abs(y - (int)p.y))
	{
		if (p.x > x)
			put_line_l(g, xy, p.x, p.y);
		else
			put_line_l(g, p, x, y);
	}
	else
	{
		if (p.y > y)
			put_line_h(g, xy, p.x, p.y);
		else
			put_line_h(g, p, x, y);
	}
}

int	pixel_color(t_mimg texture, int x, int y)
{
	char	*pixel;

	pixel = texture.addr + (y * texture.line_length + x * (texture.bpp / 8));
	return (*(unsigned int *)pixel);
}
