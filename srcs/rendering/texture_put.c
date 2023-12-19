/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:38:35 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/19 12:51:09 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	set_n_s_textures(int *texture_id, ssize_t *texture_x,
					t_position ray_collision, t_cub *cub)
{
	if (cub->player_position->y > ray_collision.y)
	{
		*texture_id = 0;
		*texture_x = (int)((ray_collision.x - ((int) ray_collision.x)) \
			* cub->textures[*texture_id].width);
	}
	else
	{
		*texture_id = 1;
		*texture_x = (int)((((int) ray_collision.x) + 1 - ray_collision.x) \
			* cub->textures[*texture_id].width);
	}
}

void	set_texture_id_and_x(int *texture_id, ssize_t *texture_x, \
							t_position ray_collision, t_cub *cub)
{
	if (ray_collision.x == (int) ray_collision.x)
	{
		if (cub->player_position->x > ray_collision.x)
		{
			*texture_id = 2;
			*texture_x = (int)(((int)(ray_collision.y) + 1 - ray_collision.y) \
								* cub->textures[*texture_id].width);
		}
		else
		{
			*texture_id = 3;
			*texture_x = (int)((ray_collision.y - (int)(ray_collision.y)) \
								* cub->textures[*texture_id].width);
		}
		return ;
	}
	set_n_s_textures(texture_id, texture_x, ray_collision, cub);
}

int	cub_texture_put(int x, t_cub *cub, int wall_height,
			t_position ray_collision)
{
	int			i;
	int			y;
	int			screen_wall_height;
	int			texture_id;
	t_iposition	texture;

	set_texture_id_and_x(&texture_id, &texture.x, ray_collision, cub);
	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[0])
		screen_wall_height = cub->win_size[0];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	i = 0;
	while (i < screen_wall_height)
	{
		texture.y = (i + (wall_height - screen_wall_height) / 2) \
				* cub->textures[texture_id].height / wall_height;
		if (texture.y > 0 && y >= 0 && x >= 0 && y < cub->win_size[0] && x < cub->win_size[1])
			cub_pixel_put(&cub->img, x, y, \
			*((int *)(cub->textures[texture_id].addr + (texture.y * \
			cub->textures[texture_id].line_length + texture.x * \
			(cub->textures[texture_id].bits_per_pixel / 8)))));
		y++;
		i++;
	}
	return (y);
}
