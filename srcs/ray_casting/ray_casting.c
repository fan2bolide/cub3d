/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:52:06 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/09 09:18:40 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void get_delta_to_next_column(t_position ray, double ray_direction, t_position *delta)
{
	if (cos(ray_direction) > 0)
	{
		delta->x = 1.0 - (ray.x - (int)ray.x);
		delta->y = tan(ray_direction) * delta->x;
		return ;
	}
	delta->x = -(ray.x - (int)ray.x) - (ray.x == (int)ray.x);
	delta->y = tan(ray_direction) * delta->x;
}

void get_delta_to_next_line(t_position ray, double ray_direction, t_position *delta)
{
	if (sin(ray_direction) > 0)
	{
		delta->y = 1 - (ray.y - (int)ray.y);
		delta->x = delta->y / tan(ray_direction);
		return ;
	}
	delta->y = -(ray.y - (int)ray.y + ((int)ray.y == ray.y));
	delta->x = delta->y / tan(ray_direction);
}

void apply_minimal_distance(t_position *ray, t_position delta_x, t_position delta_y)
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

static double	compute_distance(t_position player, t_position ray)
{
	return (sqrt((ray.x - player.x) * (ray.x - player.x) \
				+ (ray.y - player.y) * (ray.y - player.y)));
}

t_position get_portal_position(t_cub *cub, char portal) {
	t_position result;

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

char get_portal_orientation(t_cub *cub, char portal)
{
	if (portal == 'B')
		return cub->blue_prtl;
	else
		return cub->orange_prtl;
}

void teleport_ray(t_cub *cub, t_position *ray, double *angle, char portal)
{
	t_position	portal_position;
	char 		portal_orientation;

	if (portal == 'B')
		portal = 'O';
	else
		portal = 'B';
	portal_position = get_portal_position(cub, portal);
	portal_orientation = get_portal_orientation(cub, portal);
	if (ray->x - (int)ray->x == 0)
	{
		if (portal_orientation == 'N' || portal_orientation == 'S')
		{
			ray->x += (portal_position.x - (int)ray->x);
			if (portal_orientation == 'N')
				ray->y = portal_position.y;
			else
				ray->y = portal_position.y + 1;
		}
	}
	return ;
}

void shoot_ray(t_position *ray, t_cub *cub, double angle, double *distance)
{
	t_position		new_x;
	t_position		new_y;
	char 			collision_point;
	t_position		ray_start;

	*distance = 0;
	ray_start.x = cub->player_position->x;
	ray_start.y = cub->player_position->y;
	while (1)
	{
		get_delta_to_next_column(*ray, angle, &new_x);
		get_delta_to_next_line(*ray, angle, &new_y);
		apply_minimal_distance(ray, new_x, new_y);
		if (ray->y < 0 || ray->x < 0)
			return ;
		collision_point = cub->data->map[(int)ray->y - \
		((int)ray->y && ray->y == (int)ray->y && sin(angle) < 0)][(int)ray->x \
		- ((int) ray->x && ray->x == (int)ray->x &&(cos(angle) < 0))];
		if (collision_point == '1')
		{
			*distance += compute_distance(ray_start, *ray);
			return ;
		}
		if (collision_point == 'B' || collision_point == 'O')
		{
			*distance += compute_distance(ray_start, *ray);
			if (collision_point == 'B')
				teleport_ray(cub, ray, &angle, collision_point);
		}
	}
}

double get_orientation(char **map, t_position *pos) {
	char	orientation_char;
	double	orientation_angle;

	orientation_char = map[(int)pos->y][(int)pos->x];
	if (orientation_char == 'N')
		orientation_angle = 3 * M_PI_2;
	if (orientation_char == 'E')
		orientation_angle = 0;
	if (orientation_char == 'W')
		orientation_angle = M_PI;
	if (orientation_char == 'S')
		orientation_angle = M_PI_2;
	map[(int)pos->y][(int)pos->x] = '0';
	return (orientation_angle);
}
