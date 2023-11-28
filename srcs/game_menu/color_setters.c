/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 07:28:41 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/28 07:34:19 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_shadow_color(int texture_x, int texture_y, int *coords,
					t_cub *cub)
{
	if (texture_x > *coords + cub->menu.reset.width - 4
		|| texture_y > *(coords + 1) + cub->menu.reset.height - 4
		|| (texture_x > *coords + cub->menu.reset.width - 6
			&& texture_y > *(coords + 1) + cub->menu.reset.height - 6))
		return (true);
	return (false);
}

static int	set_reset_button_color(t_cub *cub, int texture_x, int texture_y)
{
	int			color;
	static int	coords[4];
	int			i;

	init_reseters(coords, cub->menu.reseters);
	color = -1;
	i = 0;
	while (i < 3 && color < 0)
	{
		if (texture_x > coords[i]
			&& texture_x < coords[i] + cub->menu.reset.width
			&& texture_y > coords[i + 1]
			&& texture_y < coords[i + 1] + cub->menu.reset.height)
			color = *((int *)(cub->menu.reset.addr + \
			((texture_y - coords[i + 1]) * cub->menu.reset.line_length + \
			(texture_x - coords[i]) * \
			(cub->menu.reset.bits_per_pixel / 8))));
		if (cub->menu.reseters[i == 2].is_pressed)
			if (is_shadow_color(texture_x, texture_y, &coords[i], cub)
				|| color == 15783256 || color == 15783257)
				color = -1;
		i += 2;
	}
	return (color);
}

int	set_button_color(t_cub *cub, int texture_x, int texture_y)
{
	int		color;
	int		save_color;
	t_image	bu_sh;

	color = set_reset_button_color(cub, texture_x, texture_y);
	bu_sh = cub->menu.button_shadow;
	if (cub->menu.on_screen || cub->menu.x < -100)
	{
		if (texture_x > 425 && texture_x < 425 + bu_sh.width \
		&& texture_y > 67 && texture_y < 67 + bu_sh.height)
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
	int			color;
	t_cursor	*cursors;
	t_image		curs_img;
	int			i;

	cursors = cub->menu.cursors;
	curs_img = cub->menu.cursor;
	color = -1;
	i = 0;
	while (i < 2)
	{
		if (texture_x > cursors[i].x
			&& texture_x < cursors[i].x + curs_img.width
			&& texture_y > cursors[i].y
			&& texture_y < cursors[i].y + curs_img.height)
			color = *((int *)(curs_img.addr + \
			((texture_y - cursors[i].y) * curs_img.line_length + \
			(texture_x - cursors[i].x) * (curs_img.bits_per_pixel / 8))));
		i++;
	}
	return (color);
}
