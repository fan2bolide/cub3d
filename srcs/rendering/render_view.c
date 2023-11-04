/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/04 05:58:19 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	render_view(t_cub *cub, t_position ray_collision[cub->win_size[1]], \
		double angle[cub->win_size[1]], const int wall_height[cub->win_size[1]])
{
	int			i;
	int			j;
	int			color_x;
	int			color_y;
	int			color;

	i = 0;
	while (i < cub->win_size[1])
	{
		color = get_color_of_wall((int)ray_collision[i].x - \
		(ray_collision[i].x == (int)ray_collision[i].x && cos(angle[i]) < 0), \
		(int)ray_collision[i].y - \
		(ray_collision[i].y == (int)ray_collision[i].y && sin(angle[i]) < 0));
		j = 0;
		while (j < (cub->win_size[0] - wall_height[i]) / 2)
			j++;
		while (j < (cub->win_size[0] - wall_height[i]) / 2 + wall_height[i])
		{
			cub_pixel_put(&cub->img, i, j, color);
			j++;
		}
		while (j < cub->win_size[0])
			j++;
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
	if (wall_distance < 0.5)
		wall_distance = 0.5;
	wall_height = (SCREEN_DISTANCE * cub->win_size[0] / wall_distance);
	if (wall_height > cub->win_size[0])
		wall_height = cub->win_size[0];
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

	mlx_destroy_image(cub->mlx, cub->img.img);
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, \
	&cub->img.line_length, &cub->img.endian);
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
//		if (i == win_size_2 * 2 - 1)
//			printf("%f\n", atan(nb_segments * segments_size));
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
