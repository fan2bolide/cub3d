/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/06 23:14:51 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void swap(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}

void	set_texture_id_and_x(int *texture_id, size_t *texture_x, t_position ray_collision, t_cub *cub)
{
	if (ray_collision.x == (int)ray_collision.x)
	{
		if (cub->player_position->x > ray_collision.x)
		{
			*texture_id = 2;
			*texture_x = (int) (((int) (ray_collision.y) + 1 - ray_collision.y) * cub->textures[*texture_id].width);
		}
		else
		{
			*texture_id = 3;
			*texture_x = (int) ((ray_collision.y - (int) (ray_collision.y)) * cub->textures[*texture_id].width);
		}
		return ;
	}
	if (cub->player_position->y > ray_collision.y)
	{
		*texture_id = 0;
		*texture_x = (int) ((ray_collision.x - ((int) ray_collision.x)) * cub->textures[*texture_id].width);
	}
	else
	{
		*texture_id = 1;
		*texture_x = (int) ((((int)ray_collision.x) + 1 - ray_collision.x) * cub->textures[*texture_id].width);
	}
}

void	set_next_bajeanno_pos(t_cub *cub, int bj_x, int bj_y)
{
	if (!cub->data->map[bj_y][bj_x + 1] || cub->data->map[bj_y][bj_x + 1] == 0)
	{
		if (bj_y - 1 >= 0 && (!cub->data->map[bj_y - 1][bj_x] || cub->data->map[bj_y - 1][bj_x] == 0))
		{
			if (cub->data->map[bj_y + 1] && (!cub->data->map[bj_y + 1][bj_x] || cub->data->map[bj_y + 1][bj_x] == 0))
			{
				if (bj_x - 1 >= 0 && (!cub->data->map[bj_y][bj_x - 1] || cub->data->map[bj_y][bj_x - 1] == 0))
				{

				}
				else if (cub->data->map[bj_y][bj_x - 1] == 1)
					return (cub->bajeanno.coords.x -= 1, (void) 0);
			}
			else if (cub->data->map[bj_y - 1][bj_x] == 1)
				return (cub->bajeanno.coords.y -= 1, (void) 0);
		}
		else if (cub->data->map[bj_y - 1][bj_x] == 1)
			return (cub->bajeanno.coords.y -= 1, (void) 0);
	}
	else if (cub->data->map[bj_y][bj_x + 1] == 1)
		return (cub->bajeanno.coords.x += 1, (void) 0);
}

void	set_bajenno_texture(int *texture_id, size_t *texture_x, t_position ray_collision, t_cub *cub)
{
	*texture_id = 4;
	if (ray_collision.x == (int)ray_collision.x)
	{
		if (cub->player_position->x > ray_collision.x)
			*texture_x = (int) (((int) (ray_collision.y) + 1 - ray_collision.y) * cub->textures[*texture_id].width);
		else
			*texture_x = (int) ((ray_collision.y - (int) (ray_collision.y)) * cub->textures[*texture_id].width);
	}
	else
	{
		if (cub->player_position->y > ray_collision.y)
			*texture_x = (int) ((ray_collision.x - ((int) ray_collision.x)) * cub->textures[*texture_id].width);
		else
			*texture_x = (int) ((((int)ray_collision.x) + 1 - ray_collision.x) * cub->textures[*texture_id].width);
	}
	set_next_bajeanno_pos(cub, cub->bajeanno.coords.x, cub->bajeanno.coords.y);
}

int	cub_textures_put(t_cub *cub, int wall_height, int x,t_position ray_collision)
{
	t_iposition	texture;
	int		screen_wall_height;
	int 	y;
	int 	i;
	int 	texture_id;

	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[0])
		screen_wall_height = cub->win_size[0];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	if (cub->bajeanno.is_activated && (ray_collision.x == (double)cub->bajeanno.coords.x || ray_collision.y == (double)cub->bajeanno.coords.y))
		set_bajenno_texture(&texture_id, &texture.x, ray_collision, cub);
	set_texture_id_and_x(&texture_id, &texture.x, ray_collision, cub);
	i = 0;
	while (i < screen_wall_height)
	{
		texture.y = (i + (wall_height - screen_wall_height) / 2) * cub->textures[texture_id].height / wall_height;
		if (y >= 0 && x >= 0 && y < cub->win_size[0] && x < cub->win_size[1])
			cub_pixel_put(&cub->img, x, y, *((int*)(cub->textures[texture_id].addr + (texture.y * cub->textures[texture_id].line_length + texture.x * (cub->textures[texture_id].bits_per_pixel / 8)))));
		y++;
		i++;
	}
	return (y);
}

void	render_view(t_cub *cub, t_position *ray_collision, \
								const int *wall_height)
{
	int	i;
	int	j;
	int screen_height;

	screen_height = cub->win_size[0] / 2;
	i = 0;
	while (i < cub->win_size[1])
	{
		j = 0;
		{
			while (j < screen_height)
				cub_pixel_put(&cub->img, i, j++, *((int *)cub->data->ceiling_color));
			while (j < cub->win_size[0])
				cub_pixel_put(&cub->img, i, j++, *((int *)cub->data->floor_color));
		}
		i++;
	}
	i = 0;
	while (i < cub->win_size[1])
	{
//		if (wall_height[i] < cub->win_size[0])
		cub_textures_put(cub, wall_height[i], i, ray_collision[i]);
		i++;
	}
}
