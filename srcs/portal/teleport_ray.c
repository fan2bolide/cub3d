/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:16:39 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/27 07:48:05 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	tp_from_west(	t_position *ray,
						t_position portal_position,
						double *angle,
						char portal_orientation)
{
	double	offset;

	offset = ray->y - (int)ray->y;
	if (portal_orientation == 'S' || portal_orientation == 'W')
		offset = 1 - offset;
	if (portal_orientation == 'N' || portal_orientation == 'S')
	{
		ray->x = portal_position.x + offset;
		ray->y = portal_position.y + ((portal_orientation == 'S') * 1.01) - 0.005;
	}
	else if (portal_orientation == 'E' || portal_orientation == 'W')
	{
		ray->y = portal_position.y + offset;
		ray->x = portal_position.x + ((portal_orientation == 'E') * 1.01) - 0.005;
	}
	*angle = *angle + ((portal_orientation == 'S') * M_PI_2) \
					- ((portal_orientation == 'N') * M_PI_2) \
					+ ((portal_orientation == 'W') * M_PI);
}

void	tp_from_east(	t_position *ray,
						t_position portal_position,
						double *angle,
						char portal_orientation)
{
	double	offset;

	offset = ray->y - (int)ray->y;
	if (portal_orientation == 'N' || portal_orientation == 'E')
		offset = 1 - offset;
	if (portal_orientation == 'N' || portal_orientation == 'S')
	{
		ray->x = portal_position.x + offset;
		ray->y = portal_position.y + ((portal_orientation == 'S') * 1.01) - 0.005;
	}
	if (portal_orientation == 'E' || portal_orientation == 'W')
	{
		ray->y = portal_position.y + offset;
		ray->x = portal_position.x + ((portal_orientation == 'E') * 1.01) - 0.005;
	}
	*angle = *angle + (M_PI_2 * (portal_orientation == 'N')) \
					+ (-M_PI_2 * (portal_orientation == 'S')) \
					+ (M_PI * (portal_orientation == 'E'));
}

void	tp_from_south(	t_position *ray,
						t_position portal_position,
						double *angle,
						char portal_orientation)
{
	double	offset;

	offset = ray->x - (int)ray->x;
	if (portal_orientation == 'S' || portal_orientation == 'W')
		offset = 1 - offset;
	if (portal_orientation == 'N' || portal_orientation == 'S')
	{
		ray->x = portal_position.x + offset;
		ray->y = portal_position.y + ((portal_orientation == 'S') * 1.01) - 0.005;
	}
	if (portal_orientation == 'E' || portal_orientation == 'W')
	{
		ray->y = portal_position.y + offset;
		ray->x = portal_position.x + ((portal_orientation == 'E') * 1.01) - 0.005;
	}
	*angle = *angle + (M_PI * (portal_orientation == 'S')) \
					+ (M_PI_2 * (portal_orientation == 'E')) \
					+ (-M_PI_2 * (portal_orientation == 'W'));
}

void	tp_from_north(	t_position *ray,
						t_position portal_position,
						double *angle,
						char portal_orientation)
{
	double	offset;

	offset = ray->x - (int)ray->x;
	if (portal_orientation == 'N' || portal_orientation == 'E')
		offset = 1 - offset;
	if (portal_orientation == 'N' || portal_orientation == 'S')
	{
		ray->x = portal_position.x + offset;
		ray->y = portal_position.y + ((portal_orientation == 'S') * 1.01) - 0.005;
	}
	if (portal_orientation == 'E' || portal_orientation == 'W')
	{
		ray->y = portal_position.y + offset;
		ray->x = portal_position.x + ((portal_orientation == 'E') * 1.01) - 0.005;
	}
	*angle = *angle + (M_PI * (portal_orientation == 'N')) \
					+ (-M_PI_2 * (portal_orientation == 'E')) \
					+ (M_PI_2 * (portal_orientation == 'W'));
}

int	teleport_ray(t_cub *cub, t_position *ray, double *angle, char entry_portal)
{
	t_position	prtl_pos;
	char		prtl_or;
	char		out_portal;

	out_portal = get_other_portal(entry_portal);
	prtl_pos = get_prtl_pos(cub, out_portal);
	if (prtl_pos.x == -1 && prtl_pos.y == -1)
		return (0);
	prtl_or = get_prtl_or(cub, out_portal);
	if ((ray->y - (int)ray->y) == 0)
	{
		if (get_prtl_or(cub, entry_portal) == 'S' && sin(*angle) < 0)
			return (tp_from_south(ray, prtl_pos, angle, prtl_or), 1);
		if (get_prtl_or(cub, entry_portal) == 'N' && sin(*angle) > 0)
			return (tp_from_north(ray, prtl_pos, angle, prtl_or), 1);
	}
	if ((ray->x - (int)ray->x) == 0)
	{
		if (get_prtl_or(cub, entry_portal) == 'E' && cos(*angle) < 0)
			return (tp_from_east(ray, prtl_pos, angle, prtl_or), 1);
		if (get_prtl_or(cub, entry_portal) == 'W' && cos(*angle) > 0)
			return (tp_from_west(ray, prtl_pos, angle, prtl_or), 1);
	}
	return (0);
}
