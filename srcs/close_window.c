/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:03:52 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/20 11:08:09 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	destroy_menu_images(t_cub *cub)
{
	t_image	*menu_images[6];
	int		i;

	ft_memcpy(menu_images, (t_image *[6]){cub->menu.button_shadow.img,
		cub->menu.button.img, cub->menu.checker_plain.img, cub->menu.cursor.img,
		cub->menu.menu_bg.img, cub->menu.reset.img}, sizeof(t_image *) * 6);
	i = 0;
	while (i < 6)
		if (menu_images[i++])
			mlx_destroy_image(cub->mlx, menu_images[i - 1]);
}

static void	cub_destroy_images(t_cub *cub)
{
	int	i;

	i = 0;
	while (i <= 17)
		if (cub->textures[i++].img)
			mlx_destroy_image(cub->mlx, cub->textures[i - 1].img);
	destroy_menu_images(cub);
	if (cub->load_screen.img)
		mlx_destroy_image(cub->mlx, cub->load_screen.img);
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
}

static void	free_cub(t_cub *cub)
{
	destroy_data(cub->data);
	clear_lists(cub);
	free(cub->threads);
	free(cub->mlx);
	free(cub->portals);
	free(cub->doors);
	free(cub->doors_status);
	free(cub->glass);
	free(cub->rays);
	free(cub->angles);
	free(cub->wall_heights);
	free(cub->wall_distance);
	free(cub);
}

#if defined(__linux__)

int	close_window(t_cub *cub)
{
	destroy_threads(cub);
	mlx_loop_end(cub->mlx);
	cub_destroy_images(cub);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free_cub(cub);
	exit(0);
}
#elif defined(__APPLE__)

int	close_window(t_cub *cub)
{
	destroy_threads(cub);
	cub_destroy_images(cub);
	mlx_destroy_window(cub->mlx, cub->win);
	free_cub(cub);
	exit(0);
}
#endif
