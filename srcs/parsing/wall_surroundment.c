/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_surroundment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:24:21 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/15 13:22:42 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_not_alone(char **map, int x, int y)
{
	if (!y || !x)
		return (1);
	if (!map[y + 1] || ft_strlen(map[y + 1]) <= (size_t) x + 1
		|| ft_strlen(map[y - 1]) <= (size_t) x + 1)
		return (1);
	if (!map[y][x + 1])
		return (1);
	if (map[y][x + 1] == '0' && map[y][x - 1] == '0' && map[y - 1][x] == '0'
	&& map[y + 1][x] == '0'
		&& map[y - 1][x - 1] == '0' && map[y - 1][x + 1] == '0'
		&& map[y + 1][x - 1] == '0' && map[y + 1][x + 1] == '0')
		return (0);
	return (1);
}

void	fill_wall_surr_map(char **map, char **wall_surr, int x, int y)
{
	if (y < 0 || x < 0)
		return ;
	if (!map[y] || !map[y][x] || map[y][x] == ' ' || wall_surr[y][x] == '-')
		return ;
	if (wall_surr[y][x] == '-')
		return ;
	if (map[y][x] == '1' && check_not_alone(map, x, y))
		return (wall_surr[y][x] = '1', (void) 0);
	else if (map[y][x] == '1')
		return (wall_surr[y][x] = '-', (void) 0);
	wall_surr[y][x] = '-';
	fill_wall_surr_map(map, wall_surr, x + 1, y);
	fill_wall_surr_map(map, wall_surr, x - 1, y);
	fill_wall_surr_map(map, wall_surr, x, y + 1);
	fill_wall_surr_map(map, wall_surr, x, y - 1);
}

int	paint_w_surr(size_t i, t_bajeanno *next_one, t_int_position *cur_pos,
					char **w_surr)
{
	size_t			y_del[4];
	size_t			x_del[4];
	static char		replacement[4] = {'X', 'V', 'O', 'T'};
	static char		charset[4][4] = {"-+T", "-+X", "-+V", "-+O"};
	static char		orientation[4] = {'N', 'E', 'S', 'W'};

	ft_memcpy(y_del, (size_t[4]){cur_pos->y - 1, cur_pos->y, \
	cur_pos->y + 1, cur_pos->y}, 4 * sizeof(size_t));
	ft_memcpy(x_del, (size_t[4]){cur_pos->x, cur_pos->x + 1, cur_pos->x, \
	cur_pos->x - 1}, 4 * sizeof(size_t));
	if (ft_isset(w_surr[cur_pos->y][cur_pos->x], charset[i])
	&& ft_isset(w_surr[y_del[i]][x_del[i]], "1"))
	{
		w_surr[cur_pos->y][cur_pos->x] = replacement[i];
		return (next_one->x = x_del[i], next_one->y = y_del[i], \
		next_one->orientation = orientation[i], 1);
	}
	return (0);
}

void	clear_map(size_t x, size_t y, char **w_surr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (w_surr[i])
	{
		j = 0;
		while (w_surr[i][j])
		{
			if ((i != y || j != x) && ft_isset(w_surr[i][j], "+XVOT"))
				w_surr[i][j] = '-';
			j++;
		}
		i++;
	}
}

void	clear_line(char **w_surr, t_int_position *cur_pos)
{
	size_t	y;
	size_t	x;

	x = cur_pos->x;
	y = cur_pos->y;
	if (w_surr[y][x + 1] == '1' && w_surr[y][x] == 'O'
	&& w_surr[y + 1][x] == '1' && w_surr[y - 1][x] == '1')
		clear_map(x, y, w_surr);
	if (w_surr[y][x - 1] == '1' && w_surr[y][x] == 'X'
	&& w_surr[y + 1][x] == '1' && w_surr[y - 1][x] == '1')
		clear_map(x, y, w_surr);
	if (w_surr[y - 1][x] == '1' && w_surr[y][x] == 'V'
	&& w_surr[y][x + 1] == '1' && w_surr[y][x - 1] == '1')
		clear_map(x, y, w_surr);
	if (w_surr[y - 1][x] == '1' && w_surr[y][x] == 'T'
	&& w_surr[y][x + 1] == '1' && w_surr[y][x - 1] == '1')
		clear_map(x, y, w_surr);
}
