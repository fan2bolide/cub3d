/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 07:58:32 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/30 21:34:30 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CODES_H
# define ERROR_CODES_H

# define ERR			"Error\n"
# define WRONG_ARG_N 	"Wrong number of parameters (expected one)"
# define WRONG_P_N		"Wrong number of player on map (expected one)"
# define E_WALL_SUR		"Map is not surrounded by walls"
# define MULT_DEF		"Multiple definition of: "
# define AMB_ASS		"Ambiguous assignation for: "
# define ILL_CHAR		"Illegal char in map"
# define WRONG_FORMAT	"Wrong format for: "
# define EXP_CUB		" (expected .cub)"
# define EXP_XPM		" (expected .xpm)"
# define NO_DEF			"No before map definition of: "
# define NO_TXTR		"'North texture'"
# define SO_TXTR		"'South texture'"
# define EA_TXTR		"'East texture'"
# define WE_TXTR		"'West texture'"
# define FL_CLR			"'Floor color'"
# define CL_CLR			"'Ceiling color'"
# define NO_FILE		"No such data or directory: "
# define NO_MAP			"No map in data."
# define IS_DIR			"Is a directory: "
# define MISS_COL		"Missings one or several colors in source data\
before map."
# define WRONG_COL_ASS	"Wrong color assignation format! expected\
(0-255,0-255,0-255)"
# define UNEXP_LINE		"Unexpected character(s) in line: "
# define MAP_E			"Could not load map"
# define EMPTY_FILE 	"Empty data"
# define EMPTY_LINE_M	"Empty line(s) in map"
# define OR				" or "
# define ALLOC_ERR 		"Allocation error occured"
# define EOL			"\n"
# define MINUS_KEY 		6
# define PLUS_KEY		7
# define UP_KEY 		126
# define DOWN_KEY 		125

# define ESC_KEY 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

//# define KEY_LEFT		123
//# define KEY_RIGHT		124
//# define ESC_KEY 		53
# define KEY_W 			13
# define KEY_A 			0
# define KEY_S 			1
# define KEY_D 			2
# define DEFLT_WIN_SIZE 1080
# define USAGE			"cub3D: usage: ./cub3D ./path_to_map.cub [-s window_height]"

#endif