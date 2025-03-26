/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:26:43 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/26 12:42:28 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_color	t_color;
typedef struct s_mimg	t_mimg;
typedef struct s_data	t_data;
typedef struct s_player	t_player;
typedef struct s_game	t_game;

/* exit_game */
void	err_message(t_game *g, char *arg, char *mess, int ecode);
void	free_img(void *init, t_mimg *img);
void	exit_game(t_game *g, int ecode);

/* put_pixel */
void	put_pixel(t_data *d, int x, int y, int color);
void	put_square(t_data *d, int xc, int yc, int c);
void	put_player_circle(t_game *g, int color, int r);
void	put_player_line(t_game *g, int x, int y);

/* put_pixel_lines */
void	put_vline(t_game *g, int y_start, int y_end, int x, int color);
void	put_hline(t_game *g, int x_start, int x_end, int y);
void	put_lineL(t_game *g, int x0, int y0, int x1, int y1);
void	put_lineH(t_game *g, int x0, int y0, int x1, int y1);

# endif