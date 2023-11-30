/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:44:48 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/28 08:28:09 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_checked(int i, t_cub *cub)
{
	if ((i == 2 && cub->menu.cross_hair == 1)
		|| (i == 4 && cub->menu.cross_hair == 2)
		|| (i == 6 && cub->menu.outline == 1)
		|| (i == 8 && cub->menu.outline == 2))
		return (true);
	return (false);
}

static void	display_customized(t_cub *cub, int texture_x, int texture_y)
{
	int			color;
	int			i;
	static int	coords[10] = {425, 67, 382, 322, 477, 322, 516, 507, 516, 578};
	t_image		text[2];

	text[0] = cub->menu.checker_plain;
	text[1] = cub->menu.button;
	color = set_button_color(cub, texture_x, texture_y);
	i = 0;
	while (color < 0 && i < 9)
	{
		if (texture_x > coords[i] && texture_x < coords[i] + text[!i].width
			&& texture_y > coords[i + 1] && texture_y < coords[i + 1] + \
			text[!i].height && (!i || is_checked(i, cub)))
			color = *((int *)(text[!i].addr + ((texture_y - coords[i + 1]) * \
					text[!i].line_length + (texture_x - coords[i]) * \
					(text[!i].bits_per_pixel / 8))));
		i += 2;
	}
	if (color < 0)
		color = set_cursor_color(cub, texture_x, texture_y);
	if (color > 0)
		cub_pixel_put(&cub->img, cub->menu.x + texture_x,
			cub->menu.y + texture_y, color);
}

static void	display_menu(t_cub *cub, int max_y, int display_x, int texture_x)
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

	if (dir < 0 && cub->menu.x == -cub->menu.menu_bg.width)
		return ;
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
		cub_mouse_hide(cub);
		cub->menu.x -= 1;
	}
	else
	{
		cub->menu.on_screen = true;
		cub_mouse_show(cub);
		ft_bzero(cub->keys_states, 65509 * sizeof(int));
	}
}
