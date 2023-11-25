/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:40:40 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/25 02:35:30 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*routine(void *attr)
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
		}
		else
			usleep(100);
	}
}

int	create_threads(t_cub *cub)
{
	pthread_t	threads[NB_THREADS];
	int			i;

	i = 0;
	while (i < NB_THREADS)
	{
		pthread_create(threads + i, NULL, routine, cub);
		i++;
	}
	return (0);
}
