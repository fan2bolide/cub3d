/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:03:33 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/13 00:04:11 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 *
 * @param map
 * @return the position of the player at the start of the game
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

/**
 * \param map the parsed map
 * \param pos the player position
 * \return the angle of the player at the begining of the game
 */
double	get_orientation(char **map, const t_position pos)
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