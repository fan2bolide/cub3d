/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:59:47 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/26 04:12:05 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

# define NB_OF_USECONDS_IN_A_SECOND 1000000
# define NB_OF_USECONDS_IN_A_MILLISECOND 1000

static double	modulo_2_pi(double angle)
{
	if (angle < 0)
		angle += M_PI * 2;
	if (angle >= M_PI * 2)
		angle -= M_PI * 2;
	return (angle);
}

int	get_wall_height(t_cub *cub, double wall_distance, double ray_angle)
{
	double	wall_height;
	double	view_angle;

	view_angle = cub->view_angle;
	while (cos(fabs(ray_angle - view_angle)) < cos(cub->fov / 2))
		view_angle = modulo_2_pi(view_angle + M_PI_2);
	wall_distance *= cos(ray_angle - view_angle);
	wall_height = (SCREEN_DISTANCE * cub->win_size[0] / wall_distance);
	return ((int)wall_height);
}

void	compute_ray(t_cub *cub, int ray_id, double segments_size)
{
	int	win_size_2;
	int	nb_segments;

	win_size_2 = cub->win_size[WIDTH] / 2;
	cub->rays[ray_id].x = cub->player_position->x;
	cub->rays[ray_id].y = cub->player_position->y;
	if (ray_id <= win_size_2)
		nb_segments = win_size_2 - ray_id;
	else
		nb_segments = (cub->win_size[1] - ray_id) - win_size_2;
	cub->angles[ray_id] = (cub->view_angle * (ray_id <= (win_size_2))) \
		+ (cub->view_angle * (ray_id > (win_size_2))) \
		- atan(nb_segments * segments_size);
	cub->angles[ray_id] = modulo_2_pi(cub->angles[ray_id]);
	shoot_ray(cub->rays + ray_id, cub, cub->angles + ray_id, cub->wall_distance + ray_id);
	cub->wall_heights[ray_id] = get_wall_height(cub, cub->wall_distance[ray_id], cub->angles[ray_id]);
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
	int	i;

	i = 0;
	while (i < cub->win_size[WIDTH])
		ft_lstclear((t_list **)(cub->portals + i++), free);
}

struct timeval	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_usec >= NB_OF_USECONDS_IN_A_SECOND)
	{
		current_time.tv_sec += current_time.tv_usec \
								/ NB_OF_USECONDS_IN_A_SECOND;
		current_time.tv_usec %= NB_OF_USECONDS_IN_A_SECOND;
	}
	return (current_time);
}

long long	get_timestamp(const struct timeval start_time, \
							const struct timeval current_time)
{
	return ((current_time.tv_sec - start_time.tv_sec)
			* (long long)NB_OF_USECONDS_IN_A_MILLISECOND
			+ (current_time.tv_usec - start_time.tv_usec)
			  / NB_OF_USECONDS_IN_A_MILLISECOND);
}

int	render_frame(t_cub *cub)
{
	struct timeval start_time;

	start_time = get_current_time();
	if (cub->load_screen)
		return (1);
	clear_lists(cub);
	pthread_mutex_lock(&cub->ray_mutex);
	cub->next_ray_to_compute = 0;
	pthread_mutex_unlock(&cub->ray_mutex);
	while (1)
	{
		pthread_mutex_lock(&cub->ray_mutex);
		if (cub->next_ray_to_compute >= cub->win_size[WIDTH])
		{
			pthread_mutex_unlock(&cub->ray_mutex);
			break;
		}
		pthread_mutex_unlock(&cub->ray_mutex);
		usleep(100);
	}
	while (get_timestamp(start_time, get_current_time()) < 5)

		usleep(100);
//	compute_arrays(cub, cub->rays, cub->angles, cub->wall_heights);
//	render_view(cub, cub->rays, cub->wall_heights);
	render_mini_map(cub, cub->rays);
	display_crosshair(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	ft_putnbr(get_timestamp(start_time, get_current_time()));
	write(1, "\n", 1);
	return (1);
}
