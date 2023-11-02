/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:28:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/02 01:57:59 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double get_orientation(char **map, t_position *pos);
t_data	*test_parsing();
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
	cub->data = parsing(argc, argv);
	if (!cub->data)
		return (1);
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->win_size[1], cub->win_size[0], "cub3D");
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
	cub->view_angle = get_orientation(cub->data->map, cub->player_position);
	if (!ray_casting(cub))
		return (close_window(cub), 1);
	printf("lalalal\n");
	cub_mlx_config(cub);
	return (mlx_loop(cub->mlx), 0);
}

void cub_mlx_config(t_cub *cub)
{
	printf("dwodjweoijdoiwejdijwed\n");
	mlx_key_hook(cub->win, cub_handle_key_press, cub);
	mlx_hook(cub->win, 17, 0, close_window, cub);
}

int cub_handle_key_press(int keycode, t_cub *cub)
{
	printf("%i\n", keycode);
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
	if (keycode == KEY_LEFT)
		cub->view_angle -= 0.05;
	else
		cub->view_angle += 0.05;
	if (cub->view_angle < 0)
		cub->view_angle += (2 * M_PI);
	else if (cub->view_angle > (2 * M_PI))
		cub->view_angle -= (2 * M_PI);
}

void cub_update_player_position(int keycode, t_cub *cub)
{
	(void)keycode;
	(void)cub;
	//todo redo that shit with trigonometry
}

int cub_render_frame(t_cub *cub)
{
	ray_casting(cub);
	return (0);
}

int close_window(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	exit(0);
}
