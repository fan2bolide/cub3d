/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 07:54:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/28 17:40:38 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**get_map_from_file(t_list *file);

bool	is_all_metadata_set(t_data *data);

void	print_map(char **map);

static int	check_file_format(char *path)
{
	if (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 5))
	{
		ft_putstr_fd(ERR WRONG_FORMAT, 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(EXP_CUB EOL, 2);
		return (1);
	}
	return (0);
}


//todo norm
static t_list	*list_from_file(char *input_path)
{
	t_list	*list;
	t_list	*curr;
	int		input_fd;
	char	*line;

	if (check_file_format(input_path) || is_directory(input_path))
		return (NULL);
	input_fd = open(input_path, O_RDONLY);
	if (input_fd == -1)
		return (ft_putstr_fd(ERR, 2), perror(input_path), NULL);
	line = get_next_line(input_fd);
	if (!line && errno == ENOMEM)
		return (close(input_fd), ft_putstr_fd(ERR ALLOC_ERR EOL, 2), NULL);
	if (!line)
		return (close(input_fd), ft_putstr_fd(ERR EMPTY_FILE EOL, 2), NULL);
	list = ft_lstnew(line);
	if (!list)
		return (close(input_fd), ft_putstr_fd(ERR ALLOC_ERR EOL, 2), NULL);
	curr = list;
	while (line)
	{
		line = get_next_line(input_fd);
		curr->next = ft_lstnew(line);
		if (!curr->next || (!line && errno == ENOMEM))
			return (close(input_fd), ft_lstclear(&list, free), ft_putstr_fd(ERR ALLOC_ERR, 2), NULL);
		curr = curr->next;
	}
	return (close(input_fd), list);
}

