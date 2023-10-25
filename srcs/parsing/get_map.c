/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 07:54:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/25 17:06:41 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_list	*list_from_file(char *input_path)
{
	t_list	*list;
	t_list	*curr;
	int		input_fd;
	char	*line;

	input_fd = open(input_path, O_RDONLY);
	if (input_fd == -1)
		return (ft_putstr_fd(ERR, 2), perror(input_path), NULL);
	line = get_next_line(input_fd);
	if (!line)
		return (ft_putstr_fd(EMPTY_FILE, 2), NULL);
	list = ft_lstnew(line);
	curr = list;
	while (line)
	{
		line = get_next_line(input_fd);
		curr->next = ft_lstnew(line);
		if (!curr->next)
			return (ft_lstclear(&list, free), ft_putstr_fd(ALLOC_ERR, 2), NULL);
		curr = curr->next;
	}
	return (list);
}

size_t	get_size(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static int	get_colors(t_data *data, t_list *file)
{
	char	**colors;

	if (!ft_strncmp(file->content, "F ", 2))
	{
		if (!data->floor_color)
		{
			data->floor_color = ft_calloc(1, sizeof(t_color));
			colors = ft_split(file->content + 2, ',');
			if (!colors)
				return (-1);
			if (get_size(colors) != 3)
				return (ft_split_destroy(colors), 1);
			data->floor_color->red = ft_atoi(colors[0]);
			data->floor_color->green = ft_atoi(colors[1]);
			data->floor_color->blue = ft_atoi(colors[2]);
			ft_split_destroy(colors);
		}
		else
			return (ft_putstr_fd(ERR MULT_DEF FL_CLR, 2), 1);
	}
	if (!ft_strncmp(file->content, "C ", 2))
	{
		if (!data->ceiling_color)
		{
			data->ceiling_color = ft_calloc(1, sizeof(t_color));
			colors = ft_split(file->content + 2, ',');
			if (!colors)
				return (-1);
			if (get_size(colors) != 3)
				return (ft_split_destroy(colors), 1);
			data->ceiling_color->red = ft_atoi(colors[0]);
			data->ceiling_color->green = ft_atoi(colors[1]);
			data->ceiling_color->blue = ft_atoi(colors[2]);
			ft_split_destroy(colors);
		}
		else
			return (ft_putstr_fd(ERR MULT_DEF CL_CLR, 2), 1);
	}
	return (0);
}

t_data	*get_data(char **argv)
{
	t_list	*file;
	t_list	*curr;
	t_data	*data;

	file = list_from_file(argv[1]);//todo secure
	data = ft_calloc(1, sizeof(t_data));
	refactor_spaces(file);
	curr = file;
	if (parse_textures(data, curr))
		return (ft_lstclear(&file, free), NULL);
	while (curr && curr->content)
	{
		if (get_colors(data, curr))
			return (free(data->ceiling_color), free(data->floor_color), free(data), ft_lstclear(&file, free), NULL);
		curr = curr->next;
	}
	return (ft_lstclear(&file, free), data);
}
