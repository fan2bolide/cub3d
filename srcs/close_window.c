/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:03:52 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/12 20:05:52 by bajeanno         ###   ########.fr       */
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
	usleep(1000);
	while (i < NB_THREADS)
		pthread_join(cub->threads[i++], NULL);
	pthread_mutex_destroy(&cub->finished_mutex);
	pthread_mutex_destroy(&cub->program_ends_mutex);
	pthread_mutex_destroy(&cub->ray_mutex);
	free(cub->threads);
	i = 0;
	while (i <= 16)
		mlx_destroy_image(cub->mlx, cub->textures[i++].img);
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	destroy_data(cub->data);
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
	while (i <= 15)
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
