/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:04:24 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/19 08:19:19 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_cub(t_cub *cub)
{
	cub->win_size[HEIGHT] = DEFLT_WIN_SIZE;
	cub->win_size[WIDTH] = cub->win_size[HEIGHT] * 16 / 10;
	cub->rays = malloc(sizeof(t_position) * cub->win_size[WIDTH]);
	cub->angles = malloc(sizeof(double) * cub->win_size[WIDTH]);
	cub->wall_heights = malloc(sizeof(int) * cub->win_size[WIDTH]);
}

void	init_player(t_cub *cub)
{
	cub->player_position = get_position(cub->data->map);
	cub->player_position->x += 0.5;
	cub->player_position->y += 0.5;
	cub->view_angle = get_orientation(cub->data->map, cub->player_position);
	cub->fov = M_PI_2;
}
