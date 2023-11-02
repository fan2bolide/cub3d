/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:28:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/02 17:54:06 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double get_orientation(char **map, t_position *pos);
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

t_position *create_position(double i, double j)
{
	t_position *pos;

	pos = malloc(sizeof(t_position));
	pos->x = j;
	pos->y = i;
	return (pos);
}

t_position *get_position(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
				return (create_position((double)i, (double)j));
			j++;
		}
		i++;
	}
	return (NULL);
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
	cub->player_position = get_position(cub->data->map);
	cub->player_position->x += 0.5;
	cub->player_position->y += 0.5;
	printf("%.2f %.2f\n", cub->player_position->x, cub->player_position->y);
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->win_size[1], cub->win_size[0], "cub3D");
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
	cub->view_angle = get_orientation(cub->data->map, cub->player_position);
	cub->fov = M_PI_2;
	if (!ray_casting(cub))
		return (close_window(cub), 1);
	cub_mlx_config(cub);
	return (mlx_loop(cub->mlx), 0);
}

void cub_mlx_config(t_cub *cub)
{
	mlx_hook(cub->win, KEY_PRESS, KEY_PRESS_MASK, cub_handle_key_press, cub);
	mlx_hook(cub->win, DESTROY_NOTIFY, NO_EVENT_MASK, close_window, cub);
}

void cub_update_fov(int keycode, t_cub *cub)
{
	if (keycode == KEY_Z)
		cub->fov -= 0.05;
	else
		cub->fov += 0.05;
	if (cub->fov > M_PI)
		cub->fov = M_PI;
	if (cub->fov < M_PI_4)
		cub->fov = M_PI_4;
}

int cub_handle_key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_ESC)
		return (close_window(cub));
	else if (keycode == KEY_Z || keycode == KEY_X)
		cub_update_fov(keycode, cub);
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
	if (keycode == KEY_W)
	{
		cub->player_position->x += cos(cub->view_angle) / 10;
		cub->player_position->y += sin(cub->view_angle) / 10;
	}
	if (keycode == KEY_S)
	{
		cub->player_position->x -= cos(cub->view_angle) / 10;
		cub->player_position->y -= sin(cub->view_angle) / 10;
	}
	if (keycode == KEY_A)
	{
		cub->player_position->x += cos(cub->view_angle - M_PI_2) / 10;
		cub->player_position->y += sin(cub->view_angle - M_PI_2) / 10;
	}
	if (keycode == KEY_D)
	{
		cub->player_position->x += cos(cub->view_angle + M_PI_2) / 10;
		cub->player_position->y += sin(cub->view_angle + M_PI_2) / 10;
	}
	if (cub->data->map[(int)cub->player_position->y][(int)cub->player_position->x] == '1')
	{
		if (keycode == KEY_W)
			cub_update_player_position(KEY_S, cub);
		if (keycode == KEY_A)
			cub_update_player_position(KEY_D, cub);
		if (keycode == KEY_D)
			cub_update_player_position(KEY_A, cub);
		if (keycode == KEY_S)
			cub_update_player_position(KEY_W, cub);
	}
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
