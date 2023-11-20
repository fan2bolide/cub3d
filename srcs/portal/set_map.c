/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 00:09:33 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/18 20:56:21 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "portal.h"

static void	set_east_portal(t_cub *cub, t_position middle_ray, char prtl_id)
{
	char	other_ptrl_id;

	if (prtl_id == 'O')
		other_ptrl_id = 'B';
	else
		other_ptrl_id = 'O';
	if (cub->data->map[(int)middle_ray.y][(int)middle_ray.x - 1] == other_ptrl_id)
	{
		if (other_ptrl_id == 'O')
			cub->orange_prtl = '-';
		else
			cub->blue_prtl = '-';
	}
	cub->data->map[(int)middle_ray.y][(int)middle_ray.x - 1] = prtl_id;
	if (prtl_id == 'O')
		cub->orange_prtl = 'E';
	else
		cub->blue_prtl = 'E';
}

static void	set_west_portal(t_cub *cub, t_position middle_ray, char prtl_id)
{
	char	other_ptrl_id;

	if (prtl_id == 'O')
		other_ptrl_id = 'B';
	else
		other_ptrl_id = 'O';
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
	else
		cub->blue_prtl = 'W';
}

static void	set_north_portal(t_cub *cub, t_position middle_ray, char prtl_id)
{
	char	other_ptrl_id;

	if (prtl_id == 'O')
		other_ptrl_id = 'B';
	else
		other_ptrl_id = 'O';
	if (cub->data->map[(int)middle_ray.y - 1][(int)middle_ray.x] == other_ptrl_id)
	{
		if (other_ptrl_id == 'O')
			cub->orange_prtl = '-';
		else
			cub->blue_prtl = '-';
	}
	cub->data->map[(int)middle_ray.y - 1][(int)middle_ray.x] = prtl_id;
	if (prtl_id == 'O')
		cub->orange_prtl = 'S';
	else
		cub->blue_prtl = 'S';
}

static void	set_south_portal(t_cub *cub, t_position middle_ray, char prtl_id)
{
	char	other_ptrl_id;

	if (prtl_id == 'O')
		other_ptrl_id = 'B';
	else
		other_ptrl_id = 'O';
	if (cub->data->map[(int)middle_ray.y][(int)middle_ray.x] == other_ptrl_id)
	{
		if (other_ptrl_id == 'O')
			cub->orange_prtl = '-';
		else
			cub->blue_prtl = '-';
	}
	cub->data->map[(int)middle_ray.y][(int)middle_ray.x] = prtl_id;
	if (prtl_id == 'O')
		cub->orange_prtl = 'N';
	else
		cub->blue_prtl = 'N';

}

void	set_portal_on_map(t_cub *cub, char prtl_id)
{
	t_position	middle_ray;
	size_t		i;
	size_t		j;

	i = 0;
	while (cub->data->map[i])
	{
		j = 0;
		while (cub->data->map[i][j])
			if (cub->data->map[i][j++] == prtl_id)
				cub->data->map[i][j - 1] = '1';
		i++;
	}
	middle_ray = cub->rays[cub->win_size[WIDTH] / 2];
	if ((int)middle_ray.x == middle_ray.x)
	{
		if (cub->player_position->x > middle_ray.x)
			set_east_portal(cub, middle_ray, prtl_id);
		else
			set_west_portal(cub, middle_ray, prtl_id);
	}
	else
	{
		if (cub->player_position->y > middle_ray.y)
			set_north_portal(cub, middle_ray, prtl_id);
		else
			set_south_portal(cub, middle_ray, prtl_id);
	}
	printf("%c %c\n", cub->orange_prtl, cub->blue_prtl);

}