#include "cub3D.h"

void	fdf_pixel_put(t_cub *cub, int x, int y, int color);
static void	fdf_put_line(t_cub *cub, t_position a, t_position b, int color);

void put_wall(t_cub *cub, int i, int j, int scale)
{
	int 			pixel_x;
	int 			pixel_y;
	int 			savej;
	int	color;

	pixel_y = 0;
	if (j % 2) {
		if (i % 2) {
			color = 0x0000FF00;
		} else {
			color = 0x000000FF;
		}
	} else {
		if (i % 2) {
			color = 0x000000FF;
		} else {
			color = 0x0000FF00;
		}
	}
	i *= scale;
	j *= scale;
	savej = j;
	while (pixel_y < scale)
	{
		pixel_x = 0;
		j = savej;
		while (pixel_x < scale)
		{
			fdf_pixel_put(cub, j, i, color);
			pixel_x++;
			j++;
		}
		pixel_y++;
		i++;
	}
}

void render_minimap(t_cub *cub, t_position ray_collision[cub->win_size[1]], double angle[cub->win_size[1]], int wall_height[cub->win_size[1]])
{
	int			i;
	int			j;
	int			scale;
	t_position	player_dupl;
	t_position	ray_dupl;
	int			color_x;
	int			color_y;
	int			color;

	i = 0;
	mlx_destroy_image(cub->mlx, cub->img.img);
	cub->img.img = mlx_new_image(cub->mlx, cub->win_size[1], cub->win_size[0]);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, &cub->img.line_length, &cub->img.endian);
	while (i < cub->win_size[1])
	{
		color_y = (int)ray_collision[i].y - (ray_collision[i].y == (int)ray_collision[i].y && sin(angle[i]) < 0);
		color_x = (int)ray_collision[i].x - (ray_collision[i].x == (int)ray_collision[i].x && cos(angle[i]) < 0);
		if (color_y % 2) {
			if (color_x % 2) {
				color = 0x0000FF00;
			} else {
				color = 0x000000FF;
			}
		} else {
			if (color_x % 2) {
				color = 0x000000FF;
			} else {
				color = 0x0000FF00;
			}
		}
		j = 0;
		while (j < (cub->win_size[0] - wall_height[i]) / 2)
		{
			j++;
		}
		while (j < (cub->win_size[0] - wall_height[i]) / 2 + wall_height[i])
		{
			fdf_pixel_put(cub, i, j, color);
			j++;
		}
		while (j < cub->win_size[0])
			j++;
		i++;
	}
	scale = 10;
	i = 0;
	while (cub->data->map[i])
	{
		j = 0;
		while (cub->data->map[i][j])
		{
			if (cub->data->map[i][j] == '1')
				put_wall(cub, i, j, scale);
			j++;
		}
		i++;
	}
	player_dupl.x = cub->player_position->x * scale;
	player_dupl.y = cub->player_position->y * scale;
	i = 0;
	while (i < cub->win_size[1])
	{
		ray_dupl.x = ray_collision[i].x * scale;
		ray_dupl.y = ray_collision[i].y * scale;
		fdf_put_line(cub, player_dupl, ray_dupl, 0xFF0000);
		i++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}

void	fdf_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (y >= cub->win_size[0] || x >= cub->win_size[1] || x <= 0 || y <= 0)
		return ;
	dst = cub->img.addr + (y * cub->img.line_length + x * (cub->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	fdf_put_line(t_cub *cub, t_position a, t_position b, int color)
{
	int		i;
	int		steps;
	double	x;
	double	y;

	steps = ft_max(fabs(b.x - a.x), fabs(b.y - a.y));
	x = a.x;
	y = a.y;
	i = 0;
	while (i <= steps)
	{
		if (round(x) >= 0 && round(x) < cub->win_size[1] && round(y) >= 0
			&& round(y) < cub->win_size[0])
			fdf_pixel_put(cub, (int)round(x), (int)round(y), color);
		x += (b.x - a.x) / (double)steps;
		y += (b.y - a.y) / (double)steps;
		i++;
	}
}