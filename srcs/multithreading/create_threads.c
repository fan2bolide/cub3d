/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:40:40 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/28 15:37:35 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*render_thread_routine(void *attr);

void delete_threads(t_cub *cub, int last_thread)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&cub->program_ends_mutex);
	cub->program_ends = 1;
	pthread_mutex_unlock(&cub->program_ends_mutex);
	while (i < last_thread)
		pthread_join(cub->threads[i++], NULL);
}

int	create_threads(t_cub *cub)
{
	int	i;

	i = 0;
	cub->threads = malloc(sizeof(pthread_t) * NB_THREADS);
	t_render_thread renderThread[NB_THREADS];
	while (i < NB_THREADS)
	{
		renderThread[i].cub = cub;
		renderThread[i].id = i;
		if (pthread_create(cub->threads + i, NULL, render_thread_routine, &renderThread[i]))
			return (delete_threads(cub, i), 0);
		i++;
	}
	return (1);
}
