/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:38:35 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/01 14:18:37 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	set_custom_texture(int texture_id, size_t *texture_x,
							t_position ray_collision, t_cub *cub)
{
	if (ray_collision.x == (int)ray_collision.x)
	{
		if (cub->player_position.x > ray_collision.x)
			*texture_x = (int)(((int)(ray_collision.y) + 1 - ray_collision.y)
					* cub->textures[texture_id].width);
		else
			*texture_x = (int)((ray_collision.y - (int)(ray_collision.y))
					* cub->textures[texture_id].width);
	}
	else
	{
		if (cub->player_position.y > ray_collision.y)
			*texture_x = (int)((ray_collision.x - ((int) ray_collision.x))
					* cub->textures[texture_id].width);
		else
			*texture_x = (int)((((int)ray_collision.x) + 1 - ray_collision.x)
					* cub->textures[texture_id].width);
	}
}

bool	is_bajeanno_tile(t_position ray_collision, t_cub *cub)
{
	size_t		i;
	static char	orientations[4] = {'N', 'S', 'W', 'E'};
	int			ray_x_match[2];
	int			ray_y_match[2];
	int			ray_glob_cond[4];

	ft_memcpy(ray_x_match, (int [2]){ray_collision.x != (int)ray_collision.x, \
	ray_collision.x == (int)ray_collision.x}, 2 * sizeof(int));
	ft_memcpy(ray_y_match, (int [2]){ray_collision.y == (int)ray_collision.y, \
	ray_collision.y != (int)ray_collision.y}, 2 * sizeof(int));
	ft_memcpy(ray_glob_cond, (int [4]){(int)ray_collision.y - 1 == \
	cub->data->baj->y, (int)ray_collision.y == cub->data->baj->y, \
	(int)ray_collision.x == cub->data->baj->x + 1, \
	(int)ray_collision.x == cub->data->baj->x}, 4 * sizeof(int));
	i = 0;
	while (i++ < 4)
		if (cub->data->baj->orientation == orientations[i - 1])
			if ((ft_isset(orientations[i - 1], "NS") && (int)ray_collision.x \
			== cub->data->baj->x) || (ft_isset(orientations[i - 1], "WE") \
			&& (int)ray_collision.y == cub->data->baj->y))
				if (ray_x_match[i - 1 > 1] && ray_y_match[i - 1 > 1]
					&& ray_glob_cond[i - 1])
					return (true);
	return (false);
}

int	set_n_s_textures(size_t *texture_x,
					t_position ray_collision, t_cub *cub, double angle)
{
	int	texture_id;

	if (sin(angle) < 0)
	{
		texture_id = 0;
		*texture_x = (int)((ray_collision.x - ((int) ray_collision.x)) \
			* cub->textures[texture_id].width);
	}
	else
	{
		texture_id = 1;
		*texture_x = (int)((((int) ray_collision.x) + 1 - ray_collision.x) \
			* cub->textures[texture_id].width);
	}
	return (texture_id);
}

int	set_texture_id_and_x(size_t *texture_x, \
							t_position ray_collision, t_cub *cub, double angle)
{
	int	texture_id;

	if (cub->data->baj->is_activated && is_bajeanno_tile(ray_collision, cub))
		return (set_custom_texture(4, texture_x, ray_collision, cub), 4);
	if (ray_collision.x == (int) ray_collision.x)
	{
		if (cos(angle) < 0)
		{
			texture_id = 2;
			*texture_x = (int)(((int)(ray_collision.y) + 1 - ray_collision.y) \
								* cub->textures[texture_id].width);
		}
		else
		{
			texture_id = 3;
			*texture_x = (int)((ray_collision.y - (int)(ray_collision.y)) \
								* cub->textures[texture_id].width);
		}
		return (texture_id);
	}
	return (set_n_s_textures(texture_x, ray_collision, cub, angle));
}

int	cub_texture_put(int x, t_cub *cub, int wall_height,
			t_position ray_collision)
{
	int			i;
	int			y;
	int			screen_wall_height;
	int			texture_id;
	t_iposition	texture;

	texture_id = set_texture_id_and_x(&texture.x, ray_collision, \
										cub, cub->angles[x]);
	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[0])
		screen_wall_height = cub->win_size[0];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	i = 0;
	while (i < screen_wall_height)
	{
		texture.y = (i + (wall_height - screen_wall_height) / 2) \
				* cub->textures[texture_id].height / wall_height;
		if (y >= 0 && x >= 0 && y < cub->win_size[0] && x < cub->win_size[1])
			cub_pixel_put(&cub->img, x, y, \
			*((int *)(cub->textures[texture_id].addr + (texture.y * \
			cub->textures[texture_id].line_length + texture.x * \
			(cub->textures[texture_id].bits_per_pixel / 8)))));
		y++;
		i++;
	}
	return (y);
}

int	put_outline_texture(int x, t_cub *cub, int wall_height, \
						t_position ray_collision)
{
	int			i;
	int			y;
	int			screen_wall_height;
	int			texture_id;
	t_iposition	texture;

	texture_id = set_texture_id_and_x(&texture.x, ray_collision, cub,
	((t_prtl_list *)ft_dblstlast((t_dblist *)cub->portals[x]))->portal->angle);
	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[0])
		screen_wall_height = cub->win_size[0];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	i = 0;
	while (i < screen_wall_height)
	{
		texture.y = (i + (wall_height - screen_wall_height) / 2) \
				* cub->textures[texture_id].height / wall_height;
		if (((int)texture.x > cub->textures[texture_id].width / 5 && (int)texture.x < cub->textures[texture_id].width - cub->textures[texture_id].width / 5)
			&& ((int)texture.y > cub->textures[texture_id].height / 5 && (int)texture.y < cub->textures[texture_id].height - cub->textures[texture_id].width / 5))
		{
			y++;
			i++;
			continue ;
		}
		if (y >= 0 && x >= 0 && y < cub->win_size[0] && x < cub->win_size[1])
			cub_pixel_put(&cub->img, x, y, \
			*((int *)(cub->textures[texture_id].addr + (texture.y * \
			cub->textures[texture_id].line_length + texture.x * \
			(cub->textures[texture_id].bits_per_pixel / 8)))));
		y++;
		i++;
	}
	return (y);
}

int	cub_portal_texture_put(int x, t_cub *cub, int wall_height,
					   t_position ray_collision)
{
	int			i;
	int			y;
	int			screen_wall_height;
	int			texture_id;
	t_iposition	texture;

	texture_id = -1;
	if (cub->menu.outline == 1)
		put_outline_texture(x, cub, wall_height, ray_collision);
	set_portal_texture(&texture_id, &texture.x, ray_collision, cub);
	if (texture_id == -1)
		return (1);
	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[0])
		screen_wall_height = cub->win_size[0];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	i = 0;
	while (i < screen_wall_height)
	{
		texture.y = (i + (wall_height - screen_wall_height) / 2) \
				* cub->textures[texture_id].height / wall_height;
		int color = *((int *)(cub->textures[texture_id].addr + (texture.y * \
			cub->textures[texture_id].line_length + texture.x * \
			(cub->textures[texture_id].bits_per_pixel / 8))));
		if (color < 0)
		{
			y++;
			i++;
			continue;
		}
		if (y >= 0 && x >= 0 && y < cub->win_size[0] && x < cub->win_size[1])
			cub_pixel_put(&cub->img, x, y, color);
		y++;
		i++;
	}
	return (y);
}
