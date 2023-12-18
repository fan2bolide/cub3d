/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:12:11 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/13 00:13:02 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	remove_load_screen(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->load_screen.img);
	cub->load_screen.img = NULL;
	cub->menu.on_screen = false;
	cub_mouse_hide(cub);
}

void	display_background(t_cub *cub, int start_x, int start_y)
{
	int	x;
	int	y;

	x = 0;
	while (x < cub->win_size[WIDTH])
	{
		y = 0;
		while (y < cub->win_size[HEIGHT])
		{
			if (y < start_y || y > start_y + cub->load_screen.height
				|| x < start_x || x > start_x + cub->load_screen.width)
				cub_pixel_put(&cub->img, x, y, 0x2089ef);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}

void	display_load_screen(t_cub *cub)
{
	int		height;
	int		width;
	int		x;
	int		y;

	cub->load_screen.img = mlx_xpm_file_to_image(cub->mlx, LOAD_SCREEN, &width,
			&height);
	if (!cub->load_screen.img)
	{
		ft_putstr_fd(ERR TXTR_LOAD EOL, 2);
		close_window(cub);
	}
	mlx_get_data_addr(cub->load_screen.img, &cub->load_screen.bits_per_pixel,
		&cub->load_screen.line_length, &cub->load_screen.endian);
	x = (cub->win_size[WIDTH] / 2) - (width / 2);
	y = (cub->win_size[HEIGHT] / 2) - (height / 2);
	display_background(cub, x, y);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->load_screen.img, x, y);
}
