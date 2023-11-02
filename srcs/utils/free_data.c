/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:15:18 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/02 06:08:19 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_data(t_data *data)
{
	if (data)
	{
		free(data->s_texture);
		free(data->n_texture);
		free(data->e_texture);
		free(data->w_texture);
		free(data->ceiling_color);
		free(data->floor_color);
		if (data->map)
			ft_old_split_destroy(data->map);
		free(data);
	}
}
