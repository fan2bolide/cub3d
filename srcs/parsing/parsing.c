/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:38:22 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/25 11:09:48 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsing(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (printf(ERR WRONG_ARG_N), 1);
	data = get_data(argv);
	free(data->floor_color);
	free(data->ceiling_color);
	free(data->n_texture);
	free(data->s_texture);
	free(data->e_texture);
	free(data->w_texture);
	free(data);
	return (0);
}
