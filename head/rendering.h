/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:38:30 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/24 00:16:40 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H
# include "cub3D.h"
# define MINIMAP_SCALE			10
# define MINIMAP_SIZE			50
# define MINIMAP_OFFSET			30
# define OUTER_MINIMAP_COLOR	0x000000

void		render_mini_map(t_cub *cub, t_position *ray_collision);
int			pixel_is_in_minimap(int x, int y, t_cub *cub);
void		put_walls(t_cub *cub);
int			shoot_ray(t_position *ray, t_cub *cub, double *angle, \
													double *distance);
void		cub_put_line(t_cub *cub, t_position a, t_position b, int color);
int			cub_texture_put(int x, t_cub *cub, int wall_height,
				t_position ray_collision);
int			get_color_of_wall(int x, int y);
void		render_view(t_cub *cub, t_position *ray_collision, \
									const int *wall_height);
void		set_custom_texture(int texture_id, size_t *texture_x,
				t_position ray_collision, t_cub *cub);
int			cub_portal_texture_put(int x, t_cub *cub, int wall_height,
				t_position ray_collision);
int			get_wall_height(t_cub *cub, double wall_distance, double ray_angle);
t_position	get_prtl_pos(t_cub *cub, char portal);
char		get_prtl_or(t_cub *cub, char portal);
char		get_other_portal(char portal);

#endif
