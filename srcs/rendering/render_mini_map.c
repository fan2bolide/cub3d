/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:50:04 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/06 23:35:35 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	put_wall(t_cub *cub, int i, int j, int scale, int color)
{
	int	pixel_x;
	int	pixel_y;
	int	j_save;

	i *= scale;
	j *= scale;
	j_save = j;
	pixel_y = 0;
	while (pixel_y < scale)
	{
		pixel_x = 0;
		j = j_save;
		while (pixel_x < scale)
		{
			cub_pixel_put(&cub->img, j, i, color);
			pixel_x++;
			j++;
		}
		pixel_y++;
		i++;
	}
}

void cub_put_ray_on_minimap(t_cub *cub, t_position player, t_position ray[], int scale)
{
	t_position	ray_dupl;
	int			i;

	i = 0;
	while (i < cub->win_size[1])
	{
		ray_dupl.x = ray[i].x * scale;
		ray_dupl.y = ray[i].y * scale;
		cub_put_line(cub, player, ray_dupl, 0xFF0000);
		i++;
	}
}

void	render_mini_map(t_cub *cub, t_position ray_collision[cub->win_size[1]])
{
	int			i;
	int			j;
	int			scale;
	t_position	player_dupl;

	scale = 10;
	i = 0;
	while (cub->data->map[i])
	{
		j = 0;
		while (cub->data->map[i][j])
		{
			if (cub->data->map[i][j] == '1')
				put_wall(cub, i, j, scale, 0x000000);
			else
				put_wall(cub, i, j, scale, 0xFFFFFF);
			j++;
		}
		i++;
	}
	player_dupl.x = cub->player_position->x * scale;
	player_dupl.y = cub->player_position->y * scale;
	cub_put_ray_on_minimap(cub, player_dupl, ray_collision, scale);
}
