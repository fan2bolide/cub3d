/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:52:06 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/04 15:24:50 by nfaust           ###   ########.fr       */
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

/**
 * @param player
 * @param ray
 * @return the distance between the player and the ray
 */
double	compute_distance(t_position player, t_position ray)
{
	return (sqrt((ray.x - player.x) * (ray.x - player.x) \
				+ (ray.y - player.y) * (ray.y - player.y)));
}

/**
 * shoots a ray until it collides with a wall (or a portal)
 * @param ray
 * @param cub
 * @param angle
 * @param distance
 * @return
 */
int	shoot_ray(t_position *ray, t_cub *cub, double *angle, double *distance)
{
	char		collision_point;
	t_position	ray_start;
	t_prtl_list	*door_lst;
	t_portal	*door;

	*distance = 0;
	ray_start.x = cub->player_position.x;
	ray_start.y = cub->player_position.y;
	while (1)
	{
		apply_minimal_distance(ray, get_delta_to_next_column(*ray, *angle), \
			get_delta_to_next_line(*ray, *angle));
		collision_point = cub->data->map[(int)ray->y - \
		((int)ray->y && ray->y == (int)ray->y && sin(*angle) < 0)][(int)ray->x \
		- ((int)ray->x && ray->x == (int)ray->x && (cos(*angle) < 0))];
		if (collision_point == '1')
			return (*distance += compute_distance(ray_start, *ray), 1);
		if (collision_point == 'B' || collision_point == 'O')
		{
			*distance += compute_distance(ray_start, *ray);
			add_new_portal_to_ray(cub, *distance, ray, angle);
			if (*distance > 300 || !teleport_ray(cub, ray, angle, \
												collision_point))
				return (1);
			ray_start = *ray;
		}
		if (collision_point == 'd' || collision_point == 'D')
		{
			door = malloc(sizeof (t_portal));
			if (!door)
				return (0);
			door->distance = *distance + compute_distance(ray_start, *ray);
			door->position.x = ray->x;
			door->position.y = ray->y;
			door->angle = *angle;
			door->height = get_wall_height(cub, door->distance, door->angle);
			door_lst = (t_prtl_list *)ft_dblstnew(door);
			if (!door_lst)
				return (0);
			ft_dblstadd_back((t_dblist **)&cub->doors[angle - cub->angles], (t_dblist *)door_lst);
			*distance += compute_distance(ray_start, *ray);
			if (collision_point == 'D' && get_door(*ray, *angle, cub)->opening_percent == 0)
				return (1);
			ray_start.x = ray->x;
			ray_start.y = ray->y;
		}
	}
}
