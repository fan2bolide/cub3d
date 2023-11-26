/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bajeanno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:20:55 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/26 12:06:55 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	get_ind_start(t_iposition *cur_pos, char **w_surr)
{
	size_t	x;
	size_t	y;

	x = cur_pos->x;
	y = cur_pos->y;
	if (ft_isset(w_surr[y][x - 1], "-X") && w_surr[y - 1][x] == '1'
	&& w_surr[y][x + 1] != 'O')
		return (0);
	if (ft_isset(w_surr[y + 1][x], "-T") && w_surr[y][x - 1] == '1'
	&& w_surr[y - 1][x] != 'V')
		return (3);
	if (ft_isset(w_surr[y - 1][x], "-V") && w_surr[y][x + 1] == '1'
	&& w_surr[y + 1][x] != 'T')
		return (1);
	if (ft_isset(w_surr[y][x + 1], "-O") && w_surr[y + 1][x] == '1'
	&& w_surr[y][x - 1] != 'X')
		return (2);
	return (4);
}

int	check_empty(char **w_surr, t_iposition *cur_pos, t_bajeanno *baj)
{
	size_t	x;
	size_t	y;

	x = cur_pos->x;
	y = cur_pos->y;
	if (w_surr[y][x] == '-')
	{
		if (ft_isset(w_surr[y][x - 1], "X+") && w_surr[y - 1][x] == '-')
			return (cur_pos->y -= 1, get_next_baj(w_surr, baj, cur_pos), 1);
		if (ft_isset(w_surr[y - 1][x], "V+") && w_surr[y][x + 1] == '-')
			return (cur_pos->x += 1, get_next_baj(w_surr, baj, cur_pos), 1);
		if (ft_isset(w_surr[y + 1][x], "T+") && w_surr[y][x - 1] == '-')
			return (cur_pos->x -= 1, get_next_baj(w_surr, baj, cur_pos), 1);
		if (ft_isset(w_surr[y][x + 1], "O+") && w_surr[y + 1][x] == '-')
			return (cur_pos->y += 1, get_next_baj(w_surr, baj, cur_pos), 1);
	}
	return (0);
}

int	check_letter(char **w_surr, t_iposition *cur_pos, t_bajeanno *baj)
{
	size_t	x;
	size_t	y;

	x = cur_pos->x;
	y = cur_pos->y;
	if (w_surr[y][x] == 'X' && w_surr[y][x + 1] != '1')
		return (cur_pos->x += 1, get_next_baj(w_surr, baj, cur_pos), 1);
	if (w_surr[y][x] == 'V' && w_surr[y + 1][x] != '1')
		return (cur_pos->y += 1, get_next_baj(w_surr, baj, cur_pos), 1);
	if (w_surr[y][x] == 'O' && w_surr[y][x - 1] != '1')
		return (cur_pos->x -= 1, get_next_baj(w_surr, baj, cur_pos), 1);
	if (w_surr[y][x] == 'T' && w_surr[y - 1][x] != '1')
		return (cur_pos->y -= 1, get_next_baj(w_surr, baj, cur_pos), 1);
	return (0);
}

t_iposition	get_next_baj(char **w_surr, t_bajeanno *next_one,
							t_iposition *cur_pos)
{
	size_t	save_start;
	size_t	i;

	clear_line(w_surr, cur_pos);
	if (check_empty(w_surr, cur_pos, next_one))
		return (*cur_pos);
	save_start = get_ind_start(cur_pos, w_surr);
	i = save_start;
	while (i != 4)
	{
		if (paint_w_surr(i, next_one, cur_pos, w_surr))
			return (*cur_pos);
		if (++i > 3)
			i = 0;
		if (i == save_start)
			break ;
	}
	if (check_letter(w_surr, cur_pos, next_one))
		return (*cur_pos);
	return (get_next_baj(w_surr, next_one, cur_pos));
}

int	get_wall_surroundment(t_data *data)
{
	t_position	player_pos;
	size_t		i;
	size_t		j;

	data->wall_sur = tab_dup_empty(data->map);
	player_pos = get_position(data->map);
	data->baj = ft_calloc(1, sizeof(t_bajeanno));
	if (data->baj)
		data->baj->cur_pos = ft_calloc(1, sizeof(t_iposition));
	if (!data->wall_sur || !data->baj || !data->baj->cur_pos)
		return (ft_putstr_fd(ERR ALLOC_ERR EOL, 2), 0);
	fill_wall_surr_map(data->map, data->wall_sur, (int)player_pos.x,
		(int)player_pos.y);
	data->baj->speed = 2000;
	i = 0;
	while (data->wall_sur[i++])
	{
		j = 0;
		while (data->wall_sur[i - 1][j])
			if (data->wall_sur[i - 1][j++] == '-')
				return (data->baj->cur_pos->x = (int)j - 1, \
		data->baj->cur_pos->y = (int)i - 1, data->baj->orientation = '/', 1);
	}
	return (1);
}
