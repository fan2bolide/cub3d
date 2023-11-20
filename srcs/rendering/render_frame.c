/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:59:47 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/20 23:51:57 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static double	modulo_2_pi(double angle)
{
	if (angle < 0)
		angle += M_PI * 2;
	if (angle >= M_PI * 2)
		angle -= M_PI * 2;
	return (angle);
}

static int	get_wall_height(t_cub *cub, double wall_distance, double ray_angle)
{
	double	wall_height;
	double	view_angle;

	view_angle = cub->view_angle;
	while (cos(fabs(ray_angle - view_angle)) < cos(M_PI_4))
		view_angle = modulo_2_pi(view_angle + M_PI_2);
	wall_distance *= cos(ray_angle - view_angle);
	wall_height = (SCREEN_DISTANCE * cub->win_size[0] / wall_distance);
	return ((int)wall_height);
}

static void	compute_arrays(t_cub *cub, t_position *ray_pos, double *angle, \
															int *wall_height)
{
	int		nb_segments;
	int		win_size_2;
	int		i;
	double	segments_size;

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
		angle[i] = (cub->view_angle * (i <= (win_size_2))) \
		+ (cub->view_angle * (i > (win_size_2))) \
		- atan(nb_segments * segments_size);
		angle[i] = modulo_2_pi(angle[i]);
		shoot_ray(ray_pos + i, cub, angle + i, cub->wall_distance + i);
		wall_height[i] = get_wall_height(cub, cub->wall_distance[i], angle[i]);
		i++;
	}
}

void	clear_lists(t_cub *cub)
{
	int i;

	i = 0;
	while (i < cub->win_size[WIDTH])
		ft_lstclear(cub->portals[i++], free);
}

int	render_frame(t_cub *cub)
{
	compute_arrays(cub, cub->rays, cub->angles, cub->wall_heights);
	render_view(cub, cub->rays, cub->wall_heights);
	render_mini_map(cub, cub->rays);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	clear_lists(cub);
	return (1);
}
