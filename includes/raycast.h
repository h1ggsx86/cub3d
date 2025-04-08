/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:45:27 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/08 15:03:56 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3d.h"

typedef struct s_ivector	t_ivector;
typedef struct s_fvector	t_fvector;
typedef struct s_floor		t_floor;
typedef struct s_ray		t_ray;
typedef struct s_door		t_door;
typedef struct s_color		t_color;
typedef struct s_mimg		t_mimg;
typedef struct s_data		t_data;
typedef struct s_player		t_player;
typedef struct s_game		t_game;

/* loop_raycast */
void	set_var(t_ray *r, t_player p, int x);
int		dda_algo(t_game *g, t_ray *r);
void	ray_loop(t_game *g, t_player p);

/* render */
void	render_map(t_game *g, t_player p, t_data d);
void	render_pov(t_game *g);
void	render_img(t_game *g);

/* math_stuff */
void	calculate_dist(t_ray *r, t_player p);
void	calculate_tex(t_ray *r, double wall_x);

#endif