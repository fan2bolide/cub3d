/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 07:25:15 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/28 08:34:34 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_menu_coords(t_cub *cub)
{
	int			i;
	static int	c_coords[4] = {1031, 315, 1031, 513};
	static int	r_coords[4] = {1317, 344, 1317, 542};

	cub->menu.y = (cub->win_size[HEIGHT] - cub->menu.menu_bg.height) / 2;
	cub->menu.x = cub->menu.menu_bg.width * -1;
	cub->menu.on_screen = true;
	cub->menu.cross_hair = 1;
	cub->menu.outline = 1;
	i = 0;
	while (i < 4)
	{
		cub->menu.cursors[i == 2].x = c_coords[i];
		cub->menu.cursors[i == 2].y = c_coords[i + 1];
		cub->menu.cursors[i == 2].initial_pos.x = c_coords[i];
		cub->menu.cursors[i == 2].initial_pos.y = c_coords[i + 1];
		cub->menu.reseters[i == 2].x = r_coords[i];
		cub->menu.reseters[i == 2].y = r_coords[i + 1];
		cub->menu.cursors[i == 2].is_pressed = false;
		cub->menu.reseters[i == 2].is_pressed = false;
		i += 2;
	}
}

void	load_game_menu(t_cub *cub)
{
	static char	*filenames[6] = {MENU_BG, BUTTON, BUTTON_SH, CHECK, CURSOR,
		RESET};
	t_image		*images[6];
	int			i;

	ft_memcpy(images, (t_image *[6]){&cub->menu.menu_bg, &cub->menu.button,
		&cub->menu.button_shadow, &cub->menu.checker_plain, &cub->menu.cursor,
		&cub->menu.reset}, sizeof(t_image) * 6);
	i = 0;
	while (i < 6)
	{
		images[i]->img = mlx_xpm_file_to_image(cub->mlx, filenames[i],
				&(images[i]->width), &(images[i]->height));
		if (!images[i]->img)
			close_window(cub);
		images[i]->addr = mlx_get_data_addr(images[i]->img,
				&images[i]->bits_per_pixel, &images[i]->line_length,
				&images[i]->endian);
		i++;
	}
	init_menu_coords(cub);
}

void	init_reseters(int coords[4], t_cursor *reseters)
{
	int	i;

	coords[0] = reseters[SPEED].x;
	coords[1] = reseters[SPEED].y;
	coords[2] = reseters[SENSI].x;
	coords[3] = reseters[SENSI].y;
	i = 0;
	while (i < 4)
		if (reseters[i++ > 1].is_pressed)
			coords[i - 1] += 4;
}
