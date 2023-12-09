/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:52:06 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/06 14:42:52 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * compute the vector coordinates to the next column from ray
 * with the angle <ray_direction>
 * @param ray
 * @param ray_direction
 * @return
 */
t_position	get_delta_to_next_column(t_position ray, double ray_direction)
{
	t_position	delta;

	if (cos(ray_direction) > 0)
	{
		delta.x = 1.0 - (ray.x - (int)ray.x);
		delta.y = tan(ray_direction) * delta.x;
		return (delta);
	}
	delta.x = -(ray.x - (int)ray.x) - (ray.x == (int)ray.x);
	delta.y = tan(ray_direction) * delta.x;
	return (delta);
}

/**
 * compute the vector coordinates to the next line from ray
 * with the angle <ray_direction>
 * @param ray
 * @param ray_direction
 * @return the vector to the next line
 */
t_position	get_delta_to_next_line(t_position ray, double ray_direction)
{
	t_position	delta;

	if (sin(ray_direction) > 0)
	{
		delta.y = 1 - (ray.y - (int)ray.y);
		delta.x = delta.y / tan(ray_direction);
		return (delta);
	}
	delta.y = -(ray.y - (int)ray.y + ((int)ray.y == ray.y));
	delta.x = delta.y / tan(ray_direction);
	return (delta);
}

/**
 * chooses the least normed vector between delta_x and delta_y
 * and applies it to ray
 * @param ray
 * @param delta_x
 * @param delta_y
 */
void	apply_minimal_distance(t_position *ray, t_position delta_x, \
												t_position delta_y)
{
	if (sqrt(delta_x.x * delta_x.x + delta_x.y * delta_x.y) \
					< sqrt(delta_y.x * delta_y.x + delta_y.y * delta_y.y))
	{
		ray->x += delta_x.x;
		ray->y += delta_x.y;
		return ;
	}
	ray->x += delta_y.x;
	ray->y += delta_y.y;
}

void	update_ray_attr(t_ray_shoot *ray_attr, t_cub *cub)
{
	t_position	*ray;
	double		*angle;

	ray = ray_attr->ray;
	angle = ray_attr->angle;
	apply_minimal_distance(ray, get_delta_to_next_column(*ray, *angle), \
			get_delta_to_next_line(*ray, *angle));
	ray_attr->collision_point = cub->data->map[(int)ray->y - \
		((int)ray->y && ray->y == (int)ray->y && sin(*angle) < 0)][(int)ray->x \
		- ((int)ray->x && ray->x == (int)ray->x && (cos(*angle) < 0))];
}

/**
 * shoots a ray until it collides with a wall (or a portal/door)
 * @param ray
 * @param cub
 * @param angle
 * @param distance
 * @return
 */
int	shoot_ray(t_position *ray, t_cub *cub, double *angle, double *distance)
{
	t_ray_shoot	ray_attr;
	int			return_value;

	init_ray_attr(cub, ray, angle, &ray_attr);
	ray_attr.distance = distance;
	*distance = 0;
	while (1)
	{
		update_ray_attr(&ray_attr, cub);
		if (ray_attr.collision_point == '1')
			return (*ray_attr.distance += compute_distance(ray_attr.ray_start,
					*ray_attr.ray), 1);
		if (ray_attr.collision_point == 'B' || ray_attr.collision_point == 'O')
		{
			return_value = shoot_portal_ray(&ray_attr, cub);
			if (return_value)
				return (return_value);
		}
		if (ray_attr.collision_point == 'd' || ray_attr.collision_point == 'D')
		{
			return_value = shoot_door_ray(&ray_attr, cub);
			if (return_value)
				return (return_value);
		}
		if (ray_attr.collision_point == 'G')
		{
			return_value = shoot_glass_ray(&ray_attr, cub);
			if (return_value)
				return (return_value);
		}
	}
}
