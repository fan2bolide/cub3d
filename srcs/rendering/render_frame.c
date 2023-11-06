/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:59:47 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/06 21:06:32 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void	modulo_2_pi(double *angle)
{
	if (*angle < 0)
		*angle += M_PI * 2;
	if (*angle > M_PI * 2)
		*angle -= M_PI * 2;
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

static void	compute_arrays(t_cub *cub, t_position *ray_pos, double *angle, \
															int *wall_height)
{
	int		nb_segments;
	int		win_size_2;
	double	segments_size;
	int		i;

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
		modulo_2_pi(angle + i);
		shoot_ray(ray_pos + i, cub, angle[i]);
		wall_height[i] = get_wall_height(cub, ray_pos[i], angle[i]);
		i++;
	}
}

int	render_frame(t_cub *cub)
{
	t_position	*ray_pos;
	double		*angle;
	int			*wall_height;

	ray_pos = malloc(sizeof(t_position) * cub->win_size[1]);
	angle = malloc(sizeof(double) * cub->win_size[1]);
	wall_height = malloc(sizeof(int) * cub->win_size[1]);
	if (!ray_pos || !angle || !wall_height)
		return (free(ray_pos), free(angle), free(wall_height), 0);
	compute_arrays(cub, ray_pos, angle, wall_height);
	render_view(cub, ray_pos, angle, wall_height);
	render_mini_map(cub, ray_pos);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (1);
}
