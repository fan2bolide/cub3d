/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 00:02:41 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/24 00:03:01 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

t_position	get_prtl_pos(t_cub *cub, char portal)
{
	t_position	result;

	result.y = 0;
	while (cub->data->map[(int)result.y])
	{
		result.x = 0;
		while (cub->data->map[(int)result.y][(int)result.x])
		{
			if (cub->data->map[(int)result.y][(int)result.x] == portal)
				return (result);
			result.x = result.x + 1;
		}
		result.y = result.y + 1;
	}
	result.x = -1;
	result.y = -1;
	return (result);
}

char	get_prtl_or(t_cub *cub, char portal)
{
	if (portal == 'B')
		return (cub->blue_prtl);
	else
		return (cub->orange_prtl);
}

char	get_other_portal(char portal)
{
	if (portal == 'B')
		return ('O');
	return ('B');
}

void	reset_portal(t_cub *cub, char prtl_id)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (cub->data->map[i])
	{
		j = 0;
		while (cub->data->map[i][j])
			if (cub->data->map[i][j++] == prtl_id)
				cub->data->map[i][j - 1] = '1';
		i++;
	}
}

int	add_new_portal_to_ray(t_cub *cub, double distance, t_position *ray, \
																double *angle)
{
	t_portal	*portal;
	t_prtl_list	*new;

	portal = malloc(sizeof (t_portal));
	if (!portal)
		return (0);
	portal->distance = distance;
	portal->position.x = ray->x;
	portal->position.y = ray->y;
	portal->angle = *angle;
	portal->height = get_wall_height(cub, portal->distance, portal->angle);
	new = (t_prtl_list *)ft_dblstnew(portal);
	if (!new)
		return (free(portal), 0);
	ft_dblstadd_back((t_dblist **)&cub->portals[angle - cub->angles], \
															(t_dblist *)new);
	return (1);
}
