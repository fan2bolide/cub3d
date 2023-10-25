/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 07:58:32 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/25 17:04:11 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CODES_H
# define ERROR_CODES_H

# define ERR			"Error\n"
# define WRONG_ARG_N 	"Wrong number of parameters (expected one)\n"
# define MULT_DEF		"Multiple definition of: "
# define AMB_ASS		"Ambiguous assignation for: "
# define NO_DEF			"No definition of: "
# define NO_TXTR		"'North texture'\n"
# define SO_TXTR		"'South texture'\n"
# define EA_TXTR		"'East texture'\n"
# define WE_TXTR		"'West texture'\n"
# define FL_CLR			"'Floor color'\n"
# define CL_CLR			"'Ceiling color'\n"
# define NO_FILE		"no such file or directory: "
# define IS_DIR			"is a directory: "
# define ESC_KEY 53
# define MINUS_KEY 6
# define PLUS_KEY 7
# define UP_KEY 126
# define DOWN_KEY 125
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define DEFAULT_WIN_SIZE 1080
# define ALLOC_ERR "allocation error occured, aborting\n"
# define WRONG_MAP "wrong map format, aborting\n"
# define USAGE "fdf usage: ./fdf <map_path> [-s <win_size>]\n"
# define EMPTY_FILE "empty file\n"

#endif