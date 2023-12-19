/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_from_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:17:38 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/19 14:52:23 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_eof(t_list *file)
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

static size_t	get_count(char *prev, char *curr, t_list *next)
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

static int	refactor_file(t_list *prev)
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

static char	**create_map(t_list *curr)
{
	char	**map;
	int		i;

	i = 0;
	while (curr && curr->content && ((char *)curr->content)[0] && ++i)
		curr = curr->next;
	map = malloc(sizeof(char *) * (i + 1));
	if (!map)
		return (NULL);
	ft_bzero(map, i + 1);
	return (map);
}

char	**get_map_from_file(t_list *file)
{
	int		i;
	char	**map;
	t_list	*curr;

	if (refactor_file(file))
		return (NULL);
	curr = skip_metadata_in_file(file);
	if (!curr->content)
		return (ft_putstr_fd(ERR NO_MAP EOL, 2), NULL);
	map = create_map(curr);
	if (!map)
		return (ft_putstr_fd(ERR ALLOC_ERR EOL, 2), NULL);
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
