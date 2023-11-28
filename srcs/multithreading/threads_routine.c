/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:36:26 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/28 16:04:10 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "rendering.h"

static int	get_ray_index(t_cub *cub)
{
	int	i;

	pthread_mutex_lock(&cub->ray_mutex);
	i = cub->next_ray_to_compute;
	if (i < cub->win_size[WIDTH])
		cub->next_ray_to_compute++;
	pthread_mutex_unlock(&cub->ray_mutex);
	return (i);
}

void	*render_thread_routine(void *attr)
{
	t_cub	*cub;
	int		i;
	double	segments_size;

	cub = ((t_render_thread *)attr)->cub;
	segments_size = 2 * tan(cub->fov / 2) / (cub->win_size[1] - 1);
	while (1)
	{
		if (cub->program_ends)
			return (NULL);
		i = get_ray_index(cub);
		if (i < cub->win_size[WIDTH])
		{
			if (!compute_ray(cub, i, segments_size))
			{
				pthread_mutex_lock(&cub->program_ends_mutex);
				cub->program_ends = 1;
				pthread_mutex_unlock(&cub->program_ends_mutex);
				continue ;
			}
			render_column(cub, i);
			pthread_mutex_lock(&cub->ray_mutex);
			if (cub->next_ray_to_compute == cub->win_size[WIDTH])
			{
				cub->is_frame_rendered = true;
			}
			pthread_mutex_unlock(&cub->ray_mutex);
		}
		else
		{
			pthread_mutex_lock(&cub->ray_mutex);
			cub->threads_finished_rendering[((t_render_thread *)attr)->id] = true;
			pthread_mutex_unlock(&cub->ray_mutex);
			usleep(100);
		}
	}
}
