/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 04:06:32 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/05 20:32:19 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	cub_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

//	if (y < 0 || x < 0 || x > data->width || y > data->height)
//		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	cub_put_line(t_cub *cub, t_position a, t_position b, int color)
{
	int		i;
	int		steps;
	double	x;
	double	y;

	steps = ft_max(fabs(b.x - a.x), fabs(b.y - a.y));
	x = a.x;
	y = a.y;
	i = 0;
	while (i <= steps)
	{
		if (round(x) >= 0 && round(x) < cub->win_size[1] && round(y) >= 0
			&& round(y) < cub->win_size[0])
			cub_pixel_put(&cub->img, (int)round(x), (int)round(y), color);
		x += (b.x - a.x) / (double)steps;
		y += (b.y - a.y) / (double)steps;
		i++;
	}
}

int	get_color_of_wall(int x, int y)
{
	int	color;

	if (x % 2)
	{
		if (y % 2)
			color = 0xff4500;
		else
			color = 0x80;
	}
	else
	{
		if (y % 2)
			color = 0x80;
		else
			color = 0xff4500;
	}
	return (color);
}
