/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:25:56 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/29 11:38:06 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	get_tile_type(t_position pos, double angle, t_cub *cub)
{
	double	x;
	double	y;

	x = pos.x;
	y = pos.y;
	if (pos.x == (int)pos.x)
	{
		if (cos(angle) < 0)
			return (cub->data->map[(int)y][(int)x - 1]);
		else
			return (cub->data->map[(int)y][(int)x]);
	}
	if (sin(angle) < 0)
		return (cub->data->map[(int)y - 1][(int)x]);
	return (cub->data->map[(int)y][(int)x]);
}

void	open_door(t_cub *cub)
{
	if (get_tile_type(cub->rays[cub->win_size[WIDTH] / 2], cub->angles[cub->win_size[WIDTH] / 2], cub) != 'D')
		return ;
	printf("porte trouvee\n");
}
