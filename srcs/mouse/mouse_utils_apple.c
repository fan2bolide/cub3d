/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:12:18 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/12 20:12:19 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#if defined (__APPLE__)

void	mouse_get_pos(t_cub *cub, int *x, int *y)
{
	mlx_mouse_get_pos(cub->win, x, y);
}

void	cub_mouse_move(t_cub *cub, int x, int y)
{
	mlx_mouse_move(cub->win, x, y);
}

void	cub_mouse_show(t_cub *cub)
{
	(void)cub;
	mlx_mouse_show();
}

void	cub_mouse_hide(t_cub *cub)
{
	(void)cub;
	mlx_mouse_hide();
}

#endif