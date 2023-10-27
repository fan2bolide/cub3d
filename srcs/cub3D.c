/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:28:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/27 14:37:55 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_file	*test_parsing();
void	cub_mlx_config(t_cub *cub);
int		cub_handle_key_press(int keycode, t_cub *cub);
int		close_window(t_cub *cub);
int		cub_render_frame(t_cub *cub);

void cub_update_player_position(int keycode, t_cub *cub);

void cub_update_view_angle(int keycode, t_cub *cub);

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
	t_cub *cub;

	cub = malloc(sizeof (t_cub));
	cub->win_size[0] = 900;
	if (cub_check_args(argc, argv, cub))
		return (free(cub), 1);
	cub->win_size[1] = cub->win_size[0] * 16 / 10;
	cub->file = test_parsing(); //todo add real parsing here
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->win_size[1], cub->win_size[0], "cub3D");
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
	ray_casting(cub);
	cub_mlx_config(cub);
	return (mlx_loop(cub->mlx), 0);
}

void cub_mlx_config(t_cub *cub)
{
	mlx_hook(cub->win, 2, 0, cub_handle_key_press, cub);
	mlx_hook(cub->win, 17, 0, close_window, cub);
}

int cub_handle_key_press(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		return (close_window(cub));
	else if (keycode == KEY_W || keycode == KEY_A
			 || keycode == KEY_S || keycode == KEY_D)
		cub_update_player_position(keycode, cub);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		cub_update_view_angle(keycode, cub);
	else
		return (1);
	return (cub_render_frame(cub));
}

void cub_update_view_angle(int keycode, t_cub *cub)
{
	if (keycode == KEY_RIGHT)
		cub->view_angle -= 0.005;
	else
		cub->view_angle += 0.005;
	if (cub->view_angle < 0)
		cub->view_angle += (2 * M_PI);
	else if (cub->view_angle > (2 * M_PI))
		cub->view_angle -= (2 * M_PI);
}

void cub_update_player_position(int keycode, t_cub *cub)
{
	//todo redo that shit with trigonometry
}

int cub_render_frame(t_cub *cub)
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
	test->map[3] = ft_strdup("10000N0001");
	test->map[4] = ft_strdup("1111111111");
	test->map[5] = NULL;
	return (test);
}
