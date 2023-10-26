/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:28:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/26 19:32:41 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_file *test_parsing();

void cub_mlx_config(t_cub *cub);

int	cub_handle_key_press(int keycode, t_cub *cub);

int	close_window(t_cub *cub);

int cub_render(t_cub *cub);

static int	cub_check_args(int argc, char **argv, t_cub *cub)
{
	if (argc == 4)
		if (ft_strequ(argv[2], "-s"))
			return (cub->win_size[0] = ft_atoi(argv[3]), 0);
	if (argc != 2)
		return (write(2, USAGE, ft_strlen(USAGE)), 1);
	return (0);
}

int	main(int argc, char **argv)
{
//	if (parsing(argc, argv))
//		return (1);
	t_cub *cub;

	cub = malloc(sizeof (t_cub));
	cub->win_size[0] = 1080;
	if (cub_check_args(argc, argv, cub))
		return (free(cub), 1);
	cub->win_size[1] = cub->win_size[0] * 16 / 10;
	cub->file = test_parsing();
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->win_size[1], cub->win_size[0], "cub3D");
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
	ray_casting(cub);
	cub_mlx_config(cub);
	return (mlx_loop(cub->mlx), 0);
}

void cub_mlx_config(t_cub *cub) {
	mlx_hook(cub->win, 2, 0, cub_handle_key_press, cub);
	mlx_hook(cub->win, 17, 0, close_window, cub);
}

int cub_handle_key_press(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		return (close_window(cub));
//	else if (keycode == KEY_W || keycode == KEY_A
//			 || keycode == KEY_S || keycode == KEY_D)
//		cub_update_shift(keycode, cub);
	else
		return (1);
	return (cub_render(cub));
}

int cub_render(t_cub *cub)
{
	ray_casting(cub);
	return 0;
}

int close_window(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	exit(0);
}

t_file *test_parsing()
{
	t_file *test;
	test = malloc(sizeof(t_file));
	test->floor_color = malloc(sizeof(t_color));
	test->ceiling_color = malloc(sizeof(t_color));
	test->s_texture = ft_strdup("./textures/test_texture1");
	test->n_texture = ft_strdup("./textures/test_texture2");
	test->e_texture = ft_strdup("./textures/test_texture3");
	test->w_texture = ft_strdup("./textures/test_texture4");
	test->map = malloc(sizeof(char *) * 6);
	test->map[0] = ft_strdup("1111111111");
	test->map[1] = ft_strdup("1000000001");
	test->map[2] = ft_strdup("1000000001");
	test->map[3] = ft_strdup("1000000N01");
	test->map[4] = ft_strdup("1111111111");
	test->map[5] = NULL;
	return (test);
}
