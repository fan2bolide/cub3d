/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:38:35 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/18 13:15:28 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	cub_door_texture_put(int x, t_cub *cub, t_position *ray_collision)
{
	int			texture_id;
	t_iposition	texture;

	(void)ray_collision;
	texture_id = -1;
	set_door_texture(&texture_id, &texture.x, x, cub);
	if (texture_id == -1)
		return ;
	put_door_wall_slice(cub, texture_id, x, texture);
}

void	cub_texture_put(int x, t_cub *cub, t_position ray_collision)
{
	int			texture_id;
	t_iposition	texture;

	texture_id = set_texture_id_and_x(&texture.x, ray_collision, \
										cub, cub->angles[x]);
	put_wall_slice(cub, x, texture_id, texture);
}

void	cub_glass_texture_put(int x, t_cub *cub, t_position ray_collision)
{
	int			texture_id;
	t_iposition	texture;

	glass_put_transparency(x, cub, cub->glass[x]->portal->height);
	texture_id = 16;
	texture.x = set_custom_texture(texture_id, cub->glass[x]->portal->angle,
			ray_collision, cub);
	glass_put_wall_slice(cub, x, texture, texture_id);
}

void	cub_portal_texture_put(int x, t_cub *cub, t_position ray_collision)
{
	int			texture_id;
	t_iposition	texture;

	texture_id = -1;
	if (cub->menu.outline == 1)
		put_outline_texture(x, cub, ray_collision);
	set_portal_texture(&texture_id, &texture.x, x, cub);
	if (texture_id == -1)
		return ;
	portal_put_wall_slice(cub, x, texture, texture_id);
}
