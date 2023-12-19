/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:38:30 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/17 18:05:36 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H
# include "cub3D.h"

# define MINIMAP_SCALE			10
# define MINIMAP_SIZE			50
# define MINIMAP_OFFSET			30
# define OUTER_MINIMAP_COLOR	0x000000

void	render_mini_map(t_cub *cub, t_position *ray_collision);
int		get_wall_height(t_cub *cub, t_position ray, double angle);
void	shoot_ray(t_position *ray, t_cub *cub, double angle);
void	cub_put_line(t_cub *cub, t_position a, t_position b, int color);
void	cub_pixel_put(t_image *data, int x, int y, int color);
int		cub_texture_put(int x, t_cub *cub, int wall_height,
			t_position ray_collision);
int		get_color_of_wall(int x, int y);
void	render_view(t_cub *cub, t_position *ray_collision, \
								const int *wall_height);
void	put_wall(t_cub *cub, int i, int j, int color);

#endif
