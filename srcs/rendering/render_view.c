/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/18 17:56:23 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

int	cub_textures_render(t_cub *cub, int wall_height, int x,
					t_position ray_collision)
{
	if (cub->data->baj->is_activated \
	&& get_time() - cub->data->baj->last_moove > cub->data->baj->speed)
	{
		get_next_baj(cub->data->wall_sur, cub->data->baj,
			cub->data->baj->cur_pos);
		cub->data->baj->last_moove = get_time();
	}
	return (cub_texture_put(x, cub, wall_height, ray_collision));
}

void	render_view(t_cub *cub, t_position *ray_collision, \
								const int *wall_height)
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
		cub_textures_render(cub, wall_height[i], i, ray_collision[i]);
		i++;
	}
}
