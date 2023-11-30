/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:50:04 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/22 01:56:13 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	cub_put_player_on_map(t_cub *cub, t_position player)
{
	int	radius;
	int	i;
	int	j;

	radius = MINIMAP_SCALE / 2;
	i = (int)player.x - radius - 1;
	while (i < (int)player.x + radius + 1)
	{
		j = (int)player.y - radius - 1;
		while (j < (int)player.y + radius + 1)
		{
			if (pow(player.x - i, 2) + pow(player.y - j, 2) < pow(radius, 2))
				cub_pixel_put(&cub->img, i, j, 0x97f1d0);
			j++;
		}
		i++;
	}
}

void	cub_put_ray_on_minimap(t_cub *cub, t_position player, t_position *ray)
{
	t_position	ray_dup;
	t_position	ray_adjustment;
	int			i;

	ray_adjustment.x = -(cub->player_position.x * MINIMAP_SCALE) \
						+ (MINIMAP_SIZE) + MINIMAP_OFFSET;
	ray_adjustment.y = -(cub->player_position.y * MINIMAP_SCALE) \
						+ (MINIMAP_SIZE) + MINIMAP_OFFSET;
	i = 0;
	while (i < cub->win_size[WIDTH])
	{
		if (!cub->portals[i])
		{
			pthread_mutex_lock(&cub->ray_mutex);
			ray_dup.x = ray[i].x * MINIMAP_SCALE + ray_adjustment.x;
			ray_dup.y = ray[i++].y * MINIMAP_SCALE + ray_adjustment.y;
			pthread_mutex_unlock(&cub->ray_mutex);
		}
		else
		{
			ray_dup.x = cub->portals[i]->portal->position.x * MINIMAP_SCALE \
						+ ray_adjustment.x;
			ray_dup.y = cub->portals[i++]->portal->position.y * MINIMAP_SCALE \
						+ ray_adjustment.y;
		}
		cub_put_line(cub, player, ray_dup, 0xffa2e8);
	}
}

void	put_outer_color(t_cub *cub)
{
	static int	colors[2] = {OUT_COLOR, IN_COLOR};
	int	pixel_x;
	int	pixel_y;
	int	i;
	int	j;

	i = MINIMAP_OFFSET - 5;
	pixel_y = 0;
	while (pixel_y < (MINIMAP_SIZE * 2) + 11)
	{
		pixel_x = 0;
		j = MINIMAP_OFFSET - 5;
		while (pixel_x < (MINIMAP_SIZE * 2) + 11)
		{
			cub_pixel_put(&cub->img, j, i, colors[pixel_x > 5 && pixel_x < (MINIMAP_SIZE * 2 + 10) - 5 && pixel_y > 5 && pixel_y < (MINIMAP_SIZE * 2 + 10)- 5]);
			pixel_x++;
			j++;
		}
		pixel_y++;
		i++;
	}
}

void	render_mini_map(t_cub *cub, t_position *ray_collision)
{
	t_position	player_dup;

	put_outer_color(cub);
	put_walls(cub);
	player_dup.x = cub->player_position.x * MINIMAP_SCALE \
		- (cub->player_position.x * MINIMAP_SCALE) \
		+ (MINIMAP_SIZE) + MINIMAP_OFFSET;
	player_dup.y = cub->player_position.y * MINIMAP_SCALE \
		- (cub->player_position.y * MINIMAP_SCALE) \
		+ (MINIMAP_SIZE) + MINIMAP_OFFSET;
	cub_put_ray_on_minimap(cub, player_dup, ray_collision);
	cub_put_player_on_map(cub, player_dup);
}
