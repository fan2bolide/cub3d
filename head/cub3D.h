/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:30:22 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/25 09:07:31 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//================== STUCTURES =====================//
typedef struct s_color{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}		t_color;

typedef struct s_data{
	char	**map;
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	t_color	*ceiling_color;
	t_color	*floor_color;
}		t_data;


//=================== INCLUDES =====================//
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "error_codes.h"
# include "libft.h"

//==================== PARSING =====================//
int		parsing(int argc, char **argv);
t_data	*get_data(char **argv);
t_list *skip_metadata_in_file(t_list *file);

#endif