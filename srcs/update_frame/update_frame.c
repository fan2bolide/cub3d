/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:50:06 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/18 11:51:17 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	update_frame(t_cub *cub)
{
	int	x;
	int	y;

	mouse_get_pos(cub, &x, &y);
	if (cub->menu.cursors[SPEED].is_pressed)
	{
		if (x < 862)
			x = 862;
		if (x > 1200)
			x = 1200;
		cub->menu.cursors[SPEED].x = x;
		cub->player_speed = 20 + (((int)cub->menu.cursors[SPEED].initial_pos.x
					- (int)cub->menu.cursors[SPEED].x) / 10);
	}
	if (cub->menu.cursors[SENSI].is_pressed)
	{
		if (x < 862)
			x = 862;
		if (x > 1200)
			x = 1200;
		cub->menu.cursors[SENSI].x = x;
		cub->sensivity = 0.017 + (double)((int)cub->menu.cursors[SENSI].x - (int)cub->menu.cursors[SENSI].initial_pos.x) / 10000;
	}
	if (cub->menu.reseters[SPEED].is_pressed)
	{
		cub->player_speed = 20;
		cub->menu.cursors[SPEED].x = (int) cub->menu.cursors[SPEED].initial_pos.x;
	}
	if (cub->menu.reseters[SENSI].is_pressed)
	{
		cub->sensivity = 0.017;
		cub->menu.cursors[SENSI].x = (int) cub->menu.cursors[SENSI].initial_pos.x;
	}
	cub_update_doors(cub);
	if ((cub->menu.cross_hair == 2 && cub->cross_hair > 0) || (cub->menu.cross_hair == 1 && cub->cross_hair < 0))
		cub->cross_hair *= -1;
	if (cub->keys_states[KEY_ESC])
		return (close_window(cub));
	if (cub->keys_states[KEY_W])
		cub_update_player_position(KEY_W, cub);
	if (cub->keys_states[KEY_A])
		cub_update_player_position(KEY_A, cub);
	if (cub->keys_states[KEY_S])
		cub_update_player_position(KEY_S, cub);
	if (cub->keys_states[KEY_D])
		cub_update_player_position(KEY_D, cub);
	if (cub->keys_states[KEY_F])
		cub->fov = M_PI_2;
	if (cub->keys_states[KEY_LEFT])
		cub_update_view_angle(KEY_LEFT, cub);
	if (cub->keys_states[KEY_RIGHT])
		cub_update_view_angle(KEY_RIGHT, cub);
	clear_lists(cub);
	return (render_frame(cub));
}
