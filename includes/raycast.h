/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:45:27 by arotondo          #+#    #+#             */
/*   Updated: 2025/04/07 15:10:10 by tnedel           ###   ########.fr       */
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
int		dda_algo(t_game *g, t_ray *r);
void	ray_loop(t_game *g, t_player p);
void	set_var(t_ray *r, t_player p, int x);
void	calculate_dist(t_ray *r, t_player p);
void	draw_door(t_game *g, t_ray *r, t_player p, int x);
void	door_input(int keycode, t_game *g);
void	calculate_dist(t_ray *r, t_player p);
void	calculate_tex(t_ray *r, double wall_x);
void	calculate_door(t_ray *r, t_player p, double *step, double *tex_pos);
void	draw_floor(t_game *g, t_player p);
void	*init_door_map(t_game *g, t_data *d);

/* render */
void	render_map(t_game *g, t_player p, t_data d);
void	render_img(t_game *g);

/* door */
int		ray_check_door(t_game *g);
int		check_collisions_next(t_data *d, t_ray *r, int *hit);
void	handle_framerate(t_game *g, t_data *d, t_ray *r);

#endif