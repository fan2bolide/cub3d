/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:28:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/27 11:29:05 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub_mlx_config(t_cub *cub);
int		cub_handle_key_press(int keycode, t_cub *cub);
int		close_window(t_cub *cub);

void	cub_update_player_position(int keycode, t_cub *cub);

void	cub_update_view_angle(int keycode, t_cub *cub);

double	get_orientation(char **map, t_position pos)
{
	char	orientation_char;
	double	orientation_angle;

	orientation_char = map[(int)pos.y][(int)pos.x];
	if (orientation_char == 'N')
		orientation_angle = 3 * M_PI_2;
	if (orientation_char == 'E')
		orientation_angle = 0;
	if (orientation_char == 'W')
		orientation_angle = M_PI;
	if (orientation_char == 'S')
		orientation_angle = M_PI_2;
	map[(int)pos.y][(int)pos.x] = '0';
	return (orientation_angle);
}

static int	cub_check_args(int argc, char **argv, t_cub *cub)
{
	if (argc == 4)
		if (ft_strequ(argv[2], "-s"))
			return (cub->win_size[0] = ft_atoi(argv[3]), 0);
	if (argc != 2)
		return (write(2, USAGE, ft_strlen(USAGE)), 1);
	return (0);
}

/**
 *
 * @param map
 * @return the position of the player at the start aof the game
 */
t_position	get_position(char **map)
{
	int			i;
	int			j;
	t_position	position;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
			{
				position.x = j;
				position.y = i;
				return (position);
			}
			j++;
		}
		i++;
	}
	position.x = -1;
	position.y = -1;
	return (position);
}

void	convert_path_to_mlx_img(t_cub *cub)
{
	int i;
	static char	*custom_path[5] = {BJ_PATH, BLUE_PATH, ORG_PATH, BLUE_TR_PATH, ORG_TR_PATH};

	i = -1;
	while (++i < 4)
	{
		cub->textures[i].img = mlx_xpm_file_to_image(cub->mlx, cub->data->texture[i], &cub->textures[i].width, &cub->textures[i].height);
		cub->textures[i].addr = mlx_get_data_addr(cub->textures[i].img, &cub->textures[i].bits_per_pixel, &cub->textures[i].line_length, &cub->textures[i].endian);
	}
	while (i < 9)
	{
		cub->textures[i].img = mlx_xpm_file_to_image(cub->mlx, custom_path[i - 4], &cub->textures[i].width,
													 &cub->textures[i].height);
		cub->textures[i].addr = mlx_get_data_addr(cub->textures[i].img, &cub->textures[i].bits_per_pixel,
												  &cub->textures[i].line_length, &cub->textures[i].endian);
		i++;
	}
}

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

void display_load_screen(t_cub *cub)
{
	int 	height;
	int		widht;
	int		x;
	int 	y;

	cub->load_screen= mlx_xpm_file_to_image(cub->mlx, LOAD_SCREEN, &widht, &height);
	x = (cub->win_size[WIDTH] / 2) - (widht / 2);
	y = (cub->win_size[HEIGHT] / 2) - (height / 2);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->load_screen,x , y);
}

t_cub	*init_game(int argc, char **argv)
{
	t_cub	*cub;

	cub = malloc(sizeof (t_cub));
	if (!cub)
		return (NULL);
	ft_bzero(cub->keys_states, 65509 * sizeof(int));
	cub->is_fullscreen = false;
	cub->win_size[0] = 900;
	cub->cross_hair = 'C';
	cub->blue_prtl = '-';
	cub->orange_prtl = '-';
	if (cub_check_args(argc, argv, cub))
		return (free(cub), NULL);
	cub->win_size[1] = cub->win_size[0] * 16 / 10;
	cub->rays = malloc(sizeof(t_position) * cub->win_size[1]);
	cub->angles = malloc(sizeof(double) * cub->win_size[1]);
	cub->wall_heights = malloc(sizeof(int) * cub->win_size[1]);
	cub->wall_distance = malloc(sizeof(double) * cub->win_size[1]);
	cub->portals = ft_calloc(cub->win_size[WIDTH], sizeof (t_prtl_list *));
	if (!cub->rays || !cub->angles || !cub->wall_heights || !cub->portals)
		return (free(cub->rays), free(cub->angles), free(cub->wall_heights), free(cub->portals), free(cub), NULL);
	cub->data = parsing(argc, argv);
	if (!cub->data)
		return (free(cub), NULL);
	cub->player_position = get_position(cub->data->map);
	cub->player_position.x += 0.5;
	cub->player_position.y += 0.5;
	cub->next_ray_to_compute = cub->win_size[WIDTH];
	pthread_mutex_init(&cub->ray_mutex, NULL);
	pthread_mutex_init(&cub->program_ends_mutex, NULL);
	return (cub);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init_game(argc, argv);
	if (!cub)
		return (ft_putstr_fd(ALLOC_ERR, 2), 1);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (ft_putstr_fd("Failed to create mlx pointer\n", 2), 1);
	cub->win = mlx_new_window(cub->mlx, cub->win_size[1], cub->win_size[0], "cub3D");
	if (!cub->win)
		return (ft_putstr_fd("failed to create window\n", 2), 1);
	convert_path_to_mlx_img(cub);
	display_load_screen(cub);
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, \
	&cub->img.line_length, &cub->img.endian);cub->view_angle = get_orientation(cub->data->map, cub->player_position);
	cub->fov = M_PI_2;
	if (!render_frame(cub))
		return (close_window(cub), 1);
	cub_mlx_config(cub);
	create_threads(cub);
	return (mlx_loop(cub->mlx), 0);
}

