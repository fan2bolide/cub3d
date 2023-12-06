/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:06:40 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/06 11:07:37 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_door_hint(t_cub *cub)
{
	cub->door_hint.x = cub->win_size[WIDTH] - cub->textures[12].width - 50;
	cub->door_hint.y = -cub->textures[12].height;
	cub->door_hint.is_displayed = false;
}

t_door	*alloc_doors(t_cub *cub)
{
	size_t	doors_count;
	t_door	*doors;
	size_t	i;
	size_t	j;

	init_door_hint(cub);
	i = 0;
	doors_count = 0;
	while (cub->data->map[i])
	{
		j = 0;
		while (cub->data->map[i][j])
			if (cub->data->map[i][j++] == 'D')
				doors_count++;
		i++;
	}
	doors = ft_calloc(doors_count + 1, sizeof(t_door));
	return (doors);
}

int	init_doors(t_cub *cub)
{
	t_door	*doors;
	int		i;
	int		j;
	int		k;

	doors = alloc_doors(cub);
	if (!doors)
		return (0);
	i = -1;
	k = 0;
	while (cub->data->map[++i])
	{
		j = 0;
		while (cub->data->map[i][j])
		{
			if (cub->data->map[i][j++] == 'D')
			{
				doors[k].x = j - 1;
				doors[k].y = i;
				doors[k++].is_open = false;
			}
		}
	}
	doors[k].x = 0;
	return (cub->doors_status = doors, 1);
}
