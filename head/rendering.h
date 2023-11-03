/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:38:30 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/03 04:24:33 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# include "cub3D.h"

void	render_mini_map(t_cub *cub, t_position ray_collision[cub->win_size[1]]);
int		get_wall_height(t_cub *cub, t_position ray, double angle);
void	shoot_ray(t_position *ray, t_cub *cub, double angle);
void	cub_put_line(t_cub *cub, t_position a, t_position b, int color);
void	cub_pixel_put(t_image *data, int x, int y, int color);
int		get_color_of_wall(int x, int y);

#endif