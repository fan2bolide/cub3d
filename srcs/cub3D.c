/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:28:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/19 08:22:01 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub_mlx_config(t_cub *cub);
int		cub_handle_key_press(int keycode, t_cub *cub);

void	convert_path_to_mlx_img(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		cub->textures[i].img = mlx_xpm_file_to_image(cub->mlx,
				cub->data->texture[i], &cub->textures[i].width,
				&cub->textures[i].height);
		if (!cub->textures[i].img)
		{
			ft_putstr_fd(ERR TXTR_LOAD EOL, 2);
			close_window(cub);
		}
		cub->textures[i].addr = mlx_get_data_addr(cub->textures[i].img,
				&cub->textures[i].bits_per_pixel, &cub->textures[i].line_length,
				&cub->textures[i].endian);
	}
	cub->textures[i].img = mlx_xpm_file_to_image(cub->mlx, BJ_PATH,
			&cub->textures[i].width, &cub->textures[i].height);
	if (!cub->textures[i].img)
		return (ft_putstr_fd(ERR TXTR_LOAD EOL, 2), close_window(cub), (void)0);
	cub->textures[i].addr = mlx_get_data_addr(cub->textures[i].img,
			&cub->textures[i].bits_per_pixel, &cub->textures[i].line_length,
			&cub->textures[i].endian);
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

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = ft_calloc(1, sizeof (t_cub));
	if (!cub)
		close_window(cub);
	init_cub(cub);
	if (!cub->rays || !cub->angles || !cub->wall_heights)
		return (ft_putstr_fd(ERR ALLOC_ERR EOL, 2), close_window(cub), 1);
	cub->data = parsing(argc, argv);
	if (!cub->data)
		return (close_window(cub));
	init_player(cub);
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->win_size[WIDTH], \
			cub->win_size[0], "cub3D");
	convert_path_to_mlx_img(cub);
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[WIDTH], \
			cub->win_size[HEIGHT]);
	if (!cub->img.img)
		close_window(cub);
	cub->img.addr = mlx_get_data_addr(cub->img.img, \
			&cub->img.bits_per_pixel, \
				&cub->img.line_length, &cub->img.endian);
	if (!render_frame(cub))
		return (close_window(cub), 1);
	return (cub_mlx_config(cub), mlx_loop(cub->mlx), 0);
}

void	cub_mlx_config(t_cub *cub)
{
	mlx_hook(cub->win, KEY_PRESS, KEY_PRESS_MASK, cub_handle_key_press, cub);
	mlx_hook(cub->win, KEY_RELEASE, KEY_RELEASE_MASK,
		cub_handle_key_release, cub);
	mlx_hook(cub->win, DESTROY_NOTIFY, NO_EVENT_MASK,
		close_window, cub);
	mlx_loop_hook(cub->mlx, (int (*)())perform_actions, cub);
}
