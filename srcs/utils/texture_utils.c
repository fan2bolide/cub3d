/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:11:52 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/30 15:13:14 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_definition(t_data *data)
{
	if (!data->s_texture || !data->s_texture[0])
		return (ft_putstr_fd(ERR NO_DEF SO_TXTR EOL, 2), 1);
	if (!data->n_texture || !data->n_texture[0])
		return (ft_putstr_fd(ERR NO_DEF NO_TXTR EOL, 2), 1);
	if (!data->e_texture || !data->e_texture[0])
		return (ft_putstr_fd(ERR NO_DEF EA_TXTR EOL, 2), 1);
	if (!data->w_texture || !data->w_texture[0])
		return (ft_putstr_fd(ERR NO_DEF WE_TXTR EOL, 2), 1);
	return (0);
}

int	check_assignation(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->s_texture[i])
		if (ft_isspace(data->s_texture[i++]))
			return (ft_putstr_fd(ERR AMB_ASS SO_TXTR EOL, 2), 1);
	i = 0;
	while (data->n_texture[i])
		if (ft_isspace(data->n_texture[i++]))
			return (ft_putstr_fd(ERR AMB_ASS NO_TXTR EOL, 2), 1);
	i = 0;
	while (data->w_texture[i])
		if (ft_isspace(data->w_texture[i++]))
			return (ft_putstr_fd(ERR AMB_ASS WE_TXTR EOL, 2), 1);
	i = 0;
	while (data->e_texture[i])
		if (ft_isspace(data->e_texture[i++]))
			return (ft_putstr_fd(ERR AMB_ASS EA_TXTR EOL, 2), 1);
	return (0);
}

int	check_format(t_data *data)
{
	if (ft_strncmp(data->s_texture + ft_strlen(data->s_texture) - 4, ".xpm", 5))
		return (ft_putstr_fd(ERR WRONG_FORMAT SO_TXTR EXP_XPM EOL, 2), 1);
	if (ft_strncmp(data->n_texture + ft_strlen(data->n_texture) - 4, ".xpm", 5))
		return (ft_putstr_fd(ERR WRONG_FORMAT NO_TXTR EXP_XPM EOL, 2), 1);
	if (ft_strncmp(data->w_texture + ft_strlen(data->w_texture) - 4, ".xpm", 5))
		return (ft_putstr_fd(ERR WRONG_FORMAT WE_TXTR EXP_XPM EOL, 2), 1);
	if (ft_strncmp(data->e_texture + ft_strlen(data->e_texture) - 4, ".xpm", 5))
		return (ft_putstr_fd(ERR WRONG_FORMAT EA_TXTR EXP_XPM EOL, 2), 1);
	return (0);
}
