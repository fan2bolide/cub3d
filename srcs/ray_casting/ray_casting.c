/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:52:06 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/03 01:39:57 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double get_orientation(char **map, t_position *pos);

void shoot_ray(t_position *ray, t_cub *cub, double angle);

int get_wall_height(t_cub *cub, t_position ray, double angle) {
	double	wall_distance;

	wall_distance = sqrt((ray.x - cub->player_position->x) * (ray.x - cub->player_position->x) + (ray.y - cub->player_position->y) * (ray.y - cub->player_position->y));
	wall_distance *= cos(cub->view_angle - angle);
	return ((int)(SCREEN_DISTANCE * cub->win_size[0] / wall_distance));
}

int	ray_casting(t_cub *cub)
{
	t_position	ray_pos[cub->win_size[1]];
	double		angle[cub->win_size[1]];
	int			wall_height[cub->win_size[1]];
	double		ray_spacing;
	int			i;

	i = 0;
	ray_spacing = cub->fov / (cub->win_size[1] - 1);
	while (i < cub->win_size[1])
	{
		ray_pos[i].x = cub->player_position->x;
		ray_pos[i].y = cub->player_position->y;
		angle[i] = cub->view_angle - (cub->fov / 2) + (i * ray_spacing);
		i++;
	}
	i = 0;
	while (i < cub->win_size[1])
	{
		shoot_ray(ray_pos + i, cub, angle[i]);
		wall_height[i] = get_wall_height(cub, ray_pos[i], angle[i]);
		i++;
	}
	render_minimap(cub, ray_pos, angle, wall_height);
	return (1);
}

void print_distance(t_position ray, t_cub *cub)
{
	double	distance;

	distance = sqrt((ray.x - cub->player_position->x) * (ray.x - cub->player_position->x) + (ray.y - cub->player_position->y) * (ray.y - cub->player_position->y));

	printf("distance = %f\n", distance);
}

void jesaispasencore(t_position *ray, double ray_direction, t_position *delta, t_cub *cub)
{
	delta->y = 0;
	if (ray_direction == M_PI_2)
	{
		while (cub->data->map[(int)((int)ray->y + delta->y + 1)][(int)ray->x] == '0')
		{
			delta->y++;
		}
		ray->y += delta->y;
		print_distance(*ray, cub);
	}
}

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

double v_norm(t_position ray) {
	return sqrt(ray.x * ray.x + ray.y * ray.y);
}

void apply_minimal_distance(t_position *ray, t_position delta_x, t_position delta_y)
{
	if (v_norm(delta_x) < v_norm(delta_y))
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
		if (ray->y < 0 || ray->x < 0 || cub->data->map[(int)ray->y - (ray->y == (int)ray->y && sin(angle) < 0)][(int)ray->x - (ray->x == (int)ray->x &&(cos(angle) < 0))] == '1')
			return ;
	}
}

double get_orientation(char **map, t_position *pos) {
	char	orientation;

	orientation = map[(int)pos->y][(int)pos->x];
	if (orientation == 'N')
		return (3 * M_PI_2);
	if (orientation == 'E')
		return (0);
	if (orientation == 'W')
		return (M_PI);
	if (orientation == 'S')
		return (M_PI_2);
}
