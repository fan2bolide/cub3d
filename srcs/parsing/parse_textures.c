/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:57:08 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/25 17:23:35 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_texture_path(char **texture_ptr, char *err_code, char *content)
{
	if (!(*texture_ptr))
		*texture_ptr = ft_substr(content, 3, ft_strlen(content) - 3);
	else
		return (ft_putstr_fd(err_code, 2), 1);
	return (0);
}

static int	get_textures_paths(t_data *data, t_list *file)
{
	if (!ft_strncmp(file->content, "NO ", 3))
		return (get_texture_path(&data->n_texture,
								 ERR MULT_DEF NO_TXTR, file->content));
	if (!ft_strncmp(file->content, "SO ", 3))
		return (get_texture_path(&data->s_texture,
								 ERR MULT_DEF SO_TXTR, file->content));
	if (!ft_strncmp(file->content, "WE ", 3))
		return (get_texture_path(&data->w_texture,
								 ERR MULT_DEF WE_TXTR, file->content));
	if (!ft_strncmp(file->content, "EA ", 3))
		return (get_texture_path(&data->e_texture,
								 ERR MULT_DEF EA_TXTR, file->content));
	return (0);
}

int	check_definition(t_data *data)
{
	if (!data->s_texture || !data->s_texture[0])
		return (ft_putstr_fd(ERR NO_DEF SO_TXTR, 2), 1);
	if (!data->n_texture || !data->n_texture[0])
		return (ft_putstr_fd(ERR NO_DEF NO_TXTR, 2), 1);
	if (!data->e_texture || !data->e_texture[0])
		return (ft_putstr_fd(ERR NO_DEF EA_TXTR, 2), 1);
	if (!data->w_texture || !data->w_texture[0])
		return (ft_putstr_fd(ERR NO_DEF WE_TXTR, 2), 1);
	return (0);
}

int check_assignation(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->s_texture[i])
		if (ft_isspace(data->s_texture[i++]))
			return (ft_putstr_fd(ERR AMB_ASS SO_TXTR, 2), 1);
	i = 0;
	while (data->n_texture[i])
		if (ft_isspace(data->n_texture[i++]))
			return (ft_putstr_fd(ERR AMB_ASS NO_TXTR, 2), 1);
	i = 0;
	while (data->w_texture[i])
		if (ft_isspace(data->w_texture[i++]))
			return (ft_putstr_fd(ERR AMB_ASS WE_TXTR, 2), 1);
	i = 0;
	while (data->e_texture[i])
		if (ft_isspace(data->e_texture[i++]))
			return (ft_putstr_fd(ERR AMB_ASS EA_TXTR, 2), 1);
	return (0);
}

int	check_format(t_data *data)
{
	if (ft_strncmp(data->s_texture + ft_strlen(data->s_texture) - 4, ".xpm", 5))
		return (ft_putstr_fd(ERR WRONG_FORMAT SO_TXTR, 2), 1);
	if (ft_strncmp(data->n_texture + ft_strlen(data->n_texture) - 4, ".xpm", 5))
		return (ft_putstr_fd(ERR WRONG_FORMAT NO_TXTR, 2), 1);
	if (ft_strncmp(data->w_texture + ft_strlen(data->w_texture) - 4, ".xpm", 5))
		return (ft_putstr_fd(ERR WRONG_FORMAT WE_TXTR, 2), 1);
	if (ft_strncmp(data->e_texture + ft_strlen(data->e_texture) - 4, ".xpm", 5))
		return (ft_putstr_fd(ERR WRONG_FORMAT EA_TXTR, 2), 1);
	return (0);
}

int	parse_textures(t_data *data, t_list *file)
{

	//! rajouter check d'apres map.
	while (file && file->content)
	{
		if (get_textures_paths(data, file))
			return (free_data(data), 1);
		file = file->next;
	}
	if (check_definition(data) || check_assignation(data) || check_file_path(data) || check_format(data))
		return (free_data(data), 1);
	return (0);
}
