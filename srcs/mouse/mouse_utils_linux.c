/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils_linux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:14:00 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/18 08:39:08 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#ifdef LINUX

void	mouse_get_pos(t_cub *cub, int *x, int *y)
{
	mlx_mouse_get_pos(cub->mlx, cub->win, x, y);
}

void	cub_mouse_move(t_cub *cub, int x, int y)
{
	mlx_mouse_move(cub->mlx, cub->win, x, y);
}

void	cub_mouse_show(t_cub *cub)
{
	mlx_mouse_show(cub->mlx, cub->win);
}

void	cub_mouse_hide(t_cub *cub)
{
	(void) cub;
	//mlx_mouse_hide(cub->mlx, cub->win);
}

#endif
