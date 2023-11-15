/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:57:08 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/04 11:59:44 by nfaust           ###   ########.fr       */
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
	static char	id[4][4] = {"NO ", "SO ", "WE ", "EA "};
	static char	msg[4][100] = {ERR MULT_DEF NO_TXTR EOL, ERR MULT_DEF SO_TXTR EOL, ERR MULT_DEF WE_TXTR EOL , ERR MULT_DEF EA_TXTR EOL};
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(file->content, id[i], 3))
			return (get_texture_path(&data->texture[i], msg[i], file->content));
		i++;
	}
	if (!ft_strisset(file->content, "10NESWOA ") && ((char *)(file->content))[0]
		&& ft_strncmp(file->content, "F ", 2) && ft_strncmp(file->content, "C "
															, 2))
	{
		return (ft_putstr_fd(ERR UNEXP_LINE, 2), ft_putstr_fd(file->content, 2),
			ft_putstr_fd(EOL, 2), 1);
	}
	return (0);
}

int	parse_textures(t_data *data, t_list *file)
{
	t_list	*end_of_metadata;

	end_of_metadata = skip_metadata_in_file(file);
	while (file && file->content && file != end_of_metadata)
	{
		if (get_textures_paths(data, file))
			return (destroy_data(data), 1);
		file = file->next;
	}
	if (check_definition(data) || check_assignation(data)
		|| check_file_path(data) || check_format(data))
		return (destroy_data(data), 1);
	return (0);
}
