/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:44:48 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/25 01:28:32 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_game_menu(t_cub *cub)
{
	cub->menu.menu_bg.img = mlx_xpm_file_to_image(cub->mlx, MENU_BG, &cub->menu.menu_bg.width, &cub->menu.menu_bg.height);
	cub->menu.menu_bg.addr = mlx_get_data_addr(cub->menu.menu_bg.img, &cub->menu.menu_bg.bits_per_pixel, &cub->menu.menu_bg.line_length, &cub->menu.menu_bg.endian);
	cub->menu.button.img = mlx_xpm_file_to_image(cub->mlx, BUTTON, &cub->menu.button.width, &cub->menu.button.height);
	cub->menu.button.addr = mlx_get_data_addr(cub->menu.button.img, &cub->menu.button.bits_per_pixel, &cub->menu.button.line_length, &cub->menu.button.endian);
	cub->menu.button_shadow.img = mlx_xpm_file_to_image(cub->mlx, BUTTON_SH, &cub->menu.button_shadow.width, &cub->menu.button_shadow.height);
	cub->menu.button_shadow.addr = mlx_get_data_addr(cub->menu.button_shadow.img, &cub->menu.button_shadow.bits_per_pixel, &cub->menu.button_shadow.line_length, &cub->menu.button_shadow.endian);
	cub->menu.checker_plain.img = mlx_xpm_file_to_image(cub->mlx, CHECK, &cub->menu.checker_plain.width, &cub->menu.checker_plain.height);
	cub->menu.checker_plain.addr = mlx_get_data_addr(cub->menu.checker_plain.img, &cub->menu.checker_plain.bits_per_pixel, &cub->menu.checker_plain.line_length, &cub->menu.checker_plain.endian);
	cub->menu.y = (cub->win_size[HEIGHT] - cub->menu.menu_bg.height) / 2;
	cub->menu.x = cub->menu.menu_bg.width * -1;
	cub->menu.on_screen = false;
	cub->menu.cross_hair = 1;
	cub->menu.outline = 1;
}

int	get_color(int texture_x, int texture_y, t_cub *cub)
{
	t_image	img;
	int 	x;
	int 	y;

	if (texture_x > 420 && texture_x < 420 + cub->menu.button.width && texture_y > 60 && texture_y < 60 + cub->menu.button.height)
	{
		img = cub->menu.button;
		x = texture_x - 420;
		y = texture_y - 60;
	}
	else
	{
		img = cub->menu.menu_bg;
		x = texture_x;
		y = texture_y;
	}
	return (*((int *)(img.addr + (y * \
					img.line_length + x * \
					(img.bits_per_pixel / 8)))));
}

void	display_customized(t_cub *cub, int texture_x, int texture_y)
{
	int	color;
	int save_color;

	color = -1;
	if (cub->menu.on_screen || get_time() - cub->menu.time_pressed > 400)
	{
		if (texture_x > 425 && texture_x < 425 + cub->menu.button_shadow.width && texture_y > 67 && texture_y < 67 + cub->menu.button_shadow.height)
			color = *((int *)(cub->menu.button_shadow.addr + ((texture_y - 67) * \
						cub->menu.button_shadow.line_length + (texture_x - 425) * \
						(cub->menu.button_shadow.bits_per_pixel / 8))));
		save_color = color;
		if (texture_x > 420 && texture_x < 420 + cub->menu.button.width && texture_y > 60 && texture_y < 60 + cub->menu.button.height)
			color = *((int *)(cub->menu.button.addr + ((texture_y - 60) * \
						cub->menu.button.line_length + (texture_x - 420) * \
						(cub->menu.button.bits_per_pixel / 8))));
		if (color < 0)
			color = save_color;
	}
	else if (texture_x > 425 && texture_x < 425 + cub->menu.button.width && texture_y > 67 && texture_y < 67 + cub->menu.button.height)
			color = *((int *)(cub->menu.button.addr + ((texture_y - 67) * \
						cub->menu.button.line_length + (texture_x - 425) * \
						(cub->menu.button.bits_per_pixel / 8))));
	if (texture_x >= 382 && texture_x < 382 + cub->menu.checker_plain.width && texture_y >= 322 && texture_y < 322 + cub->menu.checker_plain.height && cub->menu.cross_hair == 1)
		color = *((int *)(cub->menu.checker_plain.addr + ((texture_y - 322) * \
					cub->menu.checker_plain.line_length + (texture_x - 382) * \
					(cub->menu.checker_plain.bits_per_pixel / 8))));
	if (texture_x >= 477 && texture_x < 477 + cub->menu.checker_plain.width && texture_y >= 322 && texture_y < 322 + cub->menu.checker_plain.height && cub->menu.cross_hair == 2)
		color = *((int *)(cub->menu.checker_plain.addr + ((texture_y - 322) * \
					cub->menu.checker_plain.line_length + (texture_x - 477) * \
					(cub->menu.checker_plain.bits_per_pixel / 8))));
	if (texture_x >= 516 && texture_x < 516 + cub->menu.checker_plain.width && texture_y >= 507 && texture_y < 507 + cub->menu.checker_plain.height && cub->menu.outline == 1)
		color = *((int *)(cub->menu.checker_plain.addr + ((texture_y - 507) * \
					cub->menu.checker_plain.line_length + (texture_x - 516) * \
					(cub->menu.checker_plain.bits_per_pixel / 8))));
	if (texture_x >= 516 && texture_x < 516 + cub->menu.checker_plain.width && texture_y >= 578 && texture_y < 578 + cub->menu.checker_plain.height && cub->menu.outline == 2)
		color = *((int *)(cub->menu.checker_plain.addr + ((texture_y - 578) * \
					cub->menu.checker_plain.line_length + (texture_x - 516) * \
					(cub->menu.checker_plain.bits_per_pixel / 8))));
	if (color > 0)
		cub_pixel_put(&cub->img, cub->menu.x + texture_x, cub->menu.y + texture_y, color);
}

void	summon_game_menu(t_cub *cub, int dir)
{
	int texture_x;
	int texture_y;
	int	display_x;
	int	display_y;
	int	max_y;

	texture_x = cub->menu.menu_bg.width;
	display_x = cub->menu.x + cub->menu.menu_bg.width;
	max_y = cub->win_size[HEIGHT] - cub->menu.y;
	while (display_x > 0 && display_x > cub->menu.x)
	{
		display_y = cub->menu.y;
		texture_y = 0;
		while (display_y < max_y)
		{
			int color = *((int *)(cub->menu.menu_bg.addr + (texture_y * \
					cub->menu.menu_bg.line_length + texture_x * \
					(cub->menu.menu_bg.bits_per_pixel / 8))));
			if (color > 0)
				cub_pixel_put(&cub->img, display_x, display_y, color);
			display_customized(cub, texture_x, texture_y);
			display_y++;
			texture_y++;
		}
		display_x--;
		texture_x--;
	}
	cub->menu.x += ((cub->win_size[WIDTH] - cub->menu.menu_bg.width) / 2 - cub->menu.x) / 10 * dir;
	if (cub->menu.x < cub->menu.menu_bg.width * -1)
		cub->menu.x = cub->menu.menu_bg.width * -1;
}

void	handle_menu(t_cub *cub)
{
	if (cub->menu.on_screen)
	{
		cub->menu.on_screen = false;
		cub->menu.time_pressed = get_time();
		cub->menu.x -= 1;
	}
	else
	{
		cub->menu.on_screen = true;
		ft_bzero(cub->keys_states, 65509 * sizeof(int));
	}
}