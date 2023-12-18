/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:38:30 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/01 13:23:05 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H
# include "cub3D.h"
# define MINIMAP_SCALE			10
# define MINIMAP_SIZE			50
# define MINIMAP_OFFSET			30
# define OUT_COLOR	0x000000
# define IN_COLOR	0Xffe3b8

void		render_mini_map(t_cub *cub, t_position *ray_collision);
int			pixel_is_in_minimap(int x, int y, t_cub *cub);
void		put_walls(t_cub *cub);
int			shoot_ray(t_position *ray, t_cub *cub, double *angle, \
													double *distance);
void		cub_put_line(t_cub *cub, t_position a, t_position b, int color);
void cub_texture_put(int x, t_cub *cub, t_position ray_collision);
int			get_color_of_wall(int x, int y);
void		render_view(t_cub *cub, t_position *ray_collision, \
									const int *wall_height);
void		render_column(t_cub *cub, int column);
int			set_custom_texture(int texture_id, double angle,
					   t_position ray_collision, t_cub *cub);
void cub_portal_texture_put(int x, t_cub *cub, t_position ray_collision);
void cub_glass_texture_put(int x, t_cub *cub, t_position ray_collision);

int			get_wall_height(t_cub *cub, double wall_distance, double ray_angle);
t_position	get_prtl_pos(t_cub *cub, char portal);
char		get_prtl_or(t_cub *cub, char portal);
char		get_other_portal(char portal);
double		modulo_2_pi(double angle);
int			add_new_portal_to_ray(t_cub *cub, double distance, \
									t_position *ray, double *angle);
struct timeval	get_current_time(void);
long long	get_timestamp(struct timeval start_time, \
							struct timeval current_time);

#endif
