/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:59:47 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/29 08:07:45 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#define NB_OF_USECONDS_IN_A_SECOND		1000000
#define NB_OF_USECONDS_IN_A_MILLISECOND	1000

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

void	clear_lists(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->win_size[WIDTH])
	{
		ft_lstclear((t_list **)(cub->portals + i), free);
		cub->portals[i] = NULL;
		i++;
	}
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

void	wait_rendering(t_cub *cub, struct timeval start_time)
{
	int i;
	while (1)
	{
		pthread_mutex_lock(&cub->ray_mutex);
//		printf("%d %d\n", cub->next_ray_to_compute, cub->is_frame_rendered);
		if (cub->next_ray_to_compute >= cub->win_size[WIDTH] && cub->is_frame_rendered)
		{
			pthread_mutex_unlock(&cub->ray_mutex);
			break ;
		}
		pthread_mutex_unlock(&cub->ray_mutex);
		usleep(100);
	}
	while (get_timestamp(start_time, get_current_time()) < 5)
		usleep(100);
	i = 0;
	while (i < NB_THREADS)
	{
		bool test;
		pthread_mutex_lock(&cub->finished_mutex);
		test = cub->threads_finished_rendering[i];
		pthread_mutex_unlock(&cub->finished_mutex);
		if (test)
			i++;
		else
			usleep(100);
	}
}

int	render_frame(t_cub *cub)
{
	struct timeval	start_time;

	start_time = get_current_time();
	if (cub->load_screen.img)
		return (1);
	pthread_mutex_lock(&cub->finished_mutex);
	ft_bzero(cub->threads_finished_rendering, NB_THREADS * sizeof(bool));
	pthread_mutex_unlock(&cub->finished_mutex);
	pthread_mutex_lock(&cub->ray_mutex);
	cub->is_frame_rendered = 0;
	cub->next_ray_to_compute = 0;
	pthread_mutex_unlock(&cub->ray_mutex);
	pthread_mutex_lock(&cub->program_ends_mutex);
	if (cub->program_ends == 1)
		return (0);
	pthread_mutex_unlock(&cub->program_ends_mutex);
	wait_rendering(cub, start_time);
	if (!cub->menu.on_screen && cub->menu.x + cub->menu.menu_bg.width == 0)
		render_mini_map(cub, cub->rays);
	clear_lists(cub);
	display_crosshair(cub);
	summon_game_menu(cub, cub->menu.on_screen + (!cub->menu.on_screen * -1));
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (1);
}
