/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:50:04 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/22 01:56:13 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	put_wall(t_cub *cub, int i, int j, int color)
{
	int	pixel_x;
	int	pixel_y;
	int	j_save;

	i *= MINIMAP_SCALE;
	j *= MINIMAP_SCALE;
	j_save = j;
	pixel_y = 0;
	while (pixel_y < MINIMAP_SCALE)
	{
		pixel_x = 0;
		j = j_save;
		while (pixel_x < MINIMAP_SCALE)
		{
			if (i > (cub->player_position->y * MINIMAP_SCALE) - MINIMAP_SIZE && i < (cub->player_position->y * MINIMAP_SCALE) + MINIMAP_SIZE - 1 && j > (cub->player_position->x * MINIMAP_SCALE) - MINIMAP_SIZE && j < cub->player_position->x * MINIMAP_SCALE  + MINIMAP_SIZE - 1)
				cub_pixel_put(&cub->img, j - (int)(cub->player_position->x * MINIMAP_SCALE) + MINIMAP_SIZE + MINIMAP_OFFSET, i - (int)(cub->player_position->y * MINIMAP_SCALE) + MINIMAP_SIZE + MINIMAP_OFFSET, color);
			pixel_x++;
			j++;
		}
		pixel_y++;
		i++;
	}
}

void	cub_put_player_on_map(t_cub *cub, t_position player)
{
	int radius;
	int i;
	int j;

	radius = MINIMAP_SCALE / 2;
	i = (int)player.x - radius - 1;
	while (i < (int)player.x + radius + 1)
	{
		j = (int)player.y - radius - 1;
		while (j < (int)player.y + radius + 1)
		{
			if (pow(player.x - i, 2) + pow(player.y - j, 2) < pow(radius, 2))
				cub_pixel_put(&cub->img, i, j, 0x0000FF);
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

	ray_adjustment.x = -(cub->player_position->x * MINIMAP_SCALE) \
						+ (MINIMAP_SIZE) + MINIMAP_OFFSET;
	ray_adjustment.y = -(cub->player_position->y * MINIMAP_SCALE) \
						+ (MINIMAP_SIZE) + MINIMAP_OFFSET;
	i = 0;
	while (i < cub->win_size[WIDTH])
	{
		if (!cub->portals[i])
		{
			ray_dup.x = ray[i].x * MINIMAP_SCALE + ray_adjustment.x;
			ray_dup.y = ray[i++].y * MINIMAP_SCALE + ray_adjustment.y;
		}
		else
		{
			ray_dup.x = cub->portals[i]->portal->position.x * MINIMAP_SCALE \
						+ ray_adjustment.x;
			ray_dup.y = cub->portals[i++]->portal->position.y * MINIMAP_SCALE \
						+ ray_adjustment.y;
		}
		cub_put_line(cub, player, ray_dup, 0xFF0000);
	}
}

void put_outer_color(t_cub *cub)
{
	int	pixel_x;
	int	pixel_y;
	int	i;
	int	j;

	i = MINIMAP_OFFSET - 5;
	pixel_y = 0;
	while (pixel_y < (MINIMAP_SIZE * 2) + 10)
	{
		pixel_x = 0;
		j = MINIMAP_OFFSET - 5;
		while (pixel_x < (MINIMAP_SIZE * 2) + 10)
		{
			cub_pixel_put(&cub->img, j, i, OUTER_MINIMAP_COLOR);
			pixel_x++;
			j++;
		}
		pixel_y++;
		i++;
	}
}

void	render_mini_map(t_cub *cub, t_position *ray_collision)
{
	int			i;
	int			j;
	t_position	player_dup;

	i = 0;
	put_outer_color(cub);
	while (cub->data->map[i])
	{
		j = 0;
		while (cub->data->map[i][j])
		{
			if (cub->data->map[i][j] == '1')
				put_wall(cub, i, j, 0x000000);
			if (cub->data->map[i][j] == '0')
				put_wall(cub, i, j, 0xFFFFFF);
			if (cub->data->map[i][j] == 'B')
				put_wall(cub, i, j, 0x889BF8);
			if (cub->data->map[i][j] == 'O')
				put_wall(cub, i, j, 0xf4a460);
			j++;
		}
		i++;
	}
	player_dup.x = cub->player_position->x * MINIMAP_SCALE \
		- (cub->player_position->x * MINIMAP_SCALE) \
		+ (MINIMAP_SIZE) + MINIMAP_OFFSET;
	player_dup.y = cub->player_position->y * MINIMAP_SCALE \
		- (cub->player_position->y * MINIMAP_SCALE) \
		+ (MINIMAP_SIZE) + MINIMAP_OFFSET;
	cub_put_ray_on_minimap(cub, player_dup, ray_collision);
	cub_put_player_on_map(cub, player_dup);
}
