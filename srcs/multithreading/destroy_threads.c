/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:19:40 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/20 11:07:13 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_threads(t_cub *cub)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&cub->program_ends_mutex);
	cub->program_ends = true;
	pthread_mutex_unlock(&cub->program_ends_mutex);
	while (cub->threads && i < NB_THREADS)
		if (cub->threads[i])
			pthread_join(cub->threads[i++], NULL);
	if (&cub->finished_mutex)
	pthread_mutex_destroy(&cub->finished_mutex);
	if (&cub->program_ends_mutex)
	pthread_mutex_destroy(&cub->program_ends_mutex);
	if (&cub->ray_mutex)
	pthread_mutex_destroy(&cub->ray_mutex);
}
