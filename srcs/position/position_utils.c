/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:41:52 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/19 14:35:45 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_position	*create_position(double i, double j)
{
	t_position	*pos;

	pos = malloc(sizeof(t_position));
	if (!pos)
		return (ft_putstr_fd(ERR ALLOC_ERR EOL, 2), NULL);
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
			if (map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'W')
				return (create_position((double)i, (double)j));
			j++;
		}
		i++;
	}
	return (NULL);
}
