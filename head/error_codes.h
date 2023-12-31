/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 07:58:32 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/19 15:25:11 by nfaust           ###   ########.fr       */
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
# define TXTR_LOAD		"Failed to load one or several textures"
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
# define WRONG_COL_ASS	"Wrong color assignation format! (expected \
0-255,0-255,0-255)"
# define UNEXP_LINE		"Unexpected character(s) in line: "
# define MAP_E			"Could not load map"
# define EMPTY_FILE 	"Empty data"
# define EMPTY_LINE_M	"Empty line(s) in map"
# define OR				" or "
# define ALLOC_ERR 		"Allocation error occured"
# define EOL			"\n"

#endif