/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:49:38 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/20 14:57:46 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_position	get_prtl_pos(t_cub *cub, char portal);

double	get_walk_angle(t_cub *cub)
{
	double	walk_angle;

	if (cub->keys_states[KEY_S] && cub->keys_states[KEY_A] \
		&& !cub->keys_states[KEY_D])
		walk_angle = cub->view_angle + M_PI + M_PI_4;
	else if (cub->keys_states[KEY_S] && cub->keys_states[KEY_D] \
		&& !cub->keys_states[KEY_A])
		walk_angle = cub->view_angle + M_PI - M_PI_4;
	else if (cub->keys_states[KEY_W] && cub->keys_states[KEY_A] \
		&& !cub->keys_states[KEY_D])
		walk_angle = cub->view_angle - M_PI_4;
	else if (cub->keys_states[KEY_W] && cub->keys_states[KEY_D] \
		&& !cub->keys_states[KEY_A])
		walk_angle = cub->view_angle + M_PI_4;
	else if (cub->keys_states[KEY_S] && !cub->keys_states[KEY_A])
		walk_angle = cub->view_angle + M_PI;
	else if (cub->keys_states[KEY_A] && !cub->keys_states[KEY_W])
		walk_angle = cub->view_angle - M_PI_2;
	else if (cub->keys_states[KEY_D] && !cub->keys_states[KEY_W])
		walk_angle = cub->view_angle + M_PI_2;
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

bool	is_rick_angle_right(t_cub *cub, double angle)
{
	double		angle_sin;
	double		angle_cos;
	t_position	prtl_pos;

	prtl_pos = get_prtl_pos(cub, 'R');
	angle_sin = sin(angle);
	if ((int)prtl_pos.x == (int)cub->player_position.x)
	{
		if (cub->rick_prtl == 'N' && angle_sin > 0)
			return (true);
		if (cub->rick_prtl == 'S' && angle_sin < 0)
			return (true);
	}
	angle_cos = cos(angle);
	if ((int)prtl_pos.y == (int)cub->player_position.y)
	{
		if (cub->rick_prtl == 'E' && angle_cos < 0)
			return (true);
		if (cub->rick_prtl == 'W' && angle_cos > 0)
			return (true);
	}
	return (false);
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
	walk_angle = get_walk_angle(cub);
	walk_angle_save = walk_angle;
	if (prtl_id == 'R' && is_rick_angle_right(cub, walk_angle))
		return (cub->player_position = cub->random_position, \
			cub->view_angle = cub->random_angle, set_random_position(cub),
			(void)0);
	if (teleport_ray(cub, &new_pos, &walk_angle, prtl_id))
		change_pos(cub, walk_angle, walk_angle_save, new_pos);
	else
		report_movement(new_y, new_x, cub);
}
