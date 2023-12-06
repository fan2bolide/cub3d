/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/06 10:34:28 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

int	cub_textures_render(t_cub *cub, int wall_height, int x,
					t_position ray_collision)
{
	t_prtl_list	*save_portal;
	t_prtl_list	*save_door;

	save_door = cub->doors[x];
	save_portal = cub->portals[x];
	if (cub->data->baj->is_activated \
 && get_time() - cub->data->baj->last_move > cub->data->baj->speed)
	{
		get_next_baj(cub->data->wall_sur, cub->data->baj,
					 cub->data->baj->cur_pos);
		cub->data->baj->last_move = get_time();
	}
	cub_texture_put(x, cub, wall_height, ray_collision);
	if (cub->doors[x] && cub->portals[x])
	{
		cub->doors[x] = (t_prtl_list *) ft_dblstlast((t_dblist *) cub->doors[x]);
		cub->portals[x] = (t_prtl_list *)ft_dblstlast((t_dblist *)cub->portals[x]);
		while (cub->portals[x] && cub->doors[x])
		{
			if (cub->doors[x]->portal->distance > cub->portals[x]->portal->distance)
			{
				cub_door_texture_put(x, cub, cub->doors[x]->portal->height, \
                                    cub->doors[x]->portal->position);
				cub->doors[x] = cub->doors[x]->prev;
			}
			else
			{
				cub_portal_texture_put(x, cub, cub->portals[x]->portal->height, \
                                    cub->portals[x]->portal->position);
				cub->portals[x] = cub->portals[x]->prev;
			}
		}

	}
	if (cub->portals[x] && !cub->doors[x])
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
	if (cub->doors[x] && !cub->portals[x])
	{
		cub->doors[x] = (t_prtl_list *) ft_dblstlast((t_dblist *) cub->doors[x]);
		cub_door_texture_put(x, cub, cub->doors[x]->portal->height, \
                                    cub->doors[x]->portal->position);
		while (cub->doors[x]->prev)
		{
			cub->doors[x] = cub->doors[x]->prev;
			cub_door_texture_put(x, cub, cub->doors[x]->portal->height, \
                                        cub->doors[x]->portal->position);
		}
	}
	cub->portals[x] = save_portal;
	cub->doors[x] = save_door;
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
	cub_textures_render(cub, cub->wall_heights[column], \
								column, cub->rays[column]);
}
