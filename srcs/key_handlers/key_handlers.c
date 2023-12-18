/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:57:52 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/13 00:57:52 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	cub_handle_key_release(int keycode, t_cub *cub)
{
	if (keycode && keycode > 65508)
		return (0);
	cub->keys_states[keycode] = RELEASED;
	return (1);
}

int cub_handle_key_press(int keycode, t_cub *cub)
{
	if (keycode && keycode > 65508)
		return (0);
	if (cub->load_screen.img && keycode == KEY_RETURN)
		return (remove_load_screen(cub), 1);
	if (!cub->menu.on_screen || keycode == KEY_TAB)
	{
		if (keycode == KEY_T)
			set_portal_on_map(cub, 'B');
		else if (keycode == KEY_Y)
			set_portal_on_map(cub, 'O');
		else if (keycode == KEY_R)
		{
			set_portal_on_map(cub, 'R');
			set_random_position(cub);
		}
		else if (keycode == KEY_E)
			open_door(cub);
		else if (keycode == KEY_TAB)
			handle_menu(cub);
		else
			cub->keys_states[keycode] = PRESSED;
	}
	if (keycode == KEY_ESC) {
		if (cub->menu.on_screen)
			return (handle_menu(cub), 0);
		return (close_window(cub), 0);
	}
	return (1);
}
