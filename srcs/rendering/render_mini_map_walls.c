/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_walls.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:51:03 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/23 20:14:08 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void	put_wall(t_cub *cub, int i, int j, int color)
{
	int	pixel_x;
	int	pixel_y;
	int	j_save;

	i *= MINIMAP_SCALE;
	j *= MINIMAP_SCALE;
	j_save = j;
	pixel_y = 0;
	while (pixel_y++ < MINIMAP_SCALE)
	{
		pixel_x = 0;
		j = j_save;
		while (pixel_x++ < MINIMAP_SCALE)
		{
			if (pixel_is_in_minimap(j, i, cub))
				cub_pixel_put(&cub->img, \
				j - (int)(cub->player_position->x * MINIMAP_SCALE) \
					+ MINIMAP_SIZE + MINIMAP_OFFSET, \
				i - (int)(cub->player_position->y * MINIMAP_SCALE) \
					+ MINIMAP_SIZE + MINIMAP_OFFSET, color);
			j++;
		}
		i++;
	}
}

void	put_walls(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
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
}
