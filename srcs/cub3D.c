/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:28:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/14 14:45:57 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//todo see if it can't be replaced with time.c functions
size_t	get_time(void)
{
	struct timeval	time;
	size_t			seconds;
	size_t			u_seconds;
	size_t			m_seconds;

	gettimeofday(&time, NULL);
	seconds = time.tv_sec;
	u_seconds = time.tv_usec;
	m_seconds = u_seconds / 1000;
	m_seconds += seconds * 1000;
	return (m_seconds);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init_game(argc, argv);
	if (!cub)
		return (1);
	cub->last_mouse_pos = -1;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (ft_putstr_fd("Failed to create mlx pointer\n", 2), 1);
	cub->win = mlx_new_window(cub->mlx, cub->win_size[1], cub->win_size[0],
			"cub3D");
	if (!cub->win)
		return (ft_putstr_fd("failed to create window\n", 2), 1);
	convert_path_to_mlx_img(cub);
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, \
	&cub->img.line_length, &cub->img.endian);
	cub->view_angle = get_orientation(cub->data->map, cub->player_position);
	display_load_screen(cub);
	load_game_menu(cub);
	if (!init_doors(cub))
		return (close_window(cub));
	cub->fov = M_PI_2;
	cub->player_speed = 20;
	cub->sensivity = 0.017;
	if (!render_frame(cub))
		return (close_window(cub), 1);
	cub_mlx_config(cub);
	create_threads(cub);
	return (mlx_loop(cub->mlx), 0);
}

int	perform_actions(t_cub *cub)
{
	int	x;
	int	y;

	mouse_get_pos(cub, &x, &y);
	if (cub->menu.cursors[SPEED].is_pressed)
	{
		if (x < 862)
			x = 862;
		if (x > 1200)
			x = 1200;
		cub->menu.cursors[SPEED].x = x;
		cub->player_speed = 20 + (((int)cub->menu.cursors[SPEED].initial_pos.x
					- (int)cub->menu.cursors[SPEED].x) / 10);
	}
	if (cub->menu.cursors[SENSI].is_pressed)
	{
		if (x < 862)
			x = 862;
		if (x > 1200)
			x = 1200;
		cub->menu.cursors[SENSI].x = x;
		cub->sensivity = 0.017 + (double)((int)cub->menu.cursors[SENSI].x - (int)cub->menu.cursors[SENSI].initial_pos.x) / 10000;
	}
	if (cub->menu.reseters[SPEED].is_pressed)
	{
		cub->player_speed = 20;
		cub->menu.cursors[SPEED].x = (int) cub->menu.cursors[SPEED].initial_pos.x;
	}
	if (cub->menu.reseters[SENSI].is_pressed)
	{
		cub->sensivity = 0.017;
		cub->menu.cursors[SENSI].x = (int) cub->menu.cursors[SENSI].initial_pos.x;
	}
	cub_update_doors(cub);
	if ((cub->menu.cross_hair == 2 && cub->cross_hair > 0) || (cub->menu.cross_hair == 1 && cub->cross_hair < 0))
		cub->cross_hair *= -1;
	if (cub->keys_states[KEY_ESC])
		return (close_window(cub));
	if (cub->keys_states[KEY_W])
		cub_update_player_position(KEY_W, cub);
	if (cub->keys_states[KEY_A])
		cub_update_player_position(KEY_A, cub);
	if (cub->keys_states[KEY_S])
		cub_update_player_position(KEY_S, cub);
	if (cub->keys_states[KEY_D])
		cub_update_player_position(KEY_D, cub);
	if (cub->keys_states[KEY_F])
		cub->fov = M_PI_2;
	if (cub->keys_states[KEY_LEFT])
		cub_update_view_angle(KEY_LEFT, cub);
	if (cub->keys_states[KEY_RIGHT])
		cub_update_view_angle(KEY_RIGHT, cub);
	if (cub->keys_states[KEY_V] && cub->data->baj->speed < 3000)
		cub->data->baj->speed += 5;
	if (cub->keys_states[KEY_N] && cub->data->baj->speed > 100)
		cub->data->baj->speed -= 5;
	if (cub->keys_states[KEY_B] && get_time() - cub->data->baj->last_activation > 500)
	{
		cub->data->baj->last_activation = get_time();
		if (cub->data->baj->is_activated)
			cub->data->baj->is_activated = 0;
		else
		{
			get_next_baj(cub->data->wall_sur, cub->data->baj, cub->data->baj->cur_pos);
			cub->data->baj->is_activated = 1;
		}
	}
	clear_lists(cub);
	return (render_frame(cub));
}
