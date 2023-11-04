/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:11:52 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/04 11:59:23 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_definition(t_data *data)
{
	static char	msg[4][100] = {ERR NO_DEF NO_TXTR EOL, ERR NO_DEF SO_TXTR EOL, ERR NO_DEF WE_TXTR EOL, ERR NO_DEF EA_TXTR EOL};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (!data->texture[i] || !data->texture[i][0])
			return (ft_putstr_fd(msg[i], 2), 1);
		i++;
	}
	return (0);
}

int	check_assignation(t_data *data)
{
	static char	msg[4][100] = {ERR AMB_ASS NO_TXTR EOL, ERR AMB_ASS SO_TXTR EOL, ERR AMB_ASS WE_TXTR EOL, ERR AMB_ASS EA_TXTR EOL};
	int		i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (data->texture[i][j])
			if (ft_isspace(data->texture[i][j++]))
				return (ft_putstr_fd(msg[i], 2), 1);
		i++;
	}
	return (0);
}

int	check_format(t_data *data)
{
	static char	msg[4][100] = {ERR WRONG_FORMAT NO_TXTR EOL, ERR WRONG_FORMAT SO_TXTR EOL, ERR WRONG_FORMAT WE_TXTR EOL, ERR WRONG_FORMAT EA_TXTR EOL};
	int		i;

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(data->texture[i] + ft_strlen(data->texture[i]) - 4, ".xpm", 5))
			return (ft_putstr_fd(msg[i], 2), 1);
		i++;
	}
	return (0);
}
