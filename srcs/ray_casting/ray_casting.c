/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:52:06 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/21 03:45:59 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "rendering.h"

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

int teleport_ray(t_cub *cub, t_position *ray, double *angle, char entry_portal)
{
	t_position	portal_position;
	char 		portal_orientation;
	char		out_portal;

	if (entry_portal == 'B')
		out_portal = 'O';
	else
		out_portal = 'B';
	portal_position = get_portal_position(cub, out_portal);
	if (portal_position.x == -1 && portal_position.y == -1)
		return (0);
	portal_orientation = get_portal_orientation(cub, out_portal);
	if ((ray->y - (int)ray->y) == 0 && get_portal_orientation(cub, entry_portal) == 'S' && sin(*angle) < 0)
	{
		if (portal_orientation == 'N')
		{
			ray->x += (portal_position.x - (int)ray->x);
			ray->y = portal_position.y;
		}
		if (portal_orientation == 'S')
		{
			ray->y = portal_position.y + 1;
			ray->x = portal_position.x + (1 - (ray->x - (int)ray->x));
			*angle -= M_PI;
			if (*angle > M_PI * 2)
				*angle -= M_PI * 2;
		}
		if (portal_orientation == 'E')
		{
			ray->y = portal_position.y + (ray->x - (int)ray->x);
			ray->x = portal_position.x + 1;
			*angle += M_PI_2;
		}
		if (portal_orientation == 'W')
		{
			ray->y = portal_position.y + (1 - (ray->x - (int)ray->x));
			ray->x = portal_position.x;
			*angle -= M_PI_2;
			if (*angle > M_PI * 2)
				*angle -= M_PI * 2;
		}
		return (1);
	}
	if ((ray->y - (int)ray->y) == 0 && get_portal_orientation(cub, entry_portal) == 'N' && sin(*angle) > 0)
	{
		if (portal_orientation == 'N')
		{
			ray->y = portal_position.y;
			ray->x = portal_position.x + (1 - (ray->x - (int)ray->x));
			*angle -= M_PI;
			if (*angle > M_PI * 2)
				*angle -= M_PI * 2;
		}
		if (portal_orientation == 'S')
		{
			ray->x += (portal_position.x - (int)ray->x);
			ray->y = portal_position.y + 1;
		}
		if (portal_orientation == 'E')
		{
			ray->y = portal_position.y + (1 - (ray->x - (int)ray->x));
			ray->x = portal_position.x + 1;
			*angle -= M_PI_2;
			if (*angle > M_PI * 2)
				*angle -= M_PI * 2;
		}
		if (portal_orientation == 'W')
		{
			ray->y = portal_position.y + (ray->x - (int)ray->x);
			ray->x = portal_position.x;
			*angle += M_PI_2;
		}
		return (1);
	}
	if ((ray->x - (int)ray->x) == 0 && get_portal_orientation(cub, entry_portal) == 'E' && cos(*angle) < 0)
	{
		if (portal_orientation == 'N')
		{
			ray->x = portal_position.x + (1 - (ray->y - (int)ray->y));
			ray->y = portal_position.y;
			*angle += M_PI_2;
			if (*angle > M_PI * 2)
				*angle -= M_PI * 2;
		}
		if (portal_orientation == 'S')
		{
			ray->x = portal_position.x + (ray->y - (int)ray->y);
			ray->y = portal_position.y + 1;
			*angle -= M_PI_2;
			if (*angle > M_PI * 2)
				*angle -= M_PI * 2;
		}
		if (portal_orientation == 'E')
		{
			ray->y = portal_position.y + (1 - (ray->y - (int)ray->y));
			ray->x = portal_position.x + 1;
			*angle += M_PI;
			if (*angle > M_PI * 2)
				*angle -= M_PI * 2;
		}
		if (portal_orientation == 'W')
		{
			ray->y = portal_position.y + (ray->y - (int)ray->y);
			ray->x = portal_position.x;
		}
		return (1);
	}
	if ((ray->x - (int)ray->x) == 0 && get_portal_orientation(cub, entry_portal) == 'W' && cos(*angle) > 0)
	{
		if (portal_orientation == 'N')
		{
			ray->x = portal_position.x + (ray->y - (int)ray->y);
			ray->y = portal_position.y;
			*angle -= M_PI_2;
			if (*angle > M_PI * 2)
				*angle -= M_PI * 2;
		}
		if (portal_orientation == 'S')
		{
			ray->x = portal_position.x + (1 - (ray->y - (int)ray->y));
			ray->y = portal_position.y + 1;
			*angle += M_PI_2;
			if (*angle > M_PI * 2)
				*angle -= M_PI * 2;
		}
		if (portal_orientation == 'E')
		{
			ray->y = portal_position.y + (ray->y - (int)ray->y);
			ray->x = portal_position.x + 1;
		}
		if (portal_orientation == 'W')
		{
			ray->y = portal_position.y + (1 - (ray->y - (int)ray->y));
			ray->x = portal_position.x;
			*angle += M_PI;
			if (*angle > M_PI * 2)
				*angle -= M_PI * 2;
		}
		return (1);
	}
	return (0);
}

int	shoot_ray(t_position *ray, t_cub *cub, double *angle, double *distance)
{
	char 			collision_point;
	t_position		ray_start;
	t_portal_list	*portal_lst;
	t_portal		*portal;

	*distance = 0;
	ray_start.x = cub->player_position->x;
	ray_start.y = cub->player_position->y;
	while (1)
	{
		apply_minimal_distance(ray, get_delta_to_next_column(*ray, *angle), get_delta_to_next_line(*ray, *angle));
		if (ray->y < 0 || ray->x < 0)
			return (1);
		if (!cub->data->map[(int)ray->y - \
		((int)ray->y && ray->y == (int)ray->y && sin(*angle) < 0)])
			printf("y = %d\n", (int)ray->y - \
		((int)ray->y && ray->y == (int)ray->y && sin(*angle) < 0));
		collision_point = cub->data->map[(int)ray->y - \
		((int)ray->y && ray->y == (int)ray->y && sin(*angle) < 0)][(int)ray->x \
		- ((int) ray->x && ray->x == (int)ray->x &&(cos(*angle) < 0))];
		if (collision_point == '1')
		{
			*distance += compute_distance(ray_start, *ray);
			return (1);
		}
		if (collision_point == 'B' || collision_point == 'O')
		{
			portal = malloc(sizeof (t_portal));
			if (!portal)
				return (0);
			portal->distance = *distance + compute_distance(ray_start, *ray);
			portal->position.x = ray->x;
			portal->position.y = ray->y;
			portal->angle = *angle;
			portal->height = get_wall_height(cub, portal->distance, portal->angle);
			portal_lst = (t_portal_list *)ft_dblstnew(portal);
			if (!portal_lst)
				return (0);
			ft_dblstadd_back((t_dblist **)&cub->portals[angle - cub->angles], (t_dblist *)portal_lst);
			if (*distance > 100)
				return (1);
			*distance += compute_distance(ray_start, *ray);
			if (!teleport_ray(cub, ray, angle, collision_point))
				return (1);
			ray_start.x = ray->x;
			ray_start.y = ray->y;
		}
	}
}

double	get_orientation(char **map, t_position *pos)
{
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
