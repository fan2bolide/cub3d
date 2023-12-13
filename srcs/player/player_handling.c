/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:19:43 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/13 00:31:41 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	report_movement(double new_y, double new_x, t_cub *cub)
{
	double	old_x;
	double	old_y;

	old_x = cub->player_position.x;
	old_y = cub->player_position.y;
	if ((int)old_x != (int)new_x)
	{
		if ((int)old_y != (int)new_y)
		{
			if (ft_isset(cub->data->map[(int) old_y][(int) new_x], "BO"))
				return ;
			if (cub->data->map[(int) new_y][(int) old_x] == '1')
				return (cub->player_position.x = new_x, (void) 0);
		}
		if (ft_isset(cub->data->map[(int)new_y][(int)old_x], "BO"))
			return ;
		cub->player_position.y = new_y;
		return ;
	}
	if ((int)old_y != (int)new_y)
		if (!ft_isset(cub->data->map[(int)old_y][(int)new_x], "BO"))
			cub->player_position.x = new_x;
}

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
			cub->view_angle = cub->random_angle, set_random_position(cub), (void)0);
	walk_angle = get_walk_angle(cub);
	walk_angle_save = walk_angle;
	if (teleport_ray(cub, &new_pos, &walk_angle, prtl_id))
	{
		cub->player_position.x = new_pos.x - (0.00005 * (cos(walk_angle) < 0)) + (0.00005 * (cos(walk_angle) > 0));
		cub->player_position.y = new_pos.y - (0.00005 * (sin(walk_angle) < 0)) + (0.00005 * (sin(walk_angle) > 0));
		cub->view_angle += walk_angle - walk_angle_save;
	}
}

void	move_player(double x_change, double y_change, t_cub *cub)
{
	double	new_y;
	double	new_x;

	cub->last_player_pos.x = cub->player_position.x;
	cub->last_player_pos.y = cub->player_position.y;
	new_y = cub->player_position.y + y_change;
	new_x = cub->player_position.x + x_change;
	if (ft_isset(cub->data->map[(int)new_y][(int) cub->player_position.x],"1D") \
	&& ft_isset(cub->data->map[(int)cub->player_position.y][(int)new_x], "1D"))
		return ;
	if (ft_isset(cub->data->map[(int)new_y][(int)new_x], "1D"))
		return (report_movement(new_y, new_x, cub));
	else if (cub->data->map[(int)new_y][(int)new_x] == 'O')
		teleport_player(new_x, new_y, 'O', cub);
	else if (cub->data->map[(int)new_y][(int)new_x] == 'R')
		teleport_player(new_x, new_y, 'R', cub);
	else if (cub->data->map[(int)new_y][(int)new_x] == 'B')
		teleport_player(new_x, new_y, 'B', cub);
	else
	{
		cub->player_position.y = new_y;
		cub->player_position.x = new_x;
	}
}

void	cub_update_player_position(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		move_player(cos(cub->view_angle) / cub->player_speed, sin(cub->view_angle) / cub->player_speed, cub);
	if (keycode == KEY_S)
		move_player(-cos(cub->view_angle) / cub->player_speed, \
		-sin(cub->view_angle) / cub->player_speed, cub);
	if (keycode == KEY_A)
		move_player(cos(cub->view_angle - M_PI_2) / cub->player_speed, \
		sin(cub->view_angle - M_PI_2) / cub->player_speed, cub);
	if (keycode == KEY_D)
		move_player(cos(cub->view_angle + M_PI_2) / cub->player_speed, \
		sin(cub->view_angle + M_PI_2) / cub->player_speed, cub);
	if (cub->player_position.y - (int)cub->player_position.y < 0.0005)
		cub->player_position.y += 0.0005;
}