void	cub_update_fov(int keycode, t_cub *cub)
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

void	remove_load_screen(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->load_screen);
	cub->load_screen = NULL;
}

#if defined(__linux__)

void	cub_full_screen(t_cub *cub)
{
	cub->keys_states[KEY_F11] = RELEASED;
	if (cub->is_fullscreen == false)
	{
		cub->is_fullscreen = true;
		mlx_get_screen_size(cub->mlx, &(cub->win_size[1]), &(cub->win_size[0]));
	}
	else
	{
		cub->is_fullscreen = false;
		cub->win_size[0] = 900;
		cub->win_size[1] = cub->win_size[0] * 16 / 10;
	}
	free(cub->rays);
	free(cub->angles);
	free(cub->wall_heights);
	cub->rays = malloc(sizeof(t_position) * cub->win_size[1]);
	cub->angles = malloc(sizeof(double) * cub->win_size[1]);
	cub->wall_heights = malloc(sizeof(int) * cub->win_size[1]);
	if (!cub->rays || !cub->angles || !cub->wall_heights)
		return (close_window(cub), (void)0);
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_clear_window(cub->mlx, cub->win);
	mlx_destroy_window(cub->mlx, cub->win);
	cub->win = mlx_new_window(cub->mlx, cub->win_size[1], cub->win_size[0], "cub3D");
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, \
	&cub->img.line_length, &cub->img.endian);
	cub->view_angle = get_orientation(cub->data->map, cub->player_position);
	if (!render_frame(cub))
		return (close_window(cub), (void) 0);
	cub_mlx_config(cub);
	mlx_loop(cub->mlx);
}
#elif defined(__APPLE__)

void	cub_full_screen(t_cub *cub)
{
	(void)cub;
}
#endif

int	perform_actions(t_cub *cub)
{
	if (cub->keys_states[KEY_ESC])
		return (close_window(cub));
	if (cub->keys_states[KEY_Z])
		cub_update_fov(KEY_Z, cub);
	if (cub->keys_states[KEY_X])
		cub_update_fov(KEY_X, cub);
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
	if (cub->keys_states[KEY_F11])
		cub_full_screen(cub);
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
	return (render_frame(cub));
}

int	cub_handle_key_release(int keycode, t_cub *cub)
{
	if (keycode && keycode > 65508)
		return (1);
	cub->keys_states[keycode] = RELEASED;
	return (1);
}

int cub_handle_key_press(int keycode, t_cub *cub)
{
	if (keycode && keycode > 65508)
		return (1);
	if (cub->load_screen)
	{
		if (keycode == KEY_RETURN)
			remove_load_screen(cub);
		else if (keycode == KEY_ESC)
			return (close_window(cub));
	}
	else
	{
		if (keycode == KEY_T)
			set_portal_on_map(cub, 'B');
		else if (keycode == KEY_Y)
			set_portal_on_map(cub, 'O');
		else if (keycode == KEY_C)
			cub->cross_hair *= -1;
		else
			cub->keys_states[keycode] = PRESSED;
	}
	return (1);
}

void cub_mlx_config(t_cub *cub)
{
	mlx_hook(cub->win, KEY_PRESS, KEY_PRESS_MASK, cub_handle_key_press, cub);
	mlx_hook(cub->win, KEY_RELEASE, KEY_RELEASE_MASK, cub_handle_key_release, cub);
	mlx_hook(cub->win, DESTROY_NOTIFY, NO_EVENT_MASK, close_window, cub);
	mlx_loop_hook(cub->mlx, (int (*)())perform_actions, cub);
}

void	cub_update_view_angle(int keycode, t_cub *cub)
{
	if (keycode == KEY_LEFT)
		cub->view_angle -= 0.017;
	else
		cub->view_angle += 0.017;
	if (cub->view_angle < 0)
		cub->view_angle += (2 * M_PI);
	else if (cub->view_angle > (2 * M_PI))
		cub->view_angle -= (2 * M_PI);
}

