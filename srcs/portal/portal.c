/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:00:32 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/23 23:55:06 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	cross(t_cub *cub)
{
	t_int_position map_center;
	t_int_position cross_corner;

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

static void	point(t_cub *cub)
{
	t_int_position map_center;
	int	i;
	int	j;
	double	cos_calc;
	double	sin_calc;

	map_center.x = cub->win_size[WIDTH] / 2;
	map_center.y = cub->win_size[HEIGHT] / 2;
	i = 0;
	while (i < 360)
	{
		j = 0;
		cos_calc = cos(i * M_PI / 180);
		sin_calc = sin(i * M_PI / 180);
		while (j <= 5)
		{
			cub_pixel_put(&cub->img, map_center.x + j * cos_calc,
						  map_center.y + j * sin_calc, 0x778899);
			j++;
		}
		i++;
	}
}

void	display_crosshair(t_cub *cub)
{
	if (cub->cross_hair < 0)
		point(cub);
	else
		cross(cub);
}
