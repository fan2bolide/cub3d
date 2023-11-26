/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:40:40 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/26 03:59:28 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "rendering.h"

void	*render_thread_routine(void *attr)
{
	t_cub	*cub;
	int		i;
	double	segments_size;

	cub = attr;
	segments_size = 2 * tan(cub->fov / 2) / (cub->win_size[1] - 1);
	while (1)
	{
		if (cub->program_ends)
			return (NULL);
		pthread_mutex_lock(&cub->ray_mutex);
		i = cub->next_ray_to_compute;
		if (i < cub->win_size[WIDTH])
			cub->next_ray_to_compute++;
		pthread_mutex_unlock(&cub->ray_mutex);
		if (i < cub->win_size[WIDTH])
		{
			compute_ray(cub, i, segments_size);
			render_column(cub, i);
		}
		else
			usleep(100);
	}
}

int	create_threads(t_cub *cub)
{
	int			i;

	i = 0;
	cub->threads = malloc(sizeof(pthread_t) * NB_THREADS);
	while (i < NB_THREADS)
	{
		pthread_create(cub->threads + i, NULL, render_thread_routine, cub);
		i++;
	}
	return (0);
}
