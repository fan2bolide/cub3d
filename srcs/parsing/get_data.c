/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 07:54:49 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/30 14:36:56 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
