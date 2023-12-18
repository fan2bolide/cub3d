/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:28:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/18 15:42:10 by nfaust           ###   ########.fr       */
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
 * \brief parses the -s option that changes the size of
 * the window at program start
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
