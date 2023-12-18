/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:04:24 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/18 19:04:24 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_cub(t_cub *cub)
{
	cub->win_size[0] = 900;
	cub->win_size[1] = cub->win_size[0] * 16 / 10;
	cub->rays = malloc(sizeof(t_position) * cub->win_size[1]);
	cub->angles = malloc(sizeof(double) * cub->win_size[1]);
	cub->wall_heights = malloc(sizeof(int) * cub->win_size[1]);
}