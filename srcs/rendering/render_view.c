/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/18 13:15:28 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

int	max_distance(double f_dist, double s_dist, double t_dist)
{
	if (f_dist >= s_dist && f_dist >= t_dist)
		return (0);
	if (s_dist >= f_dist && s_dist >= t_dist)
		return (1);
	return (2);
}

int	get_furthest(t_prtl_list **customs[3])
{
	int	max_dist;

	if ((*customs[0]) && !(*customs[1]) && !(*customs[2]))
		return (0);
	if ((*customs[1]) && !(*customs[2]) && !(*customs[0]))
		return (1);
	if ((*customs[2]) && !(*customs[1]) && !(*customs[0]))
		return (2);
	if ((*customs[0]) && (*customs[1]) && (*customs[2]))
	{
		max_dist = max_distance((*customs[0])->portal->distance,
				(*customs[1])->portal->distance,
				(*customs[2])->portal->distance);
		return (max_dist);
	}
	if ((*customs[0]) && (*customs[1]))
		return (max_distance((*customs[0])->portal->distance,
				(*customs[1])->portal->distance, 0));
	if ((*customs[1]) && (*customs[2]))
		return (max_distance(0, (*customs[1])->portal->distance,
				(*customs[2])->portal->distance));
	if ((*customs[2]) && (*customs[0]))
		return (max_distance((*customs[0])->portal->distance, 0,
				(*customs[2])->portal->distance));
	return (-1);
}

void	get_last_customs(t_cub *cub, int x)
{
	if (cub->doors[x])
		cub->doors[x] = (t_prtl_list *)ft_dblstlast((t_dblist *) cub->doors[x]);
	if (cub->portals[x])
		cub->portals[x] = (t_prtl_list *)ft_dblstlast(
				(t_dblist *)cub->portals[x]);
	if (cub->glass[x])
		cub->glass[x] = (t_prtl_list *)ft_dblstlast((t_dblist *)cub->glass[x]);
}

void	cub_textures_render(t_cub *cub, int x, t_position ray_collision)
{
	int			curr;
	t_prtl_list	**customs[3];
	void		(*functions[3])(int x, t_cub *cub, t_position ray_collision);
	t_prtl_list	*saves[3];

	ft_memcpy(saves, (t_prtl_list *[3]){cub->doors[x], cub->portals[x],
		cub->glass[x]}, sizeof(t_prtl_list *) * 3);
	ft_memcpy(customs, (t_prtl_list **[3]){&cub->doors[x], &cub->portals[x],
		&cub->glass[x]}, sizeof(t_prtl_list **) * 3);
	ft_memcpy(functions, (void *[3]){cub_door_texture_put,
		cub_portal_texture_put, cub_glass_texture_put}, sizeof(void *) * 3);
	cub_texture_put(x, cub, ray_collision);
	get_last_customs(cub, x);
	curr = get_furthest(customs);
	while (curr >= 0)
	{
		functions[curr](x, cub, (*customs[curr])->portal->position);
		(*customs[curr]) = (*customs[curr])->prev;
		curr = get_furthest(customs);
	}
	cub->doors[x] = saves[0];
	cub->portals[x] = saves[1];
	cub->glass[x] = saves[2];
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
	cub_textures_render(cub, column, cub->rays[column]);
}
