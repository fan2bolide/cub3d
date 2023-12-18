/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:02:17 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/30 15:22:51 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	compute_color(t_color *final_color, t_color new_color,
			t_color old_color_rgb)
{
	final_color->red = (new_color.red * new_color.transparency
			+ old_color_rgb.red * (255 - new_color.transparency)) / 255;
	final_color->green = (new_color.green * new_color.transparency
			+ old_color_rgb.green * (255 - new_color.transparency)) / 255;
	final_color->blue = (new_color.blue * new_color.transparency
			+ old_color_rgb.blue * (255 - new_color.transparency)) / 255;
}

void	put_pixel_transparent(t_image *data, int x, int y, unsigned int color)
{
	int		old_color;
	t_color	old_color_rgb;
	t_color	new_color;
	t_color	final_color;
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	old_color = *(int *) dst;
	old_color_rgb.blue = old_color & 0xFF;
	old_color_rgb.green = (old_color >> 8) & 0xFF;
	old_color_rgb.red = (old_color >> 16) & 0xFF;
	new_color.blue = color & 0xFF;
	new_color.green = (color >> 8) & 0xFF;
	new_color.red = (color >> 16) & 0xFF;
	new_color.transparency = (color >> 24) & 0xFF;
	compute_color(&final_color, new_color, old_color_rgb);
	cub_pixel_put(data, x, y, *(int *)(&final_color));
}

size_t	get_size(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
