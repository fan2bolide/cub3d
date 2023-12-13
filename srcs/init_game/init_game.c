/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:49:00 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/13 00:11:04 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
			return (cub->win_size[0] = ft_atoi(argv[3]), 0);
	if (argc != 2)
		return (ft_putstr_fd(USAGE EOL, 2), 1);
	return (0);
}

static t_iposition	get_gun_position(t_cub *cub)
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
	cub->rick_prtl = '-';
	cub->win_size[1] = cub->win_size[0] * 16 / 10;
	cub->rays = malloc(sizeof(t_position) * cub->win_size[1]);
	cub->angles = malloc(sizeof(double) * cub->win_size[1]);
	cub->wall_heights = malloc(sizeof(int) * cub->win_size[1]);
	cub->wall_distance = malloc(sizeof(double) * cub->win_size[1]);
	cub->portals = ft_calloc(cub->win_size[WIDTH], sizeof (t_prtl_list *));
	cub->doors = ft_calloc(cub->win_size[WIDTH], sizeof(t_prtl_list *));
	if (!cub->rays || !cub->angles || !cub->wall_heights)
		return (free(cub->rays), free(cub->angles), free(cub->wall_heights), NULL);
	cub->player_position = get_position(cub->data->map);
	cub->player_position.x += 0.5;
	cub->player_position.y += 0.5;
	cub->last_player_pos.x = cub->player_position.x;
	cub->last_player_pos.y = cub->player_position.y;
	cub->gun_position = get_gun_position(cub);
	cub->last_portal_placed = 'B';
	cub->next_ray_to_compute = cub->win_size[WIDTH];
	pthread_mutex_init(&cub->ray_mutex, NULL);
	pthread_mutex_init(&cub->program_ends_mutex, NULL);
	pthread_mutex_init(&cub->finished_mutex, NULL);
	return (cub);
}