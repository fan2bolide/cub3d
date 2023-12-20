/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_button_press.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:38:13 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/20 16:40:42 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	cub_handle_button_press(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (button == BUTTON_LEFT)
		set_portal_on_map(cub, 'B');
	if (button == BUTTON_RIGHT)
		set_portal_on_map(cub, 'O');
	return (0);
}
