/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/20 18:26:18 by nfaust           ###   ########.fr       */
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
	return (cub_texture_put(x, cub, wall_height, ray_collision),
			cub_portal_texture_put(x, cub, cub->wall_heights_portal[x], cub->rays_portal[x]));
}

void	render_view(t_cub *cub, t_position *ray_collision, \
								const int *wall_height)
{
	int	i;
	int	j;
	int screen_height_2;

	screen_height_2 = cub->win_size[0] / 2;
	i = 0;
	while (i < cub->win_size[1])
	{
		j = 0;
		{
			while (j < screen_height_2)
				cub_pixel_put(&cub->img, i, j++, *((int *)cub->data->ceiling_color));
			while (j < cub->win_size[0])
				cub_pixel_put(&cub->img, i, j++, *((int *)cub->data->floor_color));
		}
		i++;
	}
	i = 0;
	int k = 0;
	while (cub->wall_heights_portal[k++])
		if (!cub->rays_portal[k - 1].y && !cub->rays_portal[k - 1].x)
			printf("%i\n", cub->wall_heights_portal[k - 1]);
	while (i < cub->win_size[1])
	{
		cub_textures_render(cub, wall_height[i], i, ray_collision[i]);
		i++;
	}
	display_crosshair(cub);
}
