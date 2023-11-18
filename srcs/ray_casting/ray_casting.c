/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:52:06 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/18 00:59:53 by nfaust           ###   ########.fr       */
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

void shoot_ray(t_position *ray, t_cub *cub, double angle)
{
	t_position		new_x;
	t_position		new_y;

	//todo coder les cas de depart (Nord Est West et Sud);
	while (1)
	{
		get_delta_to_next_column(*ray, angle, &new_x);
		get_delta_to_next_line(*ray, angle, &new_y);
		apply_minimal_distance(ray, new_x, new_y);
		if (ray->y < 0 || ray->x < 0 || cub->data->map[(int)ray->y - \
		((int)ray->y && ray->y == (int)ray->y && sin(angle) < 0)][(int)ray->x \
		- ((int) ray->x && ray->x == (int)ray->x &&(cos(angle) < 0))] == '1'
		|| cub->data->map[(int)ray->y - \
		((int)ray->y && ray->y == (int)ray->y && sin(angle) < 0)][(int)ray->x \
		- ((int) ray->x && ray->x == (int)ray->x &&(cos(angle) < 0))] == 'B'
		|| cub->data->map[(int)ray->y - \
		((int)ray->y && ray->y == (int)ray->y && sin(angle) < 0)][(int)ray->x \
		- ((int) ray->x && ray->x == (int)ray->x &&(cos(angle) < 0))] == 'O')
			return ;
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
