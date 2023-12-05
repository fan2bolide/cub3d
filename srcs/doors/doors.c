/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:25:56 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/01 16:11:22 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_door_hint(t_cub *cub)
{
	cub->door_hint.x = cub->win_size[WIDTH] - cub->textures[12].width - 50;
	cub->door_hint.y = -cub->textures[12].height;
	cub->door_hint.is_displayed = false;
}

int init_doors(t_cub *cub)
{
	t_door	*doors;
	size_t i;
	size_t j;
	size_t	doors_count;

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
	if (!doors)
		return (0);
	doors_count = 0;
	i = 0;
	while(cub->data->map[i])
	{
		j = 0;
		while (cub->data->map[i][j])
		{
			if (cub->data->map[i][j++] == 'D')
			{
				doors[doors_count].x = j - 1;
				doors[doors_count].y = i;
				doors[doors_count++].is_open = false;
			}
		}
		i++;
	}
	doors[doors_count].x = 0;
	cub->doors_status = doors;
	return (1);
}

char	get_tile_type(t_position pos, double angle, t_cub *cub)
{
	double	x;
	double	y;

	x = pos.x;
	y = pos.y;
	if (pos.x == (int)pos.x)
	{
		if (cos(angle) < 0)
			return (cub->data->map[(int)y][(int)x - 1]);
		else
			return (cub->data->map[(int)y][(int)x]);
	}
	if (sin(angle) < 0)
		return (cub->data->map[(int)y - 1][(int)x]);
	return (cub->data->map[(int)y][(int)x]);
}

t_iposition	get_door_index(t_position pos, double angle, t_cub *cub)
{
	{
		double 		x;
		double		y;
		t_iposition	result;

		x = pos.x;
		y = pos.y;
		if (pos.x == (int)pos.x)
		{
			if (cos(angle) < 0)
				return (result.y = (int)y, result.x = (int)x - 1, result);
			else
				return (result.y = (int)y, result.x = (int)x, result);
		}
		if (sin(angle) < 0)
			return (result.y = (int)y - 1, result.x = (int)x, result);
		result.x = (int)x;
		result.y = (int)y;
		return (result);
	}
}

void	open_door(t_cub *cub)
{
	t_iposition	door_index;
	t_position	ray_door;
	t_door 		*door;
	double 		door_angle;

	if (!cub->doors[cub->win_size[WIDTH] / 2])
		return ;
	ray_door = cub->doors[cub->win_size[WIDTH] / 2]->portal->position;
	door_angle = cub->doors[cub->win_size[WIDTH] / 2]->portal->angle;
	if (!ft_isset(get_tile_type(ray_door, door_angle, cub), "Dd")
	|| cub->doors[cub->win_size[WIDTH] / 2]->portal->distance > DOOR_MAX_OPENING)
		return ;
	door_index = get_door_index(ray_door, door_angle, cub);
	door = get_door(ray_door, door_angle, cub);
	if (cub->data->map[door_index.y][door_index.x] == 'D')
	{
		cub->data->map[door_index.y][door_index.x] = 'd';
		if (door->opening_percent > 0 && door->opening_percent < 1)
			door->is_open = false;
		door->opening_percent += 0.005;
	}
	else
	{
		cub->data->map[door_index.y][door_index.x] = 'D';
		if (door->opening_percent > 0 && door->opening_percent < 1)
			door->is_open = true;
		door->opening_percent-= 0.005;
	}
}
