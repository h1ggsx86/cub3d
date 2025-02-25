/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:41 by tnedel            #+#    #+#             */
/*   Updated: 2025/02/25 16:45:26 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_data *d, int x, int y, int color)
{
	char	*dst;

	dst = d->addr + (y * d->line_length + x * (d->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_square(t_data *d, int x_start, int y_start, int color)
{
	int	i;
	int	j;
	int	tmp;

	tmp = y_start;
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < d->width / 5)
		{
			put_pixel(d, j + x_start, tmp, color);
			j++;
		}
		tmp += (d->height / 5);
		i++;
	}
	tmp = x_start;
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < d->height / 5)
		{
			put_pixel(d, tmp, j + y_start, color);
			j++;
		}
		tmp += (d->width / 5);
		i++;
	}
}