/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:57:52 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/18 08:42:01 by nfaust           ###   ########.fr       */
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

void	handle_special_keys(t_cub *cub, int keycode)
{
	if (!cub->menu.on_screen || keycode == KEY_TAB)
	{
		if (keycode == KEY_R)
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
}

int	cub_handle_key_press(int keycode, t_cub *cub)
{
	if (keycode && keycode > 65508)
		return (0);
	if (cub->load_screen.img && keycode == KEY_RETURN)
		return (remove_load_screen(cub), 1);
	handle_special_keys(cub, keycode);
	if (keycode == KEY_ESC)
	{
		if (cub->menu.on_screen)
			return (handle_menu(cub), 0);
		return (close_window(cub), 0);
	}
	return (1);
}
