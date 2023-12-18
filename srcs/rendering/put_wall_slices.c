/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall_slices.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:56:30 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/18 12:59:27 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	portal_put_wall_slice(t_cub *cub, int x, t_iposition texture,
			int texture_id)
{
	int	screen_wall_height;
	int	wall_height;
	int	y;
	int	i;
	int	color;

	wall_height = cub->portals[x]->portal->height;
	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[0])
		screen_wall_height = cub->win_size[0];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	i = 0;
	while (i < screen_wall_height)
	{
		texture.y = (i + (wall_height - screen_wall_height) / 2) \
				* cub->textures[texture_id].height / wall_height;
		if (cub->menu.outline == 2)
			put_transparency(cub, x, y, texture_id);
		color = get_texture_pixel_color(cub, texture_id, texture.x, texture.y);
		if (color >= 0 && y >= 0 && x >= 0 && y < cub->win_size[0]
			&& x < cub->win_size[1])
			cub_pixel_put(&cub->img, x, y, color);
		y++;
		i++;
	}
}

void	put_door_wall_slice(t_cub *cub, int texture_id, int x,
							t_iposition texture)
{
	int	screen_wall_height;
	int	i;
	int	y;
	int	color;
	int	wall_height;

	wall_height = cub->doors[x]->portal->height;
	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[0])
		screen_wall_height = cub->win_size[0];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	i = 0;
	while (i < screen_wall_height)
	{
		texture.y = (i + (wall_height - screen_wall_height) / 2) \
		* cub->textures[texture_id].height / wall_height;
		color = get_texture_pixel_color(cub, texture_id, texture.x, texture.y);
		if (color >= 0)
			if (y >= 0 && x >= 0 && y < cub->win_size[0]
				&& x < cub->win_size[1])
				cub_pixel_put(&cub->img, x, y, color);
		y++;
		i++;
	}
}

void	glass_put_wall_slice(t_cub *cub, int x, t_iposition texture,
				int texture_id)
{
	int	screen_wall_height;
	int	wall_height;
	int	i;
	int	y;
	int	color;

	wall_height = cub->glass[x]->portal->height;
	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[HEIGHT])
		screen_wall_height = cub->win_size[HEIGHT];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	i = 0;
	while (i < screen_wall_height)
	{
		texture.y = (i + (wall_height - screen_wall_height) / 2) \
				* cub->textures[texture_id].height / wall_height;
		color = get_texture_pixel_color(cub, texture_id, texture.x, texture.y);
		if (color >= 0 && y >= 0 && x >= 0 && y < cub->win_size[0]
			&& x < cub->win_size[1])
			cub_pixel_put(&cub->img, x, y, color);
		y++;
		i++;
	}
}

void	put_outline_wall_slice(t_cub *cub, int x, int texture_id,
				t_iposition texture)
{
	int	i;
	int	y;
	int	screen_wall_height;
	int	wall_height;

	wall_height = cub->portals[x]->portal->height;
	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[0])
		screen_wall_height = cub->win_size[0];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	i = 0;
	while (i < screen_wall_height)
	{
		texture.y = (i + (wall_height - screen_wall_height) / 2) \
				* cub->textures[texture_id].height / wall_height;
		if (is_portal_middle(cub, texture, texture_id))
			put_transparency(cub, x, y, texture_id);
		else if (y >= 0 && x >= 0 && y < cub->win_size[0]
			&& x < cub->win_size[1])
			cub_pixel_put(&cub->img, x, y, \
		get_texture_pixel_color(cub, texture_id, texture.x, texture.y));
		y++;
		i++;
	}
}

void	put_wall_slice(t_cub *cub, int x, int texture_id, t_iposition texture)
{
	int	screen_wall_height;
	int	wall_height;
	int	i;
	int	y;

	wall_height = cub->wall_heights[x];
	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[HEIGHT])
		screen_wall_height = cub->win_size[HEIGHT];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	i = 0;
	while (i < screen_wall_height)
	{
		texture.y = (i + (wall_height - screen_wall_height) / 2) \
				* cub->textures[texture_id].height / wall_height;
		if (y >= 0 && x >= 0 && y < cub->win_size[0] && x < cub->win_size[1])
			cub_pixel_put(&cub->img, x, y, \
		get_texture_pixel_color(cub, texture_id, texture.x, texture.y));
		y++;
		i++;
	}
}
