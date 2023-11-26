/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:44:48 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/26 12:19:42 by nfaust           ###   ########.fr       */
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
	cub->menu.cursor.img = mlx_xpm_file_to_image(cub->mlx, CURSOR, &cub->menu.cursor.width, &cub->menu.cursor.height);
	cub->menu.cursor.addr = mlx_get_data_addr(cub->menu.cursor.img, &cub->menu.cursor.bits_per_pixel, &cub->menu.cursor.line_length, &cub->menu.cursor.endian);
	cub->menu.y = (cub->win_size[HEIGHT] - cub->menu.menu_bg.height) / 2;
	cub->menu.x = cub->menu.menu_bg.width * -1;
	cub->menu.on_screen = false;
	cub->menu.cross_hair = 1;
	cub->menu.outline = 1;
	cub->menu.cursors[SPEED].x = 1031;
	cub->menu.cursors[SPEED].y = 315;
	cub->menu.cursors[SENSI].y = 513;
	cub->menu.cursors[SENSI].x = 1031;
}

int	set_button_color(t_cub *cub, int texture_x, int texture_y)
{
	int		color;
	int		save_color;
	t_image	bu_sh;

	color = -1;
	bu_sh = cub->menu.button_shadow;
	if (cub->menu.on_screen || cub->menu.x < -100)
	{
		if (texture_x > 425 && texture_x < 425 + cub->menu.button_shadow.width \
		&& texture_y > 67 && texture_y < 67 + cub->menu.button_shadow.height)
			color = *((int *)(bu_sh.addr + ((texture_y - 67) * \
						bu_sh.line_length + (texture_x - 425) * \
						(bu_sh.bits_per_pixel / 8))));
		save_color = color;
		if (texture_x > 420 && texture_x < 420 + cub->menu.button.width \
		&& texture_y > 60 && texture_y < 60 + cub->menu.button.height)
			color = *((int *)(cub->menu.button.addr + ((texture_y - 60) * \
						cub->menu.button.line_length + (texture_x - 420) * \
						(cub->menu.button.bits_per_pixel / 8))));
		if (color < 0)
			color = save_color;
	}
	return (color);
}

int	set_cursor_color(t_cub *cub, int texture_x, int texture_y)
{
	int	color;
	int	i;

	color = -1;
	i = 0;
	while (i < 2)
	{
		if (texture_x > cub->menu.cursors[i].x && texture_x < cub->menu.cursors[i].x + cub->menu.cursor.width \
			&& texture_y > cub->menu.cursors[i].y && texture_y < cub->menu.cursors[i].y + cub->menu.cursor.height)
			color = *((int *)(cub->menu.cursor.addr + ((texture_y - cub->menu.cursors[i].y) * \
							cub->menu.cursor.line_length + (texture_x - cub->menu.cursors[i].x) * \
							(cub->menu.cursor.bits_per_pixel / 8))));
		i++;
	}
	return (color);
}

void	display_customized(t_cub *cub, int texture_x, int texture_y)
{
	int			color;
	int			i;
	static int	coords[10] = {425, 67, 382, 322, 477, 322, 516, 507, 516, 578};
	t_image		text[2];

	text[0] = cub->menu.checker_plain;
	text[1] = cub->menu.button;
	color = set_button_color(cub, texture_x, texture_y);
	i = 0;
//	if (texture_x >= 870 && texture_x < 1300 && texture_y >= 350 && texture_y < 390)
//		color = 28374695;
	while (color < 0 && i < 9)
	{
		if (texture_x > coords[i] && texture_x < coords[i] + text[!i].width && texture_y > coords[i + 1] &&
			texture_y < coords[i + 1] + text[!i].height)
			color = *((int *)(text[!i].addr + ((texture_y - coords[i + 1]) * \
					text[!i].line_length + (texture_x - coords[i]) * \
					(text[!i].bits_per_pixel / 8))));
		i += 2;
	}
	if (color < 0)
		color = set_cursor_color(cub, texture_x, texture_y);
	if (color > 0)
		cub_pixel_put(&cub->img, cub->menu.x + texture_x, cub->menu.y + texture_y, color);
}

void	display_menu(t_cub *cub, int max_y, int display_x, int texture_x)
{
	int	display_y;
	int	texture_y;
	int	color;

	while (display_x > 0 && display_x > cub->menu.x)
	{
		display_y = cub->menu.y;
		texture_y = 0;
		while (display_y < max_y)
		{
			color = *((int *)(cub->menu.menu_bg.addr + (texture_y * \
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
}

void	summon_game_menu(t_cub *cub, int dir)
{
	int	texture_x;
	int	display_x;
	int	max_y;

	max_y = cub->win_size[HEIGHT] - cub->menu.y;
	texture_x = cub->menu.menu_bg.width;
	display_x = cub->menu.x + cub->menu.menu_bg.width;
	display_menu(cub, max_y, display_x, texture_x);
	cub->menu.x += ((cub->win_size[WIDTH] - cub->menu.menu_bg.width) / 2 \
				- cub->menu.x) / 10 * dir;
	if (cub->menu.x < cub->menu.menu_bg.width * -1)
		cub->menu.x = cub->menu.menu_bg.width * -1;
}

void	handle_menu(t_cub *cub)
{
	if (cub->menu.on_screen)
	{
		cub->menu.on_screen = false;
		cub->menu.x -= 1;
	}
	else
	{
		cub->menu.on_screen = true;
		ft_bzero(cub->keys_states, 65509 * sizeof(int));
	}
}