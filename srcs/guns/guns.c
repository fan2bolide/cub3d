/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guns.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:38:36 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/08 16:18:38 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void update_gun_pos(t_cub *cub)
{
	if (cub->keys_states[KEY_S] || cub->keys_states[KEY_D] || cub->keys_states[KEY_A] || cub->keys_states[KEY_W])
		cub->gun_movement += 0.1;
}

int	display_portal_gun(t_cub *cub)
{
	t_iposition gun_size;
	t_iposition texture;
	int 		color;
	int			texture_id;

	gun_size.x = (cub->win_size[WIDTH] - cub->gun_position.x) * 1;
	gun_size.y = (cub->win_size[HEIGHT] - cub->gun_position.y) * 1.5;
	texture_id = 13;
	update_gun_pos(cub);
	int sin_movement = sin(cub->gun_movement) * 15;
	int y = (int)cub->gun_position.y;
	while (y < (int)(gun_size.y + cub->gun_position.y))
	{
		texture.y = (y - cub->gun_position.y) * cub->textures[texture_id].height / gun_size.y;
		int x = (int)cub->gun_position.x;
		while (x < cub->win_size[WIDTH])
		{
			texture.x = (x - cub->gun_position.x) * cub->textures[texture_id].width / gun_size.x;
			color = *((int *) (cub->textures[texture_id].addr + (texture.y * \
				cub->textures[texture_id].line_length + texture.x * \
				(cub->textures[texture_id].bits_per_pixel / 8))));
			if (color >= 0 && x < cub->win_size[WIDTH] && (y + sin_movement) < cub->win_size[HEIGHT])
				cub_pixel_put(&cub->img, x, y + sin_movement, color);
			x++;
		}
		y++;
	}
	return (1);
}