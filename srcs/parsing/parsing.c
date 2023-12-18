/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:38:22 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/18 10:41:53 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_data	*parsing(int argc, char **argv)
{
	t_data	*data;

	data = get_data(argv);
	(void)argc;
	if (!data)
		return (destroy_data(data), NULL);
	return (data);
}
