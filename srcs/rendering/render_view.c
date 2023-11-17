/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/16 14:38:02 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

int	cub_textures_render(t_cub *cub, int wall_height, int x,
					t_position ray_collision)
{
	if (cub->data->baj->is_activated \
	&& get_time() - cub->data->baj->last_moove > cub->data->baj->speed)
	{
		get_next_baj(cub->data->wall_sur, cub->data->baj,
			cub->data->baj->cur_pos);
		cub->data->baj->last_moove = get_time();
	}
	return (cub_texture_put(x, cub, wall_height, ray_collision));
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
		j = cub_textures_render(cub, wall_height[i], i, ray_collision[i]);
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
