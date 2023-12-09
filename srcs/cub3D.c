/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:28:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/09 21:32:32 by nfaust           ###   ########.fr       */
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
		return (ft_putstr_fd(USAGE EOL, 2), 1);
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
	static char	*custom_path[12] = {BJ_PATH, BLUE_PATH, ORG_PATH, BLUE_TR_PATH, ORG_TR_PATH, BLUE_OUT_P, OR_OUT_P, DOOR, DOOR_HINT, PORTAL_GUN, MC_GLASS, RICKS_GUN};

	i = -1;
	while (++i < 4)
	{
		cub->textures[i].img = mlx_xpm_file_to_image(cub->mlx, cub->data->texture[i], &cub->textures[i].width, &cub->textures[i].height);
		cub->textures[i].addr = mlx_get_data_addr(cub->textures[i].img, &cub->textures[i].bits_per_pixel, &cub->textures[i].line_length, &cub->textures[i].endian);
	}
	while (i < 15)
	{
		//todo secure those paths
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

void	display_background(t_cub *cub, int start_x, int start_y)
{
	int x;
	int	y;

	x = 0;
	while (x < cub->win_size[WIDTH])
	{
		y = 0;
		while (y < cub->win_size[HEIGHT])
		{
			if (y < start_y || y > start_y + cub->load_screen.height || x < start_x || x > start_x + cub->load_screen.width)
				cub_pixel_put(&cub->img, x, y, 0x2089ef);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}

void display_load_screen(t_cub *cub)
{
	int 	height;
	int		width;
	int		x;
	int 	y;

	cub->load_screen.img = mlx_xpm_file_to_image(cub->mlx, LOAD_SCREEN, &width, &height);
	mlx_get_data_addr(cub->load_screen.img, &cub->load_screen.bits_per_pixel, &cub->load_screen.line_length, &cub->load_screen.endian);
	x = (cub->win_size[WIDTH] / 2) - (width / 2);
	y = (cub->win_size[HEIGHT] / 2) - (height / 2);
	display_background(cub, x, y);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->load_screen.img, x, y);
}

t_iposition get_gun_position(t_cub *cub)
{
	t_iposition result;

	result.x = 45 * cub->win_size[WIDTH] / 100;
	result.y = 45 * cub->win_size[HEIGHT] / 100;
	return result;
}

t_cub	*init_game(int argc, char **argv)
{
	t_cub	*cub;

	cub = ft_calloc(1, sizeof (t_cub));
	if (!cub)
		return (ft_putstr_fd(ALLOC_ERR EOL, 2), NULL);
	cub->data = parsing(argc, argv);
	if (!cub->data || cub_check_args(argc, argv, cub))
		return (free(cub), NULL);
	ft_bzero(cub->keys_states, 65509 * sizeof(int));
	cub->is_fullscreen = false;
	cub->last_frame_time = get_time();
	cub->win_size[0] = 900;
	cub->cross_hair = 'C';
	cub->blue_prtl = '-';
	cub->orange_prtl = '-';
	cub->win_size[1] = cub->win_size[0] * 16 / 10;
	cub->rays = malloc(sizeof(t_position) * cub->win_size[1]);
	cub->angles = malloc(sizeof(double) * cub->win_size[1]);
	cub->wall_heights = malloc(sizeof(int) * cub->win_size[1]);
	cub->wall_distance = malloc(sizeof(double) * cub->win_size[1]);
	cub->portals = ft_calloc(cub->win_size[WIDTH], sizeof (t_prtl_list *));
	cub->doors = ft_calloc(cub->win_size[WIDTH], sizeof(t_prtl_list *));
	cub->glass = ft_calloc(cub->win_size[WIDTH], sizeof(t_prtl_list *));
	if (!cub->rays || !cub->angles || !cub->wall_heights)
		return (free(cub->rays), free(cub->angles), free(cub->wall_heights), NULL);
	cub->player_position = get_position(cub->data->map);
	cub->player_position.x += 0.5;
	cub->player_position.y += 0.5;
	cub->gun_position = get_gun_position(cub);
	cub->next_ray_to_compute = cub->win_size[WIDTH];
	pthread_mutex_init(&cub->ray_mutex, NULL);
	pthread_mutex_init(&cub->program_ends_mutex, NULL);
	pthread_mutex_init(&cub->finished_mutex, NULL);
	return (cub);
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
	cub->win = mlx_new_window(cub->mlx, cub->win_size[1], cub->win_size[0], "cub3D");
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
	mlx_destroy_image(cub->mlx, cub->load_screen.img);
	cub->load_screen.img = NULL;
	cub->menu.on_screen = false;
	cub_mouse_hide(cub);
}

void	cub_update_doors(t_cub *cub)
{
	size_t	i;

	i = 0;
	while (cub->doors_status[i].x)
	{
		if (cub->doors_status[i].opening_percent > 0 && cub->doors_status[i].opening_percent < 1)
		{
			if (cub->doors_status[i].is_open)
				cub->doors_status[i].opening_percent -= 0.05;
			else
				cub->doors_status[i].opening_percent += 0.05;
			if (cub->doors_status[i].opening_percent < 0)
				cub->doors_status[i].opening_percent = 0;
			else if (cub->doors_status[i].opening_percent > 1)
				cub->doors_status[i].opening_percent = 1;
			if (cub->doors_status[i].opening_percent == 1)
				cub->doors_status[i].is_open = true;
			else if (cub->doors_status[i].opening_percent == 0)
				cub->doors_status[i].is_open = false;
		}
		i++;
	}
}

void	display_door_hint(t_cub *cub, int texture_y, int display_y)
{
	int	display_x;
	int	texture_x;
	int	color;
	int max_x;

	max_x = cub->textures[12].width + cub->door_hint.x;
	while (display_y > 0 && display_y > cub->door_hint.y)
	{
		display_x = cub->door_hint.x;
		texture_x = 0;
		while (display_x < max_x && display_x < cub->win_size[WIDTH])
		{
			color = *((int *)(cub->textures[12].addr + (texture_y * \
					cub->textures[12].line_length + texture_x * \
					(cub->textures[12].bits_per_pixel / 8))));
			if (color > 0)
				cub_pixel_put(&cub->img, display_x, display_y, color);
			display_x++;
			texture_x++;
		}
		display_y--;
		texture_y--;
	}
}

void	cub_display_door_hint(t_cub *cub)
{
	t_prtl_list	*door;
	int 		dir;
	int 		texture_y;
	int 		display_y;

	door = cub->doors[cub->win_size[WIDTH] / 2];
	if (door && cub->menu.x == -cub->menu.menu_bg.width)
	{
		while (door->next && get_door(door->portal->position, door->portal->angle, cub)->is_open)
			door = door->next;
		dir = (door->portal->distance > DOOR_MAX_OPENING) * -1 + (door->portal->distance <= DOOR_MAX_OPENING);
		if (dir < 0 && cub->door_hint.y == cub->textures[12].height * -1)
			return ;
	}
	else
		dir = -1;
	texture_y = cub->textures[12].height;
	display_y = cub->door_hint.y + cub->textures[12].height;
	display_door_hint(cub, texture_y, display_y);
	cub->door_hint.y += dir * 2;
	if (cub->door_hint.y > 15)
		cub->door_hint.y = 15;
	if (cub->door_hint.y < -cub->textures[12].height)
		cub->door_hint.y = -cub->textures[12].height;
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
		cub->player_speed = 20 + (((int)cub->menu.cursors[SPEED].initial_pos.x - (int)cub->menu.cursors[SPEED].x) / 10);
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
	if (cub->load_screen.img)
	{
		if (keycode == KEY_RETURN)
			remove_load_screen(cub);
	}
	else if (!cub->menu.on_screen || keycode == KEY_TAB)
	{
		if (keycode == KEY_T)
			set_portal_on_map(cub, 'B');
		else if (keycode == KEY_Y)
			set_portal_on_map(cub, 'O');
		else if (keycode == KEY_E)
			open_door(cub);
		else if (keycode == KEY_TAB)
			handle_menu(cub);
		else
			cub->keys_states[keycode] = PRESSED;
	}
	if (keycode == KEY_ESC)
		return (close_window(cub));
	return (1);
}

int cub_handle_mouse_release(int button, int x, int y, t_cub *cub)
{
	(void)button;
	(void)x;
	(void)y;
	if (cub->menu.cursors[SPEED].is_pressed)
		cub->menu.cursors[SPEED].is_pressed = false;
	if (cub->menu.cursors[SENSI].is_pressed)
		cub->menu.cursors[SENSI].is_pressed = false;
	if (cub->menu.reseters[SPEED].is_pressed)
		cub->menu.reseters[SPEED].is_pressed = false;
	if (cub->menu.reseters[SENSI].is_pressed)
		cub->menu.reseters[SENSI].is_pressed = false;
	return (0);
}

int	cub_handle_mouse(int button, int x, int y, t_cub *cub)
{
	(void)button;
	if (!cub->menu.on_screen)
		return (1);
	if (x >= cub->menu.x + 516 && x < cub->menu.x + 516 + cub->menu.checker_plain.width && y >= cub->menu.y + 578 && y < cub->menu.y + 578 + cub->menu.checker_plain.height)
		cub->menu.outline = 2;
	if (x >= cub->menu.x + 516 && x < cub->menu.x + 516 + cub->menu.checker_plain.width && y >= cub->menu.y + 507 && y < cub->menu.y + 507 + cub->menu.checker_plain.height)
		cub->menu.outline = 1;
	if (x >= cub->menu.x + 382 && x < cub->menu.x + 382 + cub->menu.checker_plain.width && y >= cub->menu.y + 322 && y < cub->menu.y + 322 + cub->menu.checker_plain.height)
		cub->menu.cross_hair = 1;
	if (x >= cub->menu.x + 477 && x < cub->menu.x + 477 + cub->menu.checker_plain.width && y >= cub->menu.y + 322 && y < cub->menu.y + 322 + cub->menu.checker_plain.height)
		cub->menu.cross_hair = 2;
	if (x >= cub->menu.x + 420 && x < cub->menu.x + 420 + cub->menu.button.width && y >= cub->menu.y + 60 && y < cub->menu.y + 60 + cub->menu.button.height)
		handle_menu(cub);
	if ((x - cub->menu.x >= cub->menu.cursors[SPEED].x && x - cub->menu.x < cub->menu.cursors[SPEED].x + cub->menu.cursor.width && y - abs(cub->menu.y) >= cub->menu.cursors[SPEED].y && y - abs(cub->menu.y) < cub->menu.cursors[SPEED].y + cub->menu.cursor.height) || (x - cub->menu.x >= 870 && x - cub->menu.x < 1300 && y - cub->menu.y >= 350 && y - cub->menu.y < 390))
	{
		cub->menu.cursors[SPEED].is_pressed = true;
		cub->menu.cursors[SPEED].press_x = x;
		cub->menu.cursors[SPEED].press_y = y;
	}
	if ((x - cub->menu.x >= cub->menu.cursors[SENSI].x && x - cub->menu.x < cub->menu.cursors[SENSI].x + cub->menu.cursor.width && y - abs(cub->menu.y) >= cub->menu.cursors[SENSI].y && y - abs(cub->menu.y) < cub->menu.cursors[SENSI].y + cub->menu.cursor.height) || (x - cub->menu.x >= 870 && x - cub->menu.x < 1300 && y - cub->menu.y >= 548 && y - cub->menu.y < 588))
	{
		cub->menu.cursors[SENSI].is_pressed = true;
		cub->menu.cursors[SENSI].press_x = x;
		cub->menu.cursors[SENSI].press_y = y;
	}
	if ((x - cub->menu.x >= cub->menu.reseters[SPEED].x && x - cub->menu.x < cub->menu.reseters[SPEED].x + cub->menu.reset.width && y - abs(cub->menu.y) >= cub->menu.reseters[SPEED].y && y - abs(cub->menu.y) < cub->menu.reseters[SPEED].y + cub->menu.reset.height))// || (x - cub->menu.x >= 870 && x - cub->menu.x < 1300 && y - cub->menu.y >= 548 && y - cub->menu.y < 588))
	{
		cub->menu.reseters[SPEED].is_pressed = true;
		cub->menu.reseters[SPEED].press_x = x;
		cub->menu.reseters[SPEED].press_y = y;
	}
	if ((x - cub->menu.x >= cub->menu.reseters[SENSI].x && x - cub->menu.x < cub->menu.reseters[SENSI].x + cub->menu.reset.width && y - abs(cub->menu.y) >= cub->menu.reseters[SENSI].y && y - abs(cub->menu.y) < cub->menu.reseters[SENSI].y + cub->menu.reset.height)) //|| (x - cub->menu.x >= 870 && x - cub->menu.x < 1300 && y - cub->menu.y >= 548 && y - cub->menu.y < 588))
	{
		cub->menu.reseters[SENSI].is_pressed = true;
		cub->menu.reseters[SENSI].press_x = x;
		cub->menu.reseters[SENSI].press_y = y;
	}
	return (0);
}

int	cub_handle_mouse_move(int x, int y, t_cub *cub)
{
	(void)y;
	if (!cub->menu.on_screen)
	{
		double view_angle = cub->view_angle;
		if (cub->last_mouse_pos != -1)
			cub->view_angle += (x - cub->last_mouse_pos) * M_PI / 64 * cub->sensivity;
		if (fabs(view_angle - cub->view_angle) > 0.001)
			cub_mouse_move(cub, cub->win_size[WIDTH] / 2, cub->win_size[HEIGHT] / 2);
		cub->last_mouse_pos = cub->win_size[WIDTH] / 2;
	}
	return (1);
}

void cub_mlx_config(t_cub *cub)
{
	mlx_hook(cub->win, KEY_PRESS, KEY_PRESS_MASK, cub_handle_key_press, cub);
	mlx_hook(cub->win, KEY_RELEASE, KEY_RELEASE_MASK, cub_handle_key_release, cub);
	mlx_hook(cub->win, MOTION_NOTIFY, POINTER_MOTION_MASK, cub_handle_mouse_move, cub);
	mlx_hook(cub->win, DESTROY_NOTIFY, NO_EVENT_MASK, close_window, cub);
	mlx_mouse_hook(cub->win, cub_handle_mouse, cub);
	mlx_hook(cub->win, BUTTON_RELEASE, BUTTON_RELEASE_MASK, cub_handle_mouse_release, cub);
	mlx_loop_hook(cub->mlx, perform_actions, cub);
}

void	cub_update_view_angle(int keycode, t_cub *cub)
{
	if (keycode == KEY_LEFT)
		cub->view_angle -= cub->sensivity;
	else
		cub->view_angle += cub->sensivity;
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
	if (ft_isset(cub->data->map[(int)new_y][(int) cub->player_position.x],"1DG") \
	&& ft_isset(cub->data->map[(int)cub->player_position.y][(int)new_x], "1DG"))
		return ;
	if (ft_isset(cub->data->map[(int)new_y][(int)new_x], "1DG"))
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
		move_player(cos(cub->view_angle) / cub->player_speed, sin(cub->view_angle) / cub->player_speed, cub);
	if (keycode == KEY_S)
		move_player(-cos(cub->view_angle) / cub->player_speed, \
		-sin(cub->view_angle) / cub->player_speed, cub);
	if (keycode == KEY_A)
		move_player(cos(cub->view_angle - M_PI_2) / cub->player_speed, \
		sin(cub->view_angle - M_PI_2) / cub->player_speed, cub);
	if (keycode == KEY_D)
		move_player(cos(cub->view_angle + M_PI_2) / cub->player_speed, \
		sin(cub->view_angle + M_PI_2) / cub->player_speed, cub);

	if (cub->player_position.y - (int)cub->player_position.y < 0.0005)
		cub->player_position.y += 0.0005;
}

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

#elif defined (__linux__)

void	mouse_get_pos(t_cub *cub, int *x, int *y)
{
	mlx_mouse_get_pos(cub->mlx, cub->win, x, y);
}

void	cub_mouse_move(t_cub *cub, int x, int y)
{
	mlx_mouse_move(cub->mlx, cub->win, x, y);
}

void	cub_mouse_show(t_cub *cub)
{
	mlx_mouse_show(cub->mlx, cub->win);
}

void	cub_mouse_hide(t_cub *cub)
{
	mlx_mouse_hide(cub->mlx, cub->win);
}

#endif

#if defined(__linux__)

int close_window(t_cub *cub)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&cub->program_ends_mutex);
	cub->program_ends = true;
	pthread_mutex_unlock(&cub->program_ends_mutex);
	usleep(1000);
	while (i < NB_THREADS)
		pthread_join(cub->threads[i++], NULL);
	pthread_mutex_destroy(&cub->finished_mutex);
	pthread_mutex_destroy(&cub->program_ends_mutex);
	pthread_mutex_destroy(&cub->ray_mutex);
	free(cub->threads);
	i = 0;
	while (i <= 14)
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
	pthread_mutex_destroy(&cub->finished_mutex);
	pthread_mutex_destroy(&cub->program_ends_mutex);
	pthread_mutex_destroy(&cub->ray_mutex);
	free(cub->threads);
	i = 0;
	while (i <= 13)
		mlx_destroy_image(cub->mlx, cub->textures[i++].img);
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
