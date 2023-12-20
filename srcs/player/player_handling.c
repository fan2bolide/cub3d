/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:19:43 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/20 13:30:38 by nfaust           ###   ########.fr       */
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
			if (ft_isset(cub->data->map[(int)old_y][(int)new_x], "BOR"))
				return ;
			if (ft_isset(cub->data->map[(int) new_y][(int) old_x], "1GD"))
				return (cub->player_position.x = new_x, (void) 0);
		}
		if (!ft_isset(cub->data->map[(int)new_y][(int)old_x], "BOR"))
			cub->player_position.y = new_y;
		return ;
	}
	if ((int)old_y != (int)new_y)
		if (!ft_isset(cub->data->map[(int)old_y][(int)new_x], "BOR"))
			cub->player_position.x = new_x;
}

void	move_player(double x_change, double y_change, t_cub *cub)
{
	double	new_y;
	double	new_x;

	cub->last_player_pos.x = cub->player_position.x;
	cub->last_player_pos.y = cub->player_position.y;
	new_y = cub->player_position.y + y_change;
	new_x = cub->player_position.x + x_change;
	if (ft_isset(cub->data->map[(int)new_y] \
	[(int) cub->player_position.x], "1DGBORD")
		&& ft_isset(cub->data->map[(int)cub->player_position.y][(int)new_x],
		"1DGBORD"))
		return ;
	if (ft_isset(cub->data->map[(int)new_y][(int)new_x], "1DG"))
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
		move_player(cos(cub->view_angle) / cub->player_speed,
			sin(cub->view_angle) / cub->player_speed, cub);
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
