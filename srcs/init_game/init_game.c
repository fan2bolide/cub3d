/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:49:00 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/13 18:13:50 by bajeanno         ###   ########.fr       */
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

/**
 * \brief
 * \param cub the game
 * \return
 */
int init_portals(t_cub *cub)
{
	cub->blue_prtl = '-';
	cub->orange_prtl = '-';
	cub->rick_prtl = '-';
	cub->last_portal_placed = 'B';
	cub->portals = ft_calloc(cub->win_size[WIDTH], sizeof (t_prtl_list *));
	cub->doors = ft_calloc(cub->win_size[WIDTH], sizeof(t_prtl_list *));
	return (cub->portals != NULL && cub->doors != NULL);
}

int check_allocations(t_cub *cub)
{
	if (!cub->rays || !cub->angles || !cub->wall_heights \
			|| !cub->wall_distance || !init_portals(cub) \
			|| !init_mutex(cub)) {
		free(cub->rays);
		free(cub->angles);
		free(cub->wall_heights);
		free(cub->wall_distance);
		free(cub->portals);
		free(cub->doors);
		free(cub);
		return (0);
	}
	return (1);
}

void	init_player(t_cub *cub)
{
	cub->player_position = get_position(cub->data->map);
	cub->player_position.x += 0.5;
	cub->player_position.y += 0.5;
	cub->last_player_pos.x = cub->player_position.x;
	cub->last_player_pos.y = cub->player_position.y;
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
	cub->cross_hair = 'C';
	cub->win_size[HEIGHT] = 900;
	cub->win_size[WIDTH] = cub->win_size[0] * 16 / 10;
	cub->rays = malloc(sizeof(t_position) * cub->win_size[WIDTH]);
	cub->angles = malloc(sizeof(double) * cub->win_size[WIDTH]);
	cub->wall_heights = malloc(sizeof(int) * cub->win_size[WIDTH]);
	cub->wall_distance = malloc(sizeof(double) * cub->win_size[WIDTH]);
	init_player(cub);
	cub->gun_position = get_gun_position(cub);
	cub->next_ray_to_compute = cub->win_size[WIDTH];
	if (!check_allocations(cub))
		return (NULL);
	return (cub);
}