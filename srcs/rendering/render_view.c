/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:01:35 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/05 20:30:10 by nfaust           ###   ########.fr       */
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

int	cub_textures_put(t_cub *cub, const int wall_height, int x,t_position ray_collision)
{
	char	*color;
	t_iposition	texture;
	int		screen_wall_height;
	int 	y;
	int 	i;

	screen_wall_height = wall_height;
	if (wall_height > cub->win_size[0])
		screen_wall_height = cub->win_size[0];
	texture.x = (int)((ray_collision.x - (int)(ray_collision.x)) * cub->textures[0].width);
	y = cub->win_size[0] / 2 - screen_wall_height / 2;
//	if ((int)x == x)
//		swap(&x, &y);
	// TODO faire un truc si la ligne est plus grande que la taille de la fenetre
	i = 0;
//	if (x== cub->win_size[1] / 2)
	while (i < screen_wall_height)
	{
		texture.y = (i + (wall_height - screen_wall_height) / 2) * cub->textures[0].height / wall_height;
		color = cub->textures[0].addr + (texture.y * cub->textures[0].line_length + texture.x * (cub->textures[0].bits_per_pixel / 8));
		cub_pixel_put(&cub->img, x, y, (int)*color);
		y++;
		i++;
	}
//	printf("%i %d %d\n", screen_wall_height, x, y);

	return (y);
}

void	render_view(t_cub *cub, t_position ray_collision[cub->win_size[1]], \
		double angle[cub->win_size[1]], const int wall_height[cub->win_size[1]])
{
	int			i;
	int			j;
//	int			color_x;
//	int			color_y;
//	int			color;

	i = 0;
	while (i < cub->win_size[1])
	{
//		color = get_color_of_wall((int)ray_collision[i].x -
//		(ray_collision[i].x == (int)ray_collision[i].x && cos(angle[i]) < 0),
//		(int)ray_collision[i].y -
//		(ray_collision[i].y == (int)ray_collision[i].y && sin(angle[i]) < 0));
		j = 0;
		while (j < (cub->win_size[0] - wall_height[i]) / 2)
		{
			cub_pixel_put(&cub->img, i, j, 0xff69b4);
			j++;
		}
//		while (j < (cub->win_size[0] - wall_height[i]) / 2 + wall_height[i])
//		{
			j = cub_textures_put(cub, wall_height[i], i, ray_collision[i]);
//		}
		while (j < cub->win_size[0])
		{
			cub_pixel_put(&cub->img, i, j, 0xFF00FF);
			j++;
		}

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
