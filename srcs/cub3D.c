/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:28:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/17 05:33:40 by bajeanno         ###   ########.fr       */
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

/**
 * \brief parses the -s option that changes the size of the window at program start
 * \param argc
 * \param argv
 * \param cub
 * \return 1 if the arguments are invalid
 */
static int	cub_check_args(int argc, char **argv, t_cub *cub)
{
	if (argc == 4)
		if (ft_strequ(argv[2], "-s"))
			return (cub->win_size[HEIGHT] = ft_atoi(argv[3]), 0);
	if (argc != 2)
		return (ft_putstr_fd(USAGE EOL, 2), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		return (ft_putstr_fd(ALLOC_ERR EOL, 2), 1);
	cub->win_size[HEIGHT] = 900;
	if (cub_check_args(argc, argv, cub))
		return (free(cub), 1);
	cub->win_size[WIDTH] = cub->win_size[0] * 16 / 10;
	cub->data = parsing(argc, argv);
	if (!cub->data)
		return (free(cub), 1);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (ft_putstr_fd("Failed to create mlx pointer\n", 2), 1);
	cub->win = mlx_new_window(cub->mlx, cub->win_size[1], cub->win_size[0],
			"cub3D");
	if (!cub->win)
		return (ft_putstr_fd("failed to create window\n", 2), 1);
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, \
	&cub->img.line_length, &cub->img.endian);
	cub_mlx_config(cub);
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
