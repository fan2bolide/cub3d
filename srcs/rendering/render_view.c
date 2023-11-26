/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/26 03:53:54 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

int	cub_textures_render(t_cub *cub, int wall_height, int x,
					t_position ray_collision)
{
	if (cub->data->baj->is_activated \
	&& get_time() - cub->data->baj->last_move > cub->data->baj->speed)
	{
		get_next_baj(cub->data->wall_sur, cub->data->baj,
			cub->data->baj->cur_pos);
		cub->data->baj->last_move = get_time();
	}
	if (!cub->portals[x])
		return (cub_texture_put(x, cub, wall_height, ray_collision), 1);
	cub_texture_put(x, cub, wall_height, ray_collision);
	cub->portals[x] = (t_prtl_list *)ft_dblstlast((t_dblist *)cub->portals[x]);
	cub_portal_texture_put(x, cub, cub->portals[x]->portal->height, \
								cub->portals[x]->portal->position);
	while (cub->portals[x]->prev)
	{
		cub->portals[x] = cub->portals[x]->prev;
		cub_portal_texture_put(x, cub, cub->portals[x]->portal->height, \
									cub->portals[x]->portal->position);
	}
	return (1);
}

void	render_column(t_cub *cub, int column)
{
	int	i;
	int	screen_height_2;

	i = 0;
	screen_height_2 = cub->win_size[0] / 2;
	while (i < screen_height_2)
		cub_pixel_put(&cub->img, column, i++, \
								*((int *)cub->data->ceiling_color));
	while (i < cub->win_size[0])
		cub_pixel_put(&cub->img, column, i++, \
								*((int *)cub->data->floor_color));
	cub_textures_render(cub, cub->wall_heights[column], column, cub->rays[column]);
}
