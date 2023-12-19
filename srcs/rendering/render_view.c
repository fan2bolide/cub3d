/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/19 13:38:06 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	cub_textures_render(t_cub *cub, int x, t_position ray_collision)
{
	return (cub_texture_put(x, cub, ray_collision));
}

void	render_view(t_cub *cub, t_position *ray_collision)
{
	int	i;
	int	j;
	int	screen_height_2;

	screen_height_2 = cub->win_size[HEIGHT] / 2;
	i = 0;
	while (i < cub->win_size[WIDTH])
	{
		j = 0;
		{
			while (j < screen_height_2)
				cub_pixel_put(&cub->img, i, j++, \
					*((int *)cub->data->ceiling_color));
			while (j < cub->win_size[HEIGHT])
				cub_pixel_put(&cub->img, i, j++, \
					*((int *)cub->data->floor_color));
		}
		i++;
	}
	i = 0;
	while (i < cub->win_size[WIDTH])
	{
		cub_textures_render(cub, i, ray_collision[i]);
		i++;
	}
}
