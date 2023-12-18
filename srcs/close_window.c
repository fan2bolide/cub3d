/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:03:52 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/14 17:28:28 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#if defined(__linux__)

int close_window(t_cub *cub)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&cub->program_ends_mutex);
	cub->program_ends = true;
	pthread_mutex_unlock(&cub->program_ends_mutex);
//	usleep(1000);
	while (i < NB_THREADS)
		pthread_join(cub->threads[i++], NULL);
	pthread_mutex_destroy(&cub->finished_mutex);
	pthread_mutex_destroy(&cub->program_ends_mutex);
	pthread_mutex_destroy(&cub->ray_mutex);
	mlx_loop_end(cub->mlx);
	free(cub->threads);
	i = 0;
	while (i <= 17)
		mlx_destroy_image(cub->mlx, cub->textures[i++].img);
	mlx_destroy_image(cub->mlx, cub->menu.button.img);
	mlx_destroy_image(cub->mlx, cub->menu.button_shadow.img);
	mlx_destroy_image(cub->mlx, cub->menu.checker_plain.img);
	mlx_destroy_image(cub->mlx, cub->menu.cursor.img);
	mlx_destroy_image(cub->mlx, cub->menu.menu_bg.img);
	mlx_destroy_image(cub->mlx, cub->menu.reset.img);
	mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->load_screen.img)
		mlx_destroy_image(cub->mlx, cub->load_screen.img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	destroy_data(cub->data);
	clear_lists(cub);
	free(cub->portals);
	free(cub->doors);
	free(cub->doors_status);
	free(cub->glass);
	free(cub->rays);
	free(cub->angles);
	free(cub->wall_heights);
	free(cub->wall_distance);
	free(cub);
	exit(0);
}
#elif defined(__APPLE__)

int	close_window(t_cub *cub)
{
	int i;

	i = 0;
	pthread_mutex_lock(&cub->program_ends_mutex);
	cub->program_ends = true;
	pthread_mutex_unlock(&cub->program_ends_mutex);
	usleep(1000);
	while (i < NB_THREADS)
		pthread_join(cub->threads[i++], NULL);
	pthread_mutex_destroy(&cub->finished_mutex);
	pthread_mutex_destroy(&cub->program_ends_mutex);
	pthread_mutex_destroy(&cub->ray_mutex);
	free(cub->threads);
	i = 0;
	while (i <= 17)
		mlx_destroy_image(cub->mlx, cub->textures[i++].img);
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	free(cub->angles);
	free(cub->rays);
	free(cub->wall_heights);
	free(cub->mlx);
	destroy_data(cub->data);
	free(cub);
	exit(0);
}
#endif
