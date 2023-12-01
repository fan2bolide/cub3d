/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:25:56 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/01 11:11:28 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int init_doors(t_cub *cub)
{
	t_door	*doors;
	size_t i;
	size_t j;
	size_t	doors_count;

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

	if (cub->doors[cub->win_size[WIDTH] / 2])
	{
		ray_door = cub->doors[cub->win_size[WIDTH] / 2]->portal->position;
		door_angle = cub->doors[cub->win_size[WIDTH] / 2]->portal->angle;
	}
	else
	{
		ray_door = cub->rays[cub->win_size[WIDTH] / 2];
		door_angle = cub->angles[cub->win_size[WIDTH] / 2];
	}
	if (!ft_isset(get_tile_type(ray_door, door_angle, cub), "Dd")
	|| compute_distance(*cub->player_position, ray_door) > DOOR_MAX_OPENING)
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
