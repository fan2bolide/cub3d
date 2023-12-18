/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:49:00 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/18 07:34:01 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_iposition	get_gun_position(t_cub *cub)
{
	t_iposition	result;

	result.x = 45 * cub->win_size[WIDTH] / 100;
	result.y = 45 * cub->win_size[HEIGHT] / 100;
	return (result);
}

/**
 * \brief
 * \param cub the game
 * \return
 */
int	init_portals(t_cub *cub) //TODO peut etre changerr le nom
{
	cub->blue_prtl = '-';
	cub->orange_prtl = '-';
	cub->rick_prtl = '-';
	cub->last_portal_placed = 'B';
	cub->portals = ft_calloc(cub->win_size[WIDTH], sizeof (t_prtl_list *));
	cub->doors = ft_calloc(cub->win_size[WIDTH], sizeof(t_prtl_list *));
	cub->glass = ft_calloc(cub->win_size[WIDTH], sizeof(t_prtl_list *));
	return (cub->portals && cub->doors && cub->glass);
}

int	check_allocations(t_cub *cub)
{
	if (!cub->rays || !cub->angles || !cub->wall_heights \
		|| !cub->wall_distance || !init_portals(cub) \
		|| !init_mutex(cub))
	{
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

int	init_game(t_cub *cub)
{
	ft_bzero(cub->keys_states, 65509 * sizeof(int));
	cub->cross_hair = 'C';
	cub->rays = malloc(sizeof(t_position) * cub->win_size[WIDTH]);
	cub->angles = malloc(sizeof(double) * cub->win_size[WIDTH]);
	cub->wall_heights = malloc(sizeof(int) * cub->win_size[WIDTH]);
	cub->wall_distance = malloc(sizeof(double) * cub->win_size[WIDTH]);
	init_player(cub);
	cub->gun_position = get_gun_position(cub);
	cub->next_ray_to_compute = cub->win_size[WIDTH];
	if (!check_allocations(cub))
		close_window(cub);
	cub->last_mouse_pos = -1;
	convert_path_to_mlx_img(cub);
	cub->view_angle = get_orientation(cub->data->map, cub->player_position);
	load_game_menu(cub);
	if (!init_doors(cub))
		close_window(cub);
	cub->fov = M_PI_2;
	cub->player_speed = 20;
	cub->sensivity = 0.017;
	display_load_screen(cub);
	if (!render_frame(cub))
		close_window(cub);
	create_threads(cub);
	return (mlx_loop_hook(cub->mlx, perform_actions, cub), sleep(1), 1);
}
