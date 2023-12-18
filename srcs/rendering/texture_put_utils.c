/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_put_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:02:59 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/18 12:05:52 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_texture_pixel_color(t_cub *cub, int texture_id, size_t x, size_t y)
{
	return (*((int *)(cub->textures[texture_id].addr + (y * \
		cub->textures[texture_id].line_length + x * \
		(cub->textures[texture_id].bits_per_pixel / 8)))));
}

int	set_custom_texture(int texture_id, double angle,
			t_position ray_collision, t_cub *cub)
{
	int	texture_x;

	if (ray_collision.x == (int)ray_collision.x)
	{
		if (cos(angle) < 0)
			texture_x = (int)(((int)(ray_collision.y) + 1 - ray_collision.y)
					* cub->textures[texture_id].width);
		else
			texture_x = (int)((ray_collision.y - (int)(ray_collision.y))
					* cub->textures[texture_id].width);
	}
	else
	{
		if (sin(angle) < 0)
			texture_x = (int)((ray_collision.x - ((int) ray_collision.x))
					* cub->textures[texture_id].width);
		else
			texture_x = (int)((((int)ray_collision.x) + 1 - ray_collision.x)
					* cub->textures[texture_id].width);
	}
	return (texture_x);
}

int	set_n_s_textures(size_t *texture_x,
						t_position ray_collision, t_cub *cub, double angle)
{
	int	texture_id;

	if (sin(angle) < 0)
	{
		texture_id = 0;
		*texture_x = (int)((ray_collision.x - ((int) ray_collision.x)) \
			* cub->textures[texture_id].width);
	}
	else
	{
		texture_id = 1;
		*texture_x = (int)((((int) ray_collision.x) + 1 - ray_collision.x) \
			* cub->textures[texture_id].width);
	}
	return (texture_id);
}

int	set_texture_id_and_x(size_t *texture_x,
			t_position ray_collision, t_cub *cub, double angle)
{
	int	texture_id;

	if (ray_collision.x == (int) ray_collision.x)
	{
		if (cos(angle) < 0)
		{
			texture_id = 2;
			*texture_x = (int)(((int)(ray_collision.y) + 1 - ray_collision.y) \
								* cub->textures[texture_id].width);
		}
		else
		{
			texture_id = 3;
			*texture_x = (int)((ray_collision.y - (int)(ray_collision.y)) \
								* cub->textures[texture_id].width);
		}
		return (texture_id);
	}
	return (set_n_s_textures(texture_x, ray_collision, cub, angle));
}
