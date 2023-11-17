/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 04:06:32 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/17 18:20:47 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	cub_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	cub_put_line(t_cub *cub, t_position a, t_position b, int color)
{
	int		i;
	int		steps;
	double	x;
	double	y;

	steps = ft_max(fabs(b.x - a.x), fabs(b.y - a.y)) * 2;
	x = a.x;
	y = a.y;
	i = 0;
	while (i <= steps)
	{
		if (round(x) >= 0 && round(x) < cub->win_size[WIDTH] && round(y) >= 0
			&& round(y) < cub->win_size[HEIGHT])
			if ((int)round(y) > a.y - MINIMAP_SIZE && (int)round(y) < a.y + MINIMAP_SIZE && (int)round(x) > a.x - MINIMAP_SIZE && (int)round(x) < a.x + MINIMAP_SIZE)
				cub_pixel_put(&cub->img, (int)round(x), (int)round(y), color);
		x += (b.x - a.x) / (double)steps;
		y += (b.y - a.y) / (double)steps;
		i++;
	}
}
