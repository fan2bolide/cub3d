/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:36:29 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/06 13:57:51 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

double	modulo_2_pi(double angle)
{
	if (angle < 0)
		angle += M_PI * 2;
	if (angle >= M_PI * 2)
		angle -= M_PI * 2;
	return (angle);
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

int	compute_ray(t_cub *cub, int ray_id, double segments_size)
{
	int	win_size_2;
	int	nb_segments;

	win_size_2 = cub->win_size[WIDTH] / 2;
	pthread_mutex_lock(&cub->ray_mutex);
	cub->rays[ray_id].x = cub->player_position.x;
	cub->rays[ray_id].y = cub->player_position.y;
	pthread_mutex_unlock(&cub->ray_mutex);
	if (ray_id <= win_size_2)
		nb_segments = win_size_2 - ray_id;
	else
		nb_segments = (cub->win_size[1] - ray_id) - win_size_2;
	cub->angles[ray_id] = (cub->view_angle * (ray_id <= (win_size_2))) \
		+ (cub->view_angle * (ray_id > (win_size_2))) \
		- atan(nb_segments * segments_size);
	cub->angles[ray_id] = modulo_2_pi(cub->angles[ray_id]);
	pthread_mutex_lock(&cub->finished_mutex);
	if (shoot_ray(cub->rays + ray_id, cub, cub->angles + ray_id, \
		cub->wall_distance + ray_id) == -1)
		return (ft_putstr_fd(ERR ALLOC_ERR EOL, 2), 0);
	pthread_mutex_unlock(&cub->finished_mutex);
	cub->wall_heights[ray_id] = get_wall_height(cub, \
		cub->wall_distance[ray_id], cub->angles[ray_id]);
	return (1);
}
