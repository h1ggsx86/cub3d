/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:37:51 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/08 10:38:00 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	apply_intensity(int color, double intensity)
{
	int	r;
	int	g;
	int	b;

	r = get_r(color);
	r *= intensity;
	g = get_g(color);
	g *= intensity;
	b = get_b(color);
	b *= intensity;
	return (0x00 << 24 | r << 16 | g << 8 | b);
}
