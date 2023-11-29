/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/28 11:05:41 by nfaust           ###   ########.fr       */
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
	cub_texture_put(x, cub, wall_height, ray_collision);
	if (!cub->portals[x] && !cub->doors[x])
		return (1);
	if (cub->portals[x])
	{
		cub->portals[x] = (t_prtl_list *)ft_dblstlast((t_dblist *)cub->portals[x]);
		cub_portal_texture_put(x, cub, cub->portals[x]->portal->height, \
									cub->portals[x]->portal->position);
		while (cub->portals[x]->prev)
		{
			cub->portals[x] = cub->portals[x]->prev;
			cub_portal_texture_put(x, cub, cub->portals[x]->portal->height, \
										cub->portals[x]->portal->position);
		}
	}
	if (cub->doors[x])
	{
		cub->portals[x] = (t_prtl_list *) ft_dblstlast((t_dblist *) cub->portals[x]);
		cub_door_texture_put(x, cub, cub->doors[x]->portal->height, \
                                    cub->doors[x]->portal->position);
		while (cub->portals[x]->prev)
		{
			cub->portals[x] = cub->portals[x]->prev;
			cub_portal_texture_put(x, cub, cub->portals[x]->portal->height, \
                                        cub->portals[x]->portal->position);
		}
	}
	return (1);
}

void	render_view(t_cub *cub, t_position *ray_collision, \
								const int *wall_height)
{
	int	i;
	int	j;
	int	screen_height_2;

	screen_height_2 = cub->win_size[0] / 2;
	i = 0;
	while (i < cub->win_size[1])
	{
		j = 0;
		while (j < screen_height_2)
			cub_pixel_put(&cub->img, i, j++, \
									*((int *)cub->data->ceiling_color));
		while (j < cub->win_size[0])
			cub_pixel_put(&cub->img, i, j++, \
									*((int *)cub->data->floor_color));
		i++;
	}
	i = 0;
	while (i < cub->win_size[1])
	{
		cub_textures_render(cub, wall_height[i], i, ray_collision[i]);
		i++;
	}
	display_crosshair(cub);
}
