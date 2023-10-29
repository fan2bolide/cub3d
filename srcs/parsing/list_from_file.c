/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 22:26:10 by bajeanno          #+#    #+#             */
/*   Updated: 2023/10/29 22:27:26 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static int	open_file_rd(char *file_path)
{
	int	fd;

	if (check_file_format(file_path) || is_directory(file_path))
		return (-1);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd(ERR, 2), perror(file_path), -1);
	return (fd);
}

static t_list	*create_first_node(int fd, char *str)
{
	t_list	*node;

	if (!str && errno == ENOMEM)
		return (close(fd), ft_putstr_fd(ERR ALLOC_ERR EOL, 2), NULL);
	if (!str)
		return (close(fd), ft_putstr_fd(ERR EMPTY_FILE EOL, 2), NULL);
	node = ft_lstnew(str);
	if (!node)
		return (close(fd), ft_putstr_fd(ERR ALLOC_ERR EOL, 2), NULL);
	return (node);
}

t_list	*list_from_file(char *file_path)
{
	t_list	*list;
	t_list	*curr;
	int		fd;
	char	*line;

	fd = open_file_rd(file_path);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	list = create_first_node(fd, line);
	if (!list)
		return (NULL);
	curr = list;
	while (line)
	{
		line = get_next_line(fd);
		curr->next = ft_lstnew(line);
		if (!curr->next || (!line && errno == ENOMEM))
			return (close(fd), ft_lstclear(&list, free), \
					ft_putstr_fd(ERR ALLOC_ERR, 2), NULL);
		curr = curr->next;
	}
	return (close(fd), list);
}
