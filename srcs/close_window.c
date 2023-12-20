/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:39:48 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/20 10:49:30 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#if defined(__linux__)

int	close_window(t_cub *cub)
{
	int	i;

	if (cub)
	{
		i = 0;
		while (i <= 4)
			if (cub->textures[i++].img)
				mlx_destroy_image(cub->mlx, cub->textures[i - 1].img);
		if (cub->img.img)
			mlx_destroy_image(cub->mlx, cub->img.img);
		if (cub->win)
			mlx_destroy_window(cub->mlx, cub->win);
		if (cub->mlx)
			mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		destroy_data(cub->data);
		free(cub->player_position);
		free(cub->rays);
		free(cub->angles);
		free(cub->wall_heights);
		free(cub);
	}
	exit(0);
}
#elif defined(__APPLE__)

int	close_window(t_cub *cub)
{
	int	i;

	i = 0;
	if (!cub)
		exit(3);
	while (i <= 4)
		if (cub->textures[i++].img)
			mlx_destroy_image(cub->mlx, cub->textures[i - 1].img);
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	free(cub->angles);
	free(cub->rays);
	free(cub->wall_heights);
	free(cub->mlx);
	destroy_data(cub->data);
	free(cub->player_position);
	free(cub);
	exit(0);
}
#endif
