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

void	*render_thread_routine(t_render_thread *attr);

void	delete_threads(t_cub *cub, int last_thread)
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
	int				i;
	static t_render_thread	render_thread[NB_THREADS];

	i = 0;
	cub->threads = malloc(sizeof(pthread_t) * NB_THREADS);
	while (i < NB_THREADS)
	{
		render_thread[i].cub = cub;
		render_thread[i].id = i;
		if (pthread_create(cub->threads + i, NULL, \
		(void *(*)(void *))render_thread_routine, &render_thread[i]))
			return (delete_threads(cub, i), 0);
		i++;
	}
	return (1);
}
