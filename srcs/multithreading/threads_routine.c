/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:36:26 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/27 09:37:36 by bajeanno         ###   ########.fr       */
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

	cub = attr;
	segments_size = 2 * tan(cub->fov / 2) / (cub->win_size[1] - 1);
	while (1)
	{
		if (cub->program_ends)
			return (NULL);
		i = get_ray_index(cub);
		if (i < cub->win_size[WIDTH])
		{
			ft_lstclear((t_list **)&cub->portals[i], free);
			cub->portals[i] = NULL;
			if (!compute_ray(cub, i, segments_size))
			{
				pthread_mutex_lock(&cub->program_ends_mutex);
				cub->program_ends = 1;
				pthread_mutex_unlock(&cub->program_ends_mutex);
				continue ;
			}
			render_column(cub, i);
			if (i == cub->win_size[WIDTH] - 1)
			{
				pthread_mutex_lock(&cub->ray_mutex);
				cub->is_frame_rendered = true;
				pthread_mutex_unlock(&cub->ray_mutex);
			}
		}
		else
			usleep(100);
	}
}
