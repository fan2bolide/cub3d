/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:38:44 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/18 09:25:06 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	cub_handle_mouse_move(int x, int y, t_cub *cub)
{
	double	view_angle;

	(void)y;
	if (!cub->menu.on_screen)
	{
		view_angle = cub->view_angle;
		if (cub->last_mouse_pos != -1)
			cub->view_angle += (x - cub->last_mouse_pos) \
								* M_PI / 64 * cub->sensivity;
		if (fabs(view_angle - cub->view_angle) > 0.001)
			cub_mouse_move(cub, cub->win_size[WIDTH] / 2, \
								cub->win_size[HEIGHT] / 2);
		cub->last_mouse_pos = cub->win_size[WIDTH] / 2;
	}
	return (1);
}

void	cub_update_view_angle(int keycode, t_cub *cub)
{
	if (keycode == KEY_LEFT)
		cub->view_angle -= cub->sensivity;
	else
		cub->view_angle += cub->sensivity;
	if (cub->view_angle < 0)
		cub->view_angle += (2 * M_PI);
	else if (cub->view_angle > (2 * M_PI))
		cub->view_angle -= (2 * M_PI);
}
