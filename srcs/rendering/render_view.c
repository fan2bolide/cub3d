/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/15 14:53:50 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

void	set_texture_id_and_x(int *texture_id, size_t *texture_x, \
							t_position ray_collision, t_cub *cub)
{
	if (ray_collision.x == (int) ray_collision.x)
	{
		if (cub->player_position->x > ray_collision.x)
		{
			*texture_id = 2;
			*texture_x = (int)(((int)(ray_collision.y) + 1 - ray_collision.y) \
								* cub->textures[*texture_id].width);
		}
		else
		{
			*texture_id = 3;
			*texture_x = (int)((ray_collision.y - (int)(ray_collision.y)) \
								* cub->textures[*texture_id].width);
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
}

bool	is_bajeanno_tile(t_position ray_collision, t_cub *cub)
{
	size_t	i;
	static char	orientations[4] = {'N', 'S', 'W', 'E'};
	int	ray_x_match[4] = {ray_collision.x != (int)ray_collision.x, ray_collision.x == (int)ray_collision.x};
	int	ray_y_match[4] = {ray_collision.y == (int)ray_collision.y, ray_collision.y != (int)ray_collision.y};
	int	ray_glob_cond[4] = {(int)ray_collision.y - 1 == cub->data->baj->y, (int)ray_collision.y == cub->data->baj->y, (int)ray_collision.x == cub->data->baj->x + 1, (int)ray_collision.x == cub->data->baj->x};

	if (!cub->data->baj->is_activated)
		return (false);
	i = 0;
	while (i < 4)
	{
		if (cub->data->baj->orientation == orientations[i])
			if ((ft_isset(orientations[i], "NS") && (int)ray_collision.x == cub->data->baj->x) || (ft_isset(orientations[i], "WE") && (int)ray_collision.y == cub->data->baj->y))
				if (ray_x_match[i > 1] && ray_y_match[i > 1] && ray_glob_cond[i])
					return (true);
		i++;
	}
	return (false);
}

int	cub_textures_put(t_cub *cub, int wall_height, int x, t_position ray_collision)
{
	t_iposition	texture;
	int			screen_wall_height;
	int			y;
	int			i;
	int			texture_id;

	screen_wall_height = wall_height;
	if (cub->data->baj->is_activated && get_time() - cub->data->baj->last_moove > cub->data->baj->speed)
	{
		get_next_baj(cub->data->wall_sur, cub->data->baj, cub->data->baj->cur_pos);
		cub->data->baj->last_moove = get_time();
	}
	if (wall_height > cub->win_size[0])
		screen_wall_height = cub->win_size[0];
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
	if (is_bajeanno_tile(ray_collision, cub))
		set_bajenno_texture(&texture_id, &texture.x, ray_collision, cub);
	else
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
	int screen_height_2;

	screen_height_2 = cub->win_size[0] / 2;
	i = 0;
	while (i < cub->win_size[1])
	{
		j = 0;
		{
			while (j < screen_height_2)
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
