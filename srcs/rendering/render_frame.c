/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:59:47 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/09 21:18:28 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

int	get_wall_height(t_cub *cub, double wall_distance, double ray_angle)
{
	double	wall_height;
	double	view_angle;

	view_angle = cub->view_angle;
	while (cos(fabs(ray_angle - view_angle)) < cos(cub->fov / 2))
		view_angle = modulo_2_pi(view_angle + M_PI_2);
	wall_distance *= cos(ray_angle - view_angle);
	wall_height = (SCREEN_DISTANCE * cub->win_size[0] / wall_distance);
	if (wall_height > 10000000)
		wall_height = 10000000;
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
		ft_lstclear((t_list **)(cub->glass + i), free);
		cub->glass[i] = NULL;
		ft_lstclear((t_list **)(cub->doors + i), free);
		cub->doors[i++] = NULL;

	}
}

void	wait_rendering(t_cub *cub, struct timeval start_time)
{
	int		i;
	bool	thread_has_finished;

	i = 0;
	while (i < NB_THREADS)
	{
		pthread_mutex_lock(&cub->finished_mutex);
		thread_has_finished = cub->threads_finished_rendering[i];
		pthread_mutex_unlock(&cub->finished_mutex);
		if (thread_has_finished)
			i++;
		else
			usleep(100);
	}
	while (get_timestamp(start_time, get_current_time()) < 5)
		usleep(100);
}

void put_pixel_transparent(t_image *data, int x, int y, unsigned int color)
{
	int		old_color;
	t_color old_color_rgb;
	t_color new_color;
	t_color final_color;
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	old_color = *(int *) dst;
	old_color_rgb.blue = old_color & 0xFF;
	old_color_rgb.green = (old_color >> 8) & 0xFF;
	old_color_rgb.red = (old_color >> 16) & 0xFF;
	new_color.blue = color & 0xFF;
	new_color.green = (color >> 8) & 0xFF;
	new_color.red = (color >> 16) & 0xFF;
	new_color.transparency = (color >> 24) & 0xFF;
	final_color.red = (new_color.red * new_color.transparency + old_color_rgb.red * (255 - new_color.transparency)) / 255;
	final_color.green = (new_color.green * new_color.transparency + old_color_rgb.green * (255 - new_color.transparency)) / 255;
	final_color.blue = (new_color.blue * new_color.transparency + old_color_rgb.blue * (255 - new_color.transparency)) / 255;
	cub_pixel_put(data, x, y, *(int *) (&final_color));
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
	cub_display_door_hint(cub);
	if (!cub->menu.on_screen && cub->menu.x + cub->menu.menu_bg.width == 0)
		render_mini_map(cub, cub->rays);
	display_crosshair(cub);
	display_portal_gun(cub);
	summon_game_menu(cub, cub->menu.on_screen + (!cub->menu.on_screen * -1));
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (1);
}
