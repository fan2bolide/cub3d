/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:40:40 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/15 00:25:07 by nfaust           ###   ########.fr       */
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

int	init_mutex(t_cub *cub)
{
	if (pthread_mutex_init(&cub->finished_mutex, NULL) != 0)
		return (ft_putstr_fd(ERR MUTEX_INIT EOL, 2), 0);
	if (pthread_mutex_init(&cub->program_ends_mutex, NULL) != 0)
	{
		ft_putstr_fd(ERR MUTEX_INIT EOL, 2);
		return (pthread_mutex_destroy(&cub->finished_mutex), 0);
	}
	if (pthread_mutex_init(&cub->ray_mutex, NULL) != 0)
	{
		ft_putstr_fd(ERR MUTEX_INIT EOL, 2);
		pthread_mutex_destroy(&cub->finished_mutex);
		pthread_mutex_destroy(&cub->program_ends_mutex);
		return (0);
	}
	return (1);
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
		(void *)render_thread_routine, &render_thread[i]))
			return (delete_threads(cub, i), 0);
		i++;
	}
	return (1);
}
