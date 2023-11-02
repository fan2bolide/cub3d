/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:11:11 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/30 15:14:15 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

char	*replace_extra_spaces(char *content)
{
	size_t	i;
	size_t	j;
	size_t	counter;
	char	*new_content;

	i = 0;
	counter = 0;
	while (content[i++])
		if (!ft_isspace(content[i - 1])
			|| (content[i] && !ft_isspace(content[i])))
			counter++;
	new_content = malloc(sizeof(char) * counter + 1);
	if (!new_content)
		return (free(content), NULL);
	i = 0;
	j = 0;
	while (j < counter && content[i])
	{
		while (ft_isspace(content[i]))
			i++;
		if (i > 0 && ft_isspace(content[i - 1]))
			new_content[j++] = ' ';
		new_content[j++] = content[i++];
	}
	return (new_content[j] = 0, free(content), new_content);
}

int	refactor_spaces(t_list *file)
{
	char	*new_content;

	while (file && file->content)
	{
		if (!ft_strisset(file->content, "10NSEW \n") \
			|| ft_strisset(file->content, " \n"))
		{
			new_content = ft_strtrim(file->content, " \n");
			if (!new_content)
				return (1);
			new_content = replace_extra_spaces(new_content);
			if (!new_content)
				return (1);
		}
		else
			new_content = ft_strtrim(file->content, "\n");
		free(file->content);
		file->content = new_content;
		file = file->next;
	}
	return (0);
}
