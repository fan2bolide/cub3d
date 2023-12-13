/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guns.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:38:36 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/13 01:33:41 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

double	get_player_speed(t_cub *cub)
{
	t_position	player;
	t_position	last;

	player = cub->player_position;
	player.x *= 1000;
	player.y *= 1000;
	last = cub->last_player_pos;
	last.x *= 1000;
	last.y *= 1000;
	return (compute_distance(player, last));
}

/**
 * updates the gun position on the image
 * -makes it move as the sinus of cub->gun_movement if the player moves
 * -reset the position if the player don't move
 * @param cub
 */
void	update_gun_pos(t_cub *cub)
{
	double	moving_speed;

	moving_speed = get_player_speed(cub);
	if (cub->keys_states[KEY_W] || cub->keys_states[KEY_A] \
		|| cub->keys_states[KEY_S] || cub->keys_states[KEY_D])
		cub->gun_movement += moving_speed / 500;
	else
	{
		if (sin(cub->gun_movement) > 0)
		{
			if (cos(cub->gun_movement) > 0)
				cub->gun_movement -= 0.05;
			else
				cub->gun_movement += 0.05;
		}
		else
		{
			if (cos(cub->gun_movement) > 0)
				cub->gun_movement += 0.05;
			else
				cub->gun_movement -= 0.05;
		}
	}
}

static bool	is_pixel_valid(t_cub *cub, int x, int y, int color)
{
	return (color >= 0 \
		&& x < cub->win_size[WIDTH] \
		&& y < cub->win_size[HEIGHT]);
}

void	display_gun(t_cub *cub,
					t_iposition gun_size,
					t_iposition texture,
					int texture_id)
{
	int	sin_movement;
	int	x;
	int	y;
	int	color;

	y = cub->gun_position.y;
	sin_movement = sin(cub->gun_movement) * 15;
	while (y < (int)(gun_size.y + cub->gun_position.y))
	{
		texture.y = (y - cub->gun_position.y) * \
			cub->textures[texture_id].height / gun_size.y;
		x = (int)cub->gun_position.x;
		while (x < cub->win_size[WIDTH])
		{
			texture.x = (x - cub->gun_position.x) * \
				cub->textures[texture_id].width / gun_size.x;
			color = *((int *)(cub->textures[texture_id].addr + (texture.y * \
				cub->textures[texture_id].line_length + texture.x * \
				(cub->textures[texture_id].bits_per_pixel / 8))));
			if (is_pixel_valid(cub, x, y + sin_movement, color))
				cub_pixel_put(&cub->img, x, y + sin_movement, color);
			x++;
		}
		y++;
	}
}

/**
 *
 * @param cub
 */
void	display_portal_gun(t_cub *cub)
{
	t_iposition	gun_size;
	t_iposition	texture;
	int			texture_id;

	gun_size.x = (cub->win_size[WIDTH] - cub->gun_position.x) * 1;
	gun_size.y = (cub->win_size[HEIGHT] - cub->gun_position.y) * 1.5;
	if (cub->last_portal_placed == 'B')
		texture_id = 13;
	if (cub->last_portal_placed == 'O')
		texture_id = 14;
	if (cub->last_portal_placed == 'R')
		texture_id = 15;
	update_gun_pos(cub);
	display_gun(cub, gun_size, texture, texture_id);
}
