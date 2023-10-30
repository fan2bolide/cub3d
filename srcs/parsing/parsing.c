/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:38:22 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/28 15:19:03 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_data	*parsing(int argc, char **argv)
{
	t_file	*data;

	if (argc != 2)
		return (ft_putstr_fd(ERR WRONG_ARG_N EOL, 2), NULL);
	data = get_data(argv);
	if (!data)
		return (NULL);
	return (data);
}
