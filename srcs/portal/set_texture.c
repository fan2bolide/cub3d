/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 00:41:56 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/20 19:26:34 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "rendering.h"

static bool	is_portal_texture(t_position ray_collision, t_cub *cub, int *texture_id)
{
	if (ray_collision.x == (int) ray_collision.x)
	{
		if (cub->player_position->x > ray_collision.x && (cub->orange_prtl == 'E' || cub->blue_prtl == 'E'))
		{
			if (cub->data->map[(int) ray_collision.y][(int) ray_collision.x - 1] == 'B' && cub->blue_prtl == 'E')
				return (*texture_id = 5, true);
			if (cub->data->map[(int) ray_collision.y][(int) ray_collision.x - 1] == 'O' && cub->orange_prtl == 'E')
				return (*texture_id = 6, true);
		}
		else if (cub->orange_prtl == 'W' || cub->blue_prtl == 'W')
		{
			if (cub->data->map[(int) ray_collision.y][(int) ray_collision.x] == 'B' && cub->blue_prtl == 'W')
				return (*texture_id = 5, true);
			if (cub->data->map[(int) ray_collision.y][(int) ray_collision.x] == 'O' && cub->orange_prtl == 'W')
				return (*texture_id = 6, true);
		}
		return (false);
	}
	if (cub->player_position->y > ray_collision.y && (cub->orange_prtl == 'S' || cub->blue_prtl == 'S'))
	{
		if (cub->data->map[(int) ray_collision.y - 1][(int) ray_collision.x] == 'B' && cub->blue_prtl == 'S')
			return (*texture_id = 5, true);
		if (cub->data->map[(int) ray_collision.y - 1][(int) ray_collision.x] == 'O' && cub->orange_prtl == 'S')
			return (*texture_id = 6, true);
	}
	else if (cub->orange_prtl == 'N' || cub->blue_prtl == 'N')
	{
		if (cub->data->map[(int)ray_collision.y][(int)ray_collision.x] == 'B' && cub->blue_prtl == 'N')
			return (*texture_id = 5, true);
		if (cub->data->map[(int)ray_collision.y][(int)ray_collision.x] == 'O' && cub->orange_prtl == 'N')
			return(*texture_id = 6, true);
	}
	return (false);
}

void	set_portal_texture(int *texture_id, size_t *texture_x,
						   t_position ray_collision, t_cub *cub)
{
	if (ray_collision.x == 0 && ray_collision.y == 0)
		return ;
	if (!is_portal_texture(ray_collision, cub, texture_id))
		return ;
	if (cub->orange_prtl != '-' && cub->blue_prtl != '-')
	{
		if (*texture_id == 5)
			*texture_id = 7;
		if (*texture_id == 6)
			*texture_id = 8;
	}
	set_custom_texture(*texture_id, texture_x, ray_collision, cub);
}