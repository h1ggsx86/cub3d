/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:26:43 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/08 15:55:03 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_ivector	t_ivector;
typedef struct s_fvector	t_fvector;
typedef struct s_color		t_color;
typedef struct s_mimg		t_mimg;
typedef struct s_data		t_data;
typedef struct s_player		t_player;
typedef struct s_game		t_game;

/* exit_game */
void	err_message(t_game *g, char *arg, char *mess, int ecode);
void	exit_game(t_game *g, int ecode);

/* put_pixel */
int		pixel_color(t_mimg texture, int x, int y);
void	put_pixel(t_data *d, int x, int y, int color);
void	put_square(t_game *g, int xc, int yc, int c);
void	put_player_line(t_game *g, t_ivector p, int x, int y);

/* put_pixel_lines */
void	put_line_l(t_game *g, t_ivector start, int x1, int y1);
void	put_line_h(t_game *g, t_ivector start, int x1, int y1);

/* ft_get_time */
long	ft_get_time(void);

/* get trgb*/
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		apply_intensity(int color, double intensity);

/* input */
void	moves_input(t_game *g);

/* free */
void	free_img(void *init, t_mimg *img);
void	free_incomp_text(t_game *g);
void	free_textures(void *init, t_mimg *img, t_game *g);
void	free_map(char **map);

#endif