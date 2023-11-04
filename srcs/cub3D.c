/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:28:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/04 06:01:25 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_orientation(char **map, t_position *pos);
void	cub_mlx_config(t_cub *cub);
int		cub_handle_key_press(int keycode, t_cub *cub);
int		close_window(t_cub *cub);
int		cub_render_frame(t_cub *cub);

void	cub_update_player_position(int keycode, t_cub *cub);

void	cub_update_view_angle(int keycode, t_cub *cub);

static int	cub_check_args(int argc, char **argv, t_cub *cub)
{
	if (argc == 4)
		if (ft_strequ(argv[2], "-s"))
			return (cub->win_size[0] = ft_atoi(argv[3]), 0);
	if (argc != 2)
		return (write(2, USAGE, ft_strlen(USAGE)), 1);
	return (0);
}

t_position	*create_position(double i, double j)
{
	t_position	*pos;

	pos = malloc(sizeof(t_position));
	pos->x = j;
	pos->y = i;
	return (pos);
}

t_position	*get_position(char **map)
{
	int	i;
	int	j;

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
	t_cub	*cub;

	cub = malloc(sizeof (t_cub));
	ft_bzero(cub->keys_states, 65509);
	cub->is_fullscreen = false;
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
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->win_size[1], cub->win_size[0], "cub3D");
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
	cub->view_angle = get_orientation(cub->data->map, cub->player_position);
	cub->fov = M_PI_2;
	if (!render_frame(cub))
		return (close_window(cub), 1);
	cub_mlx_config(cub);
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
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_clear_window(cub->mlx, cub->win);
	mlx_destroy_window(cub->mlx, cub->win);
	cub->win = mlx_new_window(cub->mlx, cub->win_size[1], cub->win_size[0], "cub3D");
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
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
	if (cub->keys_states[KEY_LEFT] == 1)
		cub_update_view_angle(KEY_LEFT, cub);
	if (cub->keys_states[KEY_RIGHT] == 1)
		cub_update_view_angle(KEY_RIGHT, cub);
	if (cub->keys_states[KEY_F11] == 1)
		cub_full_screen(cub);
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
	cub->keys_states[keycode] = PRESSED;
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

	old_x = cub->player_position->x;
	old_y = cub->player_position->y;
	if ((int)old_x != (int)new_x)
	{
		if ((int)old_y != (int)new_y)
			if (cub->data->map[(int)new_y][(int)old_x] == '1')
				return (cub->player_position->x = new_x, (void) 0);
		cub->player_position->y = new_y;
		return ;
	}
	if ((int)old_y != (int)new_y)
		cub->player_position->x = new_x;
}

void	move_player(double x_change, double y_change, t_cub *cub)
{
	double	new_y;
	double	new_x;

	new_y = cub->player_position->y + y_change;
	new_x = cub->player_position->x + x_change;
	if (cub->data->map[(int)new_y][(int) cub->player_position->x] == '1' \
	&& cub->data->map[(int)cub->player_position->y][(int)new_x] == '1')
		return ;
	if (cub->data->map[(int)new_y][(int)new_x] == '1')
		return (report_movement(new_y, new_x, cub));
	cub->player_position->y = new_y;
	cub->player_position->x = new_x;
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
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	destroy_data(cub->data);
	free(cub->player_position);
	free(cub);
	exit(0);
}
#elif defined(__APPLE__)

int	close_window(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	free(cub->mlx);
	destroy_data(cub->data);
	free(cub->player_position);
	free(cub);
	exit(0);
}
#endif