void	report_movement(double new_y, double new_x, t_cub *cub)
{
	double	old_x;
	double	old_y;

	old_x = cub->player_position.x;
	old_y = cub->player_position.y;
	if ((int)old_x != (int)new_x)
	{
		if ((int)old_y != (int)new_y)
		{
			if (ft_isset(cub->data->map[(int) old_y][(int) new_x], "BO"))
				return;
			if (cub->data->map[(int) new_y][(int) old_x] == '1')
				return (cub->player_position.x = new_x, (void) 0);
		}
		if (ft_isset(cub->data->map[(int)new_y][(int)old_x], "BO"))
			return ;
		cub->player_position.y = new_y;
		return ;
	}
	if ((int)old_y != (int)new_y)
		if (!ft_isset(cub->data->map[(int)old_y][(int)new_x], "BO"))
			cub->player_position.x = new_x;
}

void	teleport_player(double new_x, double new_y, char prtl_id, t_cub *cub)
{
	t_position	new_pos;
	double		walk_angle;
	double		walk_angle_save;

	if ((int)new_x > (int)cub->player_position.x || (int)new_x < (int)cub->player_position.x)
		new_pos.x = (int)new_x;
	else
		new_pos.x = new_x;
	if ((int)new_y > (int)cub->player_position.y || (int)new_y < (int)cub->player_position.y)
		new_pos.y = (int)new_y;
	else
		new_pos.y = new_y;
	if (cub->keys_states[KEY_S])
		walk_angle = cub->view_angle + M_PI;
	else if (cub->keys_states[KEY_A])
		walk_angle = cub->view_angle - M_PI_2;
	else if (cub->keys_states[KEY_D])
		walk_angle = cub->view_angle + M_PI;
	else
		walk_angle = cub->view_angle;
	walk_angle_save = walk_angle;
	if(teleport_ray(cub, &new_pos, &walk_angle, prtl_id))
	{
		cub->player_position.x = new_pos.x - (0.00005 * (cos(walk_angle) < 0)) + (0.00005 * (cos(walk_angle) > 0));
		cub->player_position.y = new_pos.y - (0.00005 * (sin(walk_angle) < 0)) + (0.00005 * (sin(walk_angle) > 0));
		cub->view_angle += walk_angle - walk_angle_save;
	}
}

void	move_player(double x_change, double y_change, t_cub *cub)
{
	double	new_y;
	double	new_x;

	new_y = cub->player_position.y + y_change;
	new_x = cub->player_position.x + x_change;
	if (cub->data->map[(int)new_y][(int) cub->player_position.x] == '1' \
	&& cub->data->map[(int)cub->player_position.y][(int)new_x] == '1')
		return ;
	if (cub->data->map[(int)new_y][(int)new_x] == '1')
		return (report_movement(new_y, new_x, cub));
	else if (cub->data->map[(int)new_y][(int)new_x] == 'O')
		teleport_player(new_x, new_y, 'O', cub);
	else if (cub->data->map[(int)new_y][(int)new_x] == 'B')
		teleport_player(new_x, new_y, 'B', cub);
	else
	{
		cub->player_position.y = new_y;
		cub->player_position.x = new_x;
	}
}

void	cub_update_player_position(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		move_player(cos(cub->view_angle) / 20, sin(cub->view_angle) / 20, cub);
	if (keycode == KEY_S)
		move_player(-cos(cub->view_angle) / 20, \
		-sin(cub->view_angle) / 20, cub);
	if (keycode == KEY_A)
		move_player(cos(cub->view_angle - M_PI_2) / 20, \
		sin(cub->view_angle - M_PI_2) / 20, cub);
	if (keycode == KEY_D)
		move_player(cos(cub->view_angle + M_PI_2) / 20, \
		sin(cub->view_angle + M_PI_2) / 20, cub);
}

#if defined(__linux__)

int close_window(t_cub *cub)
{
	int	i;

	i = 0;
	while (i <= 8)
		mlx_destroy_image(cub->mlx, cub->textures[i++].img);
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	destroy_data(cub->data);
	free(cub);
	exit(0);
}
#elif defined(__APPLE__)

int	close_window(t_cub *cub)
{
	int i;

	i = 0;
	pthread_mutex_lock(&cub->program_ends_mutex);
	cub->program_ends = true;
	pthread_mutex_unlock(&cub->program_ends_mutex);
	usleep(1000);
	while (i < NB_THREADS)
		pthread_join(cub->threads[i++], NULL);
	pthread_mutex_destroy(&cub->program_ends_mutex);
	pthread_mutex_destroy(&cub->ray_mutex);
	free(cub->threads);
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	free(cub->angles);
	free(cub->rays);
	free(cub->wall_heights);
	free(cub->mlx);
	destroy_data(cub->data);
	free(cub);
	exit(0);
}
#endif
