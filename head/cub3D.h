/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:30:22 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/31 16:25:41 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//=================== INCLUDES =====================//
# include "error_codes.h"
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include <errno.h>

//================== STUCTURES =====================//
typedef struct s_color{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
	unsigned char	transparency;
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

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

typedef struct s_position
{
	double	x;
	double	y;
}			t_position;

typedef struct s_cub
{
	t_data	*data;
	void	*mlx;
	void	*win;
	int 	win_size[2];
	t_image img;
	t_position *player_position;
	double	view_angle;
}		t_cub;


//==================== PARSING =====================//
t_data	*parsing(int argc, char **argv);
int		parse_textures(t_data *data, t_list *file);
t_data	*get_data(char **argv);
t_list	*skip_metadata_in_file(t_list *file);
int		check_file_path(t_data *data);
int		parse_map(char **map);
int		get_colors(t_data *data, t_list *file);
int		check_for_illegal_char(t_list *file);
char	**get_map_from_file(t_list *file);
t_list	*list_from_file(char *file_path);

//===================== UTILS ======================//
void	destroy_data(t_data *data);
int		refactor_spaces(t_list *list);
int		ray_casting(t_cub *cub);

void render_minimap(t_cub *cub, t_position ray_collision);

int		is_directory(char *path);
size_t	get_size(char **tab);
int		check_definition(t_data *data);
int		check_assignation(t_data *data);
int		check_format(t_data *data);

#endif