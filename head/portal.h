/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:00:56 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/18 00:22:57 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PORTAL_H
# define PORTAL_H

# include "cub3D.h"
# ifndef RENDERING_H
#  include "rendering.h"
# endif

void	display_crosshair(t_cub *cub);
void	set_portal_on_map(t_cub *cub, char prtl_id);
void	set_portal_texture(int *texture_id, size_t *texture_x,
						   t_position ray_collision, t_cub *cub);

#endif