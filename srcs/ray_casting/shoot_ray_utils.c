/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:42:29 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/11 17:31:29 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

int get_glass_aligned(t_cub *cub, t_ray_shoot *ray_attr)
{
	int i;
	t_prtl_list *curr;

	i = 0;
	curr = cub->glass[ray_attr->angle - cub->angles];
	while (curr->next)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

int glass_stick_to_another(t_cub *cub, t_ray_shoot *ray_attr)
{
	t_prtl_list	*last_glass;

	last_glass = (t_prtl_list *)ft_dblstlast((t_dblist *) cub->glass[ray_attr->angle - cub->angles]);
	if (!last_glass)
		return (0);
	if (last_glass->portal->position.x == ray_attr->ray_start.x && last_glass->portal->position.y == ray_attr->ray_start.y)
	{
		return (1);
	}
	return (0);
}

int shoot_glass_ray(t_ray_shoot *ray_attr, t_cub *cub)
{
	t_prtl_list	*glass_list;
	t_portal	*glass;

	glass = malloc(sizeof (t_portal));
	if (!glass)
		return (-1);
	glass->distance = *ray_attr->distance + \
		compute_distance(ray_attr->ray_start, *ray_attr->ray);
	glass->position = *ray_attr->ray;
	glass->angle = *ray_attr->angle;
	glass->height = get_wall_height(cub, glass->distance, glass->angle);
	if (!ray_attr->is_in_glass)
	{
		glass_list = (t_prtl_list *) ft_dblstnew(glass);
		if (!glass_list)
			return (-1);
		ft_dblstadd_back((t_dblist **) &cub->glass[ray_attr->angle - cub->angles],
						 (t_dblist *) glass_list);
	}
	*ray_attr->distance += compute_distance(ray_attr->ray_start,
											*ray_attr->ray);
	if (get_glass_aligned(cub, ray_attr) > 10)
		return (1);
	ray_attr->ray_start.x = ray_attr->ray->x;
	ray_attr->ray_start.y = ray_attr->ray->y;
	ray_attr->is_in_glass = true;
	return (0);
}

int	shoot_portal_ray(t_ray_shoot *ray_attr, t_cub *cub)
{
	double		*distance;
	double		*angle;
	t_position	*ray;

	distance = ray_attr->distance;
	angle = ray_attr->angle;
	ray = ray_attr->ray;
	*distance += compute_distance(ray_attr->ray_start, *ray);
	if (!add_new_portal_to_ray(cub, *distance, ray, angle))
		return (-1);
	if (*distance > 300 || !teleport_ray(cub, ray, angle, \
								ray_attr->collision_point))
		return (1);
	ray_attr->ray_start.x = ray->x;
	ray_attr->ray_start.y = ray->y;
	return (0);
}

int	shoot_door_ray(t_ray_shoot *ray_attr, t_cub *cub)
{
	t_prtl_list	*door_lst;
	t_portal	*door;

	door = malloc(sizeof (t_portal));
	if (!door)
		return (-1);
	door->distance = *ray_attr->distance + \
		compute_distance(ray_attr->ray_start, *ray_attr->ray);
	door->position = *ray_attr->ray;
	door->angle = *ray_attr->angle;
	door->height = get_wall_height(cub, door->distance, door->angle);
	door_lst = (t_prtl_list *)ft_dblstnew(door);
	if (!door_lst)
		return (-1);
	ft_dblstadd_back((t_dblist **)&cub->doors[ray_attr->angle - cub->angles],
		(t_dblist *)door_lst);
	*ray_attr->distance += compute_distance(ray_attr->ray_start,
			*ray_attr->ray);
	if (ray_attr->collision_point == 'D' && get_door(*ray_attr->ray,
			*ray_attr->angle, cub)->opening_percent == 0)
		return (1);
	ray_attr->ray_start.x = ray_attr->ray->x;
	ray_attr->ray_start.y = ray_attr->ray->y;
	return (0);
}

void	init_ray_attr(t_cub *cub, t_position *ray, double *angle,
		t_ray_shoot *ray_attr)
{
	ray_attr->angle = angle;
	ray_attr->ray = ray;
	ray_attr->ray_start.x = cub->player_position.x;
	ray_attr->ray_start.y = cub->player_position.y;
	ray_attr->is_in_glass = false;
}
