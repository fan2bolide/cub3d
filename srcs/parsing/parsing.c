/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:38:22 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/07 18:16:42 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_not_alone(char **map, int x, int y)
{
	if (!y || !x)
		return (1);
	if (!map[y + 1] || ft_strlen(map[y - 1]) <= (size_t) x)
		return (1);
	if (!map[y][x + 1])
		return (1);
	if (map[y][x + 1] == '0' && map[y][x - 1] == '0' && map[y - 1][x] == '0' && map[y + 1][x] == '0')
		return (0);
	return (1);
}

void	fill_wall_surr_map(char **map, char **wall_surr, int x, int y)
{
	if (y < 0 || x < 0)
		return;
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

int	paint_w_surr(size_t i, t_bajeanno *next_one, t_iposition *cur_pos, char **w_surr)
{
	size_t	y_del[4] = {cur_pos->y - 1, cur_pos->y, cur_pos->y + 1, cur_pos->y};
	size_t	x_del[4] = {cur_pos->x, cur_pos->x + 1, cur_pos->x, cur_pos->x - 1};
	char	replacement[4] = {'X', 'V', 'O', 'T'};
	char	charset[4][4] = {"-+T", "-+X", "-+V", "-+O"};
	char	orientation[4] = {'N', 'E', 'S', 'W'};

	if (ft_isset(w_surr[cur_pos->y][cur_pos->x], charset[i]) && ft_isset(w_surr[y_del[i]][x_del[i]], "1"))
	{
		w_surr[cur_pos->y][cur_pos->x] = replacement[i];
		return (next_one->x = x_del[i], next_one->y = y_del[i], next_one->orientation = orientation[i], 1);
	}
	return (0);
}

size_t get_ind_start(t_iposition *cur_pos, char **w_surr)
{
	size_t	x;
	size_t	y;

	x = cur_pos->x;
	y = cur_pos->y;
	if (w_surr[y][x] == '+')
	{
		if (w_surr[y][x + 1] == '-')
			return (cur_pos->x += 1, 0);
		if (w_surr[y + 1][x] == '-')
			return (cur_pos->y += 1, 1);
		if (w_surr[y][x - 1] == '-')
			return (cur_pos->x -= 1, 2);
		if (w_surr[y - 1][x] == '-')
			return (cur_pos->y -= 1, 3);
	}
	if (ft_isset(w_surr[y][x - 1], "-X") && w_surr[y - 1][x] == '1')
		return (0);
	if (ft_isset(w_surr[y + 1][x], "-T") && w_surr[y][x - 1] == '1')
		return (3);
	if (ft_isset(w_surr[y - 1][x], "-V") && w_surr[y][x + 1] == '1')
		return (1);
	if ((ft_isset(w_surr[y][x + 1], "-O") && w_surr[y + 1][x] == '1'))
		return (2);
//	if (w_surr[y][x] == 'O')
//		return (2);
	return (4);
}


void clear_line(char **w_surr, t_iposition *cur_pos)
{
	size_t	y;
	size_t	x;
	size_t	i;

	x = cur_pos->x;
	y = cur_pos->y;
	if (w_surr[y][x + 1] == '1' && w_surr[y][x] == 'O' && w_surr[y + 1][x] == '1' && w_surr[y - 1][x] == '1')
	{
		i = x - 1;
		while (w_surr[y][i] != '1' && w_surr[y + 1][i] == '1' && w_surr[y - 1][i] == '1')
			w_surr[y][i--] = '+';
		if (w_surr[y][i] != '1' && i != x - 1)
			w_surr[y][i] = '+';
	}
	if (w_surr[y][x - 1] == '1' && w_surr[y][x] == 'X' && w_surr[y + 1][x] == '1' && w_surr[y - 1][x] == '1')
	{
		i = x + 1;
		while (w_surr[y][i] != '1' && w_surr[y + 1][i] == '1' && w_surr[y - 1][i] == '1')
			w_surr[y][i--] = '+';
		if (w_surr[y][i] != '1' && i != x + 1)
			w_surr[y][i] = '+';
	}
	if (w_surr[y - 1][x] == '1' && w_surr[y][x] == 'V' && w_surr[y][x + 1] == '1' && w_surr[y][x - 1] == '1')
	{
		i = y + 1;
		while (w_surr[i][x] != '1' && w_surr[i][x + 1] == '1' && w_surr[i][x - 1] == '1')
			w_surr[i++][x] = '+';
		if (w_surr[i][x] != '1' && i != y + 1)
			w_surr[i][x] = '+';
	}
	if (w_surr[y - 1][x] == '1' && w_surr[y][x] == 'T' && w_surr[y][x + 1] == '1' && w_surr[y][x - 1] == '1')
	{
		i = y + 1;
		while (w_surr[y][i] != '1' && w_surr[y + 1][i] == '1' && w_surr[y - 1][i] == '1')
			w_surr[y][i--] = '+';
		if (w_surr[y][i] != '1' && i != y + 1)
			w_surr[y][i] = '+';
	}
//	i = 0;
//	while (w_surr[i])
//		printf("%s\n", w_surr[i++]);
}

t_iposition get_next_baj(char **w_surr, t_bajeanno *next_one, t_iposition *cur_pos)
{
	size_t	y;
	size_t	x;
	size_t	save_start;
	size_t	i;

	y = cur_pos->y;
	x = cur_pos->x;

	clear_line(w_surr, cur_pos);
	if (w_surr[y][x] == '-')
	{
		if (ft_isset(w_surr[y][x - 1], "X+") && w_surr[y - 1][x] == '-')
			return (cur_pos->y -= 1, get_next_baj(w_surr, next_one, cur_pos));
		if (ft_isset(w_surr[y - 1][x], "V+") && w_surr[y][x + 1] == '-')
			return (cur_pos->x += 1, get_next_baj(w_surr, next_one, cur_pos));
		if (ft_isset(w_surr[y + 1][x], "T+") && w_surr[y][x - 1] == '-')
			return (cur_pos->x -= 1, get_next_baj(w_surr, next_one, cur_pos));
		if (ft_isset(w_surr[y][x + 1], "O+") && w_surr[y + 1][x] == '-')
			return (cur_pos->y += 1, get_next_baj(w_surr, next_one, cur_pos));
	}
	save_start = get_ind_start(cur_pos, w_surr);
	i = save_start;
	while (i != 4)
	{
		if (paint_w_surr(i, next_one, cur_pos, w_surr))
			return (*cur_pos);
		i++;
		if (i > 3)
			i = 0;
		if (i == save_start)
			break ;
	}
	if (w_surr[y][x] == 'X' && w_surr[y][x + 1] != '1')
		return (cur_pos->x += 1, get_next_baj(w_surr, next_one, cur_pos));
	if (w_surr[y][x] == 'V' && w_surr[y + 1][x] != '1')
		return (cur_pos->y += 1, get_next_baj(w_surr, next_one, cur_pos));
	if (w_surr[y][x] == 'O' && w_surr[y][x - 1] != '1')
		return (cur_pos->x -= 1, get_next_baj(w_surr, next_one, cur_pos));
	if (w_surr[y][x] == 'T' && w_surr[y - 1][x] != '1')
		return (cur_pos->y -= 1, get_next_baj(w_surr, next_one, cur_pos));

	return (get_next_baj(w_surr, next_one, cur_pos));
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
	t_iposition test;
	t_bajeanno next_one;
	test.x = 1;
	test.y = 7;
	next_one.x = 1;
	next_one.y = 7;
	while (1)
	{
		test = get_next_baj(wall_surroundment, &next_one, &test);
		int i = 0;
		while (wall_surroundment[i])
			printf("%s\n", wall_surroundment[i++]);
		printf("%i, %i\n\n\n", next_one.x, next_one.y);
		usleep(200000);
	}
	return (1);
}

t_data	*parsing(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_putstr_fd(ERR WRONG_ARG_N EOL, 2), NULL);
	data = get_data(argv);
	if (data)
		get_wall_surroundment(data);
	return (data);
}