size_t	get_size(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_color_overflow(t_color *f_c_color, char **colors)
{
	int	checker;

	checker = ft_atoi(colors[0]);
	if (checker < 0 || checker > 255)
		return (ft_split_destroy(colors), \
				ft_putstr_fd(ERR WRONG_COL_ASS EOL, 2), 0);
	f_c_color->red = checker;
	checker = ft_atoi(colors[1]);
	if (checker < 0 || checker > 255)
		return (ft_split_destroy(colors), \
				ft_putstr_fd(ERR WRONG_COL_ASS EOL, 2), 0);
	f_c_color->green = checker;
	checker = ft_atoi(colors[2]);
	if (checker < 0 || checker > 255)
		return (ft_split_destroy(colors), \
				ft_putstr_fd(ERR WRONG_COL_ASS EOL, 2), 0);
	f_c_color->blue = checker;
	return (1);
}

int	fill_color_struct(t_color **f_c_color, char *line)
{
	char	**colors;

	*f_c_color = ft_calloc(1, sizeof(t_color));
	if (!(*f_c_color))
		return (ft_putstr_fd(ERR ALLOC_ERR EOL, 2), 0);
	colors = ft_split(line + 2, ',');
	if (!colors)
		return (ft_putstr_fd(ERR ALLOC_ERR EOL, 2), 0);
	if (get_size(colors) != 3)
		return (ft_split_destroy(colors), \
				ft_putstr_fd(ERR WRONG_COL_ASS EOL, 2), 0);
	if (!check_color_overflow(*f_c_color, colors))
		return (0);
	ft_split_destroy(colors);
	return (1);
}

static int	get_colors(t_data *data, t_list *file)
{
	if (!ft_strncmp(file->content, "F ", 2))
	{
		if (!data->floor_color)
		{
			if (!fill_color_struct(&(data->floor_color), file->content))
				return (1);
		}
		else
			return (ft_putstr_fd(ERR MULT_DEF FL_CLR EOL, 2), 1);
	}
	if (!ft_strncmp(file->content, "C ", 2))
	{
		if (!data->ceiling_color)
		{
			if (!fill_color_struct(&(data->ceiling_color), file->content))
				return (1);
		}
		else
			return (ft_putstr_fd(ERR MULT_DEF CL_CLR EOL, 2), 1);
	}
	return (0);
}

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

int	check_for_unexpected_char(t_list *line)
{
	char	*content;
	size_t	i;

	content = (char *)line->content;
	if (!ft_strncmp(content, "F ", 2) || !ft_strncmp(content, "C ", 2))
	{
		i = 2;
		while (content[i])
		{
			if (!ft_strchr("0123456789-, ", content[i]))
			{
				ft_putstr_fd(ERR UNEXP_LINE, 2);
				ft_putstr_fd("'", 2);
				ft_putstr_fd(content, 2);
				ft_putstr_fd("'.\n", 2);
				return (1);
			}
			i++;
		}
	}
	return (0);
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
	if (is_empty(file))
		return (destroy_data(data), ft_lstclear(&file, free), NULL);
	curr = file;
	end_of_mdata = skip_metadata_in_file(file);
	if (!end_of_mdata)
		return (destroy_data(data), ft_lstclear(&file, free), NULL);
	while (curr && curr->content && curr != end_of_mdata)
	{
		if (check_for_unexpected_char(curr) || get_colors(data, curr))
			return (destroy_data(data), ft_lstclear(&file, free), NULL);
		curr = curr->next;
	}
	if (parse_textures(data, file))
		return (ft_lstclear(&file, free), NULL);
	if (!(data->ceiling_color && data->floor_color))
		return (ft_putstr_fd(ERR MISS_COL EOL, 2), destroy_data(data), ft_lstclear(&file, free), NULL);
	data->map = get_map_from_file(file);
	if (!data->map || parse_map(data->map))
		return (destroy_data(data), ft_lstclear(&file, free), NULL);
	return (ft_lstclear(&file, free), data);
}

int	check_eof(t_list *file)
{
	char	*content;
	size_t	i;

	while (file && file->content)
	{
		content = file->content;
		i = 0;
		while (content[i])
			if (content[i++] != ' ')
				return (ft_putstr_fd(ERR EMPTY_LINE_M EOL, 2), 1);
		file = file->next;
	}
	return (0);
}

size_t	get_count(char *prev, char *curr, t_list *next)
{
	size_t	prev_len;
	size_t	curr_len;
	size_t	next_len;

	if (!next || !next->content || !prev)
		return (0);
	prev_len = ft_strlen(prev);
	curr_len = ft_strlen(curr);
	next_len = ft_strlen(next->content);
	if (prev_len > curr_len && prev_len > next_len)
		return (prev_len);
	if (next_len > curr_len && next_len > prev_len)
		return (next_len);
	return (0);
}

int	refactor_file(t_list *prev)
{
	t_list	*curr;
	char	*save;
	size_t	count;

	curr = skip_metadata_in_file(prev);
	prev = curr;
	while (curr && curr->content)
	{
		count = get_count(prev->content, curr->content, curr->next);
		if (count)
		{
			save = curr->content;
			curr->content = ft_calloc_secure(count, sizeof(char));
			curr->content = ft_secure_strcpy(save, curr->content);
			free(save);
			if (!curr->content)
				return (ft_putstr_fd(ERR ALLOC_ERR EOL, 2), 1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

//todo norm
char	**get_map_from_file(t_list *file)
{
	int		i;
	char	**map;
	t_list	*curr;

	i = 0;
	if (refactor_file(file))
		return (NULL);
	file = skip_metadata_in_file(file);
	if (!file->content)
		return (ft_putstr_fd(ERR NO_MAP EOL, 2), NULL);
	curr = file;
	while (curr && curr->content && ((char *)curr->content)[0] && ++i)
		curr = curr->next;
	map = malloc(sizeof(char *) * (i + 1));
	// TODO secure map
	i = 0;
	curr = file;
	while (curr && curr->content && ((char *)curr->content)[0])
	{
		map[i++] = curr->content;
		curr = curr->next;
	}
	map[i] = NULL;
	if (check_for_illegal_char(file) || check_eof(curr))
		return (free(map), NULL);
	return (map);
}

t_list	*skip_metadata_in_file(t_list *file)
{
	t_list	*curr;
	char	*content;
	size_t	i;

	curr = file;
	i = 0;
	while (curr && curr->content && i < 6)
	{
		content = curr->content;
		if (content[0])
			i++;
		curr = curr->next;
	}
	while (curr && curr->content && !(((char *)curr->content)[0]))
		curr = curr->next;
	return (curr);
}
