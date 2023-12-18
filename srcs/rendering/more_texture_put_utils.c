/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_texture_put_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:05:14 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/18 13:09:37 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "rendering.h"

bool	not_portal_side(t_position ray_collision, double angle, t_cub *cub)
{
	t_iposition	portal_index;
	char		prtl;
	char		prtl_or;

	portal_index = get_door_index(ray_collision, angle);
	prtl = cub->data->map[portal_index.y][portal_index.x];
	prtl_or = get_prtl_or(cub, prtl);
	if (ray_collision.x == (int) ray_collision.x)
	{
		if ((cos(angle) < 0 && prtl_or == 'E') || (cos(angle > 0)
				&& prtl_or == 'W'))
			return (false);
	}
	else if ((sin(angle) < 0 && prtl_or == 'S')
		|| (sin(angle > 0 && prtl_or == 'N')))
		return (false);
	return (true);
}

void	put_transparency(t_cub *cub, int x, int y, int texture_id)
{
	size_t	texture_x;

	if (texture_id != 7 && texture_id != 9 && texture_id != 8
		&& texture_id != 10)
		set_portal_texture(&texture_id, &texture_x, x, cub);
	if (texture_id == 7 || texture_id == 9)
		put_pixel_transparent(&cub->img, x, y, 0x703399ff);
	else if (texture_id == 8 || texture_id == 10)
		put_pixel_transparent(&cub->img, x, y, 0x70ff6600);
}

bool	is_portal_middle(t_cub *cub, t_iposition texture, int texture_id)
{
	if (((int)texture.x > cub->textures[texture_id].width / 5
			&& (int)texture.x < cub->textures[texture_id].width
			- cub->textures[texture_id].width / 5)
		&& ((int)texture.y > cub->textures[texture_id].height / 5
			&& (int)texture.y < cub->textures[texture_id].height
			- cub->textures[texture_id].width / 5))
		return (true);
	return (false);
}

void	put_outline_texture(int x, t_cub *cub, t_position ray_collision)
{
	int			texture_id;
	t_iposition	texture;

	if (not_portal_side(ray_collision, cub->portals[x]->portal->angle, cub))
		return ;
	texture_id = set_texture_id_and_x(&texture.x, ray_collision, cub,
			cub->portals[x]->portal->angle);
	put_outline_wall_slice(cub, x, texture_id, texture);
}

void	glass_put_transparency(int x, t_cub *cub, int wall_height)
{
	int			i;
	int			y;
	int			screen_wall_height;

	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[0])
		screen_wall_height = cub->win_size[0];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	i = 0;
	while (i < screen_wall_height)
	{
		if (y >= 0 && x >= 0 && y < cub->win_size[0] && x < cub->win_size[1])
			put_pixel_transparent(&cub->img, x, y, 0x50f0f5f5);
		y++;
		i++;
	}
}
