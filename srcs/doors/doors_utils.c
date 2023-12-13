/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:45:01 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/13 19:55:57 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub_update_doors(t_cub *cub)
{
	size_t	i;

	i = 0;
	while (cub->doors_status[i].x)
	{
		if (cub->doors_status[i].opening_percent > 0 && cub->doors_status[i].opening_percent < 1)
		{
			if (cub->doors_status[i].is_open)
				cub->doors_status[i].opening_percent -= 0.05;
			else
				cub->doors_status[i].opening_percent += 0.05;
			if (cub->doors_status[i].opening_percent < 0)
				cub->doors_status[i].opening_percent = 0;
			else if (cub->doors_status[i].opening_percent > 1)
				cub->doors_status[i].opening_percent = 1;
			if (cub->doors_status[i].opening_percent == 1)
				cub->doors_status[i].is_open = true;
			else if (cub->doors_status[i].opening_percent == 0)
				cub->doors_status[i].is_open = false;
		}
		i++;
	}
}

void	display_door_hint(t_cub *cub, int texture_y, int display_y)
{
	int	display_x;
	int	texture_x;
	int	color;
	int max_x;

	max_x = cub->textures[12].width + cub->door_hint.x;
	while (display_y > 0 && display_y > cub->door_hint.y)
	{
		display_x = cub->door_hint.x;
		texture_x = 0;
		while (display_x < max_x && display_x < cub->win_size[WIDTH])
		{

			color = *((int *)(cub->textures[12].addr + (texture_y * \
					cub->textures[12].line_length + texture_x * \
					(cub->textures[12].bits_per_pixel / 8))));
			if (color > 0)
				cub_pixel_put(&cub->img, display_x, display_y, color);
			display_x++;
			texture_x++;
		}
		display_y--;
		texture_y--;
	}
}

void	cub_display_door_hint(t_cub *cub)
{
	t_prtl_list	*door;
	int 		dir;
	int 		texture_y;
	int 		display_y;

	door = cub->doors[cub->win_size[WIDTH] / 2];
	if (door && cub->menu.x == -cub->menu.menu_bg.width)
	{
		while (door->next && get_door(door->portal->position, door->portal->angle, cub)->is_open)
			door = door->next;
		dir = (door->portal->distance > DOOR_MAX_OPENING) * -1 + (door->portal->distance <= DOOR_MAX_OPENING);
		if (dir < 0 && cub->door_hint.y == cub->textures[12].height * -1)
			return ;
	}
	else
		dir = -1;
	texture_y = cub->textures[12].height - 1;
	display_y = cub->door_hint.y + texture_y;
	display_door_hint(cub, texture_y, display_y);
	cub->door_hint.y += dir * 2;
	if (cub->door_hint.y > 15)
		cub->door_hint.y = 15;
	if (cub->door_hint.y < -cub->textures[12].height)
		cub->door_hint.y = -cub->textures[12].height;
}
