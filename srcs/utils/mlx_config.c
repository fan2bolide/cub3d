/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:21:31 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/20 16:37:58 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub_mlx_config(t_cub *cub)
{
	mlx_hook(cub->win, KEY_PRESS, KEY_PRESS_MASK, \
		cub_handle_key_press, cub);
	mlx_hook(cub->win, KEY_RELEASE, KEY_RELEASE_MASK, \
		cub_handle_key_release, cub);
	mlx_hook(cub->win, MOTION_NOTIFY, POINTER_MOTION_MASK, \
		cub_handle_mouse_move, cub);
	mlx_hook(cub->win, DESTROY_NOTIFY, NO_EVENT_MASK, \
		close_window, cub);
	mlx_mouse_hook(cub->win, cub_handle_mouse, cub);
	mlx_hook(cub->win, BUTTON_RELEASE, BUTTON_RELEASE_MASK, \
		cub_handle_mouse_release, cub);
	mlx_hook(cub->win, BUTTON_PRESS, BUTTON_PRESS_MASK, \
		cub_handle_button_press, cub);
	mlx_loop_hook(cub->mlx, display_valve_guy, cub);
}
