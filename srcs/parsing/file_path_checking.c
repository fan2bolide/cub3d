/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_path_checking.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:05:52 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/04 12:02:49 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("%s %i\n", path, fd);
		ft_putstr_fd(ERR, 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, ": ", 2);
		ft_putstr_fd(path, 2);
		write(2, "\n", 1);
		return (0);
	}
	close(fd);
	return (1);
}

int	is_directory(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		ft_putstr_fd(ERR IS_DIR, 2);
		ft_putstr_fd(path, 2);
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

int	check_file_path(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (is_directory(data->texture[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (!file_exists(data->texture[i]))
			return (1);
		i++;
	}
	return (0);
}
