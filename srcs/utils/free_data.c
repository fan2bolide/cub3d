/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:41:23 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/25 15:18:37 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->s_texture)
			free(data->s_texture);
		if (data->n_texture)
			free(data->n_texture);
		if (data->e_texture)
			free(data->e_texture);
		if (data->w_texture)
			free(data->w_texture);
		if (data->ceiling_color)
			free(data->ceiling_color);
		if (data->floor_color)
			free(data->floor_color);
		free(data);
	}
}
