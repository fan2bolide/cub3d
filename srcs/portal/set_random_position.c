/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_random_position.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:34:25 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/18 15:30:17 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_in_map(const t_cub *cub, const int x, const int y)
{
	int	i;
	int	j;

	i = 0;
	while (cub->data->map[i] && i <= y)
	{
		j = 0;
		while (cub->data->map[i][j] && j <= x)
		{
			if (i == y && j == x && cub->data->map[i][j] == '0')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

static unsigned int	get_map_height(const t_cub *cub)
{
	unsigned int	i;

	i = 0;
	while (cub->data->map[i])
		i++;
	return (i);
}

static unsigned int	get_map_width(const t_cub *cub)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	max;

	i = 0;
	max = 0;
	while (cub->data->map[i])
	{
		j = 0;
		while (cub->data->map[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

void	set_random_position(t_cub *cub)
{
	struct timeval	time;

	cub->random_position.y = 0;
	cub->random_position.x = 0;
	while (1)
	{
		gettimeofday(&time, NULL);
		srand(time.tv_usec % 1024);
		cub->random_position.y = rand() % get_map_height(cub) + 0.5;
		srand(time.tv_usec % 256);
		cub->random_position.x = rand() % get_map_width(cub) + 0.5;
		if (is_in_map(cub, (int)cub->random_position.x, \
							(int)cub->random_position.y))
			return (gettimeofday(&time, NULL), srand(time.tv_usec), \
				cub->random_angle = rand() % 300, (void)0);
	}
}
