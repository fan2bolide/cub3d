/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:12:38 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/05 16:30:56 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_for_illegal_char(t_list *file)
{
	char	*content;

	while (file && file->content)
	{
		content = file->content;
		if (!ft_strisset(content, ALLOWED_CHARS))
			return (ft_putstr_fd(ERR ILL_CHAR EOL, 2), 1);
		file = file->next;
	}
	return (0);
}

int	player_count(char **map)
{
	size_t	i;
	size_t	j;
	size_t	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j++])
			if (ft_isset(map[i][j - 1], "NSEW"))
				count++;
		i++;
	}
	return (count);
}

int	check_wall_surroundment(char **map)
{
	ssize_t	x;
	ssize_t	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_isset(map[y][x], NOT_WALLS_CHARS))
			{
				if (!map[y][x + 1] || map[y][x + 1] == ' ')
					return (ft_putstr_fd(ERR E_WALL_SUR EOL, 2), 1);
				if (!map[y + 1] || !map[y + 1][x] || map[y + 1][x] == ' ')
					return (ft_putstr_fd(ERR E_WALL_SUR EOL, 2), 1);
				if ((x && (!map[y][x - 1] || map[y][x - 1] == ' ')) || !x)
					return (ft_putstr_fd(ERR E_WALL_SUR EOL, 2), 1);
				if ((y && (!map[y - 1] || !map[y - 1][x] \
					|| map[y - 1][x] == ' ')) || !y)
					return (ft_putstr_fd(ERR E_WALL_SUR EOL, 2), 1);
			}
		}
	}
	return (0);
}

int	check_door_position(char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			while (map[i][j] && map[i][j] != 'D')
				j++;
			if (!map[i][j] || !map[i][j + 1])
				break ;
			if (map[i][j - 1] != '1' || map[i][j + 1] != '1')
			{
				if (!i || !map[i + 1])
					break ;
				if (map[i - 1][j] != '1' || map[i + 1][j] != '1')
					return (ft_putstr_fd(ERR WRONG_D_POS EOL, 2), 1);
			}
		}
	}
	return (0);
}

int	parse_map(char **map)
{
	if (player_count(map) != 1)
		return (ft_putstr_fd(ERR WRONG_P_N EOL, 2), 1);
	if (check_wall_surroundment(map))
		return (1);
	if (check_door_position(map))
		return (1);
	return (0);
}
