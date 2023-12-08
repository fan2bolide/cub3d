/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guns.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:38:36 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/08 00:54:55 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

t_iposition get_gun_position(t_cub *cub)
{
	t_iposition result;

	result.x = 45 * cub->win_size[WIDTH] / 100;
	result.y = 45 * cub->win_size[HEIGHT] / 100;
	return result;
}

void update_gun_pos(t_cub *cub)
{
	if (cub->keys_states[KEY_S] || cub->keys_states[KEY_D] || cub->keys_states[KEY_A] || cub->keys_states[KEY_W])
		cub->gun_movement += 0.05;
}

int	display_portal_gun(t_cub *cub)
{
	t_iposition gun_pos;
	t_iposition gun_size;
	t_iposition texture;
	int 		color;
	int			texture_id;

	gun_pos = get_gun_position(cub);
	gun_size.x = (cub->win_size[WIDTH] - gun_pos.x) * 1;
	gun_size.y = (cub->win_size[HEIGHT] - gun_pos.y) * 1.5;
	texture_id = 13;
	update_gun_pos(cub);
	int y = (int)gun_pos.y;
	while (y < (int)(gun_size.y + gun_pos.y))
	{
		int x = (int)gun_pos.x;
		while (x < (int)(gun_size.x + gun_pos.x))
		{
			texture.x = (x - gun_pos.x) * cub->textures[texture_id].width / gun_size.x;
			texture.y = (y - gun_pos.y) * cub->textures[texture_id].width / gun_size.y;
			color = *((int *) (cub->textures[texture_id].addr + (texture.y * \
				cub->textures[texture_id].line_length + texture.x * \
				(cub->textures[texture_id].bits_per_pixel / 8))));
			if (color >= 0 && x < cub->win_size[WIDTH] && (y  + (sin(cub->gun_movement) * 15)) < cub->win_size[HEIGHT])
				cub_pixel_put(&cub->img, x, y  + (sin(cub->gun_movement) * 15), color);
			x++;
		}
		y++;
	}
	return (1);
}