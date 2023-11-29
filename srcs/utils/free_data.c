/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:15:18 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/29 11:14:56 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_data(t_data *data)
{
	int	i;

	if (data)
	{
		i = 0;
		while (i < 4)
			free(data->texture[i++]);
		free(data->ceiling_color);
		free(data->floor_color);
		if (data->map)
			ft_old_split_destroy(data->map);
		if (data->wall_sur)
			ft_old_split_destroy(data->wall_sur);
		if (data->baj)
			free(data->baj->cur_pos);
		free(data->baj);
		free(data);
	}
}
