/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:41:23 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/26 10:58:58 by nfaust           ###   ########.fr       */
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
		free(data->map);
		free(data);
	}
}
