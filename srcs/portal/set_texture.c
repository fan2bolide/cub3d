/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 00:41:56 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/18 01:16:59 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "portal.h"

static bool	is_portal_texture(t_position ray_collision, t_cub *cub, int *texture_id)
{
	if (ray_collision.x == (int) ray_collision.x)
	{
		if (cub->player_position->x > ray_collision.x && (cub->orange_prtl == 'E' || cub->blue_prtl == 'E'))
		{
			if (cub->data->map[(int) ray_collision.y][(int) ray_collision.x - 1] == 'B')
				return (*texture_id = 5, true);
			if (cub->data->map[(int) ray_collision.y][(int) ray_collision.x - 1] == 'O')
				return (*texture_id = 6, true);
		}
		else if (cub->orange_prtl == 'W' || cub->blue_prtl == 'W')
		{
			if (cub->data->map[(int) ray_collision.y][(int) ray_collision.x] == 'B')
				return (*texture_id = 5, true);
			if (cub->data->map[(int) ray_collision.y][(int) ray_collision.x] == 'O')
				return (*texture_id = 6, true);
		}
		return (false);
	}
	if (cub->player_position->y > ray_collision.y && (cub->orange_prtl == 'N' || cub->blue_prtl == 'N'))
	{
		if (cub->data->map[(int) ray_collision.y - 1][(int) ray_collision.x] == 'B')
			return (*texture_id = 5, true);
		if (cub->data->map[(int) ray_collision.y - 1][(int) ray_collision.x] == 'O')
			return (*texture_id = 6, true);
	}
	else if (cub->orange_prtl == 'S' || cub->blue_prtl == 'S')
	{
		if (cub->data->map[(int)ray_collision.y][(int)ray_collision.x] == 'B')
			return (*texture_id = 5, true);
		if (cub->data->map[(int)ray_collision.y][(int)ray_collision.x] =='O')
			return(*texture_id = 6, true);
	}
	return (false);
}

void	set_portal_texture(int *texture_id, size_t *texture_x,
						   t_position ray_collision, t_cub *cub)
{
	int		save_texture_id;
	size_t	save_texture_x;

	save_texture_id = *texture_id;
	save_texture_x = *texture_x;
	if (!is_portal_texture(ray_collision, cub, texture_id))
		return ;
	set_custom_texture(texture_id, texture_x, ray_collision, cub);

}