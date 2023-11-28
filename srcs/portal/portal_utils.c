/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 00:02:41 by bajeanno          #+#    #+#             */
/*   Updated: 2023/11/24 00:03:01 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_position	get_prtl_pos(t_cub *cub, char portal)
{
	t_position result;

	result.y = 0;
	while (cub->data->map[(int)result.y])
	{
		result.x = 0;
		while (cub->data->map[(int)result.y][(int)result.x])
		{
			if (cub->data->map[(int)result.y][(int)result.x] == portal)
				return (result);
			result.x = result.x + 1;
		}
		result.y = result.y + 1;
	}
	result.x = -1;
	result.y = -1;
	return (result);
}

char	get_prtl_or(t_cub *cub, char portal)
{
	if (portal == 'B')
		return cub->blue_prtl;
	else
		return cub->orange_prtl;
}

char	get_other_portal(char portal)
{
	if (portal == 'B')
		return ('O');
	return ('B');
}
