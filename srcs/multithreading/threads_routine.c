/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:36:26 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/29 08:51:37 by nfaust           ###   ########.fr       */
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

void	tell_rendering_is_finished(int id, t_cub *cub)
{
	pthread_mutex_lock(&cub->finished_mutex);
	cub->threads_finished_rendering[id] = true;
	pthread_mutex_unlock(&cub->finished_mutex);
	usleep(100);
}

void	render_thread_end_program(t_cub *cub)
{
	pthread_mutex_lock(&cub->program_ends_mutex);
	cub->program_ends = 1;
	pthread_mutex_unlock(&cub->program_ends_mutex);
}

void	*render_thread_routine(t_render_thread *attr)
{
	int		i;
	double	segments_size;

	segments_size = 2 * tan(attr->cub->fov / 2) / (attr->cub->win_size[1] - 1);
	while (1)
	{
		if (attr->cub->program_ends)
			return (NULL);
		i = get_ray_index(attr->cub);
		if (i < attr->cub->win_size[WIDTH])
		{
			if (!compute_ray(attr->cub, i, segments_size))
			{
				render_thread_end_program(attr->cub);
				continue ;
			}
			render_column(attr->cub, i);
			pthread_mutex_lock(&attr->cub->ray_mutex);
			if (attr->cub->next_ray_to_compute == attr->cub->win_size[WIDTH])
				attr->cub->is_frame_rendered = true;
			pthread_mutex_unlock(&attr->cub->ray_mutex);
		}
		else
			tell_rendering_is_finished(attr->id, attr->cub);
	}
}
