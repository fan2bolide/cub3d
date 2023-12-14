/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:48:23 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/14 14:56:56 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	convert_path_to_mlx_img(t_cub *cub)
{
	int i;
	static char	*custom_path[13] = {BJ_PATH, BLUE_PATH, ORG_PATH, BLUE_TR_PATH, ORG_TR_PATH, BLUE_OUT_P, OR_OUT_P, DOOR, DOOR_HINT, PORTAL_GUN_B, PORTAL_GUN_O, RICKS_GUN, MC_GLASS};

	i = -1;
	while (++i < 4)
	{
		cub->textures[i].img = mlx_xpm_file_to_image(cub->mlx, cub->data->texture[i], &cub->textures[i].width, &cub->textures[i].height);
		cub->textures[i].addr = mlx_get_data_addr(cub->textures[i].img, &cub->textures[i].bits_per_pixel, &cub->textures[i].line_length, &cub->textures[i].endian);
	}
	while (i < 17)
	{
		//todo secure those paths
		cub->textures[i].img = mlx_xpm_file_to_image(cub->mlx, custom_path[i - 4], &cub->textures[i].width,
													 &cub->textures[i].height);
		cub->textures[i].addr = mlx_get_data_addr(cub->textures[i].img, &cub->textures[i].bits_per_pixel,
												  &cub->textures[i].line_length, &cub->textures[i].endian);
		i++;
	}
}
