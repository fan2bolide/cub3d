/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:49:38 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/18 08:56:54 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_walk_angle(t_cub *cub)
{
	double	walk_angle;

	if (cub->keys_states[KEY_S])
		walk_angle = cub->view_angle + M_PI;
	else if (cub->keys_states[KEY_A])
		walk_angle = cub->view_angle - M_PI_2;
	else if (cub->keys_states[KEY_D])
		walk_angle = cub->view_angle + M_PI;
	else
		walk_angle = cub->view_angle;
	return (walk_angle);
}

void	change_pos(t_cub *cub, double walk_angle, double walk_angle_save,
			t_position new_pos)
{
	cub->player_position.x = new_pos.x - (0.00005 * (cos(walk_angle) < 0))
		+ (0.00005 * (cos(walk_angle) > 0));
	cub->player_position.y = new_pos.y - (0.00005 * (sin(walk_angle) < 0))
		+ (0.00005 * (sin(walk_angle) > 0));
	cub->view_angle += walk_angle - walk_angle_save;
}

void	teleport_player(double new_x, double new_y, char prtl_id, t_cub *cub)
{
	t_position	new_pos;
	double		walk_angle;
	double		walk_angle_save;

	if ((int)new_x > (int)cub->player_position.x \
		|| (int)new_x < (int)cub->player_position.x)
		new_pos.x = (int)new_x;
	else
		new_pos.x = new_x;
	if ((int)new_y > (int)cub->player_position.y \
		|| (int)new_y < (int)cub->player_position.y)
		new_pos.y = (int)new_y;
	else
		new_pos.y = new_y;
	if (prtl_id == 'R')
		return (cub->player_position = cub->random_position, \
			cub->view_angle = cub->random_angle, set_random_position(cub),
			(void)0);
	walk_angle = get_walk_angle(cub);
	walk_angle_save = walk_angle;
	if (teleport_ray(cub, &new_pos, &walk_angle, prtl_id))
		change_pos(cub, walk_angle, walk_angle_save, new_pos);
}
