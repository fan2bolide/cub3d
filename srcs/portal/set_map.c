/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 00:09:33 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/16 02:05:16 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rendering.h>

#include "cub3D.h"

void	reset_portal(t_cub *cub, char prtl_id);

static void	set_east_portal(t_cub *cub, t_position middle_ray, char prtl_id)
{
	char	other_ptrl_id;

	if (cub->data->map[(int)middle_ray.y][(int)middle_ray.x - 1] != '1'
	|| ft_isset(cub->data->map[(int)middle_ray.y][(int)middle_ray.x], "dDG"))
		return ;
	reset_portal(cub, prtl_id);
	other_ptrl_id = get_other_portal(prtl_id);
	if (cub->data->map[(int)middle_ray.y][(int)middle_ray.x - 1] ==
	other_ptrl_id)
	{
		if (other_ptrl_id == 'O')
			cub->orange_prtl = '-';
		else
			cub->blue_prtl = '-';
	}
	cub->data->map[(int)middle_ray.y][(int)middle_ray.x - 1] = prtl_id;
	if (prtl_id == 'O')
		cub->orange_prtl = 'E';
	if (prtl_id == 'B')
		cub->blue_prtl = 'E';
	if (prtl_id == 'R')
		cub->rick_prtl = 'E';
}

static void	set_west_portal(t_cub *cub, t_position middle_ray, char prtl_id)
{
	char	other_ptrl_id;

	if (cub->data->map[(int)middle_ray.y][(int)middle_ray.x] != '1'
	|| ft_isset(cub->data->map[(int)middle_ray.y][(int)middle_ray.x - 1], "dDG"))
		return ;
	reset_portal(cub, prtl_id);
	other_ptrl_id = get_other_portal(prtl_id);
	if (cub->data->map[(int)middle_ray.y][(int)middle_ray.x] == other_ptrl_id)
	{
		if (other_ptrl_id == 'O')
			cub->orange_prtl = '-';
		else
			cub->blue_prtl = '-';
	}
	cub->data->map[(int)middle_ray.y][(int)middle_ray.x] = prtl_id;
	if (prtl_id == 'O')
		cub->orange_prtl = 'W';
	if (prtl_id == 'B')
		cub->blue_prtl = 'W';
	if (prtl_id == 'R')
		cub->rick_prtl = 'W';
}

static void	set_north_portal(t_cub *cub, t_position middle_ray, char prtl_id)
{
	char	other_ptrl_id;

	if (cub->data->map[(int)middle_ray.y - 1][(int)middle_ray.x] != '1'
	|| ft_isset(cub->data->map[(int)middle_ray.y][(int)middle_ray.x], "dDG"))
		return ;
	reset_portal(cub, prtl_id);
	other_ptrl_id = get_other_portal(prtl_id);
	if (cub->data->map[(int)middle_ray.y - 1][(int)middle_ray.x]
	== other_ptrl_id)
	{
		if (other_ptrl_id == 'O')
			cub->orange_prtl = '-';
		if (other_ptrl_id == 'B')
			cub->blue_prtl = '-';
	}
	cub->data->map[(int)middle_ray.y - 1][(int)middle_ray.x] = prtl_id;
	if (prtl_id == 'O')
		cub->orange_prtl = 'S';
	if (prtl_id == 'B')
		cub->blue_prtl = 'S';
	if (prtl_id == 'R')
		cub->rick_prtl = 'S';
}

static void	set_south_portal(t_cub *cub, t_position middle_ray, char prtl_id)
{
	char	other_ptrl_id;

	if (cub->data->map[(int)middle_ray.y][(int)middle_ray.x] != '1'
	|| ft_isset(cub->data->map[(int)middle_ray.y - 1][(int)middle_ray.x], "dDG"))
		return ;
	reset_portal(cub, prtl_id);
	other_ptrl_id = get_other_portal(prtl_id);
	if (cub->data->map[(int)middle_ray.y][(int)middle_ray.x] == other_ptrl_id)
	{
		if (other_ptrl_id == 'O')
			cub->orange_prtl = '-';
		if (other_ptrl_id == 'B')
			cub->blue_prtl = '-';
	}
	cub->data->map[(int)middle_ray.y][(int)middle_ray.x] = prtl_id;
	if (prtl_id == 'O')
		cub->orange_prtl = 'N';
	if (prtl_id == 'B')
		cub->blue_prtl = 'N';
	if (prtl_id == 'R')
		cub->rick_prtl = 'N';
}

void	set_portal_on_map(t_cub *cub, char prtl_id)
{
	t_position	middle_ray;

	cub->last_portal_placed = prtl_id;
	if (cub->portals[cub->win_size[WIDTH] / 2])
		middle_ray = cub->portals[cub->win_size[WIDTH] / 2]->portal->position;
	else
		middle_ray = cub->rays[cub->win_size[WIDTH] / 2];
	if ((int)middle_ray.x == middle_ray.x)
	{
		if (cub->player_position.x > middle_ray.x)
			set_east_portal(cub, middle_ray, prtl_id);
		else
			set_west_portal(cub, middle_ray, prtl_id);
	}
	else
	{
		if (cub->player_position.y > middle_ray.y)
			set_north_portal(cub, middle_ray, prtl_id);
		else
			set_south_portal(cub, middle_ray, prtl_id);
	}
}
