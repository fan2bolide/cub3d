/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:38:22 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/06 14:49:48 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fill_wall_surr_map(char **map, char **wall_surr, int x, int y)
{
	if (y < 0 || x < 0)
		return;
	if (!map[y] || !map[y][x] || map[y][x] == ' ' || wall_surr[y][x] == '-')
		return ;
	if (wall_surr[y][x] == '-')
		return ;
	if (map[y][x] == '1')
		return (wall_surr[y][x] = '1', (void) 0);
	wall_surr[y][x] = '-';
	fill_wall_surr_map(map, wall_surr, x + 1, y);
	fill_wall_surr_map(map, wall_surr, x - 1, y);
	fill_wall_surr_map(map, wall_surr, x, y + 1);
	fill_wall_surr_map(map, wall_surr, x, y - 1);
}

//t_iposition	get_zero_pos(char *w_surr, int x, int y)
//{
//	t_iposition	pos;
//
//	if (!y)
//	{
//		pos.x = x;
//		pos.y = y + 1;
//	}
//	{
//	else if (!w_surr[y + 1])
//		pos.x = x;
//		pos.y = y - 1;
//	}
//	else if (!x)
//	{
//		pos.x = x + 1;
//		pos.y = y;
//	}
//	else if (!w_surr[y][x + 1])
//	{
//		pos.x = x - 1;
//		pos.y = y;
//	}
//}

t_iposition get_next_baj(char **w_surr, t_iposition *next_one, t_iposition *cur_pos)
{
	size_t	y;
	size_t	x;

	y = cur_pos->y;
	x = cur_pos->x;

//	if (w_surr[y][x + 1] && w_surr[y][x + 1] == '1' && (y - 1 < 0|| !w_surr[y - 1][x] || w_surr[y - 1][x] != '-'))
//		return (next_one->x = x + 1, next_one->y = y, *next_one);
//	if (x - 1 && w_surr[y][x - 1] == '1' && y - 1 >= 0 && w_surr[y - 1])
//	{
//		i = 0;
//		while (i++ <= x && w_surr[y - 1][i - 1])
//			if (i - 1 == x && w_surr[y - 1][i - 1] == '-')
//				return (next_one->x = x - 1, next_one->y = y, *next_one);
//	}
//	if (w_surr[y + 1] && w_surr[y + 1][x + 1] && w_surr[y + 1][x + 1] == '1' && (y < 0 || !w_surr[y][x + 1] || w_surr[y][x + 1] != '-'))
//		return (next_one->x = x + 1, next_one->y = y + 1, *next_one);
//	if (w_surr[y + 1])
//	{
//		i = 0;
//		while (i++ <= x && w_surr[y + 1][i - 1])
//			if (i - 1 == x && w_surr[y + 1][x] == '1')
//				return (next_one->x = x, next_one->y = y + 1, *next_one);
//	}
//	if (w_surr[y + 1])
//	{
//		i = 0;
//		while (i++ <= x && w_surr[y + 1][i - 1])
//			if (i - 1 == x && w_surr[y + 1][x] == '-')
//				return (next_one->x = x, next_one->y = y + 1, *next_one);
	if (w_surr[y][x] == '-' && ft_isset(w_surr[y - 1][x], "12"))
	{
		w_surr[y][x] = 'X';
		if (w_surr[y - 1][x] != '2')
		{
			w_surr[y - 1][x] = '2';
			return (next_one->x = x, next_one->y = y - 1, *cur_pos);
		}
	}
	if (w_surr[y][x] == 'X' && ft_isset(w_surr[y][x + 1], "12"))
	{
		w_surr[y][x] = 'V';
		if (w_surr[y][x + 1] != '2')
		{
			w_surr[y][x + 1] = '2';
			return (next_one->x = x + 1, next_one->y = y, *cur_pos);
		}
	}
	if (w_surr[y][x] == 'V' && ft_isset(w_surr[y + 1][x], "12"))
	{
		w_surr[y + 1][x] = 'O';
		if (w_surr[y + 1][x] != '2')
		{
			w_surr[y + 1][x] = '2';
			return (next_one->x = x, next_one->y = y + 1, *cur_pos);
		}
	}
	if (w_surr[y][x] == '0' && ft_isset(w_surr[y][x - 1], "12"))
	{
		w_surr[y][x] = '-';
		if (w_surr[y][x - 1] != '2')
		{
			w_surr[y][x - 1] = '2';
			return (next_one->x = x - 1, next_one->y = y, *cur_pos);
		}
		w_surr[y][x - 1] = '2';
		return (w_surr[y][x] = '-', next_one->x = x - 1, next_one->y = y, *cur_pos);
	}
	if (w_surr[y][x] == '-')
		return (cur_pos->x += 1, get_next_baj(w_surr, next_one, cur_pos));
	else if (w_surr[y][x] == 'X')
		return (cur_pos->y += 1, get_next_baj(w_surr, next_one, cur_pos));
	else if (w_surr[y][x] == 'V')
		return (cur_pos->x -= 1, get_next_baj(w_surr, next_one, cur_pos));
	else if (w_surr[y][x] == '0')
		return (cur_pos->y -= 1, get_next_baj(w_surr, next_one, cur_pos));


	printf("pas normal\n");
	return (*next_one);
}

int	get_wall_surroundment(t_data *data)
{
	t_position	*player_pos;
	char 		**wall_surroundment;

	wall_surroundment = tab_dup_empty(data->map);
	if (!wall_surroundment)
		return (ft_putstr_fd(ERR ALLOC_ERR EOL, 2), 0);
	player_pos = get_position(data->map);
	if (!player_pos)
		return (ft_old_split_destroy(wall_surroundment), ft_putstr_fd(ERR ALLOC_ERR EOL, 2), 0);
	fill_wall_surr_map(data->map, wall_surroundment, (int)player_pos->x, (int)player_pos->y);
	int i = 0;
	while (wall_surroundment[i])
		printf("%s\n", wall_surroundment[i++]);
	t_iposition test;
	t_iposition next_one;
	test.x = 1;
	test.y = 1;
	while (1)
	{
		test = get_next_baj(wall_surroundment, &next_one, &test);
		printf("%li, %li\n", next_one.x, next_one.y);
		int i = 0;
		while (wall_surroundment[i])
			printf("%s\n", wall_surroundment[i++]);
		sleep(1);
	}
	return (1);
//	if(!convert_to_baj(wall_surroundment, data->baj, player_pos))
//		return (ft_putstr_fd(ERR ALLOC_ERR EOL, 2), 0);
}

t_data	*parsing(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_putstr_fd(ERR WRONG_ARG_N EOL, 2), NULL);
	data = get_data(argv);
	get_wall_surroundment(data);
	return (data);
}
