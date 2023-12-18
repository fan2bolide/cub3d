/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valve_guy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 03:37:29 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/17 05:33:02 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_pixel_valid(t_cub *cub, int x, int y, int color)
{
	return (color >= 0 \
		&& x < cub->win_size[WIDTH] \
		&& y < cub->win_size[HEIGHT]);
}

void	display_valve_guy(t_cub *cub)
{
	t_image	valve_guy;
	int		x;
	int		y;
	int		color;
	int		texture_y;
	int		texture_x;

	valve_guy.img = mlx_xpm_file_to_image(cub->mlx, VALVE_GUY, &valve_guy.width, &valve_guy.height);
	// if (!valve_guy.img)
	// 	close_window(cub);
	valve_guy.addr = mlx_get_data_addr(valve_guy.img, &valve_guy.bits_per_pixel, &valve_guy.line_length, &valve_guy.endian);
	y = 0;
	while (y < cub->win_size[HEIGHT])
	{
		texture_y = y * valve_guy.height / cub->win_size[HEIGHT];
		x = 0;
		while (x < cub->win_size[WIDTH])
		{
			texture_x = x * valve_guy.width / cub->win_size[WIDTH];
			color = *((int *)(valve_guy.addr + (texture_y * \
				valve_guy.line_length + texture_x * \
				(valve_guy.bits_per_pixel / 8))));
			if (is_pixel_valid(cub, x, y, color))
				cub_pixel_put(&cub->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	mlx_destroy_image(cub->mlx, valve_guy.img);
	mlx_loop_hook(cub->mlx, init_game, cub);
}