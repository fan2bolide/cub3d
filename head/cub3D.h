/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:30:22 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/26 19:30:34 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//=================== INCLUDES =====================//
# include "error_codes.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"

//================== STUCTURES =====================//
typedef struct s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}		t_color;

typedef struct s_file
{
	char	**map;
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	t_color	*ceiling_color;
	t_color	*floor_color;
}		t_file;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_position
{
	double	x;
	double	y;
}			t_position;

typedef struct s_cub
{
	t_file	*file;
	void	*mlx;
	void	*win;
	int 	win_size[2];
	t_data img;
	t_position *player_position;
}		t_cub;


//==================== PARSING =====================//
int		parsing(int argc, char **argv);
int		parse_textures(t_file *data, t_list *file);
t_file	*get_data(char **argv);
t_list *skip_metadata_in_file(t_list *file);
int		check_file_path(t_file *data);

//===================== UTILS ======================//
void	free_data(t_file *data);
int		refactor_spaces(t_list *list);
void	ray_casting(t_cub *cub);


#endif