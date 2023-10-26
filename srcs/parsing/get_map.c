/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 07:54:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/26 11:09:58 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char **get_map_from_file(t_list *file);

bool is_all_metadata_set(t_data *data);

void print_map(char **map);

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

bool are_all_colors_set(t_data *data) {
	return (data->ceiling_color && data->floor_color);
}

t_data	*get_data(char **argv)
{
	t_list	*file;
	t_list	*end_of_mdata;
	t_list	*curr;
	t_data	*data;

	file = list_from_file(argv[1]);
	if (!file)
		return (NULL);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (free(file), NULL);
	refactor_spaces(file);
	curr = file;
	end_of_mdata = skip_metadata_in_file(file);
	if (parse_textures(data, curr))
		return (ft_lstclear(&file, free), NULL);
	while (curr && curr->content && curr != end_of_mdata)
	{
		if (get_colors(data, curr))
			return (free_data(data), ft_lstclear(&file, free), NULL);
		curr = curr->next;
	}
	if (!are_all_colors_set(data))
		return (ft_putstr_fd(ERR MISS_COL EOL, 2), free_data(data), ft_lstclear(&file, free), NULL); //todo change that shit
	data->map = get_map_from_file(file);
	if (!data->map)
		return (perror("ma grosse bite"), NULL); //todo change that shit
	print_map(data->map);
	return (ft_lstclear(&file, free), data);
}

void print_map(char **map) {
	int i = 0;

	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

char **get_map_from_file(t_list *file)
{
	int i;
	char **map;
	t_list *curr;

	i = 0;
	file = skip_metadata_in_file(file);
	if (!file)
		return (NULL);
	curr = file;
	while (curr && curr->content)
	{
		curr = curr->next;
		i++;
	}
	map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (file && file->content && ft_strcmp(file->content, "\n"))
	{
		map[i] = file->content;
		file = file->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

t_list *skip_metadata_in_file(t_list *file)
{
	t_list *curr;

	curr = file;
	while (curr && curr->content)
	{
		if (ft_strchr(curr->content, '1') && !ft_strchr(curr->content, 'C') && !ft_strchr(curr->content, 'F'))//todo improve that
			return (curr);
		curr = curr->next;
	}
	return (curr);
}
