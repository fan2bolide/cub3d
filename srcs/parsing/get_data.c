/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 07:54:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/30 15:03:56 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_empty(t_list *file)
{
	while (file && file->content)
	{
		if (((char *)(file->content))[0])
			return (0);
		file = file->next;
	}
	return (ft_putstr_fd(ERR EMPTY_FILE EOL, 2), 1);
}

t_data	*get_data(char **argv)
{
	t_list	*file;
	t_data	*data;

	file = list_from_file(argv[1]);
	if (!file)
		return (NULL);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (free(file), NULL);
	refactor_spaces(file);
	if (is_empty(file) || get_colors(data, file))
		return (destroy_data(data), ft_lstclear(&file, free), NULL);
	if (parse_textures(data, file))
		return (ft_lstclear(&file, free), NULL);
	if (!(data->ceiling_color && data->floor_color))
		return (ft_putstr_fd(ERR MISS_COL EOL, 2), destroy_data(data), \
		ft_lstclear(&file, free), NULL);
	data->map = get_map_from_file(file);
	if (!data->map || parse_map(data->map))
		return (destroy_data(data), ft_lstclear(&file, free), NULL);
	return (ft_lstclear_mais_pas_trop(&file), data);
}
