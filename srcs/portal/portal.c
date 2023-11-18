/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:00:32 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/18 00:35:20 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	display_crosshair(t_cub *cub)
{
	t_iposition map_center;
	t_iposition cross_corner;

	map_center.x = cub->win_size[WIDTH] / 2;
	map_center.y = cub->win_size[HEIGHT] / 2;
	cross_corner.y = map_center.y - 10;
	while (cross_corner.y <= map_center.y + 10)
	{
		cross_corner.x = map_center.x - 10;
		while (cross_corner.x <= map_center.x + 10)
		{
			if (cross_corner.x == map_center.x || cross_corner.x == map_center.x + 1 || cross_corner.y == map_center.y || cross_corner.y == map_center.y + 1)
				cub_pixel_put(&cub->img, cross_corner.x, cross_corner.y, 0x778899);
			cross_corner.x++;
		}
		cross_corner.y++;
	}
}

