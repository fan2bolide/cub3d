/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:36:51 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/18 18:53:27 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub_update_fov(int keycode, t_cub *cub)
{
	if (keycode == KEY_Z)
		cub->fov -= 0.05;
	else
		cub->fov += 0.05;
	if (cub->fov > M_PI - 0.5)
		cub->fov = M_PI - 0.5;
	if (cub->fov < M_PI_4)
		cub->fov = M_PI_4;
}

void	cub_update_view_angle(int keycode, t_cub *cub)
{
	if (keycode == KEY_LEFT)
		cub->view_angle -= 0.017;
	else
		cub->view_angle += 0.017;
	if (cub->view_angle < 0)
		cub->view_angle += (2 * M_PI);
	else if (cub->view_angle > (2 * M_PI))
		cub->view_angle -= (2 * M_PI);
}

void	report_movement(double new_y, double new_x, t_cub *cub)
{
	double	old_x;
	double	old_y;

	old_x = cub->player_position->x;
	old_y = cub->player_position->y;
	if ((int)old_x != (int)new_x)
	{
		if ((int)old_y != (int)new_y)
			if (cub->data->map[(int)new_y][(int)old_x] == '1')
				return (cub->player_position->x = new_x, (void) 0);
		cub->player_position->y = new_y;
		return ;
	}
	if ((int)old_y != (int)new_y)
		cub->player_position->x = new_x;
}

void	move_player(double x_change, double y_change, t_cub *cub)
{
	double	new_y;
	double	new_x;

	new_y = cub->player_position->y + y_change;
	new_x = cub->player_position->x + x_change;
	if (cub->data->map[(int)new_y][(int) cub->player_position->x] == '1' \
	&& cub->data->map[(int)cub->player_position->y][(int)new_x] == '1')
		return ;
	if (cub->data->map[(int)new_y][(int)new_x] == '1')
		return (report_movement(new_y, new_x, cub));
	cub->player_position->y = new_y;
	cub->player_position->x = new_x;
}

void	cub_update_player_position(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		move_player(cos(cub->view_angle) / 20, sin(cub->view_angle) / 20, cub);
	if (keycode == KEY_S)
		move_player(-cos(cub->view_angle) / 20, \
		-sin(cub->view_angle) / 20, cub);
	if (keycode == KEY_A)
		move_player(cos(cub->view_angle - M_PI_2) / 20, \
		sin(cub->view_angle - M_PI_2) / 20, cub);
	if (keycode == KEY_D)
		move_player(cos(cub->view_angle + M_PI_2) / 20, \
		sin(cub->view_angle + M_PI_2) / 20, cub);
	if (cub->player_position->x - (int)cub->player_position->x < 0.0005)
		cub->player_position->x += 0.0005;
	if (cub->player_position->y - (int)cub->player_position->y < 0.0005)
		cub->player_position->y += 0.0005;
}
