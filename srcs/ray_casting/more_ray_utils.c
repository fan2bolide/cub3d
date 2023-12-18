/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_ray_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:30:13 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/18 09:44:23 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	shoot_special_rays(t_cub *cub, t_ray_shoot *ray_attr)
{
	int	return_value;

	if (ray_attr->collision_point == 'B' || ray_attr->collision_point == 'O'
		|| ray_attr->collision_point == 'R')
	{
		return_value = shoot_portal_ray(ray_attr, cub,
				ray_attr->collision_point);
		if (return_value)
			return (return_value);
	}
	if (ray_attr->collision_point == 'd' || ray_attr->collision_point == 'D')
	{
		return_value = shoot_door_ray(ray_attr, cub);
		if (return_value)
			return (return_value);
	}
	if (ray_attr->collision_point == 'G')
	{
		return_value = shoot_glass_ray(ray_attr, cub);
		if (return_value)
			return (return_value);
	}
	return (0);
}
