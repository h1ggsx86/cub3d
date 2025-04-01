/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:20:42 by tnedel            #+#    #+#             */
/*   Updated: 2025/04/01 09:48:17 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	ft_get_time(void)
{
	struct timeval	tv;
	suseconds_t		current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1e3 + tv.tv_usec / 1e3;;
	return (current_time);
}