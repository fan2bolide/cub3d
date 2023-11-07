/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/07 02:40:17 by nfaust           ###   ########.fr       */
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
	if (ray_collision.x == (int) ray_collision.x)
	{
		if (cub->player_position->x > ray_collision.x)
		{
			*texture_id = 2;
			*texture_x = (int) (((int) (ray_collision.y) + 1 - ray_collision.y) * cub->textures[*texture_id].width);
		} else
		{
			*texture_id = 3;
			*texture_x = (int) ((ray_collision.y - (int) (ray_collision.y)) * cub->textures[*texture_id].width);
		}
	} else
	{
		if (cub->player_position->y > ray_collision.y)
		{
			*texture_id = 0;
			*texture_x = (int) ((ray_collision.x - ((int) ray_collision.x)) * cub->textures[*texture_id].width);
		} else
		{
			*texture_id = 1;
			*texture_x = (int) ((((int) ray_collision.x) + 1 - ray_collision.x) * cub->textures[*texture_id].width);
		}
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
//	set_next_bajeanno_pos(cub, cub->bajeanno.coords.x, cub->bajeanno.coords.y);
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
//	if (cub->bajeanno.is_activated && (ray_collision.x == (double)cub->bajeanno.coords.x || ray_collision.y == (double)cub->bajeanno.coords.y))
//		set_bajenno_texture(&texture_id, &texture.x, ray_collision, cub);
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

void	render_view(t_cub *cub, t_position ray_collision[cub->win_size[1]], \
		double angle[cub->win_size[1]], const int wall_height[cub->win_size[1]])
{
	int			i;
	int			j;

	i = 0;
	while (i < cub->win_size[1])
	{
		j = 0;
		if (wall_height[i] < cub->win_size[0])
		{
			while (j < (cub->win_size[0] - wall_height[i]) / 2)
			{
				cub_pixel_put(&cub->img, i, j, *((int *)cub->data->ceiling_color));
				j++;
			}
			while (j < cub->win_size[0])
			{
				cub_pixel_put(&cub->img, i, j, *((int *)cub->data->floor_color));
				j++;
			}
		}
		j = cub_textures_put(cub, wall_height[i], i, ray_collision[i]);
		i++;
	}
}

int	get_wall_height(t_cub *cub, t_position ray, double angle)
{
	double	wall_distance;
	double	wall_height;

	wall_distance = sqrt((ray.x - cub->player_position->x) * \
	(ray.x - cub->player_position->x) + (ray.y - cub->player_position->y) * \
	(ray.y - cub->player_position->y));
	wall_distance *= cos(angle - cub->view_angle);

	wall_height = (SCREEN_DISTANCE * cub->win_size[0] / wall_distance);
	return ((int)wall_height);
}

int	render_frame(t_cub *cub)
{
	t_position	ray_pos[cub->win_size[1]];
	double		angle[cub->win_size[1]];
	int			wall_height[cub->win_size[1]];
	int			nb_segments;
	int			win_size_2;
	double		segments_size;
	int			i;

	win_size_2 = cub->win_size[1] / 2;
	i = 0;
	segments_size = 2 * tan(cub->fov / 2) / (cub->win_size[1] - 1);
	while (i < cub->win_size[1])
	{
		ray_pos[i].x = cub->player_position->x;
		ray_pos[i].y = cub->player_position->y;
		if (i <= win_size_2)
			nb_segments = win_size_2 - i;
		else
			nb_segments = (cub->win_size[1] - i) - win_size_2;
		angle[i] = (cub->view_angle * (i <= (win_size_2))) + (cub->view_angle * (i > (win_size_2))) - atan(nb_segments * segments_size);
		if (angle[i] < 0)
			angle[i] += M_PI * 2;
		if (angle[i] > M_PI * 2)
			angle[i] -= M_PI * 2;
		shoot_ray(ray_pos + i, cub, angle[i]);
		wall_height[i] = get_wall_height(cub, ray_pos[i], angle[i]);
		i++;
	}
	render_view(cub, ray_pos, angle, wall_height);
	render_mini_map(cub, ray_pos);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (1);
}

//ratio horizontal = 2tan(a) / win_size->x
