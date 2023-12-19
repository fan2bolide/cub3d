/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 07:54:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/19 15:45:24 by nfaust           ###   ########.fr       */
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

void	destroy_file(t_list *file)
{
	t_list	*end_of_mdata;
	t_list	*curr;

	curr = file;
	end_of_mdata = skip_metadata_in_file(curr);
	while (curr && curr->content && curr != end_of_mdata)
	{
		free(curr->content);
		curr = curr->next;
	}
	while (curr && curr->content && ((char *)curr->content)[0])
		curr = curr->next;
	while (curr && curr->content)
	{
		free(curr->content);
		curr = curr->next;
	}
	ft_lstclear_mais_pas_trop(&file);
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
		return (ft_lstclear(&file, free), NULL);
	if (refactor_spaces(file) || is_empty(file) || get_colors(data, file))
		return (ft_lstclear(&file, free), destroy_data(data), NULL);
	if (parse_textures(data, file))
		return (ft_lstclear(&file, free), NULL);
	if (!(data->ceiling_color && data->floor_color))
		return (ft_putstr_fd(ERR MISS_COL EOL, 2), ft_lstclear(&file, free), \
		destroy_data(data), NULL);
	data->map = get_map_from_file(file);
	if (!data->map)
		return (ft_lstclear(&file, free), destroy_data(data), NULL);
	if (parse_map(data->map))
		return (destroy_file(file), destroy_data(data), NULL);
	destroy_file(file);
	return (data);
}
