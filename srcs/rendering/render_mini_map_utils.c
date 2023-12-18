/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:23 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/18 16:59:59 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

bool	pixel_is_in_minimap(t_cub *cub, int x, int y)
{
	return (y > (cub->player_position->y * MINIMAP_SCALE) - MINIMAP_SIZE \
				&& y < (cub->player_position->y * MINIMAP_SCALE) \
				+ MINIMAP_SIZE - 1 && x > (cub->player_position->x \
				* MINIMAP_SCALE) - MINIMAP_SIZE && x \
				< cub->player_position->x * MINIMAP_SCALE \
				+ MINIMAP_SIZE - 1);
}

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
			if (pixel_is_in_minimap(cub, i, j))
				cub_pixel_put(&cub->img, j - (int)(cub->player_position->x \
					* MINIMAP_SCALE) + MINIMAP_SIZE + MINIMAP_OFFSET, i \
					- (int)(cub->player_position->y * MINIMAP_SCALE) \
					+ MINIMAP_SIZE + MINIMAP_OFFSET, color);
			pixel_x++;
			j++;
		}
		pixel_y++;
		i++;
	}
}
